#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream> 
#include <vector>
#include <list>
#include <sstream>
#include "level.h"
#include "player.h"
#include "enemy.h"
#include "weapons.h"
#include "game.h"
#include "menu.h"
#include "coin.h"

using namespace sf;
using namespace std;

/*void InitializeGame(Game * &game)
{
	game = new Game();
	InitializeGame(game->graphics);
}*/

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
	gr.im->loadFromFile(fileName);
	gr.tex->loadFromImage(*gr.im);
	gr.spr->setTexture(*gr.tex);
	return gr;
}

void CreateStatistick(RenderWindow &window, Text &text, int money, float x, float y)
{
	ostringstream money_str;
	money_str << money;
	text.setColor(Color::White);//��������� ����� � �������. ���� ������ ��� ������, �� �� ��������� �� �����
	text.setStyle(Text::Bold);
	text.setString(money_str.str());//������ ������ ������
	text.setPosition(x, y);//������ ������� ������, ����� ������
	window.draw(text);
}

string GetLevelNumb(int levelNumb)
{
	switch (levelNumb)
	{
	case 1: return "map1.tmx"; break;
	case 2: return "map2.tmx"; break;
	case 3: return "map3.tmx"; break;
	case 4: return "map4.tmx"; break;
	case 5: return "map5.tmx"; break;
	case 6: return "queen room.tmx"; break;
	default: return "end.tmx"; break;
	/*case 1: return "data/maps/map1.tmx"; break; 
	case 2: return "data/maps/map2.tmx"; break;
	case 3: return "data/maps/map3.tmx"; break;
	case 4: return "data/maps/map4.tmx"; break;
	case 5: return "data/maps/map5.tmx"; break;
	case 6: return "data/maps/queen room.tmx"; break;
	default: return "data/maps/end.tmx"; break;*/
	}
}

void EntitiesIntersection(Game &game, Player &hero, vector<Enemy*> &enemy, vector<Weapons*> &weapons)
{
	vector<Enemy*>::iterator it_e;
	vector<Weapons*>::iterator it_w;
	for (it_e = enemy.begin(); it_e != enemy.end(); it_e++)
	{
		Enemy *enemy = *it_e;
		if (hero.GetRect().intersects(enemy->GetRect()))
		{
			//////////////// ����������� ����� � ������� � ���������� ����� /////////////////
			enemy->ShiftWhenCrossing(hero.GetRect());
			hero.shock = true;
			game.health -= 5 * (enemy->evil + 1);
			game.ouch.play();
		}
		for (it_w = weapons.begin(); it_w != weapons.end(); it_w++)
		{
			Weapons *weap = *it_w;
			if (enemy->GetRect().intersects(weap->GetRect()))
			{
				/////////// ����������� ����� � ����� � ���������� ����� /////////////////
				weap->life = false;
				enemy->health -= 20 * (enemy->evil + 1);
			}
		}
	}
}

void UpdatesObjects(Game &game, Player &hero, vector<Enemy*> &enemy, vector<Weapons*> &weapons, vector<Coin> &coins)
{
	if (game.turboSpeed)
	{
		if (game.turboTime < 0)
		{
			game.turboTime = 10;
			game.turboSpeed = false;
			game.heroSpeed = game.heroSpeed / 2;
		}
		game.turboTime -= game.time * 0.01f;
	}
	vector<Enemy*>::iterator it_e;
	vector<Weapons*>::iterator it_w;
	hero.Control(game.character, &game);
	hero.Update(game.time, &game);
	game.view.setCenter(hero.GetPos().x, hero.GetPos().y);
	game.graphics.statistic.coin.setPosition(game.view.getCenter().x + WINDOW_SIZE.x / 2 - 40, game.view.getCenter().y - WINDOW_SIZE.y / 2 + 10);
	game.graphics.statistic.hero_health.setPosition(game.view.getCenter().x - WINDOW_SIZE.x / 2 + 10, game.view.getCenter().y - WINDOW_SIZE.y / 2 + 10);
	game.graphics.dark.setPosition(game.view.getCenter().x, game.view.getCenter().y + 5);
	game.graphics.key.setPosition(game.view.getCenter().x - WINDOW_SIZE.x / 2 + 40, game.view.getCenter().y - WINDOW_SIZE.y / 2 + 45);
	game.graphics.potion.setPosition(game.view.getCenter().x - WINDOW_SIZE.x / 2 + 5, game.view.getCenter().y - WINDOW_SIZE.y / 2 + 45);
	game.graphics.heart.setPosition(game.view.getCenter().x - WINDOW_SIZE.x / 2 + 200, game.view.getCenter().y - WINDOW_SIZE.y / 2 + 10);
	game.graphics.statistic.cup.setPosition(game.view.getCenter().x - WINDOW_SIZE.x / 2 + 90, game.view.getCenter().y - WINDOW_SIZE.y / 2 + 45);
	if (game.queenLvl) { 
		if (game.currentFrameQueen > 2) game.currentFrameQueen = 0;
		game.graphics.queen.setTextureRect(IntRect(108 + 12 * (int)game.currentFrameQueen, 8, 12, 12));
		game.currentFrameQueen += game.time * 0.005f;
	}
	if (game.findCoins)
	{
		coins.push_back(GetCoinObj(game.graphics.coins));
		game.findCoins = false;
	}
	EntitiesIntersection(game, hero, enemy, weapons);
	for (it_e = enemy.begin(); it_e != enemy.end();)
	{
		Enemy *b = *it_e;
		b->Update(game.time, hero.GetPos().x, hero.GetPos().y);
		if (!b->life)
		{
			it_e = enemy.erase(it_e);
			delete b;
		}
		else
			it_e++;
	}
	for (it_w = weapons.begin(); it_w != weapons.end();)
	{
		Weapons *b = *it_w;
		b->update(game.time, hero.GetRect());
		if (!b->life)
		{
			it_w = weapons.erase(it_w);
			delete b;
		}
		else
			it_w++;
	}
}

