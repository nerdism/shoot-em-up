extends Node

var enemy_scene = preload("res://enemy.tscn")



# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass


func _on_enemy_spawner_timeout():
	var enemy = enemy_scene.instantiate()
	var screen_size = get_viewport().size
	enemy.position = Vector2(randf_range(0, screen_size.x), -100)
	add_child(enemy) 
	


func _on_player_destroyed():
	$GameOverLabel.visible = true
	get_tree().paused = true
