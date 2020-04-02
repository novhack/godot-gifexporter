#ifndef GIFEXPORTER_H
#define GIFEXPORTER_H

#include <Godot.hpp>
#include <Reference.hpp>
#include <Image.hpp>

#define GIF_FREE
#include <gifanim.h>

class GifExporter : public godot::Reference {
    GODOT_CLASS(GifExporter, godot::Reference)

private:
    GifAnim ganim;
    GifWriter gwriter;

public:
    static void _register_methods();

    GifExporter();
    ~GifExporter();

    void _init(); // our initializer called by Godot

    void _process(float delta);

    void begin_export(const godot::String filename, int width, int height, float frame_delay, int loop_count = 0, int32_t bit_depth = 8, bool dither = false);

    void end_export();

    void write_frame(const godot::Ref<godot::Image> frame, godot::Color background_color, float frame_delay, int32_t bit_depth = 8, bool dither = false);
};

#endif //GIFEXPORTER_H
