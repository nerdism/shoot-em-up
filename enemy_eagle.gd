extends Area2D

@export var BulletScene: PackedScene
@export var speed = 300
@export var fire_interval = 1
@export var health = 40


var screen_size

# Called when the node enters the scene tree for the first time.
func _ready():
	screen_size = get_viewport_rect().size
	$FireInterval.wait_time = fire_interval
	$FireInterval.start()
	
func set_health(health: int):
	$HealthLabel.text = str(health) + " Hp"

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	check_movement(delta)
	set_health(health)
	

func check_movement(delta):
	var velocity = Vector2.ZERO # The player's movement vector.
	velocity = velocity.normalized() * speed
	position += velocity * delta
	position.x = clamp(position.x, 0, screen_size.x)
	position.y = clamp(position.y, 0, screen_size.y)


func _on_fire_interval_timeout():
	var bullet = BulletScene.instantiate()
	bullet.position = position
	bullet.direction = 1
	owner.add_child(bullet)
	$FireBulletSound.play()


func _on_body_entered(body):
	print_debug("test")
