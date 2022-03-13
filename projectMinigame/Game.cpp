#include "Game.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

Game::Game() {}
Game::~Game(){}

bool Game::Init()
{
	//Initialize SDL with all subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	//Create our window: title, x, y, w, h, flags
	Window = SDL_CreateWindow("Spaceship: arrow keys + space, f1: god mode", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (Window == NULL)
	{
		SDL_Log("Unable to create window: %s", SDL_GetError());
		return false;
	}
	//Create a 2D rendering context for a window: window, device index, flags
	Renderer = SDL_CreateRenderer(Window, -1, 0);
	if (Renderer == NULL)
	{
		SDL_Log("Unable to create rendering context: %s", SDL_GetError());
		return false;
	}
	//Initialize keys array
	for (int i = 0; i < MAX_KEYS; ++i)
		keys[i] = KEY_IDLE;

	//Load images
	if (!LoadImages())
		return false;

	//Init variables
	//size: 104x82
	Player.Init(20, WINDOW_HEIGHT >> 1, 64, 64, 5, NULL, NULL);
	idx_shot = 0;
	int w;
	SDL_QueryTexture(img_background, NULL, NULL, &w, NULL);
	Scene.Init(0, 0, w, WINDOW_HEIGHT, 4, NULL, NULL);
	god_mode = false;
	return true;
}
bool Game::LoadImages()
{
	if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		SDL_Log("IMG_Init, failed to init required png support: %s\n", IMG_GetError());
		return false;
	}
	img_background = SDL_CreateTextureFromSurface(Renderer, IMG_Load("background.png"));
	if (img_background == NULL) {
		SDL_Log("CreateTextureFromSurface failed: %s\n", SDL_GetError());
		return false;
	}
	img_player = SDL_CreateTextureFromSurface(Renderer, IMG_Load("lil_guy(South).png"));
	if (img_player == NULL) {
		SDL_Log("CreateTextureFromSurface failed: %s\n", SDL_GetError());
		return false;
	}
	img_shot = SDL_CreateTextureFromSurface(Renderer, IMG_Load("shot.png"));
	if (img_shot == NULL) {
		SDL_Log("CreateTextureFromSurface failed: %s\n", SDL_GetError());
		return false;
	}
	//Enemy texture
	img_Enemy = SDL_CreateTextureFromSurface(Renderer, IMG_Load("Enemy.png"));
	if (img_Enemy == NULL) {
		SDL_Log("CreateTextureFromSurface failed: %s\n", SDL_GetError());
		return false;
	}
	//Enemy texture
	return true;
}
void Game::Release()
{
	//Release images
	SDL_DestroyTexture(img_background);
	SDL_DestroyTexture(img_player);
	SDL_DestroyTexture(img_shot);
	SDL_DestroyTexture(img_Enemy);
	IMG_Quit();
	
	//Clean up all SDL initialized subsystems
	SDL_Quit();
}
bool Game::Input()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)	return false;
	}

	SDL_PumpEvents();
	const Uint8* keyboard = SDL_GetKeyboardState(NULL);
	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keyboard[i])
			keys[i] = (keys[i] == KEY_IDLE) ? KEY_DOWN : KEY_REPEAT;
		else
			keys[i] = (keys[i] == KEY_REPEAT || keys[i] == KEY_DOWN) ? KEY_UP : KEY_IDLE;
	}

	buttons = SDL_GetMouseState(&mouseX, &mouseY);

	return true;
}
bool Game::Update()
{
	//Read Input
	if (!Input())	return true;

	//Process Input
	float fx = 0, fy = 0;
	if (keys[SDL_SCANCODE_ESCAPE] == KEY_DOWN)	return true;
	if (keys[SDL_SCANCODE_F1] == KEY_DOWN)		god_mode = !god_mode;
	if (keys[SDL_SCANCODE_F2] == KEY_DOWN)		toggle_enemies = !toggle_enemies;
	if (keys[SDL_SCANCODE_W] == KEY_REPEAT && Player.GetY() > 0) fy = -1;
	if (keys[SDL_SCANCODE_S] == KEY_REPEAT && Player.GetY() < 685) fy = 1;
	if (keys[SDL_SCANCODE_A] == KEY_REPEAT && Player.GetX() > 0) fx = -1;
	if (keys[SDL_SCANCODE_D] == KEY_REPEAT && Player.GetX() < 920) fx = 1;
	if (buttons == SDL_BUTTON_LEFT) {
		int x, y, w, h;
		Player.GetRect(&x, &y, &w, &h);
		//size: 56x20
		//offset from player: dx, dy = [(29, 3), (29, 59)]
		Shots[idx_shot].Init(x, y, 12, 12, 10, (mouseX - x) / sqrt(pow(mouseY - y, 2) + pow(mouseX - x, 2)), (mouseY - y) / sqrt(pow(mouseY - y, 2) + pow(mouseX - x, 2)));
		idx_shot++;
		idx_shot %= MAX_SHOTS;
	}

	if (toggle_enemies == true && idx_Enemy < (MAX_ENEMIES-1)) {
		int val1 = rand() % 2, val2 = rand() % 2, val3 = rand() % WINDOW_WIDTH, val4 = rand() % WINDOW_HEIGHT, x = 0, y = 0;
		if (val1 == 0 && val2 == 0) {
			x = -50;
			y = val4;
			Enemy[idx_Enemy].Init(x, y, 49, 64, 1, (Player.GetX() - x) / sqrt(pow(Player.GetY() - y, 2) + pow(Player.GetX() - x, 2)), (Player.GetY() - y) / sqrt(pow(Player.GetY() - y, 2) + pow(Player.GetX() - x, 2)));
			idx_Enemy++;
			idx_Enemy %= MAX_ENEMIES;
		}
		if (val1 == 1 && val2 == 0) {
			x = WINDOW_WIDTH;
			y = val4;
			Enemy[idx_Enemy].Init(x, y, 49, 64, 1, (Player.GetX() - x) / sqrt(pow(Player.GetY() - y, 2) + pow(Player.GetX() - x, 2)), (Player.GetY() - y) / sqrt(pow(Player.GetY() - y, 2) + pow(Player.GetX() - x, 2)));
			idx_Enemy++;
			idx_Enemy %= MAX_ENEMIES;
		}
		if (val1 == 0 && val2 == 1) {
			y = -50;
			x = val3;
			Enemy[idx_Enemy].Init(x, y, 49, 64, 1, (Player.GetX() - x) / sqrt(pow(Player.GetY() - y, 2) + pow(Player.GetX() - x, 2)), (Player.GetY() - y) / sqrt(pow(Player.GetY() - y, 2) + pow(Player.GetX() - x, 2)));
			idx_Enemy++;
			idx_Enemy %= MAX_ENEMIES;
		}
		if (val1 == 1 && val2 == 1) {
			y = WINDOW_HEIGHT;
			x = val3;
			Enemy[idx_Enemy].Init(x, y, 49, 64, 1, (Player.GetX() - x) / sqrt(pow(Player.GetY() - y, 2) + pow(Player.GetX() - x, 2)), (Player.GetY() - y) / sqrt(pow(Player.GetY() - y, 2) + pow(Player.GetX() - x, 2)));
			idx_Enemy++;
			idx_Enemy %= MAX_ENEMIES;
		}
	}
	
	//Logic
	//Player update
	Player.Move(fx, fy);
	//Shots update
	for (int i = 0; i < MAX_SHOTS; ++i)
	{
		if (Shots[i].IsAlive())
		{
			Shots[i].Move(Shots[i].GetShotX(), Shots[i].GetShotY());
			if (Shots[i].GetX() > WINDOW_WIDTH)	Shots[i].ShutDown();
		}
	}
	//Enemy update
		for (int i = 0; i < idx_Enemy; i++) {
			int aux = 0;
			if (aux == 0) {
				Enemy[i].Move(((Player.GetX() + PLAYER_CENTER) - Enemy[i].GetX()) / sqrt(pow(Player.GetY() - Enemy[i].GetY(), 2) + pow((Player.GetX() + PLAYER_CENTER) - Enemy[i].GetX(), 2)), (Player.GetY() - Enemy[i].GetY()) / sqrt(pow(Player.GetY() - Enemy[i].GetY(), 2) + pow((Player.GetX() + PLAYER_CENTER) - Enemy[i].GetX(), 2)));
			}
			//if ((Player.GetX() + PLAYER_CENTER) - (Enemy[i].GetX()) <= 20 || (Player.GetY()) - (Enemy[i].GetY()) <= 20 || (Player.GetX() + PLAYER_CENTER) - (Enemy[i].GetX()) >= -20 || (Player.GetY()) - (Enemy[i].GetY()) >= -20) {
			//	//Enemy[i].Move(Enemy[i].GetX(), Enemy[i].GetY());
			//	Enemy[i].Stop();
			//	aux = 1;
			//}
		}
		
	return false;
}
void Game::Draw()
{
	SDL_Rect rc;

	//Set the color used for drawing operations
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
	//Clear rendering target
	SDL_RenderClear(Renderer);

	//God mode uses red wireframe rectangles for physical objects
	if (god_mode) SDL_SetRenderDrawColor(Renderer, 192, 0, 0, 255);

	//Draw scene
	Scene.GetRect(&rc.x, &rc.y, &rc.w, &rc.h);
	SDL_RenderCopy(Renderer, img_background, NULL, &rc);
	rc.x += rc.w;
	SDL_RenderCopy(Renderer, img_background, NULL, &rc);
	
	//Draw player
	Player.GetRect(&rc.x, &rc.y, &rc.w, &rc.h);
	SDL_RenderCopy(Renderer, img_player, NULL, &rc);
	if (god_mode) SDL_RenderDrawRect(Renderer, &rc);

	//Draw shots
	for (int i = 0; i < MAX_SHOTS; ++i)
	{
		if (Shots[i].IsAlive())
		{
			Shots[i].GetRect(&rc.x, &rc.y, &rc.w, &rc.h);
			SDL_RenderCopy(Renderer, img_shot, NULL, &rc);
			if (god_mode) SDL_RenderDrawRect(Renderer, &rc);
		}
	}

	//Draw enemies
	for (int i = 0; i < MAX_ENEMIES; ++i)
	{
		if (Enemy[i].IsAlive())
		{
			Enemy[i].GetRect(&rc.x, &rc.y, &rc.w, &rc.h);
			SDL_RenderCopy(Renderer, img_Enemy, NULL, &rc);
			if (god_mode) SDL_RenderDrawRect(Renderer, &rc);
		}
	}


	//Update screen
	SDL_RenderPresent(Renderer);

	SDL_Delay(10);	// 1000/10 = 100 fps max
}