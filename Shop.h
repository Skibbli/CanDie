#pragma once

//Include guards
#ifndef SHOP_H
#define SHOP_H

//Include necessary additional files
#include "GameState.h"
#include "Player.h"
#include <allegro.h>

class Shop : public GameState
{
	public:
		Shop(Player &myPlayer);
		~Shop();

		void HandleEvents();
		void Logic();
		void Render();

	protected:

	private:
		int m_mouseCounter;

		FONT *m_myfont;

		Player *m_myPlayer;
};

#endif