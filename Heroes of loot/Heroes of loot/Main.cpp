#include <SFML/Graphics.hpp>
#include <iostream> 
#include <vector>
#include <list>
#include <sstream>
#include "levels.h"
#include "view.h"
#include "player.h"
#include "enemy.h"
#include "weapons.h"

using namespace sf;
using namespace std;

const Vector2f WINDOW_SIZE = { 920, 640 };

struct GraphicResource {
	Image* im;
	Texture* tex;
	Sprite* spr;
};

void CleanTheMemory(GraphicResource & gr) 
{
	delete gr.im;
	delete gr.tex;
	delete gr.spr;
}

GraphicResource MakeTheSprite(String fileName) 
{
	GraphicResource gr;
	gr.im = new Image();
	gr.tex = new Texture();
	gr.spr = new Sprite();
	gr.im->loadFromFile("images/" + fileName);
	gr.tex->loadFromImage(*gr.im);
	gr.spr->setTexture(*gr.tex);
	return gr;
}

int main()
{
	
	float current_frame = 0;
	Clock clock;

	RenderWindow window(VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Heroes of Loot");
	view.reset(FloatRect(0, 0, WINDOW_SIZE.x, WINDOW_SIZE.y));
	Level lvl;
	lvl.LoadFromFile("map.tmx");
	
	Object player = lvl.GetObject("hero");
	Player hero("wizard.psd", lvl, player.rect.left, player.rect.top, player.rect.width, player.rect.height);

	vector<Object> enemy;
	enemy = lvl.GetObjects("enemy");
	
	vector<Enemy*> ghosts;
	vector<Enemy*>::iterator it_e;
	for (int i = 0; i < enemy.size(); i++)
	{
		ghosts.push_back(new Enemy("enemies.psd", lvl, enemy[i].rect.left, enemy[i].rect.top, enemy[i].rect.width, enemy[i].rect.height));
	}

	vector<Weapons*> weapons;
	vector<Weapons*>::iterator it_w;
	
	
	GraphicResource stFire = MakeTheSprite("fire.png");
	Sprite s_fire = *stFire.spr;
	GraphicResource stBonus = MakeTheSprite("bonus.png");
	Sprite s_bonus = *stBonus.spr;
	GraphicResource stDark = MakeTheSprite("darkness.psd");
	Sprite s_dark = *stDark.spr;
	s_dark.setOrigin(WINDOW_SIZE.x / 2, WINDOW_SIZE.y / 2);
	GraphicResource stScales = MakeTheSprite("scales.png");
	Sprite s_money = *stScales.spr;
	s_money.setTextureRect(IntRect(0, 0, 30, 30));
	Sprite s_living = *stScales.spr;
	s_living.setTextureRect(IntRect(0, 30, 180, 40));
	Sprite s_scale = *stScales.spr;

	Font font;//шрифт 
	font.loadFromFile("font.ttf");//передаем нашему шрифту файл шрифта
	Text text("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	text.setColor(Color::White);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	text.setStyle(sf::Text::Bold);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый

	

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
				weapons.push_back(new Weapons("weapons.psd", 20, 20, time, hero.GetHeroPos().x, hero.GetHeroPos().y, hero.dir));
				hero.isShoot = false;
			}
		}
		
		hero.control();
		hero.update(time);
		s_dark.setPosition(view.getCenter().x, view.getCenter().y);
		s_money.setPosition(view.getCenter().x + WINDOW_SIZE.x / 2 - 40, view.getCenter().y - WINDOW_SIZE.y / 2 + 10);
		s_living.setPosition(view.getCenter().x - WINDOW_SIZE.x / 2 + 10, view.getCenter().y - WINDOW_SIZE.y / 2 + 10);
		ostringstream money_str;
		money_str << hero.money;
		text.setString(money_str.str());//задает строку тексту
		text.setPosition(view.getCenter().x, view.getCenter().y - WINDOW_SIZE.y / 2 + 10);//задаем позицию текста, центр камеры
		

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
		lvl.Draw(window);
		lvl.DrawDynamicObjects(hero.obj, window, "bonus", s_bonus, 0, 0, time, current_frame);
		lvl.DrawDynamicObjects(hero.obj, window, "diamond", s_bonus, 0, 60, time, current_frame);
		lvl.DrawStaticObjects(hero.obj, window, "chest", s_bonus, 60, 120);
		window.draw(hero.sprite);
		lvl.DrawDynamicObjects(hero.obj, window, "fire", s_fire, 0, 0, time, current_frame);
		
		for (it_e = ghosts.begin(); it_e != ghosts.end(); it_e++)
			window.draw((*it_e)->sprite);
		for (it_w = weapons.begin(); it_w != weapons.end(); it_w++)
			window.draw((*it_w)->sprite);
		//window.draw(s_dark);
		window.draw(s_money);
		window.draw(s_living);
		lvl.DrawDynamicSprite(window, s_scale, 0, 100, 136, 10, time, view.getCenter().x - WINDOW_SIZE.x / 2 + 50, view.getCenter().y - WINDOW_SIZE.y / 2 + 20, current_frame);
		window.draw(text);//рисую этот текст
		window.display();
	}
	CleanTheMemory(stFire);
	CleanTheMemory(stBonus);
	CleanTheMemory(stDark);
	CleanTheMemory(stScales);
	return 0;
}