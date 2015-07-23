#include "BaseChar.h"

//Constructor
BaseChar::BaseChar()
{

}

void BaseChar::DrawChar(BITMAP *buffer)
{
	masked_blit(m_charSprite, buffer, 0, 0, m_xPos - m_boundX, m_yPos - m_boundY, m_charSprite->w, m_charSprite->h);
}

//Destroys bitmaps if they exist
void BaseChar::DestroyBitmaps()
{
	if(m_charSprite != NULL)
	{
		destroy_bitmap(m_charSprite);
	}
	
	if(m_bulletSprite != NULL)
	{
		destroy_bitmap(m_bulletSprite);
	}
}

//Checks for collision against position passed in - returns true if collision is occuring
bool BaseChar::CollisionCheck(float xPos, float yPos)
{
	if(m_xPos - m_boundX < xPos && xPos < m_xPos + m_boundX &&
		m_yPos - m_boundY < yPos && yPos < m_yPos + m_boundY)
	{
		return true;
	}

	else
	{
		return false;
	}
}

//Reduces character HP by value passed in - returns true if character is dead
bool BaseChar::TakeDamage(int damage)
{
	m_shipCurrHP -= damage;

	if(m_shipCurrHP <= 0)
	{
		return true;
	}

	else
	{
		return false;
	}
}

//++++++++++++++++
//Getters
//++++++++++++++++
int BaseChar::GetID()
{
	return m_ID;
}

int BaseChar::GetAtkCD()
{
	return m_atkCDCounter;
}

float BaseChar::GetXPos()
{
	return m_xPos;
}

float BaseChar::GetYPos()
{
	return m_yPos;
}

float BaseChar::GetBoundX()
{
	return m_boundX;
}

float BaseChar::GetBoundY()
{
	return m_boundY;
}

int BaseChar::GetCurrHP()
{
	return m_shipCurrHP;
}

int BaseChar::GetWeapFireRate()
{
	return m_weapFireRate;
}

int BaseChar::GetWeapDamage()
{
	return m_weapDmg;
}

float BaseChar::GetBulletSpeed()
{
	return m_bulletSpeed;
}

BITMAP* BaseChar::GetBulletImage()
{
	return m_bulletSprite;
}

//+++++++++++++++
//Setters
//+++++++++++++++
void BaseChar::SetAtkCD(int atkCD)
{
	if(atkCD != 0)
	{
		m_atkCDCounter += atkCD;
	}
	else
		m_atkCDCounter = atkCD;
}

//Destructor
BaseChar::~BaseChar()
{

}