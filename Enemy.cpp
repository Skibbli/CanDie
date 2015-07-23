#include "Enemy.h"
#include <fstream>
#include <string>
#include <vector>

//Constructor - parameter of line number to load the corresponding line in the enemy CSV
Enemy::Enemy(int lineNo)
{
	//Open CSV containing enemy data
	std::ifstream inFile;
	inFile.open("Enemy Data.csv");

	//Check file has opened correctly
	if(inFile.fail())
	{
		allegro_message("ENEMY DATA FILE");
		exit(-1);
	}
	
	//Use the line number parameter to read the data up to the line we want
	std::string input;
	
	for(int i = 0; i < lineNo; i++)
	{
		std::getline(inFile, input, '?');
	}

	char skip;

	//Extract data from the text file in to the class variables, using the above variable to ignore the ',' separators
	inFile >> m_shipMaxHP >> skip >> m_shipVelocity >> skip >> m_weapDmg >> skip;
	inFile >> m_weapFireRate >> skip >> m_bulletSpeed >> skip;
	std::getline(inFile, m_shipImgNo, ',');
	std::getline(inFile, m_bulletImgNo, ',');
	inFile >> m_level >> skip >> m_sugarReward;

	//Load the corresponding enemy images dependant on the image numbers in the file - also give error message if open fails
	std::string fileName = "Images/EnemyIMG.bmp";

	m_charSprite = load_bitmap(fileName.insert(15, m_shipImgNo).c_str(), 0);

	if(!m_charSprite)
	{
		allegro_message("ENEMY SHIP BITMAP");
		exit(-1);
	}

	fileName = "Images/BulletIMG.bmp";

	m_bulletSprite = load_bitmap(fileName.insert(16, m_bulletImgNo).c_str(), 0);

	if(!m_bulletSprite)
	{
		allegro_message("ENEMY BULLET BITMAP");
		exit(-1);
	}

	//Initialise necessary variables
	m_boundX = m_charSprite->w / 2;
	m_boundY = m_charSprite->h / 2;
	m_atkCDCounter = 0;
	m_yPos = -100;
	m_shipCurrHP = m_shipMaxHP;
	m_ID = ENEMY;
}

bool Enemy::UpdateAndBoundsCheck()
{
	//Update enemy position
	m_yPos += m_shipVelocity;

	//If enemy has gone off screen return true so that it can be deleted and level health reduced
	if(m_yPos > SCREEN_H + 50)
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool Enemy::PlayerCollisionCheck(Player &myPlayer)
{
	//Check if enemy is colliding with player - if true return true for player health
	// to be decreased and enemy destroyed
	if(m_xPos - m_boundX < myPlayer.GetXPos() + myPlayer.GetBoundX() &&
		m_xPos + m_boundX > myPlayer.GetXPos() - myPlayer.GetBoundX() &&
		m_yPos + m_boundY > myPlayer.GetYPos() - myPlayer.GetBoundY() &&
		m_yPos - m_boundY < myPlayer.GetYPos() - myPlayer.GetBoundY())
	{
		return true;
	}

	else
	{
		return false;
	}
}

void Enemy::SetXPos(float xPos)
{
	m_xPos = xPos;
}

void Enemy::SetYPos(float yPos)
{
	m_yPos = yPos;
}

int Enemy::GetSugarReward()
{
	return m_sugarReward;
}

//Destructor
Enemy::~Enemy()
{

}