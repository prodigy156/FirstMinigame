#pragma once
class Entity
{
public:
	Entity();
	~Entity();

	void Init(int posx, int posy, int w, int h, int s, int posx2, int posy2);
	void GetRect(int *posx, int *posy, int *w, int *h);
	void SetX(int posx);
	int  GetX();
	int  GetY();
	int  GetShotX();
	int  GetShotY();
	int  GetWidth();
	void ShutDown(); 
	bool IsAlive();
	void Move(float dx, float dy);
	void EMove(float dx, float dy);

private:
	float x, y;
	int width, height;
	float speed;
	bool is_alive;
	int x_shot, y_shot; //Position for bullets to travel to (should be given as (y2-y1) / (x2-x1))
};

