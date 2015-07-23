#include "Shop.h"

//Constructor with player address to initialise player pointer
Shop::Shop(Player &myPlayer)
{
	m_myPlayer = &myPlayer;

	//Load background bitmap and display error if it fails
	m_background = load_bitmap("Images/ShopBG.bmp", 0);
	
	if(!m_background)
	{
		allegro_message("SHOP SCREEN BITMAP");
		exit(-1);
	}

	//Load font and display error if it fails
	m_myfont = load_font("Fonts/font2.pcx", NULL, NULL);

	if(!m_myfont)
	{
		allegro_message("SHOP FONT");
		exit(-1);
	}


	m_mouseCounter = 0;
}

void Shop::HandleEvents()
{
	//This is used to pick up only one mouse click - will be true for the below checks for the first frame 
	//and then the mouse must be released before the below checks can be true again
	if(mouse_b & 1)
	{
		m_mouseCounter++;
	}

	else
	{
		m_mouseCounter = 0;
	}
	
	if(m_mouseCounter == 1)
	{
		//This chain of IF statements is used to pick up when the player clicks on specific areas of the screen
		//so that the appropriate upgrade can be purchased (if possible). It passes an int into the function and
		//that function then changes the corresponding variable
		if(15 < mouse_x && mouse_x < 315 && 150 < mouse_y && mouse_y < 450 && m_myPlayer->GetShipHPLvl() <= 5)
		{
			m_myPlayer->UpgradeShip(1);
		}

		else if(330 < mouse_x && mouse_x < 630 && 150 < mouse_y && mouse_y < 450 && m_myPlayer->GetShipVelLvl() <= 5)
		{
			m_myPlayer->UpgradeShip(2);
		}

		else if(660 < mouse_x && mouse_x < 960 && 150 < mouse_y && mouse_y < 450 && m_myPlayer->GetShipAccelLvl() <= 5)
		{
			m_myPlayer->UpgradeShip(3);
		}

		else if(15 < mouse_x && mouse_x < 315 && 500 < mouse_y && mouse_y < 800 && m_myPlayer->GetWeapDmgLvl() <= 5)
		{
			m_myPlayer->UpgradeShip(4);
		}

		else if(330 < mouse_x && mouse_x < 630 && 500 < mouse_y && mouse_y < 800 && m_myPlayer->GetWeapRateLvl() <= 5)
		{
			m_myPlayer->UpgradeShip(5);
		}

		else if(660 < mouse_x && mouse_x < 960 && 500 < mouse_y && mouse_y < 800 && m_myPlayer->GetBulletSpeedLvl() <= 5)
		{
			m_myPlayer->UpgradeShip(6);
		}

		else if(mouse_x > 910 && mouse_x < 975 && mouse_y > 25 && mouse_y < 100 && m_mouseCounter == 1)
		{
			m_nextState = STATE_LEVEL_SELECT;
		}
	}
}

void Shop::Logic()
{

}

void Shop::Render()
{
	//Here the main background is drawn and then the values that go with each of the upgrade options is drawn on top of it.
	//If the upgrade limit has been reached then the word MAXED wil be displayed instead, indicating no more upgrades are possible
	show_mouse(NULL);
	blit(m_background, m_buffer, 0, 0, 0, 0, m_background->w, m_background->h);

	if(m_myPlayer->GetShipHPLvl() <= 5)
	{
		textprintf_ex(m_buffer, m_myfont, 100, 415, makecol(255, 120, 183), -1, "Ship HP Lvl: %i", m_myPlayer->GetShipHPLvl());
		textprintf_ex(m_buffer, m_myfont, 85, 445, makecol(255, 120, 183), -1, "Upgrade Cost: %i", (m_myPlayer->GetShipHPLvl() * 50));
	}
	else
	{
		textout_ex(m_buffer, m_myfont, "MAXED", 155, 430, makecol(255, 120, 183), -1);
	}

	if(m_myPlayer->GetShipVelLvl() <= 5)
	{
		textprintf_ex(m_buffer, m_myfont, 390, 415, makecol(255, 120, 183), -1, "Ship Speed Lvl: %i", m_myPlayer->GetShipVelLvl());
		textprintf_ex(m_buffer, m_myfont, 390, 445, makecol(255, 120, 183), -1, "Upgrade Cost: %i", (m_myPlayer->GetShipVelLvl() * 50));
	}
	else
	{
		textout_ex(m_buffer, m_myfont, "MAXED", 470, 430, makecol(255, 120, 183), -1);
	}

	if(m_myPlayer->GetShipAccelLvl() <= 5)
	{
		textprintf_ex(m_buffer, m_myfont, 690, 415, makecol(255, 120, 183), -1, "Ship Handling Lvl: %i", m_myPlayer->GetShipAccelLvl());
		textprintf_ex(m_buffer, m_myfont, 690, 445, makecol(255, 120, 183), -1, "Upgrade Cost: %i", (m_myPlayer->GetShipAccelLvl() * 50));
	}
	else
	{
		textout_ex(m_buffer, m_myfont, "MAXED", 770, 430, makecol(255, 120, 183), -1);
	}

	if(m_myPlayer->GetWeapDmgLvl() <= 5)
	{
		textprintf_ex(m_buffer, m_myfont, 77, 720, makecol(255, 120, 183), -1, "Weapon Dmg Lvl: %i", m_myPlayer->GetWeapDmgLvl());
		textprintf_ex(m_buffer, m_myfont, 77, 750, makecol(255, 120, 183), -1, "Upgrade Cost: %i", (m_myPlayer->GetWeapDmgLvl() * 50));
	}
	else
	{
		textout_ex(m_buffer, m_myfont, "MAXED", 155, 740, makecol(255, 120, 183), -1);
	}

	if(m_myPlayer->GetWeapRateLvl() <= 5)
	{
		textprintf_ex(m_buffer, m_myfont, 385, 720, makecol(255, 120, 183), -1, "Weapon Rate Lvl: %i", m_myPlayer->GetWeapRateLvl());
		textprintf_ex(m_buffer, m_myfont, 385, 750, makecol(255, 120, 183), -1, "Upgrade Cost: %i", (m_myPlayer->GetWeapRateLvl() * 50));
	}
	else
	{
		textout_ex(m_buffer, m_myfont, "MAXED", 470, 740, makecol(255, 120, 183), -1);
	}

	if(m_myPlayer->GetWeapRateLvl() <= 5)
	{
		textprintf_ex(m_buffer, m_myfont, 690, 720, makecol(255, 120, 183), -1, "Bullet Speed Lvl: %i", m_myPlayer->GetBulletSpeedLvl());
		textprintf_ex(m_buffer, m_myfont, 690, 750, makecol(255, 120, 183), -1, "Upgrade Cost: %i", (m_myPlayer->GetBulletSpeedLvl() * 50));
	}
	else
	{
		textout_ex(m_buffer, m_myfont, "MAXED", 770, 740, makecol(255, 120, 183), -1);
	}

	textprintf_ex(m_buffer, m_myfont, 440, 925, makecol(255, 120, 183), -1, "Sugar: %i", m_myPlayer->GetSugar());
	blit(m_buffer, screen, 0, 0, 0, 0, m_buffer->w, m_buffer->h);
	show_mouse(screen);
}

//Destructor
Shop::~Shop()
{
	//This saves the player data to the player data CSV file so that if the game is quit their progress is available next time.
	//It is saved at various stages in the program to mitigate loss of data if program quits unexpectedly
	m_myPlayer->SavePlayer();
	m_myPlayer = NULL;

	//Destroys custom font to avoid memory leaks
	destroy_font(m_myfont);
}