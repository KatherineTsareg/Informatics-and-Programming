/*
#ifndef Map_H
#define Map_H
#include <SFML\Graphics.hpp>

const int HEIGHT_MAP = 16;//размер карты высота
const int WIDTH_MAP = 20;//размер карты ширина 

sf::String TileMap[HEIGHT_MAP] = {
	"01f11f11f1---11f1f12",
	"0        2---0     2",
	"0        1f1f1     2",
	"0                  2",
	"0 11111f11f111f1   2",
	"0   20             2",
	"0   20             2",
	"0   20       2     2",
	"0   20       2     2",
	"0   20       2     2",
	"0   20       1f11f12",
	"0   20             2",
	"0   233333333330   2",
	"0   211f11f11f10   2",
	"0   20             2",
	"03333333333333333332",
};

void randomMapGenerate(char name_bonus, int numb_bonus)
{
	int randomElementX = 0;//случайный элемент по горизонтали
	int randomElementY = 0;//случ эл-т по вертикали
	srand(time(0));//рандом	
	int countBonuses = numb_bonus;//количество камней

	while (countBonuses > 0) {
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);//рандомное по иксу от 1 до ширина карты-1, чтобы не получать числа бордюра карты
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);//по игреку так же

		if (TileMap[randomElementY][randomElementX] == ' ') {//если встретили символ пробел, 
			TileMap[randomElementY][randomElementX] = name_bonus; //то ставим туда камень.
			countBonuses--;
		}
	}
}

#endif
*/