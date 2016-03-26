#include "weapons.h"

void Weapons::update(float time, FloatRect heroRect)
{
	interactionWithMap();
	switch (dir)
	{
	case RIGHT: 
		dx = speed; 
		dy = 0; 
		break;
	case LEFT: 
		dx = -speed; 
		dy = 0;
		break;
	case DOWN: 
		dx = 0; 
		dy = speed; 
		break;
	case UP: 
		dx = 0; 
		dy = -speed;
		break;
	}

	x += dx * time;
	y += dy * time;
	
	sprite.setPosition(x + heroRect.width / 2, y + heroRect.height / 2);
	sprite.rotate(time * 0.2);
}

void Weapons::interactionWithMap()//ф-ция взаимодействия с картой
{
	for (int i = 0; i < obj.size(); i++)//проходимся по объектам
		if (GetRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
		{
			life = false;
		}
}

sf::FloatRect Weapons::GetRect()
{
	return sf::FloatRect(x, y, w, h);
}