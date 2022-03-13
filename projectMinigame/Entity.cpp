#include "Entity.h"


Entity::Entity()
{
	is_alive = false;
}
Entity::~Entity()
{
}
void Entity::Init(int posx, int posy, int w, int h, int s, int posx2, int posy2) 
{
	x = posx;
	y = posy;
	width = w;
	height = h;
	speed = s;
	is_alive = true;
	x_shot = posx2;
	y_shot = posy2;

}
void Entity::GetRect(int *posx, int *posy, int *w, int *h)
{
	*posx = x;
	*posy = y;
	*w = width;
	*h = height;
}
int Entity::GetX()
{
	return x;
}
int Entity::GetY()
{
	return y;
}
int Entity::GetShotX()
{
	return x_shot;
}
int Entity::GetShotY()
{
	return y_shot;
}
int Entity::GetWidth()
{
	return width;
}
void Entity::SetX(int posx)
{
	x = posx;
}
void Entity::ShutDown()
{
	is_alive = false;
}
bool Entity::IsAlive()
{
	return is_alive;
}
void Entity::Move(float dx, float dy)
{
	x += dx * speed;
	y += dy * speed;
}
void Entity::EMove(float dx, float dy)
{
	x += dx * speed;
	y += dy * speed;
}