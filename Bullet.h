#pragma once

//Include guards
#ifndef BULLET_H
#define BULLET_H

//Include necessary extra files
#include "BaseChar.h"

class Bullet
{
public:
	Bullet(BaseChar &character);
	~Bullet();

	bool UpdateAndBoundsCheck();

	void DrawBullet(BITMAP *buffer);

	//Getters
	int GetID();
	int GetDamage();
	float GetXPos();
	float GetYPos();

	
	//Setters
	void SetXPos(float xPos);
	void SetYPos(float yPos);
	void SetVelocity(float velocity);

protected:

private:
	int m_ID;
	int m_damage;
	int m_direction;
	
	float m_xPos;
	float m_yPos;
	float m_velocity;

	BITMAP *m_bulletImage;
};

#endif
