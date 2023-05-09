extends Area2D

@export var speed = 400
@export var direction = -1 # up 
@export var damage = 10

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	var velocity = Vector2.ZERO
	velocity.x = 0
	velocity.y = speed
	position += velocity * direction * delta
	


func _on_visible_on_screen_notifier_2d_screen_exited():
	queue_free()
