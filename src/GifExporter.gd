extends Node

var gif_exporter_native = preload("res://addons/godot-gifexporter/src/GifExporter.gdns").new()

func begin_export(filename : String, width : int, height : int, frame_delay : float, loop_count : int = 0, bit_depth : int = 8, dither : bool = false) -> bool:
	if is_platform_supported():
		gif_exporter_native.begin_export(filename, width, height, frame_delay, loop_count, bit_depth, dither)
		return true
	else:
		return false

func write_frame(frame : Image, background_color : Color, frame_delay : float, bit_depth : int = 8, dither : bool = false) -> void:
	if is_platform_supported():
		gif_exporter_native.write_frame(frame, background_color, frame_delay, bit_depth, dither)


func end_export() -> void:
	if is_platform_supported():
		gif_exporter_native.end_export()


func is_platform_supported() -> bool:
	match OS.get_name():
		'X11', 'Windows':
			return true
		_:
			printerr("GIF export is not supported on this platform")
			return false
