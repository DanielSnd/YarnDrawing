#pragma once

#include "core/object/ref_counted.h"
#include "scene/gui/control.h"
#include "scene/resources/texture.h"
#include "core/io/image.h"
#include "core/math/vector2.h"
#include "core/math/color.h"
#include "core/variant/array.h"
#include "core/variant/variant.h"
#include "core/math/math_funcs.h"
#include "core/math/geometry_2d.h"
#include "core/io/image_loader.h"
#include "scene/resources/image_texture.h"
#include "servers/rendering_server.h"
#include "scene/gui/texture_rect.h"
#include "core/io/marshalls.h"

class YDrawing : public Control {
	GDCLASS(YDrawing, Control);

public:

	struct DrawingColor {
		uint8_t r, g, b;
		
		bool operator==(const DrawingColor& other) const {
			return r == other.r && g == other.g && b == other.b;
		}
	};
	
	struct ColorHash {
		static uint32_t hash(const DrawingColor& c) {
			return (static_cast<uint32_t>(c.r) << 16) | 
				(static_cast<uint32_t>(c.g) << 8) | 
				static_cast<uint32_t>(c.b); 
		}
	};

	TextureRect::ExpandMode expand_mode = TextureRect::EXPAND_KEEP_SIZE;
	TextureRect::StretchMode stretch_mode = TextureRect::STRETCH_SCALE;

	enum EventType {
		STROKE_START = 0,
		STROKE_START_CHANGED = 1,
		STROKE_POINT = 2,
		STROKE_END = 3,
		ERASE_START = 4,
		ERASE_START_CHANGED = 5,
		ERASE_POINT = 6,
		ERASE_END = 7,
		CLEAR_CANVAS = 8,
		CALLBACK_EVENT = 9,
		UNDO_SNAPSHOT = 10,
		REDO_SNAPSHOT = 11
	};

	String event_type_to_string(EventType p_type) const {
		switch (p_type) {
			case STROKE_START: return "STROKE_START";
			case STROKE_START_CHANGED: return "STROKE_START_CHANGED";
			case STROKE_POINT: return "STROKE_POINT";
			case STROKE_END: return "STROKE_END";
			case ERASE_START: return "ERASE_START";
			case ERASE_START_CHANGED: return "ERASE_START_CHANGED";
			case ERASE_POINT: return "ERASE_POINT";
			case ERASE_END: return "ERASE_END";
			case CLEAR_CANVAS: return "CLEAR_CANVAS";
			case CALLBACK_EVENT: return "CALLBACK_EVENT";
			case UNDO_SNAPSHOT: return "UNDO_SNAPSHOT";
			case REDO_SNAPSHOT: return "REDO_SNAPSHOT";
			default: return "UNKNOWN";
		}
	}
	

	void set_expand_mode(TextureRect::ExpandMode p_mode);
	TextureRect::ExpandMode get_expand_mode() const;

	void set_stretch_mode(TextureRect::StretchMode p_mode);
	TextureRect::StretchMode get_stretch_mode() const;

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
	
	Color last_stroke_color;
	float last_stroke_size;

	// Drawing state
	Ref<Image> canvas_image;
	Ref<ImageTexture> canvas_texture;
	bool is_drawing;
	bool is_erasing;
	
	// Smoothing system
	Vector<Vector2> smoothing_buffer;
	static const int MAX_SMOOTHING_POINTS = 100;
	
	// Event recording
	Vector<DrawingEvent> recorded_events;
	Vector<DrawingEvent> playing_back_events;
	bool is_playback_active;
	bool playback_with_pauses = false;
	float playback_speed;
	float current_playback_time;
	int playback_index;
	
	// Undo system - now using raw pixel data instead of PNG compression
	Vector<PackedByteArray> snapshot_buffer; // Now stores raw RGBA8 pixel data

	Vector2 last_stroke_point;
	Vector<int> undo_stack;
	Vector<int> redo_stack;
	int max_undo_steps;
	
