#include "ydrawing.h"

void YDrawing::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_expand_mode", "expand_mode"), &YDrawing::set_expand_mode);
	ClassDB::bind_method(D_METHOD("get_expand_mode"), &YDrawing::get_expand_mode);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "expand_mode", PROPERTY_HINT_ENUM, "Keep Size,Ignore Size,Fit Width,Fit Width Proportional,Fit Height,Fit Height Proportional"), "set_expand_mode", "get_expand_mode");

	ClassDB::bind_method(D_METHOD("set_stretch_mode", "stretch_mode"), &YDrawing::set_stretch_mode);
	ClassDB::bind_method(D_METHOD("get_stretch_mode"), &YDrawing::get_stretch_mode);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "stretch_mode", PROPERTY_HINT_ENUM, "Scale,Tile,Keep,Keep Centered,Keep Aspect,Keep Aspect Centered,Keep Aspect Covered"), "set_stretch_mode", "get_stretch_mode");

	ClassDB::bind_method(D_METHOD("set_canvas_size", "size"), &YDrawing::set_canvas_size, DEFVAL(Vector2i(600, 800)));
	ClassDB::bind_method(D_METHOD("get_canvas_size"), &YDrawing::get_canvas_size);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2I, "canvas_size"), "set_canvas_size", "get_canvas_size");
	
	ClassDB::bind_method(D_METHOD("set_background_color", "color"), &YDrawing::set_background_color);
	ClassDB::bind_method(D_METHOD("get_background_color"), &YDrawing::get_background_color);
	ADD_PROPERTY(PropertyInfo(Variant::COLOR, "background_color"), "set_background_color", "get_background_color");
	
	ClassDB::bind_method(D_METHOD("set_minimum_stroke_distance", "distance"), &YDrawing::set_minimum_stroke_distance, DEFVAL(5.0f));
	ClassDB::bind_method(D_METHOD("get_minimum_stroke_distance"), &YDrawing::get_minimum_stroke_distance);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "minimum_stroke_distance"), "set_minimum_stroke_distance", "get_minimum_stroke_distance");

	ClassDB::bind_method(D_METHOD("set_smoothing_enabled", "enabled"), &YDrawing::set_smoothing_enabled);
	ClassDB::bind_method(D_METHOD("get_smoothing_enabled"), &YDrawing::get_smoothing_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "smoothing_enabled"), "set_smoothing_enabled", "get_smoothing_enabled");
	
	ClassDB::bind_method(D_METHOD("set_smoothing_strength", "strength"), &YDrawing::set_smoothing_strength);
	ClassDB::bind_method(D_METHOD("get_smoothing_strength"), &YDrawing::get_smoothing_strength);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "smoothing_strength"), "set_smoothing_strength", "get_smoothing_strength");
	
	ClassDB::bind_method(D_METHOD("set_recording_enabled", "enabled"), &YDrawing::set_recording_enabled);
	ClassDB::bind_method(D_METHOD("get_recording_enabled"), &YDrawing::get_recording_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "recording_enabled"), "set_recording_enabled", "get_recording_enabled");
	
    ClassDB::bind_method(D_METHOD("set_current_color", "color"), &YDrawing::set_current_color);
	ClassDB::bind_method(D_METHOD("get_current_color"), &YDrawing::get_current_color);
	ADD_PROPERTY(PropertyInfo(Variant::COLOR, "current_color"), "set_current_color", "get_current_color");

	ClassDB::bind_method(D_METHOD("set_current_brush_size", "size"), &YDrawing::set_current_brush_size, DEFVAL(1.0f));
	ClassDB::bind_method(D_METHOD("get_current_brush_size"), &YDrawing::get_current_brush_size);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "current_brush_size"), "set_current_brush_size", "get_current_brush_size");

	ClassDB::bind_method(D_METHOD("set_current_eraser_size", "size"), &YDrawing::set_current_eraser_size, DEFVAL(1.0f));
	ClassDB::bind_method(D_METHOD("get_current_eraser_size"), &YDrawing::get_current_eraser_size);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "current_eraser_size"), "set_current_eraser_size", "get_current_eraser_size");

	ClassDB::bind_method(D_METHOD("set_create_snapshots", "create_snapshots"), &YDrawing::set_create_snapshots);
	ClassDB::bind_method(D_METHOD("get_create_snapshots"), &YDrawing::get_create_snapshots);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "create_snapshots"), "set_create_snapshots", "get_create_snapshots");

	// Drawing methods
	ClassDB::bind_method(D_METHOD("start_stroke_custom", "position", "color", "brush_size"), &YDrawing::start_stroke_custom, DEFVAL(Vector2(0.0f, 0.0f)), DEFVAL(Color(0.0f, 0.0f, 0.0f, 1.0f)), DEFVAL(1.0f));
	ClassDB::bind_method(D_METHOD("start_stroke", "position"), &YDrawing::start_stroke, DEFVAL(Vector2(0.0f, 0.0f)));
	ClassDB::bind_method(D_METHOD("add_stroke_point", "position"), &YDrawing::add_stroke_point);
	ClassDB::bind_method(D_METHOD("end_stroke"), &YDrawing::end_stroke);
	
	ClassDB::bind_method(D_METHOD("start_erase", "position"), &YDrawing::start_erase);
	ClassDB::bind_method(D_METHOD("add_erase_point", "position"), &YDrawing::add_erase_point);
	ClassDB::bind_method(D_METHOD("end_erase"), &YDrawing::end_erase);
	
	ClassDB::bind_method(D_METHOD("clear_canvas"), &YDrawing::clear_canvas);
	
	// Recording and playback
	ClassDB::bind_method(D_METHOD("get_recorded_events"), &YDrawing::get_recorded_events);
    ClassDB::bind_method(D_METHOD("clear_recorded_events"), &YDrawing::clear_recorded_events);
	ClassDB::bind_method(D_METHOD("playback_events", "event_data", "speed_multiplier", "include_pauses"), &YDrawing::playback_events, DEFVAL(1.0f), DEFVAL(false));
	ClassDB::bind_method(D_METHOD("is_playing_back"), &YDrawing::is_playing_back);
	ClassDB::bind_method(D_METHOD("stop_playback"), &YDrawing::stop_playback);
	
	ClassDB::bind_method(D_METHOD("add_callback_event", "position"), &YDrawing::add_callback_event);
	ClassDB::bind_method(D_METHOD("get_playing_back_events"), &YDrawing::get_playing_back_events);
	ClassDB::bind_method(D_METHOD("clear_playing_back_events"), &YDrawing::clear_playing_back_events);

	ClassDB::bind_method(D_METHOD("skip_playback_to_end"), &YDrawing::skip_playback_to_end);

	ClassDB::bind_method(D_METHOD("set_record_during_playback", "record_during_playback"), &YDrawing::set_record_during_playback);
	ClassDB::bind_method(D_METHOD("get_record_during_playback"), &YDrawing::get_record_during_playback);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "record_during_playback"), "set_record_during_playback", "get_record_during_playback");

	ClassDB::bind_method(D_METHOD("reset_counting_time"), &YDrawing::reset_counting_time);

	// Undo/Redo
	ClassDB::bind_method(D_METHOD("undo"), &YDrawing::undo);
	ClassDB::bind_method(D_METHOD("redo"), &YDrawing::redo);
	ClassDB::bind_method(D_METHOD("can_undo"), &YDrawing::can_undo);
	ClassDB::bind_method(D_METHOD("can_redo"), &YDrawing::can_redo);
	ClassDB::bind_method(D_METHOD("get_snapshot_buffer"), &YDrawing::get_snapshot_buffer);
	ClassDB::bind_method(D_METHOD("get_undo_stack"), &YDrawing::get_undo_stack);
	ClassDB::bind_method(D_METHOD("get_redo_stack"), &YDrawing::get_redo_stack);
	ClassDB::bind_method(D_METHOD("clear_undo_stack"), &YDrawing::clear_undo_stack);
	ClassDB::bind_method(D_METHOD("clear_redo_stack"), &YDrawing::clear_redo_stack);

    // Pure draw methods
    ClassDB::bind_method(D_METHOD("draw_thick_polyline", "points", "color", "width"), &YDrawing::draw_thick_polyline);
    ClassDB::bind_method(D_METHOD("draw_circle_aa", "center", "radius", "color", "filled"), &YDrawing::draw_circle_aa);
    ClassDB::bind_method(D_METHOD("draw_thick_line_aa", "p1", "p2", "color", "half_width"), &YDrawing::draw_thick_line_aa);

    ClassDB::bind_method(D_METHOD("set_dirty"), &YDrawing::set_dirty);
	// Signals
	ADD_SIGNAL(MethodInfo(SNAME("stroke_started"), PropertyInfo(Variant::COLOR, "color"), PropertyInfo(Variant::FLOAT, "brush_size")));
	ADD_SIGNAL(MethodInfo(SNAME("stroke_ended")));
	ADD_SIGNAL(MethodInfo(SNAME("playback_finished")));
	ADD_SIGNAL(MethodInfo(SNAME("executed_undo")));
	ADD_SIGNAL(MethodInfo(SNAME("executed_redo")));
	ADD_SIGNAL(MethodInfo(SNAME("created_snapshot")));
	ADD_SIGNAL(MethodInfo(SNAME("callback_event"), PropertyInfo(Variant::VECTOR2, "position")));
}

