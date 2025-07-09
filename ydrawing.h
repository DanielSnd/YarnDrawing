#pragma once

#include "core/object/ref_counted.h"
#include "scene/gui/control.h"
#include "scene/resources/texture.h"
#include "core/io/image.h"
#include "core/math/vector2.h"
#include "core/math/color.h"
#include "core/variant/array.h"
#include "core/variant/variant.h"
#include "core/input/input_event.h"
#include "core/math/math_funcs.h"
#include "core/math/geometry_2d.h"
#include "core/io/image_loader.h"
#include "scene/main/viewport.h"
#include "scene/main/canvas_layer.h"
#include "scene/main/scene_tree.h"
#include "scene/resources/image_texture.h"
#include "servers/rendering_server.h"

class YDrawing : public Control {
	GDCLASS(YDrawing, Control);

public:
	enum EventType {
		STROKE_START,
		STROKE_POINT,
		STROKE_END,
		ERASE_START,
		ERASE_POINT,
		ERASE_END,
		CLEAR_CANVAS
	};
	
	struct DrawingEvent {
		EventType type;
		float timestamp;
		Vector2 position;
		Color color;
		float size;
		
		DrawingEvent() : type(STROKE_START), timestamp(0.0f), position(Vector2()), color(Color()), size(0.0f) {}
		DrawingEvent(EventType t, float ts, const Vector2 &pos, const Color &col, float s) 
			: type(t), timestamp(ts), position(pos), color(col), size(s) {}
	};

private:
	// Canvas properties
	Vector2i canvas_size;
	Color background_color;
	bool smoothing_enabled;
	float smoothing_strength;
	bool recording_enabled;

	// Drawing state
	Ref<Image> canvas_image;
	Ref<Image> stroke_buffer;
	Ref<Image> canvas_state_before_stroke;
	Ref<ImageTexture> canvas_texture;
	bool is_drawing;
	bool is_erasing;
	
	// Smoothing system
	Vector<Vector2> smoothing_buffer;
	static const int MAX_SMOOTHING_POINTS = 100;
	
	// Event recording
	Vector<DrawingEvent> recorded_events;
	bool is_playback_active;
	float playback_speed;
	int playback_index;
	
	// Undo system
	Vector<PackedByteArray> snapshot_buffer;
	Vector<uint8_t> incremental_strokes;

	Vector2 last_stroke_point;
	Vector<int> undo_stack;
	Vector<int> redo_stack;
	int max_undo_steps;
	
	// Performance optimization
	Rect2i dirty_rect;
	bool needs_update;

	bool use_background_color = false;

	bool create_snapshots = true;
	void set_create_snapshots(bool p_create_snapshots) { create_snapshots = p_create_snapshots; }
	bool get_create_snapshots() const { return create_snapshots; }
	
	// Stroke rendering helpers
	float distance_to_line_segment(const Vector2 &point, const Vector2 &line_start, const Vector2 &line_end);
	void plot_pixel(int x, int y, Color color, float alpha);
	void draw_thick_line_aa(const Vector2 &p1, const Vector2 &p2, const Color &color, float half_width);
	void draw_thick_polyline(const Vector<Vector2> &points, const Color &color, float width);
	void draw_circle_aa(const Vector2 &center, float radius, const Color &color, bool filled);
	Vector<Vector2> get_smoothed_points(float smoothing_factor);
	void add_smoothing_point(const Vector2 &point);
	void reset_smoothing();
	
	// Event recording helpers
	void record_event(EventType type, const Vector2 &position = Vector2(), const Color &color = Color(), float size = 0.0f);
	void record_stroke_start(const Vector2 &position, const Color &color, float brush_size);
	void record_stroke_point(const Vector2 &position);
	void record_stroke_end();
	void record_erase_start(const Vector2 &position, float eraser_size);
	void record_erase_point(const Vector2 &position);
	void record_erase_end();
	void record_clear_canvas();
	
