#include "Player.h"
#include <fstream>
#include <vector>
#include <string>

//Constructor
Player::Player()
{
	m_ID = PLAYER;

	//Set the two bitmaps to NULL as they are not initialised until later
	m_charSprite = NULL;
	m_bulletSprite = NULL;
}

void Player::IncreaseLevel()
{
	m_level++;
}

void Player::EarnSugar(int sugar)
{
	m_sugar += sugar;
}

//Loads the player sprite based off choices they make at the title menu
void Player::LoadShipSprite(std::string shipImgNo)
{
	//If player chooses previous save then -1 is passed in here. This is then filtered out here
	//so that the player image number isn't overwritten incorrectly. Otherwise the image number is
	//updated with the player choice at the title screen
	if(shipImgNo != "-1")
	{
		m_shipImgNo = shipImgNo;
	}

	//Uses the player image number to load the corresponding image from the source directory
	//Gives and error if it fails then exits program
	std::string fileName = "Images/PlayerIMG.bmp";

	m_charSprite = load_bitmap(fileName.insert(16, m_shipImgNo).c_str(), 0);

	if(!m_charSprite)
	{
		allegro_message("PLAYER SHIP BITMAP");
		exit(-1);
	}

	//Inits bounding box for player based off the size of their ship bitmap
	m_boundX = m_charSprite->w / 2;
	m_boundY = m_charSprite->h / 2;
}

//Gets player movement and firing input
void Player::GetPlayerMovement()
{
	if(key[KEY_UP])
	{
		m_yVelocity -= m_shipAccel;
		m_playerMoving = true;

		if(m_yVelocity < -m_maxShipVel)
		{
			m_yVelocity = -m_maxShipVel;
		}
	}

	if(key[KEY_DOWN])
	{
		m_yVelocity += m_shipAccel;
		m_playerMoving = true;

		if(m_yVelocity > m_maxShipVel)
		{
			m_yVelocity = m_maxShipVel;
		}
	}

	if(key[KEY_LEFT])
	{
		m_xVelocity -= m_shipAccel;
		m_playerMoving = true;

		if(m_xVelocity < -m_maxShipVel)
		{
			m_xVelocity = -m_maxShipVel;
		}
	}

	if(key[KEY_RIGHT])
	{
		m_xVelocity += m_shipAccel;
		m_playerMoving = true;

		if(m_xVelocity > m_maxShipVel)
		{
			m_xVelocity = m_maxShipVel;
		}
	}

	if(key[KEY_SPACE])
	{
		m_playerFiring = true;
	}
}

//Loads player data from the save file based off choice at title menu
//New game is line 1, previous save is line 2
void Player::LoadPlayerStats(int lineNo)
{
	//Opens player save file - gives error message and exits program if file not found
	std::ifstream inFile("Player Data.csv");

	if(inFile.fail())
	{
		allegro_message("PLAYER DATA FILE");
		exit(-1);
	}
	
	//Reads the corresponding line from the text file and initialises the player variables
	//with this data using the stream object
	std::string input;
		
	for(int i = 0; i < lineNo; i++)
	{
		std::getline(inFile, input, '?');
	}

	char skip;

	inFile >> m_shipBaseHP >> skip >> m_shipHPperLvl >> skip >> m_shipHPLvl >> skip;
	inFile >> m_shipBaseVel  >> skip >> m_shipVelPerLvl >> skip >> m_shipVelLvl >> skip;
	inFile >> m_shipBaseAccel >> skip >> m_shipAccelPerLvl >> skip >> m_shipAccelLvl >> skip;
	inFile >> m_weapBaseDmg >> skip >> m_weapDmgPerLvl >> skip >> m_weapDmgLvl >> skip;
	inFile >> m_weapBaseFireRate >> skip >> m_weapFireRatePerLvl >> skip >> m_weapFireRateLvl >> skip;
	inFile >> m_bulletBaseSpeed >> skip >> m_bulletSpeedPerLvl >> skip >> m_bulletSpeedLvl >> skip;
	std::getline(inFile, m_shipImgNo, ',');
	std::getline(inFile, m_bulletImgNo, ',');
	inFile >> m_level >> skip >> m_sugar;

	//Loads the bullet image - if it fails give error message and exit program
	std::string fileName = "Images/BulletIMG.bmp";

	m_bulletSprite = load_bitmap(fileName.insert(16, m_bulletImgNo).c_str(), 0);

	if(!m_bulletSprite)
	{
		allegro_message("PLAYER BULLET IMAGE");
		exit(-1);
	}
}

