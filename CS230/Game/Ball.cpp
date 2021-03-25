#include "Ball.h"
#include "Level1.h"

Ball::Ball(math::vec2 startPos) : initPosition(startPos) {};

void Ball::Load()
{
	sprite.Load("assets/Ball.png", (0, 14));
	position = initPosition;
	velocity = math::vec2(0, 0);
}

void Ball::Update(double dt)
{

	velocity.y += Level1::gravity * dt;
	position.y += velocity.y * dt;
	
	if (position.y < Level1::floor)
	{
		position.y = Level1::floor;
		velocity.y = bounceVelocity;
	}
	
}

void Ball::Draw()
{
	sprite.Draw(position);
}


