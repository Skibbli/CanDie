#pragma once

//Include guards
#ifndef INTRO_H
#define INTRO_H

//Include necessary additional files
#include "GameState.h"
#include "Allegro.h"

class Intro : public GameState
{
	public: 
		Intro();
		virtual ~Intro();

		virtual void HandleEvents();
		virtual void Logic();
		virtual void Render();

	protected:

	private:
};

#endif