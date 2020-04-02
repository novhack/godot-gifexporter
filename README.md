# godot-gifexporter
Plugin adding a GifExporter singleton enabling export of Image objects as a GIF file.

### Installation:
1. Clone this repository into your Godot projects addons folder.
2. Enable this plugin in Project Settings.
3. A new singleton `GifExporter` will now be available in all scripts.

### Usage:
1. Starts gif export:

`GifExporter.begin_export(filename: String, width: int, height: int, frame_delay: float, loop_count: int = 0, bit_depth: int = 8, dither: bool = false)`
- filename - full path with a filename ('/home/user/anim.gif')
- width, height - default frame dimmensions
- frame_delay - default delay between animation frames
- loop_count - how many times is animation repeated - 0 is infinite
- bit_depth - default frame color bit depth
- dither - default apply dithering algorithm to frames

2. Adds a frame to gif:

`GifExporter.write_frame(frame : Image, background_color : Color, frame_delay : float, bit_depth : int = 8, dither : bool = false)`
- frame - Godot::Image object to write to file
- background_color - GIF don't support transparency - background color is applied as the background layer
- frame_delay - delay of this frame
- bit_depth - bit depth of this frame
- dither - apply dithering algorithm to frame

3. Finish gif exporting:

`GifExporter.end_export()`

### Changes to gifanimcplusplus
- This plugin uses https://github.com/fyngyrz/gifanimcplusplus
- Added includes of `cstding` and `cstring` libraries to `gifanim.h`
