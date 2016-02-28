#include <SFML/Graphics.hpp>
#include <iostream> 
#include <vector>
#include <list>
#include "map.h"
#include "view.h"
#include "player.h"
#include "enemy.h"
#include "weapons.h"

using namespace sf;
using namespace std;

struct GraphicResource {
	Image* im;
	Texture* tex;
	Sprite* spr;
};

void CleanTheMemory(GraphicResource & gr) {
	delete gr.im;
	delete gr.tex;
	delete gr.spr;
}

GraphicResource MakeTheSprite(String fileName) {
	GraphicResource gr;
	gr.im = new Image();
	gr.tex = new Texture();
	gr.spr = new Sprite();
	gr.im->loadFromFile("images/" + fileName);
	gr.tex->loadFromImage(*gr.im);
	gr.spr->setTexture(*gr.tex);
	return gr;
}

void draw_map(RenderWindow &window, Sprite &s_map, Sprite &s_fire, Sprite &s_bonus, float &current_frame, float time)
{
	for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == 'f')
			{
				if (current_frame > 3)
					current_frame -= 3;
				s_fire.setTextureRect(IntRect(60 * (int)current_frame, 0, 60, 180));
				s_fire.setPosition(j * 60, i * 60 - 120);
				window.draw(s_fire);
			}
			else if (TileMap[i][j] == '-')
			{}
			else if (TileMap[i][j] == 'c') {
				s_bonus.setTextureRect(IntRect(60, 120, 60, 60));
				s_bonus.setPosition(j * 60, i * 60);
				window.draw(s_bonus);
			}
			else if ((TileMap[i][j] == 'd') || (TileMap[i][j] == 'b')) {
				if (current_frame > 3)
					current_frame -= 3;
				if (TileMap[i][j] == 'd')
					s_bonus.setTextureRect(IntRect(60 * (int)current_frame, 0, 60, 60));
				else
					s_bonus.setTextureRect(IntRect(60 * (int)current_frame, 60, 60, 60));
				s_bonus.setPosition(j * 60, i * 60);
				window.draw(s_bonus);
			}
			else
			{
				if (TileMap[i][j] == ' ')
					s_map.setTextureRect(IntRect(240, 0, 60, 60));
				if ((TileMap[i][j] == '0'))
					s_map.setTextureRect(IntRect(0, 0, 60, 60));
				if (TileMap[i][j] == '1')
					s_map.setTextureRect(IntRect(60, 0, 60, 60));
				if ((TileMap[i][j] == '2'))
					s_map.setTextureRect(IntRect(120, 0, 60, 60));
				if ((TileMap[i][j] == '3'))
					s_map.setTextureRect(IntRect(180, 0, 60, 60));
				if ((TileMap[i][j] == 's'))
					s_map.setTextureRect(IntRect(300, 0, 60, 60));
				s_map.setPosition(j * 60, i * 60);
				window.draw(s_map);
			}
		}
	current_frame += 0.005 * time;
}

int main()
{
	RenderWindow window(VideoMode(1280, 650), "Heroes of Loot");

	Player hero("wizard.psd", 640, 380, 50, 50);
	view.reset(FloatRect(0, 0, 1280, 650));
	
	vector<Enemy*> ghosts;
	vector<Enemy*>::iterator it_e;

	vector<Weapons*> weapons;
	vector<Weapons*>::iterator it_w;
	
	ghosts.push_back(new Enemy("enemies.psd", 500, 500, 50, 50));
	ghosts.push_back(new Enemy("enemies.psd", 600, 600, 50, 50));
	ghosts.push_back(new Enemy("enemies.psd", 600, 500, 50, 50));
	
	GraphicResource stMap = MakeTheSprite("map1.psd");
	Sprite s_map = *stMap.spr;
	GraphicResource stFire = MakeTheSprite("fire2.psd");
	Sprite s_fire = *stFire.spr;
	GraphicResource stBonus = MakeTheSprite("bonus.psd");
	Sprite s_bonus = *stBonus.spr;

	float current_frame = 0;
	Clock clock;

	randomMapGenerate('d', 8);
	randomMapGenerate('b', 10);
	randomMapGenerate('c', 4);

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time /800;
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape))
				window.close();
			if (hero.isShoot == true) 
			{
				weapons.push_back(new Weapons("weapons.psd", 20, 20, time, hero.getplayercoordinateX(), hero.getplayercoordinateY(), hero.dir));
				hero.isShoot = false;
			}
		}
		hero.control();
		hero.update(time);
		for (it_e = ghosts.begin(); it_e != ghosts.end(); it_e++)
		{
			Enemy *b = *it_e;
			b->update(time);
		}
		for (it_w = weapons.begin(); it_w != weapons.end();)
		{
			Weapons *b = *it_w;
			b->update(time);
			if (!b->life) 
			{
				it_w = weapons.erase(it_w);
				delete b;
			}
			else
				it_w++;
		}
		window.setView(view);//"оживляем" камеру в окне sfml
		
		window.clear();
		draw_map(window, s_map, s_fire, s_bonus, current_frame, time);
		window.draw(hero.sprite);
		for (it_e = ghosts.begin(); it_e != ghosts.end(); it_e++)
			window.draw((*it_e)->sprite);
		for (it_w = weapons.begin(); it_w != weapons.end(); it_w++)
			window.draw((*it_w)->sprite);
		window.display();
	}
	CleanTheMemory(stMap);
	CleanTheMemory(stFire);
	CleanTheMemory(stBonus);
	return 0;
}