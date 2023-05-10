extends Node2D

@export var fire_interval = 1


var screen_size

# Called when the node enters the scene tree for the first time.
func _ready():
	$Airplane.fly_direction = $Airplane.Direction.DOWN
	screen_size = get_viewport_rect().size
	$FireInterval.wait_time = fire_interval
	$FireInterval.start()
	

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	handle_movement(delta)
	

func handle_movement(delta):
	var velocity = Vector2.ZERO # The player's movement vector.
	velocity = velocity.normalized() * $Airplane.speed
	position += velocity * delta
	position.x = clamp(position.x, 0, screen_size.x)
	position.y = clamp(position.y, 0, screen_size.y)


func _on_fire_interval_timeout():
	$Airplane.fire_bullet()


	
