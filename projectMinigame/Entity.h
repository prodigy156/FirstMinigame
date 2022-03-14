#pragma once
class Entity
{
public:
	Entity();
	~Entity();

	void Init(int posx, int posy, int w, int h, int s, float posx2, float posy2);
	void GetRect(int *posx, int *posy, int *w, int *h);
	void SetX(int posx);
	int  GetX();
	int  GetY();
	float  GetShotX();
	float  GetShotY();
	int  GetWidth();
	void ShutDown(); 
	bool IsAlive();
	void Move(float dx, float dy);
	void Stop();
    int GetEnemyHP();
	void EnemyHPloss(int dmg);
	void ResetEnemyPos();

private:
	float x, y;
	int width, height, HP;
	float speed;
	bool is_alive;
	float x_shot, y_shot; //Position for bullets to travel to (should be given as (y2-y1) / (x2-x1))
};