Size2 YDrawing::get_minimum_size() const {
	if (canvas_texture.is_valid()) {
		switch (expand_mode) {
			case TextureRect::EXPAND_KEEP_SIZE: {
				return canvas_texture->get_size();
			} break;
			case TextureRect::EXPAND_IGNORE_SIZE: {
				return Size2();
			} break;
			case TextureRect::EXPAND_FIT_WIDTH: {
				return Size2(get_size().y, 0);
			} break;
			case TextureRect::EXPAND_FIT_WIDTH_PROPORTIONAL: {
				real_t ratio = real_t(canvas_texture->get_width()) / canvas_texture->get_height();
				return Size2(get_size().y * ratio, 0);
			} break;
			case TextureRect::EXPAND_FIT_HEIGHT: {
				return Size2(0, get_size().x);
			} break;
			case TextureRect::EXPAND_FIT_HEIGHT_PROPORTIONAL: {
				real_t ratio = real_t(canvas_texture->get_height()) / canvas_texture->get_width();
				return Size2(0, get_size().x * ratio);
			} break;
		}
	}
	return Size2();
}

void YDrawing::set_expand_mode(TextureRect::ExpandMode p_mode) {
	if (expand_mode == p_mode) {
		return;
	}

	expand_mode = p_mode;
	queue_redraw();
	update_minimum_size();
}

TextureRect::ExpandMode YDrawing::get_expand_mode() const {
	return expand_mode;
}

void YDrawing::set_stretch_mode(TextureRect::StretchMode p_mode) {
	if (stretch_mode == p_mode) {
		return;
	}

	stretch_mode = p_mode;
	queue_redraw();
}

TextureRect::StretchMode YDrawing::get_stretch_mode() const {
	return stretch_mode;
}

void YDrawing::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_READY:{
			// Initialize canvas
			if (canvas_size == Vector2i()) {
				canvas_size = Vector2i(600, 800);
			}
			canvas_image = Image::create_empty(canvas_size.x, canvas_size.y, false, Image::FORMAT_RGBA8);
			canvas_image->fill(background_color);
			
			canvas_texture = ImageTexture::create_from_image(canvas_image);
            if (!Engine::get_singleton()->is_editor_hint()) {
				create_snapshot();
                set_process(true);
                set_process_input(true);
                set_process_unhandled_input(true);
            }
		}
		break;
			
		case NOTIFICATION_DRAW:
		{
			if (canvas_texture.is_null()) {
				return;
			}

			Size2 size;
			Point2 offset;
			Rect2 region;
			bool tile = false;

			switch (stretch_mode) {
				case TextureRect::STRETCH_SCALE: {
					size = get_size();
				} break;
				case TextureRect::STRETCH_TILE: {
					size = get_size();
					tile = true;
				} break;
				case TextureRect::STRETCH_KEEP: {
					size = canvas_texture->get_size();
				} break;
				case TextureRect::STRETCH_KEEP_CENTERED: {
					offset = (get_size() - canvas_texture->get_size()) / 2;
					size = canvas_texture->get_size();
				} break;
				case TextureRect::STRETCH_KEEP_ASPECT_CENTERED:
				case TextureRect::STRETCH_KEEP_ASPECT: {
					size = get_size();
					int tex_width = canvas_texture->get_width() * size.height / canvas_texture->get_height();
					int tex_height = size.height;

					if (tex_width > size.width) {
						tex_width = size.width;
						tex_height = canvas_texture->get_height() * tex_width / canvas_texture->get_width();
					}

					if (stretch_mode == TextureRect::STRETCH_KEEP_ASPECT_CENTERED) {
						offset.x += (size.width - tex_width) / 2;
						offset.y += (size.height - tex_height) / 2;
					}

					size.width = tex_width;
					size.height = tex_height;
				} break;
					case TextureRect::STRETCH_KEEP_ASPECT_COVERED: {
					size = get_size();

					Size2 tex_size = canvas_texture->get_size();
					Size2 scale_size(size.width / tex_size.width, size.height / tex_size.height);
					float scale = scale_size.width > scale_size.height ? scale_size.width : scale_size.height;
					Size2 scaled_tex_size = tex_size * scale;

					region.position = ((scaled_tex_size - size) / scale).abs() / 2.0f;
					region.size = size / scale;
				} break;
			}

			if (region.has_area()) {
				draw_texture_rect_region(canvas_texture, Rect2(offset, size), region);
			} else {
				draw_texture_rect(canvas_texture, Rect2(offset, size), tile);
			}
		} break;
		case NOTIFICATION_RESIZED: {
			update_minimum_size();
		} break;
		case NOTIFICATION_PROCESS:
			{
				if (counting_time) {
					current_time += get_process_delta_time();
				}
				if (is_playback_active) {
					process_playback_events();
				}
				if (needs_update) {
					update_canvas_texture();
					needs_update = false;
				}
			}
			break;
	}
}

