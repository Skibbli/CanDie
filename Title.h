#pragma once

//Include guards
#ifndef TITLE_H
#define TITLE_H

//Include necessary additional files
#include "GameState.h"
#include "Player.h"
#include "Allegro.h"

class Title : public GameState
{
	public:
		Title(Player &myPlayer);
		~Title();

		void HandleEvents();
		void Logic();
		void Render();

	protected:

	private:
		int m_mouseCounter;
		int m_state;
		int m_saveSelect;
		
		bool m_prevSavePresent;

		std::string m_shipImgNo;

		BITMAP *m_ship1;
		BITMAP *m_ship2;
		BITMAP *m_ship3;
		BITMAP *m_ship4;
		BITMAP *m_newGameButton;
		BITMAP *m_loadGameButton;
		BITMAP *m_instructionsButton;
		BITMAP *m_instructions;
		BITMAP *m_cloud;

		Player *m_myPlayer;

		//Enum that is used for switching between states internal to this gamestate
		enum m_state
		{
			SAVE_SELECT,
			SHIP_SELECT,
			INSTRUCTIONS,
			FINISHED
		};
};

#endif