void GetInfo(RenderWindow & window, Game * game, Player &hero)
{
	if (game->findKey)
	{
		game->graphics.infoBlock.setPosition(game->view.getCenter().x - 64 * 4.0f, game->view.getCenter().y + 100);
		game->graphics.statistic.info.setTextureRect(IntRect(64, 93, 75, 5));
		game->graphics.statistic.info.setPosition(game->view.getCenter().x - 158, game->view.getCenter().y + 100 + 32); 
		game->infoTime -= game->time * 0.0005f;
		window.draw(game->graphics.infoBlock);
		window.draw(game->graphics.statistic.info);
		if (game->infoTime < 0) { game->infoTime = 2; game->findKey = false; }
	}
	else if (game->findPotion)
	{
		game->graphics.infoBlock.setPosition(game->view.getCenter().x - 64 * 4.0f, game->view.getCenter().y + 100);
		game->graphics.statistic.info.setTextureRect(IntRect(64, 98, 107, 5));
		game->graphics.statistic.info.setPosition(game->view.getCenter().x - 220, game->view.getCenter().y + 100 + 32);
		game->infoTime -= game->time * 0.0005f;
		window.draw(game->graphics.infoBlock);
		window.draw(game->graphics.statistic.info);
		if (game->infoTime < 0) { game->infoTime = 2; game->findPotion = false; }
	}
	if (game->clue)
	{
		game->graphics.infoBlock.setPosition(game->view.getCenter().x - 64 * 4.0f, game->view.getCenter().y + 100);
		game->graphics.statistic.info.setTextureRect(IntRect(64, 103, 83, 5));
		game->graphics.statistic.info.setPosition(game->view.getCenter().x - 190, game->view.getCenter().y + 100 + 32);
		game->infoTime -= game->time * 0.0005f;
		window.draw(game->graphics.infoBlock);
		window.draw(game->graphics.statistic.info);
		if (game->infoTime < 0) { game->infoTime = 2; game->clue = false; }
	}
}

