#include "GameState.h"

//Constructor
GameState::GameState()
{
	//Buffer is created in base as all gamestates will have the same one
	m_buffer = create_bitmap(SCREEN_W, SCREEN_H);
	m_nextState = STATE_NULL;
}

//+++++++++++++
//Setters
//+++++++++++++
void GameState::SetNextState(int newState)
{
	m_nextState = newState;	//Set the next state
}

void GameState::SetStateID(int stateID)
{
	m_stateID = stateID;
}

//+++++++++++++
//Getters
//+++++++++++++
int GameState::GetNextState()
{
	return m_nextState;
}

int GameState::GetStateID()
{
	return m_stateID;
}

//Destructor
GameState::~GameState()
{
	//Bitmaps destroyed here as all derived classes will need to delete them
	destroy_bitmap(m_buffer);
	destroy_bitmap(m_background);
}