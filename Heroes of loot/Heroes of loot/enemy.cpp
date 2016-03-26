#include "enemy.h"

void Enemy::Update(float time, const float player_x, const float player_y)
{
	if (time * 0.01 > 2) { time = 20; }
	if (health <= 0)
		life = false;
	if (stop_move){
		dir = rand() % 4;
		stop_move = false;
	}
	if (move_time >= 3){
		dir = rand() % 4;
		move_time -= 3;
	}
	
	switch (dir)
	{
	case RIGHT: dx = speed; dy = 0; sprite.setTextureRect(IntRect(39, 64 + evil * 12 * 2 + 12 * dir, 12, 12)); break;
	case LEFT: dx = -speed; dy = 0; sprite.setTextureRect(IntRect(39, 64 + evil * 12 * 2 + 12 * dir, 12, 12)); break;
	case UP: dx = 0; dy = speed; break;
	case DOWN: dx = 0; dy = -speed; break;
	}

	x += dx * time;
	y += dy * time;
	Collision();
	
	move_time += time * 0.0001f;
	sprite.setPosition(x, y);
}

void Enemy::Collision()
{
	for (int i = 0; i < obj.size(); i++)
		if (GetRect().intersects(obj[i].rect)){
			if ((obj[i].name == "solid") || (obj[i].name == "door") || (obj[i].name == "none")) {
				stop_move = true;
				if (dy > 0) { y = obj[i].rect.top - h; }
				if (dy < 0) { y = obj[i].rect.top + obj[i].rect.height; }
				if (dx > 0) { x = obj[i].rect.left - w; }
				if (dx < 0) { x = obj[i].rect.left + obj[i].rect.width; }
			}
		}
}

FloatRect Enemy::GetRect()
{
	return FloatRect(x, y, w, h);
}

void Enemy::ShiftWhenCrossing(FloatRect hero_rect)
{
	if ((dx > 0) || (dx < 0)) {
		if (x > hero_rect.left) x = hero_rect.left + hero_rect.width;
		else x = hero_rect.left - w;
	}
	if ((dy > 0) || (dy < 0))
	{
		if (y > hero_rect.top) y = hero_rect.top + hero_rect.height;
		else y = hero_rect.top - h;
	}
	dir = abs(dir - 3);
}