YDrawing::YDrawing() {
	canvas_size = Vector2i(800, 600);
	background_color = Color(1.0f, 1.0f, 1.0f, 1.0f);
	smoothing_enabled = true;
	smoothing_strength = 0.5f;
	recording_enabled = true;
	
	is_drawing = false;
	is_erasing = false;
	current_color = Color(0.0f, 0.0f, 0.0f, 1.0f);
	current_brush_size = 5.0f;
	current_eraser_size = 20.0f;
	
	is_playback_active = false;
	playback_speed = 1.0f;
	
	max_undo_steps = 20;
	needs_update = false;
    create_snapshots = true;
}

YDrawing::~YDrawing() {
	// Cleanup
    canvas_image = Ref<Image>();
    canvas_texture = Ref<ImageTexture>();
}

// Property setters/getters
void YDrawing::set_canvas_size(const Vector2i &p_size) {
	canvas_size = p_size;
	if (canvas_image.is_valid()) {
		canvas_image->resize(canvas_size.x, canvas_size.y);
		canvas_image->fill(background_color);
		canvas_texture->set_image(canvas_image);
	}
}

Vector2i YDrawing::get_canvas_size() const {
	return canvas_size;
}

void YDrawing::set_background_color(const Color &p_color) {
	background_color = p_color;
	if (canvas_image.is_valid()) {
		canvas_image->fill(background_color);
		update_canvas_texture();
	}
}

Color YDrawing::get_background_color() const {
	return background_color;
}

void YDrawing::set_smoothing_enabled(bool p_enabled) {
	smoothing_enabled = p_enabled;
}

bool YDrawing::get_smoothing_enabled() const {
	return smoothing_enabled;
}

void YDrawing::set_smoothing_strength(float p_strength) {
	smoothing_strength = CLAMP(p_strength, 0.0f, 1.0f);
}

float YDrawing::get_smoothing_strength() const {
	return smoothing_strength;
}

void YDrawing::set_recording_enabled(bool p_enabled) {
	recording_enabled = p_enabled;
}

bool YDrawing::get_recording_enabled() const {
	return recording_enabled;
}

// Drawing methods
void YDrawing::start_stroke_custom(const Vector2 &position, const Color &color, float brush_size) {
    current_color = color;
    current_brush_size = brush_size;
    start_stroke(position);
}

bool YDrawing::should_record_event() const {
	return recording_enabled && (!is_playback_active || record_during_playback);
}

void YDrawing::start_stroke(const Vector2 &position) {
	is_drawing = true;

    reset_smoothing();
	add_smoothing_point(position); // Will be updated with first point
	
	if (should_record_event()) {
		record_stroke_start(position, current_color, current_brush_size);
	}

	emit_signal(SNAME("stroke_started"), current_color, current_brush_size);
}

void YDrawing::add_stroke_point(const Vector2 &position) {
    if (!is_drawing) return;
    
    if (!is_point_valid(position)) return;
    
    if (position.distance_squared_to(last_stroke_point) < minimum_stroke_distance_squared) {
        return;
    }
    last_stroke_point = position;

    add_smoothing_point(position);
    
    if (should_record_event()) {
        record_stroke_point(position);
    }
    
    draw_stroke_incremental(smoothing_buffer);
        
    needs_update = true;
}

void YDrawing::end_stroke() {
	if (!is_drawing) return;
	
	is_drawing = false;
	
	if (should_record_event()) {
		record_stroke_end();
	}

	create_snapshot();

	emit_signal(SNAME("stroke_ended"));
}

void YDrawing::start_erase(const Vector2 &position) {

	is_erasing = true;
	use_background_color = true;

	reset_smoothing();
	add_smoothing_point(position); // Will be updated with first point
	
	if (should_record_event()) {
		record_erase_start(position, current_eraser_size);
	}
}

void YDrawing::add_erase_point(const Vector2 &position) {
	if (!is_erasing) return;
	
	if (!is_point_valid(position)) return;
	
    if (position.distance_squared_to(last_stroke_point) < minimum_stroke_distance_squared) {
        return;
    }
    last_stroke_point = position;

    add_smoothing_point(position);
    
    if (should_record_event()) {
        record_erase_point(position);
    }
    
    draw_stroke_incremental(smoothing_buffer);
    
    needs_update = true;
}

void YDrawing::end_erase() {
	if (!is_erasing) return;
	
	is_erasing = false;

	create_snapshot();
	
	if (should_record_event()) {
		record_erase_end();
	}
}

void YDrawing::clear_canvas() {
	if (canvas_image.is_valid()) {
		canvas_image->fill(background_color);
		needs_update = true;
	}
	
	if (should_record_event()) {
		record_clear_canvas();
	}

	create_snapshot();
}

// Stroke rendering helpers

float YDrawing::distance_to_line_segment(const Vector2 &point, const Vector2 &line_start, const Vector2 &line_end) {
    float dx = line_end.x - line_start.x;
    float dy = line_end.y - line_start.y;
    float length_sq = dx * dx + dy * dy;
    
    if (length_sq < 0.0001f) {
        // Line is actually a point
        dx = point.x - line_start.x;
        dy = point.y - line_start.y;
        return std::sqrt(dx * dx + dy * dy);
    }
    
    // Project point onto line
    float t = ((point.x - line_start.x) * dx + (point.y - line_start.y) * dy) / length_sq;
    t = std::clamp(t, 0.0f, 1.0f);
    
    // Closest point on line segment
    float closest_x = line_start.x + t * dx;
    float closest_y = line_start.y + t * dy;
    
    // Distance to closest point
    dx = point.x - closest_x;
    dy = point.y - closest_y;
    return std::sqrt(dx * dx + dy * dy);
}

// Helper: plot a pixel with alpha blending
void YDrawing::plot_pixel(int x, int y, Color color, float alpha) {
    if (!canvas_image.is_valid()) return;
    if (x < 0 || y < 0 || x >= canvas_image->get_width() || y >= canvas_image->get_height()) return;
    
    Color dst = canvas_image->get_pixel(x, y);
    Color src = color;
    
    // Proper alpha blending: dst * (1 - alpha) + src * alpha
    float final_alpha = alpha * src.a;
    Color out = Color(
        dst.r * (1.0f - final_alpha) + src.r * final_alpha,
        dst.g * (1.0f - final_alpha) + src.g * final_alpha,
        dst.b * (1.0f - final_alpha) + src.b * final_alpha,
        dst.a * (1.0f - final_alpha) + src.a * final_alpha
    );
    canvas_image->set_pixel(x, y, out);
}

