#pragma once

//Include guards
#ifndef BASECHAR_H
#define BASECHAR_H

//Include necessary files
#include <allegro.h>
#include <string>

//Declare enum used for bullet identification
enum ID {PLAYER, ENEMY};

class BaseChar
{
	public:
		BaseChar();
		~BaseChar();

		void DrawChar(BITMAP *buffer);
		void DestroyBitmaps();
		
		bool CollisionCheck(float xPos, float yPos);
		bool TakeDamage(int damage);

		//Getters
		int GetID();
		int GetAtkCD();
		float GetXPos();
		float GetYPos();
		float GetBoundX();
		float GetBoundY();
		int GetCurrHP();
		int GetWeapFireRate();
		int GetWeapDamage();
		float GetBulletSpeed();

		BITMAP* GetBulletImage();

		//Setters
		void SetAtkCD(int atkCD);

	protected:
		int m_ID;
		int m_level;
		int m_shipMaxHP;
		int m_shipCurrHP;

		int m_atkCDCounter;

		int m_weapDmg;
		float m_bulletSpeed;
		int m_weapFireRate;

		float m_xPos;
		float m_yPos;

		float m_boundX;
		float m_boundY;

		BITMAP *m_charSprite;
		BITMAP *m_bulletSprite;

		std::string m_shipImgNo;
		std::string m_bulletImgNo;

	private:
};

#endif