//Resets the player variables that need to be reset in between levels
void Player::ResetPlayer()
{
	m_xPos = 500.0f;
	m_yPos = 950.0f;

	m_xVelocity = 0;
	m_yVelocity = 0;

	m_playerMoving = false;
	m_playerFiring = false;

	m_shipCurrHP = m_shipMaxHP;
	m_atkCDCounter = m_weapFireRate;
}

//Saves player data to the save file so that progress can be resumed later
void Player::SavePlayer()
{
	//Opens save file and gives error + exits if can't open
	std::fstream outFile("Player Data.csv");

	if(!outFile)
	{
		allegro_message("PLAYER DATA");
		exit(-1);
	}

	//Gets input from the save file up to the beginning of the save data line
	//Sets the output pointer to where the input pointer is located then writes
	//the player variables that need to be saved to the text file
	char *input = new char[250];

	outFile.getline(input, 250, '?');
	outFile.getline(input, 250, '?');

	outFile.seekp(outFile.tellg());

	outFile << '\n' << m_shipBaseHP << ',' << m_shipHPperLvl << ',' << m_shipHPLvl << ',';
	outFile << m_shipBaseVel << ',' << m_shipVelPerLvl << ',' << m_shipVelLvl << ',';
	outFile << m_shipBaseAccel << ',' << m_shipAccelPerLvl << ',' << m_shipAccelLvl << ',';
	outFile << m_weapBaseDmg << ',' << m_weapDmgPerLvl << ',' << m_weapDmgLvl << ',';
	outFile << m_weapBaseFireRate << ',' << m_weapFireRatePerLvl << ',' << m_weapFireRateLvl << ',';
	outFile << m_bulletBaseSpeed << ',' << m_bulletSpeedPerLvl << ',' << m_bulletSpeedLvl << ',';
	outFile << m_shipImgNo << ',' <<  m_bulletImgNo << ',' << m_level << ',' << m_sugar << ',' << '?';

	outFile.close();

	//Deletes the dynamically allocated char array that stored the temp input data
	delete input;
}

//Updates player movement variables and does bounds checking
void Player::UpdatePlayer()
{
	//If player is not moving then ship is slowed by its handling variable
	if(!m_playerMoving)
	{
		if((0 < m_xVelocity && m_xVelocity < m_shipAccel) || (-m_shipAccel < m_xVelocity && m_xVelocity < 0))
		{
			m_xVelocity = 0;
		}

		if((0 < m_yVelocity && m_yVelocity < m_shipAccel) || (-m_shipAccel < m_yVelocity && m_yVelocity < 0))
		{
			m_yVelocity = 0;
		}

		if(m_xVelocity != 0)
		{
			if(m_xVelocity > 0)
			{
				m_xVelocity -= m_shipAccel;
			}

			else if(m_xVelocity < 0)
			{
				m_xVelocity += m_shipAccel;
			}
		}

		if(m_yVelocity != 0)
		{
			if(m_yVelocity > 0)
			{
				m_yVelocity -= m_shipAccel;
			}

			else if(m_yVelocity < 0)
			{
				m_yVelocity += m_shipAccel;
			}
		}
	}

	m_xPos += m_xVelocity;
	m_yPos += m_yVelocity;

	if(m_xPos > SCREEN_W - 35)
	{
		m_xPos = SCREEN_W - 35;
		m_xVelocity = 0;
	}

	else if(m_xPos < 35)
	{
		m_xPos = 35;
		m_xVelocity = 0;
	}

	if(m_yPos > SCREEN_H - 35)
	{
		m_yPos = SCREEN_H - 35;
		m_yVelocity = 0;
	}

	else if(m_yPos < SCREEN_H - 350)
	{
		m_yPos = SCREEN_H - 350;
		m_yVelocity = 0;
	}

	m_playerMoving = false;
}

