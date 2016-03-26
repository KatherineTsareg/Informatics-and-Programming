#include "menu.h"

void Menu::SetTexture(Sprite &spr)
{
	spr.setTexture(menuTexture);
	spr.scale(scaleIndex);
}

void Menu::SetPosObjects()
{
	if (isMenu)
	{
		backgroundMenu.setTextureRect(IntRect(0, 0, 288, 162));
		backgroundMenu.setPosition(0, 0);// , 288 * scaleIndex.x, 162 * scaleIndex.y));
		flag1.setPosition(177 * scaleIndex.x, 41 * scaleIndex.y);
		elf.setPosition(100 * scaleIndex.x, 105 * scaleIndex.y);
		warrior.setPosition(122 * scaleIndex.x, 105 * scaleIndex.y);
		wizard.setPosition(144 * scaleIndex.x, 105 * scaleIndex.y);
		valkyrie.setPosition(166 * scaleIndex.x, 105 * scaleIndex.y);
	}
	else if (selectCharacter)
	{
		backgroundSelect.setTextureRect(IntRect(0, 240, 288, 162));
		backgroundSelect.setPosition(0, 0);
		elf.setPosition(100 * scaleIndex.x, 50 * scaleIndex.y);
		warrior.setPosition(122 * scaleIndex.x, 50 * scaleIndex.y);
		wizard.setPosition(144 * scaleIndex.x, 50 * scaleIndex.y);
		valkyrie.setPosition(166 * scaleIndex.x, 50 * scaleIndex.y);
	}
	else if (stopGame)
	{
		backgroundGameIsOn.setTextureRect(IntRect(0, 438, 288, 162));
		backgroundGameIsOn.setPosition(0, 0);
		flag1.setPosition(105 * scaleIndex.x, 48 * scaleIndex.y);
		flag2.setPosition(177 * scaleIndex.x, 48 * scaleIndex.y);
		info.setTextureRect(IntRect(37, 433, 55, 5));
		info.setPosition(111 * scaleIndex.x, 107 * scaleIndex.y);
		someHero.setPosition(137 * scaleIndex.x, 48 * scaleIndex.y);
	}
	else if (endGame)
	{
		backgroundGameIsOn.setTextureRect(IntRect(0, 438, 288, 162));
		backgroundGameIsOn.setPosition(0, 0);
		flag1.setPosition(105 * scaleIndex.x, 48 * scaleIndex.y);
		flag2.setPosition(177 * scaleIndex.x, 48 * scaleIndex.y);
		info.setPosition(124 * scaleIndex.x, 107 * scaleIndex.y);
		someHero.setPosition(136 * scaleIndex.x, 42 * scaleIndex.y);
		stand.setPosition(134 * scaleIndex.x, 48 * scaleIndex.y);
	}
}

void Menu::SetRectFlags()
{
	if ((int)flagFrame > 6)
		flagFrame = 0;
	flag1.setTextureRect(IntRect(50, 162 + (int)flagFrame * 7, 18, 7));
	flag2.setTextureRect(IntRect(50, 162 + (int)flagFrame * 7, 18, 7));
	flagFrame += time * 0.000007f;
}

void Menu::SetRectCharacters()
{
	if (secondGroupHeroFrame > 2)
		secondGroupHeroFrame = 0;
	if (firstGroupHeroFrame > 3)
		firstGroupHeroFrame = 0;
	elf.setTextureRect(IntRect(0, 170 + (int)firstGroupHeroFrame * 12, 12, 12));
	warrior.setTextureRect(IntRect(12, 170 + (int)secondGroupHeroFrame * 12, 13, 12));
	wizard.setTextureRect(IntRect(25, 170 + (int)firstGroupHeroFrame * 12, 12, 12));
	valkyrie.setTextureRect(IntRect(36, 170 + (int)secondGroupHeroFrame * 12, 14, 12));
	firstGroupHeroFrame += time * 0.000005f;
	secondGroupHeroFrame += time * 0.000005f;
}

void Menu::DrawCharacters(RenderWindow & window)
{
	window.draw(elf);
	window.draw(warrior);
	window.draw(wizard);
	window.draw(valkyrie);
}

void Menu::BeginMode(RenderWindow & window, Event & event, Game * game)
{
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			window.close();
			isMenu = false;
		}
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::X)
			{
				isMenu = false;//если нажали первую кнопку, то выходим из меню 
				selectCharacter = true;
				SetPosObjects();
			}
			if (event.key.code == Keyboard::O)
			{
				window.close();
				isMenu = false;
			}
		}
	}
	game->level = 1;
	game->health = 100;
	game->hearts = 0;
	game->potions = 0;
	elf.setColor(Color(255, 255, 255));
	warrior.setColor(Color(255, 255, 255));
	wizard.setColor(Color(255, 255, 255));
	valkyrie.setColor(Color(255, 255, 255));

	SetRectCharacters();
	SetRectFlags();
	window.setView(game->view);
	window.clear();
	window.draw(backgroundMenu);
	window.draw(flag1);
	DrawCharacters(window);
	window.display();
}