void YDrawing::draw_thick_polyline(const Vector<Vector2> &points, const Color &color, float width) {
    if (!canvas_image.is_valid() || points.size() < 2) return;
    
    float half_width = width * 0.5f;
    
    // For each line segment, draw it with proper anti-aliasing
    for (int i = 0; i < points.size() - 1; i++) {
        draw_thick_line_aa(points[i], points[i + 1], color, half_width);
    }
    
    // Draw round caps and joints
    for (int i = 0; i < points.size(); i++) {
        draw_circle_aa(points[i], half_width, color, true);
    }
}

void YDrawing::draw_circle_aa(const Vector2 &center, float radius, const Color &color, bool filled) {
    if (!canvas_image.is_valid()) return;
    
    int x0 = (int)center.x;
    int y0 = (int)center.y;
    int r = (int)std::ceil(radius + 1.0f);
    
    for (int y = -r; y <= r; y++) {
        for (int x = -r; x <= r; x++) {
            float dist = std::sqrt(x * x + y * y);
            int px = x0 + x;
            int py = y0 + y;
            
            if (px < 0 || py < 0 || px >= canvas_image->get_width() || py >= canvas_image->get_height()) continue;
            
            if (filled) {
                if (dist <= radius + 0.5f) {
                    float alpha = 1.0f;
                    if (dist > radius - 0.5f) {
                        alpha = radius + 0.5f - dist;
                    }
                    alpha = std::clamp(alpha, 0.0f, 1.0f);
                    
                    if (alpha > 0) {
                        plot_pixel(px, py, color, alpha);
                    }
                }
            }
        }
    }
}

void YDrawing::draw_thick_line_aa(const Vector2 &p1, const Vector2 &p2, const Color &color, float half_width) {
    if (!canvas_image.is_valid()) return;
    
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    float length = std::sqrt(dx * dx + dy * dy);
    
    if (length < 0.01f) return;
    
    // Normalize direction
    dx /= length;
    dy /= length;
    
    // Perpendicular vector
    float px = -dy * half_width;
    float py = dx * half_width;
    
    // Bounding box
    int min_x = (int)std::floor(std::min({p1.x - px, p1.x + px, p2.x - px, p2.x + px}) - 1);
    int max_x = (int)std::ceil(std::max({p1.x - px, p1.x + px, p2.x - px, p2.x + px}) + 1);
    int min_y = (int)std::floor(std::min({p1.y - py, p1.y + py, p2.y - py, p2.y + py}) - 1);
    int max_y = (int)std::ceil(std::max({p1.y - py, p1.y + py, p2.y - py, p2.y + py}) + 1);
    
    // For each pixel in bounding box
    for (int y = min_y; y <= max_y; y++) {
        for (int x = min_x; x <= max_x; x++) {
            if (x < 0 || y < 0 || x >= canvas_image->get_width() || y >= canvas_image->get_height()) continue;
            
            // Distance from pixel to line
            float dist = distance_to_line_segment(Vector2(x, y), p1, p2);
            
            // Anti-aliased coverage
            if (dist <= half_width + 0.5f) {
                float alpha = 1.0f;
                if (dist > half_width - 0.5f) {
                    alpha = half_width + 0.5f - dist;
                }
                alpha = std::clamp(alpha, 0.0f, 1.0f);
                
                if (alpha > 0) {
                    plot_pixel(x, y, color, alpha);
                }
            }
        }
    }
}

// Smoothing system
void YDrawing::add_smoothing_point(const Vector2 &point) {
	smoothing_buffer.push_back(point);
	if (smoothing_buffer.size() > MAX_SMOOTHING_POINTS) {
        int half_size = smoothing_buffer.size() / 2;
        for (int i = 0; i < half_size; i++) {
            smoothing_buffer.remove_at(0);
        }
	}
}

void YDrawing::reset_smoothing() {
	smoothing_buffer.clear();
}
Vector<Vector2> YDrawing::get_smoothed_points(float strength) {
    if (smoothing_buffer.size() < 2) return smoothing_buffer;
    if (strength < 0.01f) return smoothing_buffer; // No smoothing
    // First, simplify the line to remove unnecessary points
    // Vector<Vector2> simplified = douglas_peucker_simplify(smoothing_buffer, 0.5f);
    Vector<Vector2> smoothed;
    for (int i = 0; i < smoothing_buffer.size(); i++) {
        if (i == 0 || i == smoothing_buffer.size() - 1) {
            smoothed.push_back(smoothing_buffer[i]); // Keep endpoints unchanged
        } else {
            // Smooth middle points
            Vector2 prev = smoothing_buffer[i - 1];
            Vector2 curr = smoothing_buffer[i];
            Vector2 next = smoothing_buffer[i + 1];
            
            // Create a smoothed point by averaging with neighbors
            Vector2 smoothed_point = curr * (1.0f - strength * 0.3f) + (prev + next) * 0.5f * strength * 0.3f;
            smoothed.push_back(smoothed_point);
        }
    }    
    return smoothed;
}

Vector2 YDrawing::catmull_rom_interpolate(const Vector2 &p0, const Vector2 &p1, const Vector2 &p2, const Vector2 &p3, float t) {
    float t2 = t * t;
    float t3 = t2 * t;
    
    Vector2 result;
    result.x = 0.5f * ((2.0f * p1.x) +
                       (-p0.x + p2.x) * t +
                       (2.0f * p0.x - 5.0f * p1.x + 4.0f * p2.x - p3.x) * t2 +
                       (-p0.x + 3.0f * p1.x - 3.0f * p2.x + p3.x) * t3);
    
    result.y = 0.5f * ((2.0f * p1.y) +
                       (-p0.y + p2.y) * t +
                       (2.0f * p0.y - 5.0f * p1.y + 4.0f * p2.y - p3.y) * t2 +
                       (-p0.y + 3.0f * p1.y - 3.0f * p2.y + p3.y) * t3);
    
    return result;
}

// Event recording
void YDrawing::record_event(EventType type, const Vector2 &position, const Color &color, float size) {
	if (!recording_enabled) return;
	if (recorded_events.size() == 0) {
		counting_time = true;
		current_time = 0.0f;
	}
	DrawingEvent event(type, current_time, position, color, size);
	recorded_events.append(event);
}

void YDrawing::record_stroke_start(const Vector2 &position, const Color &color, float brush_size) {
	if (last_stroke_color != color || last_stroke_size - brush_size > 0.001f) {
		record_event(STROKE_START_CHANGED, position, color, brush_size);
		last_stroke_color = color;
		last_stroke_size = brush_size;
	} else {
		record_event(STROKE_START, position, color, brush_size);
	}
}

void YDrawing::record_stroke_point(const Vector2 &position) {
	record_event(STROKE_POINT, position);
}

void YDrawing::record_stroke_end() {
	record_event(STROKE_END);
}

void YDrawing::record_erase_start(const Vector2 &position, float eraser_size) {
	if (last_erase_size - eraser_size > 0.001f) {
		record_event(ERASE_START_CHANGED, position, background_color, eraser_size);
		last_erase_size = eraser_size;
	} else {
		record_event(ERASE_START, position, background_color, eraser_size);
	}
}

