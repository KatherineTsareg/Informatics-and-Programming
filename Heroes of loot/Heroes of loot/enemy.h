#ifndef Enemy_H
#define Enemy_H
#include <SFML/Graphics.hpp>
#include "map.h"

using namespace sf;

class  Enemy {
private:
	float x, y;
public:
	float w, h, dx, dy;
	float speed = 0.2;
	int dir = 0;
	bool stop = false;
	float move_time = 0;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	Enemy(String F, float X, float Y, float W, float H) {
		File = F;
		w = W; h = H;
		image.loadFromFile("images/" + File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
		sprite.setTextureRect(IntRect(0, 0, w, h));
	}
	void update(float time)
	{
		interactionWithMap();
		if (stop) 
		{
			dir = rand() % 4;
			stop = false;
		}
		if (move_time >= 3)
		{
			dir = rand() % 4;
			move_time -= 3;
		}

		switch (dir)
		{
		case 0: dx = speed; dy = 0; break;
		case 1: dx = -speed; dy = 0; break;
		case 2: dx = 0; dy = speed; break;
		case 3: dx = 0; dy = -speed; break;
		}
		x += dx*time;
		y += dy*time;
		move_time += time * 0.0001;

		sprite.setPosition(x, y);
	}

	void interactionWithMap()//ф-ция взаимодействия с картой
	{
		for (int i = y / 60; i < (y + h) / 60; i++)//проходимся по тайликам, контактирующим с игроком
			for (int j = x / 60; j<(x + w) / 60; j++)//икс делим на 60, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
			{
				if ((TileMap[i][j] == '0') || (TileMap[i][j] == '1') || (TileMap[i][j] == '2') || (TileMap[i][j] == '3') || (TileMap[i][j] == 'f'))//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
				{
					if (dy>0)//если мы шли вниз,
						y = i * 60 - h;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
					if (dy<0)
						y = i * 60 + 60;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
					if (dx>0)
						x = j * 60 - w;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
					if (dx < 0)
						x = j * 60 + 60;//аналогично идем влево
					stop = true;
				}
			}
	}
};

#endif
