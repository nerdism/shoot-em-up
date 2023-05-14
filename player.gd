extends Node2D

@export var airplane_scene: PackedScene
@export var hitpoint = 50
@export var speed = 300
signal player_destroyed
var airplane
var screen_size

# Called when the node enters the scene tree for the first time.
func _ready():
	screen_size = get_viewport_rect().size
	airplane = airplane_scene.instantiate()
	airplane.hitpoint = hitpoint
	
	airplane.body_entered.connect(_colission_detected)
	airplane.area_entered.connect(_area_enterd)
	airplane.airplane_destroyed.connect(_player_destroyed)
	add_child(airplane)
	


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	if not airplane.is_destroyed():
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
		
	velocity = velocity.normalized() * speed
	position += velocity * delta
	position.x = clamp(position.x, 0, screen_size.x)
	position.y = clamp(position.y, 0, screen_size.y)


func _colission_detected(body: Node2D):
	if body.is_in_group("enemy_bullet"):
		print_debug("player got hit")
		body.queue_free()
		airplane.get_damage(body.damage)


func _area_enterd(area: Area2D):
	if area.is_in_group("airplane"):
		print_debug("player got hit by allied airplane")
		airplane.get_damage(100000)

func _player_destroyed():
	player_destroyed.emit()
	queue_free()
	
	
