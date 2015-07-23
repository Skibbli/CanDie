#include "Bullet.h"

//Constructor with basechar as parameter to init the members of this bullet object being created
Bullet::Bullet(BaseChar &character)
{
	//Initialises bullet variables with those of base char parameter
	m_ID = character.GetID();
	
	m_xPos = character.GetXPos();
	m_yPos = character.GetYPos();
	m_velocity = character.GetBulletSpeed();
	m_damage = character.GetWeapDamage();

	m_bulletImage = character.GetBulletImage();

	if(m_ID == PLAYER)
	{
		m_direction = -1;
	}

	else
	{
		m_direction = 1;
	}
}

//Updates position and returns whether bullet is out of bounds
bool Bullet::UpdateAndBoundsCheck()
{
	//Update position of bullet
	m_yPos += m_velocity * m_direction; 
	
	//Return true if bullet goes out of bounds, otherwise return false
	if((m_ID == ENEMY && m_yPos > SCREEN_H + 20) || (m_ID == PLAYER && m_yPos < 0 - 20))
	{
		return true;
	}

	else
	{
		return false;
	}	 
}

//Draws bullet on to the bitmap passed in
void Bullet::DrawBullet(BITMAP *buffer)
{
	masked_blit(m_bulletImage, buffer, 0, 0, m_xPos - m_bulletImage->w / 2, m_yPos - m_bulletImage->h / 2, m_bulletImage->w, m_bulletImage->h);
}

//+++++++++++++++
//Getters
//+++++++++++++++
int Bullet::GetDamage()
{
	return m_damage;
}

int Bullet::GetID()
{
	return m_ID;
}

float Bullet::GetXPos()
{
	return m_xPos;
}

float Bullet::GetYPos()
{
	return m_yPos;
}

//++++++++++++++++
//Setters
//++++++++++++++++
void Bullet::SetXPos(float xPos)
{
	m_xPos = xPos;
}

//Destructor
Bullet::~Bullet()
{

}