#ifndef coin_h
#define coin_h

#include <SFML/Graphics.hpp>
#include "game.h"

struct Coin
{
	Sprite sprite;
	float dist = 0;
};

Coin GetCoinObj(Sprite &sprite)
{
	Coin coin;
	coin.sprite = sprite;
	return coin;
}

#endif