	// Serialization helpers
	PackedByteArray serialize_events() const;
	bool deserialize_events(const PackedByteArray &data);
	
	// Undo system helpers
	void create_snapshot();
	void apply_snapshot(const PackedByteArray &snapshot);
	PackedByteArray compress_image(const Ref<Image> &image);
	Ref<Image> decompress_image(const PackedByteArray &data);
	
	// Playback helpers
	void process_playback_events();
	float get_next_event_timestamp();
	
	// Utility functions
	bool is_point_valid(const Vector2 &point) const;
	void update_dirty_rect(const Vector2 &point, float radius);
	void update_canvas_texture();
	void set_dirty() {needs_update = true;}
protected:
	static void _bind_methods();
	void _notification(int p_what);
	void _gui_input(const Ref<InputEvent> &p_event);

public:
	YDrawing();
	~YDrawing();
	
	// Properties
	void set_canvas_size(const Vector2i &p_size);
	Vector2i get_canvas_size() const;
	
	void set_background_color(const Color &p_color);
	Color get_background_color() const;

	float minimum_stroke_distance = 5.0f;
	float minimum_stroke_distance_squared = 25.0f;
	void set_minimum_stroke_distance(float p_distance) {
		minimum_stroke_distance = p_distance; 
		minimum_stroke_distance_squared = p_distance * p_distance;
	}
	float get_minimum_stroke_distance() const { return minimum_stroke_distance; }

	Color current_color = Color(0.0f, 0.0f, 0.0f, 1.0f);
	void set_current_color(const Color &p_color) { current_color = p_color; }
	Color get_current_color() const { return current_color; }

	float current_brush_size = 1.0f;
	void set_current_brush_size(float p_size) { current_brush_size = p_size; }
	float get_current_brush_size() const { return current_brush_size; }

	float current_eraser_size = 1.0f;
	void set_current_eraser_size(float p_size) { current_eraser_size = p_size; }
	float get_current_eraser_size() const { return current_eraser_size; }
	
	void set_smoothing_enabled(bool p_enabled);
	bool get_smoothing_enabled() const;
	
	void set_smoothing_strength(float p_strength);
	float get_smoothing_strength() const;
	
	void set_recording_enabled(bool p_enabled);
	bool get_recording_enabled() const;
	
	// Drawing methods
	void start_stroke(const Vector2 &position);
	void start_stroke_custom(const Vector2 &position, const Color &color, float brush_size);
	void add_stroke_point(const Vector2 &position);
	void end_stroke();
	Vector<Vector2> douglas_peucker_simplify(const Vector<Vector2> &points, float epsilon);
	float point_to_line_distance(const Vector2 &point, const Vector2 &line_start, const Vector2 &line_end);
	Vector2 catmull_rom_interpolate(const Vector2 &p0, const Vector2 &p1, const Vector2 &p2, const Vector2 &p3, float t);

	int last_drawn_count = 0;
	Vector<Vector2> last_drawn_smoothed_points;
	void draw_stroke_incremental(const Vector<Vector2> &current_smoothed_points);
	void start_erase(const Vector2 &position);
	void add_erase_point(const Vector2 &position);
	void end_erase();
	
	void clear_canvas();

	bool auto_handle_input = true;
	void set_auto_handle_input(bool p_auto_handle_input) { auto_handle_input = p_auto_handle_input; }
	bool get_auto_handle_input() const { return auto_handle_input; }
	
	// Recording and playback
	PackedByteArray get_recorded_events() const;
	void playback_events(const PackedByteArray &event_data, float speed_multiplier = 1.0f);
	bool is_playing_back() const;
	void stop_playback();
	void clear_recorded_events();
	
	// Undo/Redo
	void undo();
	void redo();
	PackedByteArray get_snapshot_buffer() const;
	PackedByteArray get_incremental_strokes() const;
	PackedByteArray get_undo_stack() const;
	PackedByteArray get_redo_stack() const;
	void clear_undo_stack();
	void clear_redo_stack();

};
