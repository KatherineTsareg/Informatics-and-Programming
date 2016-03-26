#ifndef game_h
#define game_h

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "level.h"


using namespace sf;
using namespace std;

const Vector2f WINDOW_SIZE = { 1280, 720 };

typedef enum Characters
{
	ELF,
	WARRIOR,
	WIZARD,
	VALKYRIE
}character;

typedef enum Evil
{
	GHOST,
	CYCLOP,
	DEMON,
	FLASH,
	MINOTAUR
}evil;

typedef enum Direction
{
	RIGHT,
	LEFT,
	UP,
	DOWN
}direction;

struct Statistic
{
	Sprite hero_health;
	Sprite scale;
	Sprite coin;
	Sprite info;
	Sprite cup;
	Text score;
};

struct Graphics
{
	Texture levelTexture;
	Sprite torch;
	Sprite queen;
	Statistic statistic;
	Sprite infoBlock;
	Sprite door;
	Sprite reward;
	Sprite dark;
	Sprite heart;
	Sprite potion;
	Sprite key;
	Sprite coins;
};

struct Game 
{
	const int end_level = 7;
	float heroSpeed = 0.2f;
	
	float time, current_frame = 0;
	bool restart = false;
	int level = 7;
	int health = 100;
	int money = 0;
	int xp;
	int hearts = 0;
	int potions = 0;
	int key = 0;
	bool gameEnd = false;
	bool findHeart = false;
	bool findKey = false;
	bool findPotion = false;
	bool turboSpeed = false;
	bool queenLvl = false;
	bool clue = false;
	bool findCoins = false;
	float currentFrameQueen = 0;
	int cup = 0;
	float turboTime = 10;
	float infoTime = 2;
	float coinsDistance = 0;
	Graphics graphics;
	Characters character = ELF;
	Evil evil;
	View view;
	Music menuTheme, gameTheme, ouch, coins, shoot, info;
};

Evil GetEvilType(const string &s);

#endif