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

	void interactionWithMap()//�-��� �������������� � ������
	{
		for (int i = y / 60; i < (y + h) / 60; i++)//���������� �� ��������, �������������� � �������
			for (int j = x / 60; j<(x + w) / 60; j++)//��� ����� �� 60, ��� ����� �������� ����� ���������, � ������� �������� �������������. (�� ���� ������ ������� 32*32, ������� ����� ������������ ������ �� ���������� ���������). � j<(x + w) / 32 - ������� ����������� ��������� �� ����. �� ���� ���������� ������ ������� ��������, ������� ������������� � ����������. ����� ������� ���� � ����� ����� ������� �� ����, ������� �� �� ������ �������� (���������������� � ������), �� ������� �������� (���������������� � ������)
			{
				if ((TileMap[i][j] == '0') || (TileMap[i][j] == '1') || (TileMap[i][j] == '2') || (TileMap[i][j] == '3') || (TileMap[i][j] == 'f'))//���� ��� ��������� ������������� ������� 0 (�����), �� ��������� "����������� ��������" ���������:
				{
					if (dy>0)//���� �� ��� ����,
						y = i * 60 - h;//�� �������� ���������� ����� ���������. ������� �������� ���������� ������ ���������� �� �����(�����) � ����� �������� �� ������ ������� ���������.
					if (dy<0)
						y = i * 60 + 60;//���������� � ������� �����. dy<0, ������ �� ���� ����� (���������� ���������� ������)
					if (dx>0)
						x = j * 60 - w;//���� ���� ������, �� ���������� � ����� ����� (������ 0) ����� ������ ���������
					if (dx < 0)
						x = j * 60 + 60;//���������� ���� �����
					stop = true;
				}
			}
	}
};

#endif
