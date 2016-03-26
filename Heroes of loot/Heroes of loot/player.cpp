#include "player.h"

void Player::Control(Characters hero, Game * game)
{
	left = 0;
	top = 12 * 4 * hero;
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		dir = LEFT;
		speed = game->heroSpeed;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		dir = RIGHT;
		speed = game->heroSpeed;
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		dir = UP;
		speed = game->heroSpeed;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		dir = DOWN;
		speed = game->heroSpeed;
	}
	if (Keyboard::isKeyPressed(Keyboard::X)){
		isShoot = true;
		game->shoot.play();
	}
	if ((Keyboard::isKeyPressed(Keyboard::Tab)) && (game->potions > 0)) {
		game->turboSpeed = true;
		game->heroSpeed = game->heroSpeed * 2;
		game->potions--;
	}
}

void Player::Update(float time, Game * game)
{
	if ((game->health < 15) && (game->hearts > 0))
	{
		game->health = 100;
		game->hearts--;
	}
	if (shock)
	{
		if (ScoreAnimation(time, points))
			shock = false;
		else
		{
			sprite.setColor(Color(0, 0, 0));
		}
	}
	else
		sprite.setColor(Color(255, 255, 255));
	Collision(game, time);
	switch (dir)
	{
	case RIGHT: dx = speed; dy = 0; break;
	case LEFT: dx = -speed; dy = 0; break;
	case UP: dx = 0; dy = -speed; break;
	case DOWN: dx = 0; dy = speed; break;

	}
	x += dx * time;
	y += dy * time;

	speed = 0;
	current_frame += time * 0.005;
	if (current_frame >= 2)
		current_frame = 0;
	sprite.setTextureRect(IntRect(left + 12 * (int)current_frame, top + 12 * dir, 12, 12));
	sprite.setPosition(x, y);
	if (game->health <= 0)
		life = false;
}

void Player::Collision(Game * game, float time)
{
	for (int i = 0; i < obj.size(); i++)//проходимся по объектам
		if (GetRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
		{
			if ((obj[i].name == "solid") || (obj[i].name == "rill") || ((obj[i].name == "door") && (game->key == 0)))//если встретили препятствие
			{
				if (dy > 0) //если мы шли вниз,
					y = obj[i].rect.top - h;//то стопорим координату игрек персонажа.
				if (dy < 0)
					y = obj[i].rect.top + obj[i].rect.height;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх
				if (dx > 0)
					x = obj[i].rect.left - w; // если идем вправо, то координата Х равна стена(символ 0) минус ширина персонажа
				if (dx < 0)
					x = obj[i].rect.left + obj[i].rect.width;//аналогично идем влево
				if ((obj[i].name == "rill") && (game->cup > 0))
				{
					game->cup--;
					game->gameEnd = true;
				}
			}
			else if ((obj[i].name == "bonus") || (obj[i].name == "diamond") || (obj[i].name == "chest"))
			{
				obj.erase(obj.begin() + i);
				game->findCoins = true;
			}
			else if (obj[i].name == "trone")	
			{
				game->clue = true;
				game->info.play();
			}
			else if (obj[i].name == "heart")
			{
				if (obj[i].find)
				{
					obj.erase(obj.begin() + i);
					game->hearts++;
				}
				else 
					obj[i].find = true;
			}
			else if (obj[i].name == "potion")
			{
				obj.erase(obj.begin() + i);
				game->potions++;
				game->findPotion = true;
				game->info.play();
			}
			else if (obj[i].name == "key")
			{
				obj.erase(obj.begin() + i);
				game->key = 1;
				game->findKey = true;
				game->info.play();
			}
			else if (obj[i].name == "cup")
			{
				obj.erase(obj.begin() + i);
				game->cup++;
			}
			else if ((obj[i].name == "door") && (game->key == 1))
			{
				game->key = 1;
				game->restart = true;
				if ((game->level + 1) <= game->end_level)
				{
					game->level++; 
				}
				else
				{
					game->gameEnd = true;
				}
			}
		}
}

bool Player::ScoreAnimation(float time, Sprite & sprite)
{
	if (speed_points > 0)
	{
		sprite.setPosition(x, y - h + time * speed_points);
		speed_points -= time * 0.001;
		return false;
	}
	else
	{
		speed_points = 1;
		return true;
	}
}

Vector2f Player::GetPos()
{
	return Vector2f(x, y);
}

FloatRect Player::GetRect()
{
	return FloatRect(x, y, w, h);
}