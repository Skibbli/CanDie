#include "Title.h"
#include <fstream>
#include <sstream>

//Constructor - address of player as parameter to initialise the player pointer in this gamestate
Title::Title(Player &myPlayer)
{
	//Load BITMAPS for this gamestate. If they fail exit program and display relevant error message
	m_background = load_bitmap("Images/TitleBG.bmp", 0);

	if(!m_background)
	{
		allegro_message("TITLE BACKGROUND BITMAP");
		exit(-1);
	}

	m_ship1 = load_bitmap("Images/PlayerIMG1.bmp", 0);

	if(!m_ship1)
	{
		allegro_message("PLAYER SHIP BITMAP 3");
		exit(-1);
	}

	m_ship2 = load_bitmap("Images/PlayerIMG2.bmp", 0);

	if(!m_ship2)
	{
		allegro_message("PLAYER SHIP BITMAP 2");
		exit(-1);
	}

	m_ship3 = load_bitmap("Images/PlayerIMG3.bmp", 0);

	if(!m_ship3)
	{
		allegro_message("PLAYER SHIP BITMAP 3");
		exit(-1);
	}

	m_ship4 = load_bitmap("Images/PlayerIMG4.bmp", 0);

	if(!m_ship4)
	{
		allegro_message("PLAYER SHIP BITMAP 4");
		exit(-1);
	}

	m_newGameButton = load_bitmap("Images/NewGameButton.bmp", 0);

	if(!m_newGameButton)
	{
		allegro_message("NEW GAME BUTTON");
		exit(-1);
	}

	m_loadGameButton = load_bitmap("Images/LoadGameButton.bmp", 0);

	if(!m_loadGameButton)
	{
		allegro_message("LOAD GAME BUTTON");
		exit(-1);
	}

	m_instructionsButton = load_bitmap("Images/InstructionsButton.bmp", 0);

	if(!m_instructionsButton)
	{
		allegro_message("INSTRUCTIONS BUTTON");
		exit(-1);
	}

	m_instructions = load_bitmap("Images/Instructions.bmp", 0);

	if(!m_instructions)
	{
		allegro_message("INSTRUCTIONS");
		exit(-1);
	}

	m_cloud = load_bitmap("Images/Cloud.bmp", 0);

	if(!m_cloud)
	{
		allegro_message("CLOUD");
		exit(-1);
	}

	m_myPlayer = &myPlayer;
	m_state = SAVE_SELECT;
	m_mouseCounter = 0;

	//Load CSV file containing player data to check if existing save is present. If file not found display relevant error
	std::ifstream inFile("Player Data.csv");
			
	if(inFile.fail())
	{
		allegro_message("PLAYER DATA FILE");
		exit(-1);
	}
	
	int lineCounter = 0;
	std::string input;

	//This counts how many lines are in the file delimited by '?' - if more than 2 this means previous save is present
	while(!inFile.eof())
	{
		std::getline(inFile, input, '?');
		lineCounter++;
	}

	if(lineCounter > 2)
	{
		m_prevSavePresent = true;
	}
}

void Title::HandleEvents()
{
	//This counter is used to get only one mouse press
	if(mouse_b & 1)
	{
		m_mouseCounter++;
	}
	else
	{
		m_mouseCounter = 0;
	}

	//Offers player the options of new game, load previous game or instructions - if one is clicked then internal state is changed
	if(m_state == SAVE_SELECT)
	{		
		if(mouse_x > 225 && mouse_x < 775 && mouse_y > 180 && mouse_y < 430 && m_mouseCounter == 1)
		{
			m_state = SHIP_SELECT;
			m_saveSelect = 1;
		}

		else if(mouse_x > 225 && mouse_x < 775 && mouse_y > 450 && mouse_y < 700 && m_mouseCounter == 1 && m_prevSavePresent == true)
		{		
			m_nextState = STATE_LEVEL_SELECT;
			m_saveSelect = 2;
			m_shipImgNo = "-1";
		}

		else if(mouse_x > 225 && mouse_x < 775 && mouse_y > 720 && mouse_y < 970 && m_mouseCounter == 1)
		{
			m_state = INSTRUCTIONS;
		}

		else if(mouse_x > 910 && mouse_x < 975 && mouse_y > 25 && mouse_y < 100 && m_mouseCounter == 1)
		{
			m_nextState = STATE_EXIT;
		}
	}

	//If player has selected new game offer selection of ships
	else if(m_state == SHIP_SELECT)
	{
		if(mouse_x > 225 && mouse_x < 495 && mouse_y > 295 && mouse_y < 545 && m_mouseCounter == 1)
		{
			m_shipImgNo = "1";
			m_state = FINISHED;
			m_nextState = STATE_LEVEL_SELECT;
		}

		else if(mouse_x > 575 && mouse_x < 800 && mouse_y > 295 && mouse_y < 545 && m_mouseCounter == 1)
		{
			m_shipImgNo = "2";
			m_state = FINISHED;
			m_nextState = STATE_LEVEL_SELECT;
		}

		else if(mouse_x > 225 && mouse_x < 495 && mouse_y > 620 && mouse_y < 845 && m_mouseCounter == 1)
		{
			m_shipImgNo = "3";
			m_state = FINISHED;
			m_nextState = STATE_LEVEL_SELECT;
		}

		else if(mouse_x > 575 && mouse_x < 800 && mouse_y > 620 && mouse_y < 845 && m_mouseCounter == 1)
		{
			m_shipImgNo = "4";
			m_state = FINISHED;
			m_nextState = STATE_LEVEL_SELECT;
		}

		else if(mouse_x > 910 && mouse_x < 975 && mouse_y > 25 && mouse_y < 100 && m_mouseCounter == 1)
		{
			m_state = SAVE_SELECT;
		}
	}

	else if(m_state == INSTRUCTIONS)
	{
		if(mouse_x > 910 && mouse_x < 975 && mouse_y > 25 && mouse_y < 100 && m_mouseCounter == 1)
		{
			m_state = SAVE_SELECT;
		}
	}	
}

