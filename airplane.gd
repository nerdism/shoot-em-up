extends Area2D

@export var BulletScene: PackedScene
@export var speed = 300
@export var hitpoint = 150
@export var fly_direction: Direction = Direction.UP

enum Direction { UP = -1, DOWN = 1}

# Called when the node enters the scene tree for the first time.
func _ready():
	set_health(hitpoint)
	
	
func set_health(health: int):
	$HealthLabel.text = str(health) + " Hp"

func fire_bullet():
	var velocity = Vector2.ZERO
	var bullet = BulletScene.instantiate()
	bullet.velocity_direction = fly_direction
	bullet.global_position = global_position
	bullet.linear_velocity = Vector2(0, fly_direction * bullet.speed)
	#bullet.position.y += (($CollisionShape2D.shape.size.y / 2) + 10)
	get_tree().get_root().add_child(bullet)
	$FireBulletSound.play()

