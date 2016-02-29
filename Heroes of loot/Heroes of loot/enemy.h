#ifndef Enemy_H
#define Enemy_H
#include <SFML/Graphics.hpp>

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
	std::vector<Object> obj;
	Enemy(String F, Level & lvl, float X, float Y, float W, float H) {
		File = F;
		w = W; h = H;
		image.loadFromFile("images/" + File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
		sprite.setTextureRect(IntRect(0, 0, w, h));
		obj = lvl.GetObjects("solid");
	}
	void update(float time)
	{
		Collision();
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
	
	FloatRect GetRect()
	{
		return FloatRect(x, y, w, h);
	}

	void Collision()//�-��� �������������� � ������
	{
		for (int i = 0; i<obj.size(); i++)//���������� �� ��������
			if (GetRect().intersects(obj[i].rect))//��������� ����������� ������ � ��������
			{
				if (obj[i].name == "solid")//���� ��������� �����������
				{
					stop = true;
					if (dy>0) //���� �� ��� ����,
						y = obj[i].rect.top - h;//�� �������� ���������� ����� ���������.
					if (dy<0) 
						y = obj[i].rect.top + obj[i].rect.height;//���������� � ������� �����. dy<0, ������ �� ���� �����
					if (dx>0) 
						x = obj[i].rect.left - w; // ���� ���� ������, �� ���������� � ����� �����(������ 0) ����� ������ ���������
					if (dx<0) 
						x = obj[i].rect.left + obj[i].rect.width;//���������� ���� �����
				}
			}
	}
};

#endif