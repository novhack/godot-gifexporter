tool
extends EditorPlugin

func _enter_tree():
	add_autoload_singleton("GifExporter", "res://addons/godot-gifexporter/src/GifExporter.gd")


func _exit_tree():
	remove_autoload_singleton("GifExporter")