void YDrawing::record_erase_point(const Vector2 &position) {
	record_event(ERASE_POINT, position);
}

void YDrawing::record_erase_end() {
	record_event(ERASE_END);
}

void YDrawing::record_clear_canvas() {
	record_event(CLEAR_CANVAS);
}

// Serialization helpers
PackedByteArray YDrawing::serialize_events(const Vector<DrawingEvent> &events_to_serialize) const {
	PackedByteArray result;
	

	// First pass: build color palette and calculate size
    HashMap<Color, uint8_t> color_palette;
    Vector<Color> unique_colors;
    
    for (const DrawingEvent &event : events_to_serialize) {
        if (event.type == STROKE_START_CHANGED || event.type == ERASE_START_CHANGED) {
            if (!color_palette.has(event.color)) {
                color_palette[event.color] = unique_colors.size();
                unique_colors.push_back(event.color);
            }
        }
    }
    
    // Calculate total size
    int calculate_total_size = 2; // I start with a version byte and I use a 255 byte in the place of an event type to mark the end of the data
    calculate_total_size += sizeof(uint32_t); // event count
    calculate_total_size += sizeof(uint8_t); // color palette size
    calculate_total_size += unique_colors.size() * sizeof(float) * 3; // color palette (RGB)
    
    for (int i = 0; i < events_to_serialize.size(); i++) {
        const DrawingEvent &event = events_to_serialize[i];
        calculate_total_size += sizeof(uint8_t) + sizeof(uint16_t); // type + scaled timestamp
        
        if (event.type == STROKE_START || event.type == ERASE_START) {
            calculate_total_size += sizeof(uint16_t) * 2; // position as uint16
            
            // Count consecutive stroke points
            int point_count = 0;
            for (int j = i + 1; j < events_to_serialize.size(); j++) {
                if (events_to_serialize[j].type == STROKE_POINT || events_to_serialize[j].type == ERASE_POINT) {
                    point_count++;
                } else {
                    break;
                }
            }
            calculate_total_size += sizeof(uint16_t); // point count
            calculate_total_size += point_count * (sizeof(uint16_t) * 2 + sizeof(uint16_t)); // positions + scaled timestamp
            i += point_count; // Skip the points we'll batch
            
        } else if (event.type == STROKE_START_CHANGED || event.type == ERASE_START_CHANGED) {
            calculate_total_size += sizeof(uint16_t) * 2; // position as uint16
            calculate_total_size += sizeof(uint8_t); // color index
            calculate_total_size += sizeof(uint8_t); // size
            
            // Count consecutive stroke points
            int point_count = 0;
            for (int j = i + 1; j < events_to_serialize.size(); j++) {
                if (events_to_serialize[j].type == STROKE_POINT || events_to_serialize[j].type == ERASE_POINT) {
                    point_count++;
                } else {
                    break;
                }
            }
            calculate_total_size += sizeof(uint16_t); // point count
            calculate_total_size += point_count * (sizeof(uint16_t) * 2 + sizeof(uint16_t)); // positions + scaled timestamps
            i += point_count; // Skip the points we'll batch
            
        } else if (event.type == CALLBACK_EVENT) {
            calculate_total_size += sizeof(uint16_t) * 2; // position as uint16
        }
        // STROKE_END, ERASE_END, CLEAR_CANVAS have no additional data
    }
    
    result.resize(calculate_total_size);

    int offset = 0;

	result.write[offset] = 1; // VERSION! Starting at 1 :)
	offset += sizeof(uint8_t);

    // Write color palette
    result.write[offset] = static_cast<uint8_t>(unique_colors.size());
    offset += sizeof(uint8_t);
    
	// print_line(vformat("Writing color palette, unique colors size: %d", unique_colors.size()));
    for (const Color &color : unique_colors) {
        offset += encode_float(color.r, &result.write[offset]);
        offset += encode_float(color.g, &result.write[offset]);
        offset += encode_float(color.b, &result.write[offset]);
    }
    
    // Write events
    for (int i = 0; i < events_to_serialize.size(); i++) {
        const DrawingEvent &event = events_to_serialize[i];
        
        result.write[offset] = static_cast<uint8_t>(event.type);
        offset += sizeof(uint8_t);

        offset += encode_uint16(static_cast<uint16_t>(event.timestamp * 9.1f), &result.write[offset]);
        
		// print_line(vformat("Writing event type: %d with timestamp: %.3f uint16_t %d", event.type, event.timestamp, static_cast<uint16_t>(event.timestamp * 9.1f)));

        if (event.type == STROKE_START || event.type == ERASE_START || event.type == STROKE_START_CHANGED || event.type == ERASE_START_CHANGED) {
            // Write position as uint16
            offset += encode_uint16(static_cast<uint16_t>(event.position.x), &result.write[offset]);
            offset += encode_uint16(static_cast<uint16_t>(event.position.y), &result.write[offset]);
            // print_line(vformat("Writing start position: %.3f, %.3f as uint16_t %d %d", event.position.x, event.position.y, static_cast<uint16_t>(event.position.x), static_cast<uint16_t>(event.position.y)));

			if (event.type == STROKE_START_CHANGED || event.type == ERASE_START_CHANGED) {
				 // Write color index
				result.write[offset] = color_palette[event.color];
				offset += sizeof(uint8_t);
				
				// Write size
				result.write[offset] = static_cast<uint8_t>(std::round(event.size));
				offset += sizeof(uint8_t);
			}

            // Count and write consecutive stroke points
            int point_count = 0;
            for (int j = i + 1; j < events_to_serialize.size(); j++) {
                if (events_to_serialize[j].type == STROKE_POINT || events_to_serialize[j].type == ERASE_POINT) {
                    point_count++;
                } else {
                    break;
                }
            }
            
            offset += encode_uint16(point_count, &result.write[offset]);
            
			// Saving current position to calculate the delta
			int current_x = static_cast<int>(event.position.x);
			int current_y = static_cast<int>(event.position.y);
			float current_timestamp = event.timestamp;
			// print_line(vformat("Saving current position to calculate delta: %.3f, %.3f as int %d %d", event.position.x, event.position.y, current_x, current_y));
            // Write all stroke points in batch
            for (int j = 1; j <= point_count; j++) {
                const DrawingEvent &point_event = events_to_serialize[i + j];
				int delta_x = static_cast<int>(point_event.position.x) - current_x;
				int delta_y = static_cast<int>(point_event.position.y) - current_y;
				float real_delta_timestamp = point_event.timestamp - current_timestamp;
				
				current_x += delta_x;
				current_y += delta_y;
				current_timestamp += real_delta_timestamp;
				if (delta_x >= -128 && delta_x <= 127 && 
					delta_y >= -128 && delta_y <= 127 &&
					(real_delta_timestamp * 900.1f) < 255) {
					result.write[offset++] = 0; // small delta flag
					result.write[offset++] = static_cast<int8_t>(delta_x);
					result.write[offset++] = static_cast<int8_t>(delta_y);
					result.write[offset++] = static_cast<uint8_t>(real_delta_timestamp * 900.1f);
					// print_line(vformat("Writing delta: %.3f, %.3f, timestamp %.3f as int %d %d and timestamp delta %.3f deltas casted to int8_t %d %d and timestamp uint8_t %d", point_event.position.x, point_event.position.y, point_event.timestamp, delta_x, delta_y, real_delta_timestamp, static_cast<int8_t>(delta_x), static_cast<int8_t>(delta_y), static_cast<uint8_t>(real_delta_timestamp * 9.1f)));
				} else {
					result.write[offset++] = 1; // large delta flag
					offset += encode_uint16(static_cast<uint16_t>(delta_x), &result.write[offset]);
					offset += encode_uint16(static_cast<uint16_t>(delta_y), &result.write[offset]);
					offset += encode_uint16(static_cast<uint16_t>(real_delta_timestamp * 900.1f), &result.write[offset]);
					// print_line(vformat("Writing delta: %.3f, %.3f, timestamp %.3f as int %d %d and timestamp delta %.3f deltas casted to uint16_t %d %d %d", point_event.position.x, point_event.position.y, point_event.timestamp, delta_x, delta_y, real_delta_timestamp, static_cast<uint16_t>(delta_x), static_cast<uint16_t>(delta_y), static_cast<uint16_t>(real_delta_timestamp * 9.1f)));
				}
            }
            
            i += point_count + 1; // Skip the points we just serialized and the stroke end event
            
        } else if (event.type == CALLBACK_EVENT) {
            offset += encode_uint16(static_cast<uint16_t>(event.position.x), &result.write[offset]);
            offset += encode_uint16(static_cast<uint16_t>(event.position.y), &result.write[offset]);
        }
        // STROKE_END, ERASE_END, CLEAR_CANVAS have no additional data
    }
    
	result.write[offset] = UINT8_MAX;

    return result;
}

