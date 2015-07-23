#pragma once

//Include guards
#ifndef PLAYING_LEVEL_H
#define PLAYING_LEVEL_H

//Include necessary additional files
#include "GameState.h"
#include "BaseChar.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Allegro.h"
#include <vector>
#include <memory>

class Playing_Level : public GameState
{
	public: 
		Playing_Level(Player &myPlayer);
		virtual ~Playing_Level();

		virtual void HandleEvents();
		virtual void Logic();
		virtual void Render();

	protected:

	private:
		int m_level;
		int m_enemySpawnRate;
		int m_enemySpawnCD;
		int m_enemySpawnLimit;
		int m_enemySpawnCounter;

		int m_expFrameLimit;

		float BGyPos;

		int m_playingState;

		int m_levelHealth;

		//Enum that is used for switching between states internal to this state
		enum PLAYING_STATE
		{
			PLAYING,
			PAUSED,
			LEVEL_CLEAR,
			GAMEOVER
		};

		//Defines the variables needed for the explosions
		struct Explosion
		{
			float xPos;
			float yPos;
			int expCounter;
			
			BITMAP *expIMG;
		};

		Explosion m_explosion1;
		Explosion m_explosion2;
		Explosion m_explosion3;

		SAMPLE *m_BGMusic;

		FONT *m_myfont;

		Player *m_myPlayer;

		BITMAP *m_pauseIMG;
		BITMAP *m_winIMG;
		BITMAP *m_failIMG;
		BITMAP *m_cloud;
		
		//Defines vectors for storing the bullets, enemies and explosions
		//Anything that is active/alive is added to these and then they can be
		//iterated through when necessary
		std::vector<Enemy> m_loadedEnemies;
		std::vector<Enemy> m_liveEnemies;
		std::vector<Bullet> m_bullets;
		std::vector<Explosion> m_explosions;
};

#endif