void DrawAllObjects(RenderWindow & window, Level & lvl, Game &game, Player &hero, vector<Enemy*> enemy, vector<Weapons*> weapons, vector<Coin> &coins)
{
	vector<Enemy*>::iterator it_e;
	vector<Weapons*>::iterator it_w;
	window.setView(game.view);//"��������" ������ � ���� sfml
	lvl.Draw(window);
	window.draw(hero.sprite);
	lvl.DrawDynamicObjects(hero.obj, window, "bonus", game.graphics.reward, 180, 248, game.time, game.current_frame);
	lvl.DrawDynamicObjects(hero.obj, window, "diamond", game.graphics.reward, 180, 188, game.time, game.current_frame);
	lvl.DrawStaticObjects(hero.obj, window, "boxes", game.graphics.reward, 240, 309);
	lvl.DrawStaticObjects(hero.obj, window, "cup", game.graphics.reward, 298, 309);
	
	for (it_e = enemy.begin(); it_e != enemy.end(); it_e++)
		window.draw((*it_e)->sprite);
	for (it_w = weapons.begin(); it_w != weapons.end(); it_w++)
		window.draw((*it_w)->sprite);
	lvl.DrawStaticObjects(hero.obj, window, "door", game.graphics.reward, 0 + 60 * game.key, 192);
	lvl.DrawDynamicObjects(hero.obj, window, "torch", game.graphics.torch, 0, 252, game.time, game.current_frame);
	if (hero.shock)
		window.draw(hero.points);
	if (game.queenLvl) window.draw(game.graphics.queen);
	window.draw(game.graphics.dark);
	lvl.DrawDynamicSprite(window, game.graphics.statistic.scale, 160, 168, (int)136.0f * 0.01 * game.health, 10, (int)game.view.getCenter().x - (int)WINDOW_SIZE.x / 2 + 50, (int)game.view.getCenter().y - (int)WINDOW_SIZE.y / 2 + 20);
	window.draw(game.graphics.statistic.hero_health);
	window.draw(game.graphics.statistic.coin);
	if (game.key == 1) window.draw(game.graphics.key);
	if (game.potions > 0) window.draw(game.graphics.potion);
	if (game.hearts > 0) window.draw(game.graphics.heart);
	if (game.cup > 0) window.draw(game.graphics.statistic.cup);
	GetInfo(window, &game, hero);
	CreateStatistick(window, game.graphics.statistic.score, game.money, game.view.getCenter().x + WINDOW_SIZE.x / 2 - 100, game.view.getCenter().y - WINDOW_SIZE.y / 2 + 7);
	for (int i = 0; i < coins.size();)
	{
		if (coins[i].sprite.getGlobalBounds().intersects(game.graphics.statistic.coin.getGlobalBounds()) || (coins[i].dist > 380))
		{
			game.money += 2;
			game.coins.play();
			window.draw(coins[i].sprite);
			cout << coins[i].dist << endl;
			coins.erase(coins.begin() + i);
		}
		else
		{
			coins[i].sprite.setPosition(game.view.getCenter().x + coins[i].dist * (WINDOW_SIZE.x / WINDOW_SIZE.y), game.view.getCenter().y - coins[i].dist);
			coins[i].dist += game.time * 0.8;
			window.draw(coins[i].sprite);
			i++;
		}
	}
}

void FillingTheListOfEnemies(Level & lvl, vector<Enemy*> &enemy, Game &game)
{
	vector<Object> enemies;
	vector<Object> tempEnemy;
	vector<Object>::iterator it;
	enemies = lvl.GetObjects("ghost");
	it = enemies.end();
	tempEnemy = lvl.GetObjects("cyclop");
	if (tempEnemy.size() > 0) { enemies.insert(it, tempEnemy.begin(), tempEnemy.end()); it = enemies.end(); }
	tempEnemy = lvl.GetObjects("demon");
	if (tempEnemy.size() > 0) { enemies.insert(it, tempEnemy.begin(), tempEnemy.end()); it = enemies.end(); }
	tempEnemy = lvl.GetObjects("flash");
	if (tempEnemy.size() > 0) { enemies.insert(it, tempEnemy.begin(), tempEnemy.end()); it = enemies.end(); }
	tempEnemy = lvl.GetObjects("minotaur");
	if (tempEnemy.size() > 0) { enemies.insert(it, tempEnemy.begin(), tempEnemy.end()); it = enemies.end(); }
	for (int i = 0; i < enemies.size(); i++)
		enemy.push_back(new Enemy(game.graphics.levelTexture, lvl, GetEvilType(enemies[i].name), enemies[i].rect.left, enemies[i].rect.top, enemies[i].rect.width, enemies[i].rect.height));

}