bool YDrawing::deserialize_events(const PackedByteArray &data, Vector<DrawingEvent> &events_destination) {
	 if (data.size() < sizeof(uint32_t)) 
	 {
		// print_line("Data size is less than 4 bytes");
		return false;
	 }
    
    events_destination.clear();
    // print_line(vformat("Deserializing events, data size: %d", data.size()));
    const uint8_t *ptr = data.ptr();
    int offset = 0;

	uint8_t version = ptr[offset];
	offset += sizeof(uint8_t);

	if (version != 1) {
		print_line(vformat("Unsupported version: %d", version));
		return false;
	}

    // Read color palette
    uint8_t palette_size = ptr[offset];
    offset += sizeof(uint8_t);
    
    Vector<Color> color_palette;
    color_palette.resize(palette_size);
    
	// print_line(vformat("Reading color palette size: %d", palette_size));
    for (int i = 0; i < palette_size; i++) {
        color_palette.write[i].r = decode_float(ptr + offset);
        offset += sizeof(float);
        color_palette.write[i].g = decode_float(ptr + offset);
        offset += sizeof(float);
        color_palette.write[i].b = decode_float(ptr + offset);
        offset += sizeof(float);
        color_palette.write[i].a = 1.0f;
    }
	// print_line(vformat("Reading events"));
    // Read events until finding a 255 byte in place of the event type or end of data
	bool found_end = false;
    while(!found_end && offset < data.size()) {
		uint8_t event_type_byte = ptr[offset];
        offset += sizeof(uint8_t);

		if (event_type_byte == UINT8_MAX) {
			found_end = true;
			// print_line(vformat("Found end of events"));
			break;
		}

        DrawingEvent event;
        event.type = static_cast<EventType>(event_type_byte);

		uint16_t scaled_timestamp = decode_uint16(ptr + offset);
		event.timestamp = static_cast<float>(scaled_timestamp) / 9.1f;
		offset += sizeof(uint16_t);

		// print_line(vformat("Reading event type: %d with timestamp: %.3f uint16_t %d", event.type, event.timestamp, scaled_timestamp));

		if (event.type == CLEAR_CANVAS || event.type == UNDO_SNAPSHOT || event.type == REDO_SNAPSHOT) {
			events_destination.push_back(event);
			continue;
		}
        
        if (event.type == STROKE_START || event.type == ERASE_START || event.type == STROKE_START_CHANGED || event.type == ERASE_START_CHANGED) {
			uint16_t starting_x = decode_uint16(ptr + offset);
			offset += sizeof(uint16_t);
			uint16_t starting_y = decode_uint16(ptr + offset);
			offset += sizeof(uint16_t);
			event.position.x = static_cast<float>(starting_x);
			event.position.y = static_cast<float>(starting_y);
            
			if (event.type == STROKE_START_CHANGED || event.type == ERASE_START_CHANGED) {
				uint8_t color_index = ptr[offset];
				offset += sizeof(uint8_t);
				event.color = color_palette[color_index];
				
				event.size = static_cast<float>(ptr[offset]);
				offset += sizeof(uint8_t);
			}

            events_destination.push_back(event);
            
            // Read batched stroke points
            uint16_t point_count = decode_uint16(ptr + offset);
            offset += sizeof(uint16_t);
            
			int current_x = starting_x;
			int current_y = starting_y;
			float current_timestamp = event.timestamp;
			// print_line(vformat("Reading stroke starting position: %d %d and timestamp: %d. Point count %d", starting_x, starting_y, scaled_timestamp, point_count));
            for (int j = 0; j < point_count; j++) {
                DrawingEvent point_event;
                point_event.type = (event.type == STROKE_START || event.type == STROKE_START_CHANGED) ? STROKE_POINT : ERASE_POINT;

				uint8_t small_delta_flag = ptr[offset];
				offset += sizeof(uint8_t);

				if (small_delta_flag == 0) {
					int8_t delta_x = static_cast<int8_t>(ptr[offset]);
					offset += sizeof(int8_t);
					int8_t delta_y = static_cast<int8_t>(ptr[offset]);
					offset += sizeof(int8_t);
					uint8_t delta_timestamp = ptr[offset];
					offset += sizeof(uint8_t);
					current_x += delta_x;
					current_y += delta_y;
					current_timestamp += static_cast<float>(delta_timestamp) / 900.1f;
					// print_line(vformat("Reading delta: %.3f, %.3f, timestamp %.3f as int %d %d and uint16 %d new current int %d %d and timestamp %d", static_cast<float>(current_x), static_cast<float>(current_y), current_timestamp, delta_x, delta_y, delta_timestamp, current_x, current_y, current_timestamp));
				} else {
					int16_t delta_x = static_cast<int16_t>(decode_uint16(ptr + offset));
					offset += sizeof(uint16_t);
					int16_t delta_y = static_cast<int16_t>(decode_uint16(ptr + offset));
					offset += sizeof(uint16_t);
					uint16_t delta_timestamp = decode_uint16(ptr + offset);
					offset += sizeof(uint16_t);
					current_x += delta_x;
					current_y += delta_y;
					current_timestamp += static_cast<float>(delta_timestamp) / 900.1f;
					// print_line(vformat("Reading delta: %.3f, %.3f, timestamp %.3f as int %d %d and uint16 %d new current int %d %d and timestamp %d", static_cast<float>(current_x), static_cast<float>(current_y), current_timestamp, delta_x, delta_y, delta_timestamp, current_x, current_y, current_timestamp));
				}
				point_event.position.x = static_cast<float>(current_x);
				point_event.position.y = static_cast<float>(current_y);
				point_event.timestamp = static_cast<float>(current_timestamp);
                events_destination.push_back(point_event);
            }
            
            // Add stroke end event
            DrawingEvent end_event;
            end_event.type = (event.type == STROKE_START || event.type == STROKE_START_CHANGED) ? STROKE_END : ERASE_END;
            end_event.timestamp = events_destination[events_destination.size() - 1].timestamp; // Use last point's timestamp
            events_destination.push_back(end_event);
        } else if (event.type == CALLBACK_EVENT) {
            event.position.x = static_cast<float>(decode_uint16(ptr + offset));
            offset += sizeof(uint16_t);
            event.position.y = static_cast<float>(decode_uint16(ptr + offset));
            offset += sizeof(uint16_t);
            events_destination.push_back(event);
        }
    }
    // print_line(vformat("Deserialized events, size: %d", events_destination.size()));
    return true;
}