void Player::TotalStatUpdate()
{
	m_shipMaxHP = m_shipBaseHP + m_shipHPperLvl * m_shipHPLvl;
	
	m_maxShipVel = m_shipBaseVel + m_shipVelPerLvl * m_shipVelLvl;
	m_shipAccel = m_shipBaseAccel + m_shipAccelPerLvl * m_shipAccelLvl;
	m_weapDmg = m_weapBaseDmg + m_weapDmgPerLvl * m_weapDmgLvl;
	m_weapFireRate = m_weapBaseFireRate - m_weapFireRatePerLvl * m_weapFireRateLvl;
	m_bulletSpeed = m_bulletBaseSpeed + m_bulletSpeedPerLvl * m_bulletSpeedLvl;
}

//Upgrades different parts of the ship dependant on what is selected at the shop
void Player::UpgradeShip(int choice)
{
	switch(choice)
	{
	case 1:
		{
			if(m_shipHPLvl <= 5 && m_sugar >= (m_shipHPLvl * 50))
			{
				m_sugar -= (m_shipHPLvl * 50);
				m_shipHPLvl++;
			}
		}
		break;
	case 2:
		{
			if(m_shipVelLvl <= 5 && m_sugar >= (m_shipVelLvl * 50))
			{
				m_sugar -= (m_shipVelLvl * 50);
				m_shipVelLvl++;
			}
		}
		break;
	case 3:
		{
			if(m_shipAccelLvl <= 5 && m_sugar >= (m_shipAccelLvl * 50))
			{
				m_sugar -= (m_shipAccelLvl * 50);
				m_shipAccelLvl++;
			}
		}
		break;
	case 4:
		{
			if(m_weapDmgLvl <= 5 && m_sugar >= (m_weapDmgLvl * 50))
			{
				m_sugar -= (m_weapDmgLvl * 50);
				m_weapDmgLvl++;
			}
		}
		break;
	case 5:
		{
			if(m_weapFireRateLvl <= 5 && m_sugar >= (m_weapFireRateLvl * 50))
			{
				m_sugar -= (m_weapFireRateLvl * 50);
				m_weapFireRateLvl++;
			}
		}
		break;
	case 6:
		{
			if(m_bulletSpeedLvl <= 5 && m_sugar >= (m_bulletSpeedLvl * 50))
			{
				m_sugar -= (m_bulletSpeedLvl * 50);
				m_bulletSpeedLvl++;
			}
		}
		break;
	}
}

//+++++++++++++++++
//Getters
//+++++++++++++++++
bool Player::GetIsFiring()
{
	return m_playerFiring;
}

int Player::GetSugar()
{
	return m_sugar;
}

int Player::GetLevel()
{
	return m_level;
}

int Player::GetActiveLevel()
{
	return m_activeLevel;
}

int Player::GetShipHPLvl()
{
	return m_shipHPLvl;
}

int Player::GetShipVelLvl()
{
	return m_shipVelLvl;
}

int Player::GetShipAccelLvl()
{
	return m_shipAccelLvl;
}

int Player::GetWeapDmgLvl()
{
	return m_weapDmgLvl;
}

int Player::GetWeapRateLvl()
{
	return m_weapFireRateLvl;
}

int Player::GetBulletSpeedLvl()
{
	return m_bulletSpeedLvl;
}

//+++++++++++++++
//Setters
//+++++++++++++++
void Player::SetIsFiring(bool isFiring)
{
	m_playerFiring = isFiring;
}

void Player::SetActiveLevel(int level)
{
	m_activeLevel = level;
}

//Destructor
Player::~Player()
{

}