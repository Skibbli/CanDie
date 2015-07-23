#include "Playing_Level.h"
#include <fstream>
#include <string>

//Constructor that takes a player address parameter to init the player pointer to
Playing_Level::Playing_Level(Player &myPlayer)
{
	m_myPlayer = &myPlayer;

	//Updates the stat totals of the player then resets the necessary variables e.g. x and y pos
	//and current HP
	m_myPlayer->TotalStatUpdate();
	m_myPlayer->ResetPlayer();

	//This variable is used for the scrolling background
	BGyPos = 1000;

	//Retrieves the active level variable from the player then uses this to calculate the difficulty
	//for the level in the form of spawn rate/number of spawns/types of enemy
	m_level = m_myPlayer->GetActiveLevel();

	m_enemySpawnRate = 140 - m_level * 15;
	m_enemySpawnCD = 0;
	m_enemySpawnCounter = 0;
	m_enemySpawnLimit = 10 + m_level * 10;

	m_playingState = PLAYING;
	m_levelHealth = 25;

	//Loads music and explosion bitmaps - if fails gives error and exits
	m_BGMusic = load_sample("Sounds/LevelBGMusic.wav");

	if(!m_BGMusic)
	{
		allegro_message("LEVEL BACKGROUND MUSIC");
		exit(-1);
	}

	m_explosion1.expIMG = load_bitmap("Images/ExpIMG1.bmp", 0);

	if(!m_explosion1.expIMG)
	{
		allegro_message("EXPLOSION 1 BITMAP");
		exit(-1);
	}

	m_explosion2.expIMG = load_bitmap("Images/ExpIMG2.bmp", 0);

	if(!m_explosion2.expIMG)
	{
		allegro_message("EXPLOSION 2 BITMAP");
		exit(-1);
	}

	m_explosion3.expIMG = load_bitmap("Images/ExpIMG3.bmp", 0);

	if(!m_explosion3.expIMG)
	{
		allegro_message("EXPLOSION 3 BITMAP");
		exit(-1);
	}

	//Inits counters for explosions to 0 and inits how long explosions last
	m_explosion1.expCounter = 0;
	m_explosion2.expCounter = 0;
	m_explosion3.expCounter = 0;

	m_expFrameLimit = 70;

	//Loads the relevant background and other images based off the active level - if fail exit/give error
	std::string stringLevel = std::to_string((long double)m_level);
	std::string fileName = "Images/LevelBG.bmp";

	m_background = load_bitmap(fileName.insert(12, stringLevel).c_str(), 0);

	if(!m_background)
	{
		allegro_message("LEVEL BACKGROUND BITMAP");
		exit(-1);
	}

	m_pauseIMG = load_bitmap("Images/PauseIMG.bmp", 0);

	if(!m_pauseIMG)
	{
		allegro_message("PAUSE BITMAP");
		exit(-1);
	}

	m_winIMG = load_bitmap("Images/WinIMG.bmp", 0);

	if(!m_winIMG)
	{
		allegro_message("WIN BITMAP");
		exit(-1);
	}

	m_failIMG = load_bitmap("Images/FailIMG.bmp", 0);

	if(!m_failIMG)
	{
		allegro_message("FAIL BITMAP");
		exit(-1);
	}

	m_cloud = load_bitmap("Images/Cloud.bmp", 0);

	if(!m_cloud)
	{
		allegro_message("LEVEL CLOUD BITMAP");
		exit(-1);
	}

	m_myfont = load_font("Fonts/font2.pcx", NULL, NULL);

	if(!m_myfont)
	{
		allegro_message("SHOP FONT");
		exit(-1);
	}

	//Loads enemy data CSV - gives error and exits if fails
	std::ifstream inFile;
	inFile.open("Enemy Data.csv");

	if(inFile.fail())
	{
		allegro_message("ENEMY DATA FILE");
		exit(-1);
	}

	//Reads all enemies from the enemy file and loads them into a vector
	std::string input;
	
	int counter2 = -1;
	
	for(; std::getline(inFile, input); counter2++);

    for(int i = 0; i < counter2; i++)
	{
		m_loadedEnemies.push_back(Enemy(i + 1));
	}
			
	inFile.close();

	//Starts music
	play_sample(m_BGMusic, 200, 128, 1000, TRUE);
}

void Playing_Level::HandleEvents()
{
	//Gets input based off state player is currently in
	switch(m_playingState)
	{
	case PLAYING:
		{	
			if(key[KEY_P])
			{
				m_playingState = PAUSED;
			}

			m_myPlayer->GetPlayerMovement();
		}
		break;
	case PAUSED:
		{
			if(key[KEY_ENTER])
			{
				m_playingState = PLAYING;
			}

			if(key[KEY_ESC])
			{
				m_nextState = STATE_LEVEL_SELECT;
			}			
		}
		break;
	case LEVEL_CLEAR:
		{
			if(key[KEY_ENTER])
			{
				m_nextState = STATE_LEVEL_SELECT;
			}
		}
		break;
	case GAMEOVER:
		{
			if(key[KEY_ENTER])
			{
				m_nextState = STATE_LEVEL_SELECT;
			}
		}
		break;
	}	
}