bool StartGame(RenderWindow & window, Game & game, Menu & menu)
{
	Level lvl;
	lvl.LoadFromFile(GetLevelNumb(game.level));
	vector<Weapons*> weapons;
	vector<Enemy*> enemy;
	Event event;
	Clock clock;
	Coin coin;
	vector<Coin> coins;
	Object player = lvl.GetObject("hero");
	Player hero(game.graphics.levelTexture, lvl, player.rect.left, player.rect.top, player.rect.width, player.rect.height);
	if (lvl.IsExist("queen")) 
	{ 
		Object queen = lvl.GetObject("queen"); 
		game.graphics.queen.setPosition(queen.rect.left, queen.rect.top); 
		game.queenLvl = true; 
	}
	game.key = 0;
	game.restart = false;
	FillingTheListOfEnemies(lvl, enemy, game);
	game.view.setCenter(hero.GetPos().x, hero.GetPos().y);
	game.gameTheme.play();
	while (window.isOpen() && (!game.restart))
	{
		game.time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		game.time = game.time * 0.0012f;
		game.view.setCenter(WINDOW_SIZE.x / 2, WINDOW_SIZE.y / 2);
		menu.MenuDisplay(window, event, &game);
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				game.restart = false;
			}
			if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::O))
			{
				menu.stopGame = true;
				menu.SetPosObjects();
			}
			if (hero.isShoot == true)
			{
				weapons.push_back(new Weapons(game.graphics.levelTexture, game.character, lvl, game.time, hero.GetPos(), hero.dir));
				hero.isShoot = false;
			}
		}
		if (!hero.life)
		{
			menu.endGame = true;
			game.gameEnd = true;
		}
		else
		{
			UpdatesObjects(game, hero, enemy, weapons, coins);
			window.clear();
			DrawAllObjects(window, lvl, game, hero, enemy, weapons, coins);			
			window.display();
		}
	}
	return game.restart;
}

void GameRunning(RenderWindow & window, Game & game, Menu & menu)
{
	if (StartGame(window, game, menu))
		GameRunning(window, game, menu);
}

int main()
{
	Menu menu("menu.psd");
	RenderWindow window(VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Heroes of Loot");
	Game game;
	game.view.reset(FloatRect(0, 0, WINDOW_SIZE.x, WINDOW_SIZE.y));
	GraphicResource stLevel = MakeTheSprite("data/images/level.png");
	game.graphics.levelTexture = (*stLevel.tex);
	game.graphics.torch = (*stLevel.spr);
	game.graphics.reward = (*stLevel.spr);
	game.graphics.statistic.coin = (*stLevel.spr);
	game.graphics.statistic.coin.setTextureRect(IntRect(0, 330, 30, 30));
	game.graphics.coins = (*stLevel.spr);
	game.graphics.coins.setTextureRect(IntRect(141, 132, 50, 33));

	game.graphics.statistic.hero_health = (*stLevel.spr);
	game.graphics.statistic.hero_health.setTextureRect(IntRect(0, 360, 180, 40));
	game.graphics.statistic.scale = (*stLevel.spr);
	game.graphics.dark = (*stLevel.spr);
	game.graphics.dark.scale(WINDOW_SIZE.x / 288.0f, WINDOW_SIZE.y / 160.0f);
	game.graphics.dark.setTextureRect(IntRect(200, 0, 312, 162));
	game.graphics.dark.setOrigin(312 / 2, 162 / 2);
	
	game.graphics.heart = (*stLevel.spr);
	game.graphics.heart.scale(4.0f, 4.0f);
	game.graphics.heart.setTextureRect(IntRect(43, 16, 12, 12));
	
	game.graphics.potion = (*stLevel.spr);
	game.graphics.potion.scale(4.0f, 4.0f);
	game.graphics.potion.setTextureRect(IntRect(55, 16, 12, 12));
	
	game.graphics.key = (*stLevel.spr);
	game.graphics.key.scale(4.0f, 4.0f);
	game.graphics.key.setTextureRect(IntRect(67, 16, 13, 12));

	game.graphics.statistic.cup = (*stLevel.spr);
	game.graphics.statistic.cup.scale(4.0f, 4.0f);
	game.graphics.statistic.cup.setTextureRect(IntRect(80, 16, 12, 12));
	
	game.graphics.statistic.info = (*stLevel.spr);
	game.graphics.statistic.info.scale(4.0f, 4.0f);
	
	game.graphics.infoBlock = (*stLevel.spr);
	game.graphics.infoBlock.scale(4.0f, 4.0f);
	game.graphics.infoBlock.setTextureRect(IntRect(64, 65, 128, 22));

	game.graphics.queen = (*stLevel.spr);
	game.graphics.queen.scale(5.0f, 5.0f);
	
	game.menuTheme.openFromFile("data/audio/tune2.ogg");
	game.ouch.openFromFile("data/audio/ouch.ogg");
	game.gameTheme.openFromFile("data/audio/tune1.ogg");
	game.coins.openFromFile("data/audio/coin.ogg");
	game.shoot.openFromFile("data/audio/shoot.ogg");
	game.info.openFromFile("data/audio/info.ogg");

	Font font;//����� 
	font.loadFromFile("data/font/font.ttf");//�������� ������ ������ ���� ������
	Text text("", font, 25);
	game.graphics.statistic.score = text;

	GameRunning(window, game, menu);

	CleanTheMemory(stLevel);
	return 0;
}