void YDrawing::draw_stroke_incremental(const Vector<Vector2> &smoothing_points) {
    int n = smoothing_points.size();
    
    Color use_color = current_color;
    float use_brush_size = current_brush_size;
    if (is_erasing) {
        use_color = background_color;
        use_brush_size = current_eraser_size;
    }
    float half_width = use_brush_size * 0.5f;

    if (n == 0) return;

    if (smoothing_points.size() < 3) {
        // Draw simple line for first few points
        if (smoothing_points.size() > 1) {
            int last_idx = smoothing_points.size() - 1;
            draw_circle_aa(smoothing_points[last_idx], half_width, use_color, true);    
            draw_thick_line_aa(smoothing_points[last_idx - 1], smoothing_points[last_idx], 
                    use_color, half_width);
            draw_circle_aa(smoothing_points[last_idx - 1], half_width, use_color, true);
        }
        return;
    }
    
    int idx = smoothing_points.size() - 1;
    Vector2 p1 = smoothing_points[idx - 2];
    Vector2 p2 = smoothing_points[idx - 1];
    Vector2 p3 = smoothing_points[idx];
    
    float distance = p3.distance_to(p2);
    float max_gap = 6.0f;
    
    if (distance > max_gap) {
        // Calculate velocity/direction from previous points
        Vector2 velocity;
        if (smoothing_points.size() > 2) {
            velocity = (p2 - p1).normalized();
        } else {
            velocity = (p3 - p2).normalized();
        }
        // Create smooth curve using quadratic Bezier
        Vector2 control_point = p2 + velocity * (distance * 0.3f);
        
        int num_interpolated = (int)(distance / max_gap);
        Vector2 current_pos = p2;
        
        for (int i = 1; i <= num_interpolated; i++) {
            float t = (float)i / (float)(num_interpolated + 1);
            
            // Quadratic Bezier interpolation
            Vector2 interpolated = p2 * (1 - t) * (1 - t) + 
                                  control_point * 2 * (1 - t) * t + 
                                  p3 * t * t;
            
            draw_thick_line_aa(current_pos, interpolated, use_color, half_width);
            draw_circle_aa(interpolated, half_width, use_color, true);
            current_pos = interpolated;
        }
        
        // Final segment
        draw_thick_line_aa(current_pos, p3, use_color, half_width);
        draw_circle_aa(p3, half_width, use_color, true);
    } else {
        // Small gap, draw directly
        draw_thick_line_aa(p2, p3, use_color, half_width);
        draw_circle_aa(p3, half_width, use_color, true);
    }
}


Vector<Vector2> YDrawing::douglas_peucker_simplify(const Vector<Vector2> &points, float epsilon) {
    if (points.size() < 3) return points;
    
    // Find the point with maximum distance from the line segment
    float max_distance = 0.0f;
    int max_index = 0;
    
    Vector2 start = points[0];
    Vector2 end = points[points.size() - 1];
    
    for (int i = 1; i < points.size() - 1; i++) {
        float distance = point_to_line_distance(points[i], start, end);
        if (distance > max_distance) {
            max_distance = distance;
            max_index = i;
        }
    }
    
    Vector<Vector2> result;
    
    if (max_distance > epsilon) {
        // Recursively simplify
        Vector<Vector2> left_points;
        Vector<Vector2> right_points;
        
        for (int i = 0; i <= max_index; i++) {
            left_points.push_back(points[i]);
        }
        for (int i = max_index; i < points.size(); i++) {
            right_points.push_back(points[i]);
        }
        
        Vector<Vector2> left_simplified = douglas_peucker_simplify(left_points, epsilon);
        Vector<Vector2> right_simplified = douglas_peucker_simplify(right_points, epsilon);
        
        result.append_array(left_simplified);
        // Remove duplicate point at junction
        for (int i = 1; i < right_simplified.size(); i++) {
            result.push_back(right_simplified[i]);
        }
    } else {
        result.push_back(start);
        result.push_back(end);
    }
    
    return result;
}

float YDrawing::point_to_line_distance(const Vector2 &point, const Vector2 &line_start, const Vector2 &line_end) {
    Vector2 line_vec = line_end - line_start;
    Vector2 point_vec = point - line_start;
    
    float line_length_sq = line_vec.length_squared();
    if (line_length_sq < 0.001f) return point_vec.length();
    
    float projection = point_vec.dot(line_vec) / line_length_sq;
    projection = std::clamp(projection, 0.0f, 1.0f); // Clamp to line segment
    
    Vector2 closest_point = line_start + line_vec * projection;
    return point.distance_to(closest_point);
}

// Recording and playback
PackedByteArray YDrawing::get_recorded_events() const {
	return serialize_events(recorded_events);
}
PackedByteArray YDrawing::get_playing_back_events() const {
	return serialize_events(playing_back_events);
}

void YDrawing::clear_playing_back_events() {
	playing_back_events.clear();
}

void YDrawing::clear_recorded_events() {
	recorded_events.clear();
}

void YDrawing::add_callback_event(const Vector2 &position) {
	record_event(CALLBACK_EVENT, position);
}

void YDrawing::playback_events(const PackedByteArray &event_data, float speed_multiplier, bool include_pauses) {
	// Deserialize events and start playback
	if (deserialize_events(event_data, playing_back_events)) {
		is_playback_active = true;
		current_playback_time = 0.0f;
		playback_speed = speed_multiplier;
		playback_with_pauses = include_pauses;
		playback_index = 0;
		// Clear canvas for playback
		if (canvas_image.is_valid()) {
			canvas_image->fill(background_color);
			needs_update = true;
		}
	}
}

