#include <SFML/Graphics.hpp>
#include <iostream> 

using namespace sf;



////////////////////////////////////////////////////КЛАСС ИГРОКА////////////////////////
class Player {
public:
	float x, y, w, h, dx, dy, speed = 0;
	int dir = 0;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	Player(String F, float X, float Y, float W, float H) {
		File = F;
		w = W; h = H;
		image.loadFromFile("images/" + File);
		image.createMaskFromColor(Color(41, 33, 59));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
		sprite.setTextureRect(IntRect(0, 0, w, h));
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
	}
};


int main()
{
	RenderWindow window(sf::VideoMode(640, 480), "Heroes of Loot");

	Player p("hero.psd", 100, 100, 50, 50);

	float CurrentFrame = 0;
	Clock clock;

	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		///////////////////////////////////////////Управление персонажем с анимацией////////////////////////////////////////////////////////////////////////
		if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
			p.dir = 1; p.speed = 0.1;
			p.sprite.setTextureRect(IntRect(50, 0, 50, 50));
		}

		if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
			p.dir = 0; p.speed = 0.1;
			p.sprite.setTextureRect(IntRect(100, 0, 50, 50));
		}

		if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
			p.dir = 3; p.speed = 0.1;
			p.sprite.setTextureRect(IntRect(150, 0, 50, 50));

		}

		if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
			p.dir = 2; p.speed = 0.1;
			p.sprite.setTextureRect(IntRect(0, 0, 50, 50));

		}
		p.update(time);


		window.clear();
		window.draw(p.sprite);
		window.display();
	}

	return 0;
}