	// Performance optimization
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
	PackedByteArray serialize_events(const Vector<DrawingEvent> &events_to_serialize, bool print_debug = false) const;
	bool deserialize_events(const PackedByteArray &data, Vector<DrawingEvent> &events_destination);

	// Undo system helpers - now using raw pixel data
	void create_snapshot();
	void apply_snapshot(const PackedByteArray &snapshot);
	PackedByteArray capture_raw_pixels(const Ref<Image> &image);
	void restore_raw_pixels(const PackedByteArray &pixel_data, Ref<Image> &image);
	
	// Playback helpers
	void process_playback_events();
	
	// Utility functions
	bool is_point_valid(const Vector2 &point) const;
	void update_canvas_texture();
	void set_dirty() {needs_update = true;}
protected:
	static void _bind_methods();
	void _notification(int p_what);

	virtual Size2 get_minimum_size() const override;
public:
	YDrawing();
	~YDrawing();

	bool counting_time = false;
	float current_time = 0.0f;

	void reset_counting_time() { counting_time = false; current_time = 0.0f; }

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
	
	int max_playback_brushes_this_frame = 250;
	void set_max_playback_brushes_this_frame(int p_max) { max_playback_brushes_this_frame = p_max; }
	int get_max_playback_brushes_this_frame() const { return max_playback_brushes_this_frame; }

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

	void draw_stroke_incremental(const Vector<Vector2> &current_smoothed_points);
	void start_erase(const Vector2 &position);
	void add_erase_point(const Vector2 &position);
	void end_erase();
	
	void clear_canvas();

	bool record_during_playback = false;
	void set_record_during_playback(bool p_record_during_playback) { record_during_playback = p_record_during_playback; }
	bool get_record_during_playback() const { return record_during_playback; }

	bool serialize_with_pauses = false;
	void set_serialize_with_pauses(bool p_serialize_with_pauses) { serialize_with_pauses = p_serialize_with_pauses; }
	bool get_serialize_with_pauses() const { return serialize_with_pauses; }
	
	int playback_brushes_this_frame = 0;
	bool is_skipping_playback = false;
	void skip_playback_to_end();

	bool print_debugs_playback = false;
	void set_print_debugs_playback(bool p_print_debugs_playback) { print_debugs_playback = p_print_debugs_playback; }
	bool get_print_debugs_playback() const { return print_debugs_playback; }

	// Recording and playback
	PackedByteArray get_recorded_events(bool print_debugs = false) const;
	PackedByteArray get_playing_back_events(bool print_debugs = false) const;
	void playback_events(const PackedByteArray &event_data, float speed_multiplier = 1.0f, bool include_pauses = false);
	bool is_playing_back() const;
	void stop_playback();
	void clear_recorded_events();
	void clear_playing_back_events();
	void add_callback_event(const Vector2 &position);
	
	bool should_record_event() const;

	Vector<Vector2> queued_callback_events_to_record;

	bool prevent_record_snapshots = false;
	
	Ref<Image> get_canvas_image() const;

	static inline int manhattan_distance(const DrawingColor& a, const DrawingColor& b) {
		return abs(a.r - b.r) + abs(a.g - b.g) + abs(a.b - b.b);
	}

	static int find_similar_color_fast(const Vector<DrawingColor>& palette, const DrawingColor& color, int threshold = 10) {
		for (int i = 0; i < palette.size(); i++) {
			if (manhattan_distance(palette[i], color) < threshold) {
				return i;
			}
		}
		return -1;
	}

	// Undo/Redo
	void undo();
	void redo();
	bool can_undo() const;
	bool can_redo() const;
	TypedArray<PackedByteArray> get_snapshot_buffer() const;
	TypedArray<int> get_undo_stack() const;
	TypedArray<int> get_redo_stack() const;
	void clear_undo_stack();
	void clear_redo_stack();

	// Static PNG-style compression methods
	static PackedByteArray compress_drawing_result(const Ref<Image> &image, int target_width, int target_height, bool run_length_encoding = false);
	static Ref<Image> decompress_drawing_result(const PackedByteArray &compressed_data, bool run_length_encoding = false);
};
