#pragma once

//Include guards
#ifndef PLAYER_H
#define PLAYER_H

//Include necessary additional files
#include "BaseChar.h"

class Player : public BaseChar
{
	public:
		Player();
		~Player();
	
		void IncreaseLevel();
		void EarnSugar(int sugar);
		void LoadShipSprite(std::string shipImgNo);
		
		void GetPlayerMovement();
		void LoadPlayerStats(int lineNo);

		void ResetPlayer();
		void SavePlayer();
		void UpdatePlayer();
		void TotalStatUpdate();

		void UpgradeShip(int choice);

		//Getters
		bool GetIsFiring();

		int GetSugar();
		int GetLevel();
		int GetActiveLevel();
		int GetShipHPLvl();
		int GetShipVelLvl();
		int GetShipAccelLvl();
		int GetWeapDmgLvl();
		int GetWeapRateLvl();
		int GetBulletSpeedLvl();

		//Setters
		void SetIsFiring(bool isFiring);
		void SetActiveLevel(int level);

	protected:

	private:
		float m_shipAccel, m_shipBaseAccel, m_shipAccelPerLvl;
		float m_xVelocity;
		float m_yVelocity;
		float m_maxShipVel, m_shipVelPerLvl;
		
		int m_activeLevel;
		int m_sugar;
		int m_weapBaseDmg, m_weapDmgPerLvl, m_weapDmgLvl;
		int m_weapBaseFireRate, m_weapFireRatePerLvl, m_weapFireRateLvl;
		int m_bulletBaseSpeed, m_bulletSpeedPerLvl, m_bulletSpeedLvl;
		int m_shipBaseHP, m_shipHPperLvl, m_shipHPLvl;
		int m_shipBaseVel, m_shipVelLvl;
		int m_shipAccelLvl;

		bool m_playerMoving;
		bool m_playerFiring;
};

#endif