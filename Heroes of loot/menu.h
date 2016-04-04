#include <SFML/Graphics.hpp>
#include "game.h"
#include <iostream>

using namespace sf;

class Menu
{
public:
	Texture menuTexture;
	Sprite backgroundMenu, flag1, flag2, elf, warrior, wizard, valkyrie, info, someHero, stand, nameHero;
	Sprite backgroundSelect, backgroundGameIsOn;
	bool isMenu, selectCharacter, stopGame, endGame;
	bool selectHero = false;
	float flagFrame = 0;
	float firstGroupHeroFrame = 0;
	float secondGroupHeroFrame = 2;
	Clock clock;
	float time;
	Music menuMmusic;
	Vector2f scaleIndex{ WINDOW_SIZE.x / 288, WINDOW_SIZE.y / 162 };
	Menu(String const& F)
	{
		isMenu = true;
		selectCharacter = false;
		stopGame = false;
		endGame = false;
		menuTexture.loadFromFile(F);
		
		SetTexture(backgroundMenu);
		SetTexture(backgroundSelect);
		SetTexture(backgroundGameIsOn);
		SetTexture(stand);
		SetTexture(flag1);
		SetTexture(flag2);
		SetTexture(elf);
		SetTexture(warrior);
		SetTexture(wizard);
		SetTexture(valkyrie);
		SetTexture(someHero);
		SetTexture(info);
		SetTexture(nameHero);
	}
	void Menu::SetTexture(Sprite &spr);
	void Menu::SetPosObjects();
	void Menu::MenuDisplay(RenderWindow & window, Event & event, Game * game);
	void Menu::BeginMode(RenderWindow & window, Event & event, Game * game);
	void Menu::SelectionMode(RenderWindow & window, Event & event, Game * game);
	void Menu::StopMode(RenderWindow & window, Event & event, Game * game);
	void Menu::EndMode(RenderWindow & window, Event & event, Game * game);
	void Menu::SetRectFlags();
	void Menu::SetRectCharacters();
	void Menu::DrawCharacters(RenderWindow & window);
};