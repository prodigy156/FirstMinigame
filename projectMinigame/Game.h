#pragma once

#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

#include "SDL_Mixer/include/SDL_Mixer.h"
#pragma comment( lib, "SDL_Mixer/libx86/SDL2_MIxer.lib" )

#include "Entity.h"

#define WINDOW_WIDTH	1024
#define WINDOW_HEIGHT	768
#define MAX_KEYS		256
#define MAX_SHOTS		128
#define MAX_ENEMIES		128 //This number must be one higher of the desired enemies
#define PLAYER_CENTER   20
#define BULLET_DELAY	10


class Game
{
public:
	Game();
	~Game();

	bool Init();
	bool LoadImages();
	void Release();
	
	bool Input();
	bool Update();
	void Draw();

private:
	SDL_Window *Window;
	SDL_Renderer *Renderer;
	SDL_Texture *img_background, *img_player_N, * img_player_NE, * img_player_NW, * img_player_W, * img_player_SW, * img_player_S, * img_player_SE, * img_player_E, *img_shot, *img_Enemy;
	Uint32 buttons; 

	Entity Player, Shots[MAX_SHOTS], Scene, Enemy[MAX_ENEMIES];
	int idx_shot;
	int idx_Enemy;

	int mouseX, mouseY;

	bool god_mode;

	bool toggle_enemies = true;

	int bullet_delay_c = 0;

	enum KEY_STATE { KEY_IDLE, KEY_DOWN, KEY_REPEAT, KEY_UP	};
	KEY_STATE keys[MAX_KEYS]; 
};
