#include "game.h"

Evil GetEvilType(string const& s)
{
	if (s == "ghost")
		return GHOST;
	else if (s == "cyclop")
		return CYCLOP;
	else if (s == "demon")
		return DEMON;
	else if (s == "flash")
		return FLASH;
	else if (s == "minotaur")
		return MINOTAUR;
};

