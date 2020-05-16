tool
extends EditorPlugin

func _enter_tree():
	add_custom_type("GifExporter", "Node", preload("res://addons/godot-gifexporter/src/GifExporter.gd"), ImageTexture.new())

func _exit_tree():
	remove_custom_type("GifExporter")
