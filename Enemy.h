#pragma once

//Include guards
#ifndef ENEMY_H
#define ENEMY_H

//Include necessary headers
#include "BaseChar.h"
#include "Player.h"

class Enemy : public BaseChar
{
	public:
		//Constructor and destructor
		Enemy(int lineNo);
		~Enemy();

		bool UpdateAndBoundsCheck();
		bool PlayerCollisionCheck(Player &myPlayer);

		//Setters
		void SetXPos(float xPos);
		void SetYPos(float yPos);

		//Getters
		int GetSugarReward();

	protected:

	private:
		int m_sugarReward;
		
		float m_shipVelocity;
};

#endif