void Title::Logic()
{
	//Once player has selected either new game or load game load the corresponding stats from the CSV file
	//and then load either the image the player has chosen or the one in the previous save
	if(m_nextState == STATE_LEVEL_SELECT)
	{
		m_myPlayer->LoadPlayerStats(m_saveSelect);
		m_myPlayer->LoadShipSprite(m_shipImgNo);
	}
}

void Title::Render()
{
	//Draw background and then draw the images on top corresponding to the game state
	blit(m_background, m_buffer, 0, 0, 0, 0, m_background->w, m_background->h);

	if(m_state == SAVE_SELECT)
	{
		blit(m_newGameButton, m_buffer, 0, 0, 225, 200, m_newGameButton->w, m_newGameButton->h);

		if(m_prevSavePresent == true)
		{
			blit(m_loadGameButton, m_buffer, 0, 0, 225, 470, m_loadGameButton->w, m_loadGameButton->h);
		}

		blit(m_instructionsButton, m_buffer, 0, 0, 225, 740, m_instructionsButton->w, m_instructionsButton->h);
	}

	else if(m_state == SHIP_SELECT)
	{
		blit(m_cloud, m_buffer, 0, 0, 160, 270, m_cloud->w, m_cloud->h);
		masked_stretch_blit(m_ship1, m_buffer, 0, 0, m_ship1->w, m_ship1->h, 188, 295, 250, 250);

		blit(m_cloud, m_buffer, 0, 0, 510, 270, m_cloud->w, m_cloud->h);
		masked_stretch_blit(m_ship2, m_buffer, 0, 0, m_ship2->w, m_ship2->h, 538, 295, 250, 250);

		blit(m_cloud, m_buffer, 0, 0, 160, 600, m_cloud->w, m_cloud->h);
		masked_stretch_blit(m_ship3, m_buffer, 0, 0, m_ship3->w, m_ship3->h, 188, 625, 250, 250);

		blit(m_cloud, m_buffer, 0, 0, 510, 600, m_cloud->w, m_cloud->h);
		masked_stretch_blit(m_ship4, m_buffer, 0, 0, m_ship3->w, m_ship3->h, 538, 625, 250, 250);
	}

	else if (m_state == INSTRUCTIONS)
	{
		blit(m_instructions, m_buffer, 0, 0, 60, 200, m_instructions->w, m_instructions->h);
	}

	show_mouse(NULL);
	blit(m_buffer, screen, 0, 0, 0, 0, m_buffer->w, m_buffer->h);
	show_mouse(screen);
}

//Destructor
Title::~Title()
{
	//Null the player pointer
	m_myPlayer = NULL;

	//Destroy all objects used in this gamestate to prevent memory leaks
	destroy_bitmap(m_ship1);
	destroy_bitmap(m_ship2);
	destroy_bitmap(m_ship3);
	destroy_bitmap(m_ship4);
	destroy_bitmap(m_newGameButton);
	destroy_bitmap(m_loadGameButton);
	destroy_bitmap(m_instructions);
	destroy_bitmap(m_instructionsButton);
	destroy_bitmap(m_cloud);
}