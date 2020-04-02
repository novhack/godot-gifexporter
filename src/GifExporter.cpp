#include "GifExporter.h"

#include <PoolArrays.hpp>

GifExporter::GifExporter() {
}

GifExporter::~GifExporter() {
}

void GifExporter::_register_methods() {
    godot::register_method("begin_export", &GifExporter::begin_export);
    godot::register_method("end_export", &GifExporter::end_export);
    godot::register_method("write_frame", &GifExporter::write_frame);
}

void GifExporter::_init() {
}

void GifExporter::begin_export(const godot::String filename, int width, int height, float frame_delay, int loop_count, int32_t bit_depth, bool dither) {
    // opens a new gif file
    ganim.GifBegin(&gwriter, filename.utf8().get_data(), width, height, frame_delay, loop_count, bit_depth, dither);
}

void GifExporter::end_export() {
    // closes the gif file
    ganim.GifEnd(&gwriter);
}

void GifExporter::write_frame(const godot::Ref<godot::Image> frame, godot::Color background_color, float frame_delay, int32_t bit_depth, bool dither) {
    // get raw bytes from frame
    godot::PoolByteArray pool = frame->get_data();

    uint8_t data[pool.size()];
    for (size_t i = 0; i < pool.size(); i+=4) {
        // blend color with the background color because gif doesn't support alpha channel
        uint8_t red = pool[i];
        uint8_t green = pool[i + 1];
        uint8_t blue = pool[i + 2];
        uint8_t alpha = pool[i + 3];

        // background always has to have a solid alpha
        data[i + 3] = alpha + 255 * (255 - alpha);
        data[i] = (red * alpha + background_color.get_r8() * 255 * (255 - alpha)) / data[i + 3];
        data[i + 1] = (green * alpha + background_color.get_g8() * 255 * (255 - alpha)) / data[i + 3];
        data[i + 2] = (blue * alpha + background_color.get_b8() * 255 * (255 - alpha)) / data[i + 3];
    }
    ganim.GifWriteFrame(&gwriter, data, frame->get_width(), frame->get_height(), frame_delay, bit_depth, dither);
}

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
    godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
    godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
    godot::Godot::nativescript_init(handle);
    godot::register_class<GifExporter>();
}