void Menu::SelectionMode(RenderWindow & window, Event & event,  Game * game)
{
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			window.close();
			selectCharacter = false;
		}
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::X)
				selectCharacter = false;
			if (event.key.code == Keyboard::O)
			{
				isMenu = true;
				selectCharacter = false;
				SetPosObjects();
			}
		}
	}
	Vector2i mousePos = Mouse::getPosition(window);
	if (elf.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y))
	{
		warrior.setColor(Color(255, 255, 255, 128));
		wizard.setColor(Color(255, 255, 255, 128));
		valkyrie.setColor(Color(255, 255, 255, 128));
		nameHero.setTextureRect(IntRect(60, 403, 11, 5));
		nameHero.setPosition(130 * scaleIndex.x, 70 * scaleIndex.y);
		nameHero.setTextureRect(IntRect(60, 403, 11, 5));
		selectHero = true;
	}
	else if (warrior.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y))
	{
		elf.setColor(Color(255, 255, 255, 128));
		wizard.setColor(Color(255, 255, 255, 128));
		valkyrie.setColor(Color(255, 255, 255, 128));
		nameHero.setTextureRect(IntRect(72, 403, 27, 5));
		nameHero.setPosition(125 * scaleIndex.x, 70 * scaleIndex.y);
		selectHero = true;
	}
	else if (wizard.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y))
	{
		warrior.setColor(Color(255, 255, 255, 128));
		elf.setColor(Color(255, 255, 255, 128));
		valkyrie.setColor(Color(255, 255, 255, 128));
		nameHero.setTextureRect(IntRect(60, 409, 23, 5));
		nameHero.setPosition(127 * scaleIndex.x, 70 * scaleIndex.y);
		selectHero = true;
	}
	else if (valkyrie.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y))
	{
		warrior.setColor(Color(255, 255, 255, 128));
		wizard.setColor(Color(255, 255, 255, 128));
		elf.setColor(Color(255, 255, 255, 128));
		nameHero.setTextureRect(IntRect(60, 415, 31, 5));
		nameHero.setPosition(123 * scaleIndex.x, 70 * scaleIndex.y);
		selectHero = true;
	}
	else
	{
		elf.setColor(Color(255, 255, 255));
		warrior.setColor(Color(255, 255, 255));
		wizard.setColor(Color(255, 255, 255));
		valkyrie.setColor(Color(255, 255, 255));
		selectHero = false;
	}
	
	if ((event.type == Event::MouseButtonPressed) && (event.key.code == Mouse::Left))
	{
		if (elf.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y)){ game->character = ELF;}
		else if (warrior.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y)){ game->character = WARRIOR;}
		else if (wizard.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y)){ game->character = WIZARD;}
		else if (valkyrie.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y)){ game->character = VALKYRIE;}
	}
	SetRectCharacters();
	window.setView(game->view);
	window.clear();
	window.draw(backgroundSelect);
	DrawCharacters(window);
	if (selectHero) { window.draw(nameHero); }
	window.display();
}

void Menu::StopMode(RenderWindow & window, Event & event, Game * game)
{
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			window.close();
			stopGame = false;
		}
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::X)
			{
				stopGame = false;
				SetPosObjects();
			}
			if (event.key.code == Keyboard::O)
			{
				isMenu = true;
				stopGame = false;
				game->restart = true;
			}
		}
	}
	SetRectFlags();
	

	if (secondGroupHeroFrame > 2)
		secondGroupHeroFrame = 0;

	someHero.setTextureRect(IntRect(12 * game->character, 170 + (int)secondGroupHeroFrame * 12, 13, 12));
	secondGroupHeroFrame += time * 0.000003f;
	window.setView(game->view);
	window.clear();
	window.draw(backgroundGameIsOn);
	window.draw(flag1);
	window.draw(someHero);
	window.draw(flag2);
	window.draw(info);
	window.display();
}

void Menu::EndMode(RenderWindow & window, Event & event, Game * game)
{
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			window.close();
			endGame = false;
		}
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::X)
			{
				isMenu = true;//если нажали первую кнопку, то выходим из меню 
				endGame = false;
				SetPosObjects();
			}
			if (event.key.code == Keyboard::O)
			{
				window.close();
				endGame = false;
			}
		}
	}
	
	if (game->health <= 0)
	{
		info.setTextureRect(IntRect(0, 433, 35, 5));
		stand.setTextureRect(IntRect(123, 169, 16, 12));
		someHero.setTextureRect(IntRect(71 + 13 * game->character, 169, 13, 12));
		window.setView(game->view);
		SetRectFlags();
		window.clear();
		window.draw(backgroundGameIsOn);
		window.draw(flag1);
		window.draw(stand);
		window.draw(someHero);
		window.draw(flag2);
		window.draw(info);
		window.display();
	}
	else
	{
		info.setTextureRect(IntRect(139, 403, 35, 12));
		info.setPosition(122 * scaleIndex.x, 104 * scaleIndex.y);
		if (secondGroupHeroFrame > 2)
			secondGroupHeroFrame = 0;

		someHero.setTextureRect(IntRect(12 * game->character, 170 + (int)secondGroupHeroFrame * 12, 13, 12));
		someHero.setPosition(136 * scaleIndex.x, 50 * scaleIndex.y);
		secondGroupHeroFrame += time * 0.000003f;
		window.setView(game->view);
		SetRectFlags();
		window.clear();
		window.draw(backgroundGameIsOn);
		window.draw(flag1);
		window.draw(someHero);
		window.draw(flag2);
		window.draw(info);
		window.display();
	}
}

void Menu::MenuDisplay(RenderWindow & window, Event & event, Game * game)
{
	game->gameTheme.pause();
	game->menuTheme.play();
	endGame = game->gameEnd;
	while ((isMenu) || (selectCharacter) || (stopGame) || (endGame))
	{
		SetPosObjects();
		time = (float)clock.getElapsedTime().asMicroseconds();
		clock.restart();
		if (isMenu)
			BeginMode(window, event, game);
		if (selectCharacter)
			SelectionMode(window, event, game);
		if (stopGame)
			StopMode(window, event, game);
		if (endGame)
			EndMode(window, event, game);
	}
	game->menuTheme.pause();
	game->gameTheme.play();
}