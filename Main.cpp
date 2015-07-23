#include <iostream>
#include <allegro.h>
#include "GameState.h"
#include "Intro.h"
#include "Title.h"
#include "Level_Select.h"
#include "Playing_Level.h"
#include "Shop.h"

//+++++++++++++++++++
//Global Variables
//+++++++++++++++++++
volatile int fpsCounter = 0;

//+++++++++++++++++++++
//Function Prototypes
//+++++++++++++++++++++
void AllegroInit();
void FPSCounter();
GameState * ChangeState(GameState *currentState, Player &myPlayer);

int main()
{
	//Initialise Allegro
	AllegroInit();		

	//Install timer in counter function to run at constant 60FPS
	install_int_ex(FPSCounter, BPS_TO_TIMER(60));		

	//Create pointer to abstract base GameState class
	GameState *currentState = NULL;		
	Player myPlayer;

	//Dynamically create derived gamestate Intro using base pointer
	currentState = new Intro();		

	//Run game loop while the state has not been set to EXIT
	while(currentState->GetStateID() != STATE_EXIT)		
	{
		//fpsCounter is greater than zero 60 times per second so this will be true that often
		if(fpsCounter > 0)
		{
			fpsCounter = 0;

			//Handle input for the current derived game state using virtual functions from the base
			currentState->HandleEvents();

			//Process logic for the current derived game state using virtual functions from the base
			currentState->Logic();

			//Change gamestate if necessary
			currentState = ChangeState(currentState, myPlayer);		

			//Process drawing for the current derived game state using virtual functions from the base
			currentState->Render();		
		}
	}

	//Delete the current state before exiting the program, which in turn deletes the objects contained in the current state
	delete currentState;
	
	//Destroy the players bitmaps and uninstall the timers
	myPlayer.DestroyBitmaps();
	remove_int(FPSCounter);

	return 0;

}END_OF_MAIN();

//Initialise Allegro
void AllegroInit()		
{
	//Initialise graphics and create window - give error if fails
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0)
      { 
                depth = 32;
	}
      set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1000, 1000, 0, 0);
	if (res != 0) 
	{
		allegro_message("ERROR INITIALISING GRAPHICS");
		exit(-1);
	}

	set_window_title("Sweet Sweet Candy");

	//Initialise sound - give error if fails
	if(install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL) != 0)
	{
      allegro_message("ERROR INITIALISING SOUND");
      exit(-1);
	}

	//Install extra addons
	install_timer();
	install_keyboard();
	install_mouse();
}

void FPSCounter()
{
	fpsCounter++;
}

GameState* ChangeState(GameState *m_currentState, Player &myPlayer)
{
	//Store the nextState variable so that it will remain after the current state is deleted
	int nextState = m_currentState->GetNextState();		
	
	//If the state needs to be changed
	if(nextState != STATE_NULL)		
	{
		if(nextState != STATE_EXIT)
		{
			//Delete the current state if not exiting the game - if exiting state will be deleted later
			delete m_currentState;		
		}
		
		//Dynamically create new derived gamestate dependant on nextState variable
		switch(nextState)	
		{
			case STATE_TITLE:
				{
					m_currentState = new Title(myPlayer);
				}
				break;
			case STATE_LEVEL_SELECT:
				{
					m_currentState = new Level_Select(myPlayer);
				}
				break;
			case STATE_PLAYING_LEVEL:
				{
					m_currentState = new Playing_Level(myPlayer);
				}
				break;
			case STATE_SHOP:
				{
					m_currentState = new Shop(myPlayer);
				}
		}

		//Update the State ID to the new state
		m_currentState->SetStateID(nextState);		
	}

	return m_currentState;
}