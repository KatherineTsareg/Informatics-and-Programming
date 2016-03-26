#ifndef Enemy_H
#define Enemy_H
#include <SFML/Graphics.hpp>
#include "level.h"
#include "game.h"
#include <cmath>

using namespace sf;
using namespace std;

class  Enemy {
private:
	float x, y;
public:
	float w, h, dx, dy, speed, move_time = 0;
	int  dir = 0;
	bool stop_move, life = false;
	vector <Object> obj;
	Sprite sprite;
	Evil evil;
	float health;

	Enemy(Texture & texture, Level & lvl, Evil enemy_name, float X, float Y, float W, float H)
	{
		w = W; 
		h = H;
		x = X; 
		y = Y;
		evil = enemy_name;
		speed = 0.1f + 0.02f * evil;
		health = 20 * (evil + 1);

		sprite.setTexture(texture);
		sprite.scale(4.0f, 4.0f);
		sprite.setTextureRect(IntRect(39, 64 + evil * 12 * 2 , 12, 12));
		obj = lvl.GetAllObjects();
		life = true;
	}
	void Enemy::Update(float time, const float player_x, const float player_y);
	void Enemy::Collision();
	FloatRect Enemy::GetRect();
	void Enemy::ShiftWhenCrossing(FloatRect hero_rect);

};

#endif