bool YDrawing::is_playing_back() const {
	return is_playback_active;
}

void YDrawing::stop_playback() {
	is_playback_active = false;
	emit_signal(SNAME("playback_finished"));
}

void YDrawing::process_playback_events() {
	if (!is_playback_active || playing_back_events.size() == 0 || playback_index >= playing_back_events.size()) {
		stop_playback();
		is_skipping_playback = false;
		return;
	}
    current_playback_time += get_process_delta_time() * playback_speed;

    if (playback_index < playing_back_events.size()) {
        const DrawingEvent &event = playing_back_events[playback_index];
		if (!is_skipping_playback && (playback_with_pauses && event.timestamp > current_playback_time)) {
			return;
		}
        //print_line(vformat("Playing back event: %d at index %d and position %s", event.type, playback_index, event.position));
        switch (event.type) {
			case STROKE_START_CHANGED:
				// print_line(vformat("Playing back stroke start changed, position %.3f, %.3f and color %s and size %.3f", event.position.x, event.position.y, event.color, event.size));
				start_stroke_custom(event.position, event.color, event.size);
				break;
			case ERASE_START_CHANGED:
				current_eraser_size = event.size;
				start_erase(event.position);
				break;
            case STROKE_START:
                start_stroke(event.position);
                break;
            case STROKE_POINT:
				// print_line(vformat("Playing back stroke point, position %.3f, %.3f", event.position.x, event.position.y));
                add_stroke_point(event.position);
                break;
            case STROKE_END:
                end_stroke();
                break;
            case ERASE_START:
                start_erase(event.position);
                break;
            case ERASE_POINT:
                add_erase_point(event.position);
                break;
            case ERASE_END:
                end_erase();
                break;
            case CLEAR_CANVAS:
                clear_canvas();
                break;
            case CALLBACK_EVENT:
				emit_signal(SNAME("callback_event"), event.position);
				break;
			case UNDO_SNAPSHOT:
				undo();
				break;
			case REDO_SNAPSHOT:
				redo();
				break;
        }
        playback_index++;
		if (is_skipping_playback) {
			process_playback_events();
		}
    }
}

// Undo system
void YDrawing::create_snapshot() {
    if (!create_snapshots) return;

	if (snapshot_buffer.size() >= max_undo_steps) {
		// Too many snapshots, remove the oldest one
		snapshot_buffer.remove_at(0);

		// Update undo stack
		for (int i = undo_stack.size() - 1; i >= 0; i--) {
			if (undo_stack[i] > 0) {
				undo_stack.write[i] = undo_stack[i] - 1;
			} else {
				undo_stack.remove_at(i);
			}
		}
	}
	
	if (redo_stack.size() > 0) {
		// Clear redo stack when new action is performed
		redo_stack.clear();
	}
	
	PackedByteArray snapshot = compress_image(canvas_image);
	snapshot_buffer.push_back(snapshot);
	// print_line(vformat("Created snapshot at index %d", snapshot_buffer.size() - 1));
	// Add to undo stack
	undo_stack.push_back(snapshot_buffer.size() - 1);

	emit_signal(SNAME("created_snapshot"));
}

void YDrawing::skip_playback_to_end() {
	is_skipping_playback = true;
}

void YDrawing::apply_snapshot(const PackedByteArray &snapshot) {
	Ref<Image> restored_image = decompress_image(snapshot);
	if (restored_image.is_valid()) {
		canvas_image = restored_image;
		update_canvas_texture();
	}
}

PackedByteArray YDrawing::compress_image(const Ref<Image> &image) {
	Vector<uint8_t> result = image->save_png_to_buffer();
	return result;
}

Ref<Image> YDrawing::decompress_image(const PackedByteArray &data) {
	Ref<Image> image = Image::create_empty(canvas_size.x, canvas_size.y, false, Image::FORMAT_RGBA8);
	Error err = image->load_png_from_buffer(data);
	if (err != OK) {
		print_line(vformat("Error decompressing image: %d", err));
	}
	return image;
}

bool YDrawing::can_undo() const {
	return undo_stack.size() > 1;
}

bool YDrawing::can_redo() const {
	return redo_stack.size() > 0;
}

void YDrawing::undo() {
    if (undo_stack.size() > 1) {  // Need at least 2 snapshots
        if (should_record_event()) {
            record_event(UNDO_SNAPSHOT);
        }
        
        // Remove the current state from undo stack and add to redo stack
        int current_snapshot_index = undo_stack[undo_stack.size() - 1];
        undo_stack.remove_at(undo_stack.size() - 1);
        redo_stack.push_back(current_snapshot_index);
        
        // Apply the PREVIOUS state (now the last item in undo_stack)
        int previous_snapshot_index = undo_stack[undo_stack.size() - 1];
        print_line(vformat("Undoing to snapshot at index %d", previous_snapshot_index));
        
        if (previous_snapshot_index >= 0 && previous_snapshot_index < snapshot_buffer.size()) {
            apply_snapshot(snapshot_buffer[previous_snapshot_index]);
        }
		emit_signal(SNAME("executed_undo"));
    }
}

void YDrawing::redo() {
    if (redo_stack.size() > 0) {
        if (should_record_event()) {
            record_event(REDO_SNAPSHOT);
        }
        
        int snapshot_index = redo_stack[redo_stack.size() - 1];
        redo_stack.remove_at(redo_stack.size() - 1);
        
        print_line(vformat("Redoing snapshot at index %d", snapshot_index));
        if (snapshot_index >= 0 && snapshot_index < snapshot_buffer.size()) {
            undo_stack.push_back(snapshot_index);
            apply_snapshot(snapshot_buffer[snapshot_index]);
        }
		emit_signal(SNAME("executed_redo"));
    }
}

TypedArray<PackedByteArray> YDrawing::get_snapshot_buffer() const {
	TypedArray<PackedByteArray> result;
	// Serialize snapshot buffer
	for (int i = 0; i < snapshot_buffer.size(); i++) {
		result.append(snapshot_buffer[i]);
	}
	return result;
}

TypedArray<int> YDrawing::get_undo_stack() const {
	TypedArray<int> result;
	for (int i = 0; i < undo_stack.size(); i++) {
		result.append(undo_stack[i]);
	}
	return result;
}

TypedArray<int> YDrawing::get_redo_stack() const {
	TypedArray<int> result;
	for (int i = 0; i < redo_stack.size(); i++) {
		result.append(redo_stack[i]);
	}
	return result;
}

void YDrawing::clear_undo_stack() {
	undo_stack.clear();
}

void YDrawing::clear_redo_stack() {
	redo_stack.clear();
}

// Utility functions
bool YDrawing::is_point_valid(const Vector2 &point) const {
	return point.x >= 0 && point.x < canvas_size.x && point.y >= 0 && point.y < canvas_size.y;
}

void YDrawing::update_canvas_texture() {
	if (canvas_texture.is_valid() && canvas_image.is_valid()) {
		canvas_texture->update(canvas_image);
		queue_redraw();
	}
}
