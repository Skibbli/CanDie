#pragma once

//Include guards
#ifndef GAMESTATE_H
#define GAMESTATE_H

//Include necessary additional files
#include <allegro.h>

//Enum for gamestates to identify them when using switch statements
enum GameStates
{
	STATE_NULL,
	STATE_INTRO,
	STATE_TITLE,
	STATE_LEVEL_SELECT,
	STATE_PLAYING_LEVEL,
	STATE_SHOP,
	STATE_EXIT
};

class GameState
{
	public:
		//Functions declared as pure virtual so that derived classed must define them and when function
		//is called from the base GameState pointer it will derive to correct gamestate
		virtual void HandleEvents() = 0;
		virtual void Logic() = 0;
		virtual void Render() = 0;

		GameState();
		virtual ~GameState();

		void SetNextState(int nextState);
		void SetStateID(int stateID);

		int GetStateID();
		int GetNextState();

	protected:
		int m_nextState;
		int m_stateID;	

		BITMAP *m_buffer;
		BITMAP *m_background;

	private:
};

#endif