void Playing_Level::Logic()
{
	if(m_playingState == PLAYING)
	{
		//Update player position
		m_myPlayer->UpdatePlayer();

		//Fire player bullet if shoot is off cooldown
		if(m_myPlayer->GetWeapFireRate() - m_myPlayer->GetAtkCD() == 0 && m_myPlayer->GetIsFiring() == true)
		{
			m_bullets.push_back(Bullet(*m_myPlayer));
			m_myPlayer->SetAtkCD(0);
		}
		//If shoot is on cooldown reduce cooldown of shoot
		else if(m_myPlayer->GetAtkCD() < m_myPlayer->GetWeapFireRate())
		{
			m_myPlayer->SetAtkCD(1);
		}

		//Spawn enemy if enemy spawn is off cooldown
		if(m_enemySpawnRate - m_enemySpawnCD == 0 && m_enemySpawnCounter <= m_enemySpawnLimit)		
		{
			m_liveEnemies.push_back(m_loadedEnemies[rand() % (m_level + 1)]);
			m_liveEnemies.back().SetXPos(rand() % SCREEN_W);
			m_enemySpawnCounter++;
			m_enemySpawnCD = 0;
		}
		//If enemy spawn is on CD reduce cooldown of enemy spawn
		else
		{
			m_enemySpawnCD++;
		}

		//Cycle through bullets, update it and then check for collision against enemy/player
		//If collision is detected reduce the health of the target and if it runs out of HP
		//either erase enemy or move to gameover state
		for(unsigned int i = 0; i < m_bullets.size(); i++)														
		{																										
			if(m_bullets[i].UpdateAndBoundsCheck())																
			{
				m_bullets.erase(m_bullets.begin() + i);
			}
			
			else if(m_bullets[i].GetID() == PLAYER)																	
			{
				for(unsigned int j = 0; j < m_liveEnemies.size(); j++)
				{
					if(m_liveEnemies[j].CollisionCheck(m_bullets[i].GetXPos(), m_bullets[i].GetYPos()))
					{
       					if(m_liveEnemies[j].TakeDamage(m_bullets[i].GetDamage()))
						{
							m_myPlayer->EarnSugar(m_liveEnemies[j].GetSugarReward());

							//Spawn random explosion
							int z = rand() % 3;

							if(z == 0)
							{
								m_explosions.push_back(m_explosion1);
							}
							else if(z == 1)
							{
								m_explosions.push_back(m_explosion2);
							}
							else if(z == 2)
							{
								m_explosions.push_back(m_explosion3);
							}

							m_explosions.back().xPos = m_liveEnemies[j].GetXPos();
							m_explosions.back().yPos = m_liveEnemies[j].GetYPos();

							m_liveEnemies.erase(m_liveEnemies.begin() + j);
							
							j--;
						}

						m_bullets.erase(m_bullets.begin() + i);
						i--;
						break;
					}
				}
			}

			else if(m_bullets[i].GetID() == ENEMY)
			{
				if(m_myPlayer->CollisionCheck(m_bullets[i].GetXPos(), m_bullets[i].GetYPos()))
				{
					if(m_myPlayer->TakeDamage(m_bullets[i].GetDamage()))
					{
						m_playingState = GAMEOVER;
					}

					m_bullets.erase(m_bullets.begin() + i);
					i--;
					break;
				}
			}
		}

		//Cycle through live enemies - first check if out of bounds. If they are delete them and decrease level health
		//If they aren't then check for collision with player - if true then reduce player HP, award sugar, start explosion and
		//delete enemy. Finally if enemy hasn't been deleted and shoot is off cooldown fire shot, otherwise decrease shot cooldown
		for(unsigned int i = 0; i < m_liveEnemies.size(); i++)		
		{														
			if(m_liveEnemies[i].UpdateAndBoundsCheck())
			{
				m_liveEnemies.erase(m_liveEnemies.begin() + i);
				m_levelHealth--;
				i--;

				if(m_levelHealth <= 0)
				{
					m_playingState = GAMEOVER;
				}
			}

			else if(m_liveEnemies[i].PlayerCollisionCheck(*m_myPlayer))
			{
				if(m_myPlayer->TakeDamage(30))
				{
					m_playingState = GAMEOVER;
				}

				//Spawn random explosion
				int z = rand() % 3;

				if(z == 0)
				{
					m_explosions.push_back(m_explosion1);
				}
				else if(z == 1)
				{
					m_explosions.push_back(m_explosion2);
				}
				else if(z == 2)
				{
					m_explosions.push_back(m_explosion3);
				}
				
				m_explosions.back().xPos = m_liveEnemies[i].GetXPos();
				m_explosions.back().yPos = m_liveEnemies[i].GetYPos();

				m_myPlayer->EarnSugar(m_liveEnemies[i].GetSugarReward());
				m_liveEnemies.erase(m_liveEnemies.begin() + i);
			}

			else if(m_liveEnemies[i].GetWeapFireRate() - m_liveEnemies[i].GetAtkCD() == 0)
			{
				m_bullets.push_back(Bullet(m_liveEnemies[i]));
				m_liveEnemies[i].SetAtkCD(0);
			}
			else if(m_liveEnemies[i].GetAtkCD() < m_liveEnemies[i].GetWeapFireRate())		//If shoot is on cooldown reduce cooldown of shoot
			{
				m_liveEnemies[i].SetAtkCD(1);
			}
		}

		//Iterate through explosions and update their frame counter. If they reach the frame limit delete them
		for(unsigned int i = 0; i < m_explosions.size(); i++)
		{
			m_explosions[i].expCounter++;

			if(m_explosions[i].expCounter > m_expFrameLimit)
			{
				m_explosions.erase(m_explosions.begin() + i);
				i--;
			}
		}

		m_myPlayer->SetIsFiring(false);

		//Check if limit of enemy spawns has been reached and that no enemies are still alive
		//If true then player has cleared the level
		if(m_enemySpawnCounter >= m_enemySpawnLimit && m_liveEnemies.empty())
		{
			m_playingState = LEVEL_CLEAR;
			m_myPlayer->IncreaseLevel();
		}
	}
}

