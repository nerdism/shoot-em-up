extends Area2D

enum Direction { UP = -1, DOWN = 1}
@export var BulletScene: PackedScene
@export var fly_direction: Direction = Direction.UP
signal airplane_destroyed
var hitpoint
var destroyed: bool = false


# Called when the node enters the scene tree for the first time.
func _ready(): 
	$ExplosionAnimation.animation_finished.connect(_explosion_animation_finished)
	_set_health(hitpoint)
	if fly_direction == Direction.DOWN:
		$Sprite2D.rotation_degrees = 180
	else:
		$Sprite2D.rotation_degrees = 0
	
func _set_health(health: int):
	$HealthLabel.text = str(health) + " Hp"

func fire_bullet():
	if not destroyed:
		var velocity = Vector2.ZERO
		var bullet = BulletScene.instantiate()
		bullet.velocity_direction = fly_direction
		bullet.global_position = global_position
		bullet.linear_velocity = Vector2(0, fly_direction * bullet.speed)
		bullet.position.y += fly_direction * (($CollisionShape2D.shape.size.y / 2) + 10)
		get_tree().get_root().add_child(bullet)
		$FireBulletSound.play()

func get_damage(hit: int):
	hitpoint -= hit
	_set_health(hitpoint)
	if hitpoint <= 0:
		_destroy()

func _explod():
	$Sprite2D.visible = false
	$ExplosionAnimation.visible = true
	$HealthLabel.visible = false
	$CollisionShape2D.set_deferred("disabled", true)
	$ExplosionAnimation.play("explosion")
	$ExplosionSound.play()

func _destroy():
	print_debug("airplane got destroyed")
	destroyed = true
	_explod()
	

func is_destroyed():
	return destroyed

func _explosion_animation_finished():
	airplane_destroyed.emit()
	#get_parent().queue_free()
	
	
