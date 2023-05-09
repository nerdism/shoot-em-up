extends Area2D

@export var BulletScene: PackedScene
@export var speed = 300
@export var health = 150


var screen_size

# Called when the node enters the scene tree for the first time.
func _ready():
	screen_size = get_viewport_rect().size
	set_health(health)
	


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	check_player_movement(delta)
	check_fire_bullet(delta)
	
func set_health(health: int):
	$HealthLabel.text = str(health) + " Hp"

func check_fire_bullet(delta):
	if Input.is_action_just_pressed("fire_bullet"):
		var velocity = Vector2.ZERO
		var bullet = BulletScene.instantiate()
		bullet.position = position
		owner.add_child(bullet)
		$FireBulletSound.play()

func check_player_movement(delta):
	var velocity = Vector2.ZERO # The player's movement vector.
	if Input.is_action_pressed("move_right"):
		velocity.x += 1
	if Input.is_action_pressed("move_left"):
		velocity.x -= 1
	if Input.is_action_pressed("move_down"):
		velocity.y += 1
	if Input.is_action_pressed("move_up"):
		velocity.y -= 1
		
	velocity = velocity.normalized() * speed
	position += velocity * delta
	position.x = clamp(position.x, 0, screen_size.x)
	position.y = clamp(position.y, 0, screen_size.y)
