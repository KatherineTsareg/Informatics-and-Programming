#ifndef weap_h
#define weap_h
#include <SFML/Graphics.hpp>
#include "level.h"
#include "game.h"

using namespace sf;

class Weapons {
private:
	float x, y;
public:
	bool life;
	float dx, dy;
	int w, h;
	float speed = 0.2f;
	IntRect rect;
	Direction dir;
	Texture texture;
	Sprite sprite;
	std::vector<Object> obj;
	Weapons(Texture & texture, Characters hero, Level &lvl, float time, Vector2f player_pos, Direction player_dir) {
		switch (hero)
		{
		case ELF:
			w = 3;
			h = 10;
			break;
		case WARRIOR:
			w = 3;
			h = 10;
			break;
		case WIZARD:
			w = 4;
			h = 4;
			break;
		case VALKYRIE:
			w = 5;
			h = 10;
		}
		rect = { 25, hero * 12 * 4 + 12, w , h };
		sprite.scale(4.0f, 4.0f);
		sprite.setOrigin((float)w / 2.0f, (float)h / 2.0f);
		sprite.setTexture(texture);
		sprite.setTextureRect(rect);
		x = player_pos.x;
		y = player_pos.y;
		dir = player_dir;
		speed = 0.4f;
		life = true;
		obj = lvl.GetObjects("solid");
	}
	void Weapons::update(float time, FloatRect heroRect);
	void Weapons::interactionWithMap();
	FloatRect Weapons::GetRect();
};

#endif
