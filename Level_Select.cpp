#include "Level_Select.h"
#include <string>
#include <fstream>

//Constructor with player parameter to initialise player pointer
Level_Select::Level_Select(Player &myPlayer)
{
	m_myPlayer = &myPlayer;

	//Gets current level of player so that only levels player has access to are drawn later
	m_playerLevel = m_myPlayer->GetLevel();
	
	//Loading of bitmaps - checks if loading fails and if so gives error message and exits
	m_background = load_bitmap("Images/LevelSelectBG.bmp", 0);

	if(!m_background)
	{
		allegro_message("LEVEL SELECT BG BITMAP");
		exit(-1);
	}

	m_level1BG = load_bitmap("Images/Level1BG.bmp", 0);

	if(!m_level1BG)
	{
		allegro_message("LEVEL 1 BG BITMAP");
		exit(-1);
	}

	m_level2BG = load_bitmap("Images/Level2BG.bmp", 0);

	if(!m_level2BG)
	{
		allegro_message("LEVEL 2 BG BITMAP");
		exit(-1);
	}

	m_level3BG = load_bitmap("Images/Level3BG.bmp", 0);

	if(!m_level3BG)
	{
		allegro_message("LEVEL 3 BG BITMAP");
		exit(-1);
	}

	m_level4BG = load_bitmap("Images/Level4BG.bmp", 0);

	if(!m_level4BG)
	{
		allegro_message("LEVEL 4 BG BITMAP");
		exit(-1);
	}

	m_level5BG = load_bitmap("Images/Level5BG.bmp", 0);

	if(!m_level5BG)
	{
		allegro_message("LEVEL 5 BG BITMAP");
		exit(-1);
	}

	m_level6BG = load_bitmap("Images/Level6BG.bmp", 0);

	if(!m_level6BG)
	{
		allegro_message("LEVEL 6 BG BITMAP");
		exit(-1);
	}
}

void Level_Select::HandleEvents()
{
	//Gets user input and changes state based off their choices
	if(key[KEY_ESC])
	{
		m_nextState = STATE_TITLE;
	}

	if(mouse_b & 1)
	{
		m_mouseCounter++;
	}
	else
	{
		m_mouseCounter = 0;
	}

	//Offers player the levels they have access to, the candy store or an exit. When they choose a level that is set to
	//the active level on the player so that the appropriate enemies and level difficulty can be loaded for the level
	if(m_mouseCounter == 1)
	{
		if(15 < mouse_x && mouse_x < 315 && 150 < mouse_y && mouse_y < 450 && 0 < m_playerLevel)
		{
			m_myPlayer->SetActiveLevel(1);
			m_nextState = STATE_PLAYING_LEVEL;
		}

		else if(330 < mouse_x && mouse_x < 630 && 150 < mouse_y && mouse_y < 450 && 1 < m_playerLevel)
		{
			m_myPlayer->SetActiveLevel(2);
			m_nextState = STATE_PLAYING_LEVEL;
		}

		else if(660 < mouse_x && mouse_x < 960 && 150 < mouse_y && mouse_y < 450 && 2 < m_playerLevel)
		{
			m_myPlayer->SetActiveLevel(3);
			m_nextState = STATE_PLAYING_LEVEL;
		}

		else if(15 < mouse_x && mouse_x < 315 && 500 < mouse_y && mouse_y < 800 && 3 < m_playerLevel)
		{
			m_myPlayer->SetActiveLevel(4);
			m_nextState = STATE_PLAYING_LEVEL;
		}

		else if(330 < mouse_x && mouse_x < 630 && 500 < mouse_y && mouse_y < 800 && 4 < m_playerLevel)
		{
			m_myPlayer->SetActiveLevel(5);
			m_nextState = STATE_PLAYING_LEVEL;
		}

		else if(660 < mouse_x && mouse_x < 960 && 500 < mouse_y && mouse_y < 800 && 5 < m_playerLevel)
		{
			m_myPlayer->SetActiveLevel(6);
			m_nextState = STATE_PLAYING_LEVEL;
		}

		else if(50 < mouse_x && mouse_x < 950 && 900 < mouse_y && mouse_y < 990)
		{
			m_nextState = STATE_SHOP;
		}

		else if(mouse_x > 910 && mouse_x < 975 && mouse_y > 25 && mouse_y < 100 && m_mouseCounter == 1)
		{
			m_nextState = STATE_TITLE;
		}
	}
}

void Level_Select::Logic()
{

}

void Level_Select::Render()
{
	//This draws the base background and then draws the levels the player has access to, based off their overall level
	blit(m_background, m_buffer, 0, 0, 0, 0, m_buffer->w, m_buffer->h);
	
	if(0 < m_playerLevel)
	{
		stretch_blit(m_level1BG, m_buffer, 0, 0, m_level1BG->w, m_level1BG->h, 75, 235, 250, 250);
	}

	if(1 < m_playerLevel)
	{
		stretch_blit(m_level2BG, m_buffer, 0, 0, m_level2BG->w, m_level2BG->h, 385, 235, 250, 250);
	}

	if(2 < m_playerLevel)
	{
		stretch_blit(m_level3BG, m_buffer, 0, 0, m_level3BG->w, m_level3BG->h, 695, 235, 250, 250);
	}

	if(3 < m_playerLevel)
	{
		stretch_blit(m_level4BG, m_buffer, 0, 0, m_level4BG->w, m_level4BG->h, 75, 550, 250, 250);
	}

	if(4 < m_playerLevel)
	{
		stretch_blit(m_level5BG, m_buffer, 0, 0, m_level5BG->w, m_level5BG->h, 385, 550, 250, 250);
	}

	if(4 < m_playerLevel)
	{
		stretch_blit(m_level6BG, m_buffer, 0, 0, m_level6BG->w, m_level6BG->h, 690, 550, 250, 250);
	}

	//The buffer is now blitted on to the screen
	show_mouse(NULL);
	blit(m_buffer, screen, 0, 0, 0, 0, m_buffer->w, m_buffer->h);
	show_mouse(screen);
}

//Destructor
Level_Select::~Level_Select()
{
	//Destroys all the bitmaps used in this gamestates to avoid memory leaks when the program exits
	destroy_bitmap(m_level1BG);
	destroy_bitmap(m_level2BG);
	destroy_bitmap(m_level3BG);
	destroy_bitmap(m_level4BG);
	destroy_bitmap(m_level5BG);
	destroy_bitmap(m_level6BG);
}