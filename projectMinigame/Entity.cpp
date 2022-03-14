#include "Entity.h"

Entity::Entity()
{
	is_alive = false;
}
Entity::~Entity()
{
}
void Entity::Init(int posx, int posy, int w, int h, int s, float posx2, float posy2) 
{
	x = posx;
	y = posy;
	HP = 40;
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
float Entity::GetShotX()
{
	return x_shot;
}
float Entity::GetShotY()
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
void Entity::Stop()
{
	speed = 0;
}
int Entity::GetEnemyHP()
{
	return HP;
}
void Entity::EnemyHPloss(int dmg)
{
	HP -= dmg;
}
void Entity::ResetEnemyPos()
{
	x = -100;
	y = -100;
}


