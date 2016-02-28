#ifndef MY_H
#define MY_H
#include <SFML/Graphics.hpp>
#include "map.h"

using namespace sf;

class Player {
private:
	float x, y;
public:
	float w, h, dx, dy, speed = 0;
	int dir = 0;
	bool isShoot, life;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	Player(String F, float X, float Y, float W, float H) {
		File = F;
		w = W; 
		h = H;
		image.loadFromFile("images/" + File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
		sprite.setTextureRect(IntRect(0, 0, w, h));
	}
	void control()
	{	///////////////////////////////////////////���������� ���������� � ���������////////////////////////////////////////////////////////////////////////
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			dir = 1;
			speed = 0.2;
			sprite.setTextureRect(IntRect(dir * 50, 0, 50, 50));
			getplayercoordinateforview(getplayercoordinateX(), getplayercoordinateY());//�������� ���������� ������ � ������� ���������� �������
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			dir = 0;
			speed = 0.2;
			sprite.setTextureRect(IntRect(dir * 50, 0, 50, 50));
			getplayercoordinateforview(getplayercoordinateX(), getplayercoordinateY());
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			dir = 3;
			speed = 0.2;
			sprite.setTextureRect(IntRect(dir * 50, 0, 50, 50));
			getplayercoordinateforview(getplayercoordinateX(), getplayercoordinateY());
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			dir = 2;
			speed = 0.2;
			sprite.setTextureRect(IntRect(dir * 50, 0, 50, 50));
			getplayercoordinateforview(getplayercoordinateX(), getplayercoordinateY());
		}
		if (Keyboard::isKeyPressed(Keyboard::X))
		{
			isShoot = true;
		}
		
		
	}
	void update(float time)
	{
		switch (dir)
		{
		case 0: dx = speed; dy = 0; break;
		case 1: dx = -speed; dy = 0; break;
		case 2: dx = 0; dy = speed; break;
		case 3: dx = 0; dy = -speed; break;
		}
		x += dx*time;
		y += dy*time;

		speed = 0;
		sprite.setPosition(x, y);
		interactionWithMap();
	}

	void interactionWithMap()//�-��� �������������� � ������
	{

		for (int i = y / 60; i < (y + h) / 60; i++)//���������� �� ��������, �������������� � �������, �� ���� �� ���� ����������� ������� 32*32, ������� �� ���������� � 9 �����. ��� ������� ������� ����.
			for (int j = x / 60; j < (x + w) / 60; j++)//��� ����� �� 60, ��� ����� �������� ����� ���������, � ������� �������� �������������. (�� ���� ������ ������� 32*32, ������� ����� ������������ ������ �� ���������� ���������). � j<(x + w) / 32 - ������� ����������� ��������� �� ����. �� ���� ���������� ������ ������� ��������, ������� ������������� � ����������. ����� ������� ���� � ����� ����� ������� �� ����, ������� �� �� ������ �������� (���������������� � ������), �� ������� �������� (���������������� � ������)
			{
				if ((TileMap[i][j] == '0') || (TileMap[i][j] == '1') || (TileMap[i][j] == '2') || (TileMap[i][j] == '3') || (TileMap[i][j] == 'f'))//���� ��� ��������� ������������� ������� 0 (�����), �� ��������� "����������� ��������" ���������:
				{
					if (dy>0)//���� �� ��� ����,
					{
						y = i * 60 - h;//�� �������� ���������� ����� ���������. ������� �������� ���������� ������ ���������� �� �����(�����) � ����� �������� �� ������ ������� ���������.
					}
					if (dy<0)
					{
						y = i * 60 + 60;//���������� � ������� �����. dy<0, ������ �� ���� ����� (���������� ���������� ������)
					}
					if (dx>0)
					{
						x = j * 60 - w;//���� ���� ������, �� ���������� � ����� ����� (������ 0) ����� ������ ���������
					}
					if (dx < 0)
					{
						x = j * 60 + 60;//���������� ���� �����
					}
				}
				if ((TileMap[i][j] == 'b') || (TileMap[i][j] == 'd') || (TileMap[i][j] == 'c')) {
					TileMap[i][j] = ' ';
				}
			}
	}

	float getplayercoordinateX() {	//���� ������� ����� �������� ���������� �	
		return x;
	}
	float getplayercoordinateY() {	//���� ������� ����� �������� ���������� Y 	
		return y;
	}
};

#endif
