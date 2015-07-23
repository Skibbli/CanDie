#pragma once

//Include guards
#ifndef LEVEL_SELECT_H
#define LEVEL_SELECT_H

//Include necessary additional files
#include "GameState.h"
#include "Player.h"

class Level_Select : public GameState
{
	public:
		Level_Select(Player &myPlayer);
		~Level_Select();

		virtual void HandleEvents();
		virtual void Logic();
		virtual void Render();

	protected:

	private:
		int m_playerLevel;
		int m_mouseCounter;

		Player *m_myPlayer;

		BITMAP *m_level1BG;
		BITMAP *m_level2BG;
		BITMAP *m_level3BG;
		BITMAP *m_level4BG;
		BITMAP *m_level5BG;
		BITMAP *m_level6BG;
};

#endif