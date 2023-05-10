extends Node2D

@export var airplane_scene: PackedScene
var airplane
var screen_size

# Called when the node enters the scene tree for the first time.
func _ready():
	screen_size = get_viewport_rect().size
	airplane = airplane_scene.instantiate()
	airplane.body_entered.connect(_colission_detected)
	add_child(airplane)
	


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	check_player_movement(delta)
	check_fire_bullet()
	

func check_fire_bullet():
	if Input.is_action_just_pressed("fire_bullet"):
		airplane.fire_bullet()

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
		
	velocity = velocity.normalized() * airplane.speed
	position += velocity * delta
	position.x = clamp(position.x, 0, screen_size.x)
	position.y = clamp(position.y, 0, screen_size.y)


func _colission_detected(body: Node2D):
	if body.is_in_group("enemy_bullet"):
		print_debug("player got hit")