void Playing_Level::Render()
{
	//Draw the background then draw the necessary items depending on gamestate
	switch(m_playingState)
	{
	case PLAYING:
		{
			blit(m_background, m_buffer, 0, BGyPos, 0, 0, m_background->w, 1000);
			
			//Iterate through bullets and draw them
			for(unsigned int i = 0; i < m_bullets.size(); i++)
			{
				m_bullets[i].DrawBullet(m_buffer);
			}
	
			m_myPlayer->DrawChar(m_buffer);
			
			//Iterate through enemies and draw them
			for(unsigned int i = 0; i < m_liveEnemies.size(); i++)
			{
				m_liveEnemies[i].DrawChar(m_buffer);
			}

			//Iterate through explosions and draw them
			for(unsigned int i = 0; i < m_explosions.size(); i++)
			{
				masked_blit(m_explosions[i].expIMG, m_buffer, 0, 0, m_explosions[i].xPos - m_explosions[i].expIMG->w / 2, m_explosions[i].yPos - m_explosions[i].expIMG->h / 2, m_explosions[i].expIMG->w, m_explosions[i].expIMG->h);
			}

			//Draw player stats to top of screen
			textprintf_ex(m_buffer, m_myfont, 5, 5, makecol(255, 120, 183), -1, "Level Health: %i", m_levelHealth);
			textprintf_ex(m_buffer, m_myfont, 450, 5, makecol(255, 120, 183), -1, "Ship Health: %i", m_myPlayer->GetCurrHP());
			textprintf_ex(m_buffer, m_myfont, 850, 5, makecol(255, 120, 183), -1, "Sugar: %i", m_myPlayer->GetSugar());

			//Move background and loop it round if it gets to the end
			BGyPos -= 3;

			if(BGyPos <= 0)
			{
				BGyPos = 1000;
			}
		}
		break;
	case PAUSED:
		{
			blit(m_pauseIMG, m_buffer, 0, 0, 300, 300, m_pauseIMG->w, m_pauseIMG->h);
		}
		break;
	case LEVEL_CLEAR:
		{
			blit(m_winIMG, m_buffer, 0, 0, 300, 300, m_winIMG->w, m_winIMG->h);
		}
		break;
	case GAMEOVER:
		{
			blit(m_failIMG, m_buffer, 0, 0, 300, 300, m_failIMG->w, m_failIMG->h);
		}
		break;
	}

	blit(m_buffer, screen, 0, 0, 0, 0, m_buffer->w, m_buffer->h);
}

//Destructor
Playing_Level::~Playing_Level()
{
	//Stop music
	stop_sample(m_BGMusic);
	
	//Save player stats then null player pointer
	m_myPlayer->SavePlayer();
	m_myPlayer = NULL;
	
	//Clear all vectors and destroy bitmaps to avoid memory leaks
	for(unsigned int i = 0; i < m_loadedEnemies.size(); i++)
	{
		m_loadedEnemies[i].DestroyBitmaps();
	}

	destroy_bitmap(m_explosion1.expIMG);
	destroy_bitmap(m_explosion2.expIMG);
	destroy_bitmap(m_explosion3.expIMG);

	destroy_sample(m_BGMusic);

	destroy_font(m_myfont);

	m_loadedEnemies.clear();
	m_liveEnemies.clear();
	m_bullets.clear();
	m_explosions.clear();
}