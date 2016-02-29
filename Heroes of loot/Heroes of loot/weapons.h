#ifndef weap_h
#define weap_h
#include <SFML/Graphics.hpp>

using namespace sf;

class Weapons {
private:
	float x, y;
public:
	bool life;
	float w, h, dx, dy;
	float speed = 0.2;
	int dir;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	Weapons(String F, float W, float H, float time, float X, float Y, int player_dir) {
		File = F;
		w = W; h = H;
		image.loadFromFile("images/" + File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, w, h));
		x = X;
		y = Y;
		dir = player_dir;
		speed = 0.8;
		life = true;
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

		interactionWithMap();
		
		sprite.setPosition(x + w/2, y + h/2);
		
	}
	bool IsOnTheMap()
	{
		if ((x >= 0) && (y >= 0) && (x <= 1280) && (y <= 650))
			return true;
		else
			return false;
	}

	void interactionWithMap()//ф-ция взаимодействия с картой
	{
		int i = x / 60;
		int j = y / 60;
		/*if (life && IsOnTheMap())
		{
			if ((TileMap[i][j] == '0') || (TileMap[i][j] == '1') || (TileMap[i][j] == '2') || (TileMap[i][j] == '3') || (TileMap[i][j] == 'f')) 
				life = false;
		}*/
	}
};

#endif
