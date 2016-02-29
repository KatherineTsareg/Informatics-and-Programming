#ifndef MY_H
#define MY_H

#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

class Player {
private:
	float x, y;
public:
	float w, h, dx, dy, speed = 0;
	int health = 100, dir = 0;
	int  money = 10;
	bool isShoot, life;
	Image image;
	Texture texture;
	Sprite sprite;
	Vector2f pos;
	vector<Object> obj;
	Player(String F, Level &lev, float X, float Y, float W, float H) {
		image.loadFromFile("images/" + F);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		w = W;
		h = H;
		x = X;
		y = Y;
		sprite.setTextureRect(IntRect(0, 0, w, h));
		obj = lev.GetAllObjects();
		GetPlayercoordinateForView(x, y);
	}
	
	void control()
	{	///////////////////////////////////////////���������� ���������� � ���������////////////////////////////////////////////////////////////////////////
		pos = { x, y };
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			dir = 1;
			speed = 0.2;
			sprite.setTextureRect(IntRect(dir * 50, 0, w, h));
			GetPlayercoordinateForView(x, y);//�������� ���������� ������ � ������� ���������� �������
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			dir = 0;
			speed = 0.2;
			sprite.setTextureRect(IntRect(dir * 50, 0, w, h));
			GetPlayercoordinateForView(x, y);
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			dir = 3;
			speed = 0.2;
			sprite.setTextureRect(IntRect(dir * 50, 0, w, h));
			GetPlayercoordinateForView(x, y);
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			dir = 2;
			speed = 0.2;
			sprite.setTextureRect(IntRect(dir * 50, 0, w, h));
			GetPlayercoordinateForView(x, y);
		}
		if (Keyboard::isKeyPressed(Keyboard::X))
		{
			isShoot = true;
		}
	}
	void update(float time)
	{
		Collision();
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
	}
	
	void Collision()
	{
		FloatRect rect{ x, y, w, h };
		for (int i = 0; i < obj.size(); i++)//���������� �� ��������
			if (rect.intersects(obj[i].rect))//��������� ����������� ������ � ��������
			{
				if (obj[i].name == "solid")//���� ��������� �����������
				{
					if (dy>0) //���� �� ��� ����,
						y = obj[i].rect.top - h;//�� �������� ���������� ����� ���������.
					if (dy<0)
						y = obj[i].rect.top + obj[i].rect.height ;//���������� � ������� �����. dy<0, ������ �� ���� �����
					if (dx>0)
						x = obj[i].rect.left - w; // ���� ���� ������, �� ���������� � ����� �����(������ 0) ����� ������ ���������
					if (dx<0)
						x = obj[i].rect.left + obj[i].rect.width ;//���������� ���� �����
				}
				else if ((obj[i].name == "bonus") || (obj[i].name == "diamond") || (obj[i].name == "chest"))
				{
					obj.erase(obj.begin() + i);
					money += 10;
				}
			}
	}
	Vector2f GetHeroPos()
	{
		return Vector2f(x, y);
	}
};
#endif
