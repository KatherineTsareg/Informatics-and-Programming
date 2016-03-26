#ifndef player_h
#define player_h

#include <SFML/Graphics.hpp>
#include <vector>
#include "level.h"
#include "game.h"

using namespace sf;
using namespace std;

class Player {
private:
	float x, y;
public:
	float left, top, w, h, dx, dy, current_frame = 0, speed = 0;
	float speed_points = 1;
	bool isShoot, life, shock = false;
	Direction dir;
	Sprite sprite, points;
	Vector2f pos;
	vector<Object> obj;
	Player(Texture &texture, Level &lev, float X, float Y, float W, float H) {
		sprite.setTexture(texture);
		sprite.scale(4.0f, 4.0f);
		points.setTexture(texture);
		points.scale(4.0f, 4.0f);
		points.setTextureRect(IntRect(71, 0, 8, 7));
		w = W;
		h = H;
		x = X;
		y = Y;
		obj = lev.GetAllObjects();
		life = true;
	}
	void Player::Control(Characters hero, Game * game);
	void Player::Update(float time, Game * game);
	void Player::Collision(Game * game, float time);
	bool Player::ScoreAnimation(float time, Sprite & sprite);
	Vector2f Player::GetPos();
	FloatRect Player::GetRect();
};
#endif
