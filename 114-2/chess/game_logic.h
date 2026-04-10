#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "config.h"

void initBoard(void);
int getFaction(int piece);
bool canEat(int attacker, int defender);

#endif