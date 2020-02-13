#include "MainGame.h"
#include "Snake.h"
#include <cstdlib>
#include <cassert>
#include <numeric>

Game::Game()
	:m_iScore(0)
	,m_eDirection(DIRECTION::UNDEFINED)
	,m_bInitialized(false)
	,m_bGameRunning(false)
	,m_bGameOver(false)
	,m_bNewDirectionSet(false)
	,m_bPaused(false)
	,m_bSoundEnabled(true)
{

}

Game::~Game()
{

}

void Game::Play()
{
	if (!m_bInitialized)
	{
		return;
	}
	if (!m_bGameRunning)
	{
		return;
	}
	if (m_bPaused)
	{
		return;
	}
	if (m_bGameOver)
	{
		return;
	}
	// *************************************************
	// Play game:
	// 1: read direction (done in SetDirection())
	m_bNewDirectionSet = false;
	// 2: move snake in direction
	GridElement NewSnakeHead = *(m_vSnake.cbegin());
	switch (m_eDirection)
	{
	case DIRECTION::RIGHT:
	{
		NewSnakeHead.AddX(1);
		break;
	}
	case DIRECTION::LEFT:
	{
		NewSnakeHead.AddX(-1);
		break;
	}
	case DIRECTION::UP:
	{
		NewSnakeHead.AddY(-1);
		break;
	}
	case DIRECTION::DOWN:
	{
		NewSnakeHead.AddY(1);
		break;
	}
	default:
		// Somehow error something
		assert(false && "Direction is not found!");
		break;
	};

	// 3: check gameover (snakehead touching snake)
	if (TestElementInSnake(NewSnakeHead))
	{
		// Game Over
		m_bGameOver = true;
		return;
	}

	// Add new snakehead to the start of the vector
	m_vSnake.insert(m_vSnake.begin(), NewSnakeHead);

	// 4: check whether food is eaten
	if (NewSnakeHead == m_Food)
	{
		// Food eaten
		// 6: if eaten, increase score
		m_Food.SetActive(false);
		m_iScore+= 5;
	}
	else
	{
		// 5: if not eaten, pop
		m_vSnake.pop_back();
	}
	// 7: Set new food if food is eaten
	if (!m_Food.GetActive())
	{
		m_Food = GenerateFood();
	}
	// continues
}

bool Game::IsPlaying() const
{
	return m_bGameRunning && !m_bPaused && !m_bGameOver;
}

bool Game::IsGameOver()
{
	const bool bFirstTimeGameOver = m_bGameRunning && m_bGameOver;
	if (bFirstTimeGameOver)
	{
		PlaySnakeJazz(false);
	}
	if (m_bGameOver)
	{
		m_bGameRunning = false;
	}
	return bFirstTimeGameOver;
}

void Game::SetDirection(const DIRECTION eDirection)
{
	if (!m_bGameRunning)
	{
		// We start playing now, or resume from pause
		PlaySnakeJazz(true);
	}
	m_bGameRunning = true;
	m_bPaused = false;
	// Only set new direction if the direction has not already been changed without the game being called
	if (!m_bNewDirectionSet)
	{
		m_bNewDirectionSet = true;
		assert(eDirection != DIRECTION::UNDEFINED);
		switch (eDirection)
		{
		case DIRECTION::LEFT: // Fall through
		case DIRECTION::RIGHT:
			if (m_eDirection == DIRECTION::UNDEFINED || m_eDirection == DIRECTION::UP || m_eDirection == DIRECTION::DOWN)
			{
				m_eDirection = eDirection;
			}
			break;
		case DIRECTION::UP: // Fall through
		case DIRECTION::DOWN:
			if (m_eDirection == DIRECTION::UNDEFINED || m_eDirection == DIRECTION::LEFT || m_eDirection == DIRECTION::RIGHT)
			{
				m_eDirection = eDirection;
			}
			break;
		default:
			assert(false);
			break;
		}
	}
}

void Game::TogglePause()
{
	if (!m_bPaused) // If we were not paused yet, we are going to pause and thus stop the music
	{
		PlaySnakeJazz(false);
	}
	else // If we were already paused, we are going to continue and thus restart the music
	{
		PlaySnakeJazz(true);
	}
	m_bPaused = !m_bPaused;
}

void Game::InitialiseGame()
{
	// *************************************************
	// Init:
	// 1: init snake at some point
	m_vSnake.clear();
	const int iMiddle = (GRIDSIZE - 1) / 2;
	const GridElement SnakeBeginPoint(iMiddle, iMiddle);
	m_vSnake.push_back(SnakeBeginPoint);

	// 2: init food at random point, not snake point!
	m_Food = GenerateFood();
	// 3: (re)init score, game over and gamerunning
	m_iScore = 0;
	m_bGameRunning = false;
	m_bGameOver = false;
	// 4: set initialized to true to let the rest know we are ready

	m_bInitialized = true;
}

GridElement Game::GenerateFood() const
{
	// Generate a food item somewhere
	// It cannot be in the snake set!
	// TODO set random seed
	bool bFoodLocationVerified = false;
	int iTries = 0;
	while (!bFoodLocationVerified && iTries < 50)
	{
		const int iFoodX = std::rand() % GRIDSIZE;
		const int iFoodY = std::rand() % GRIDSIZE;
		GridElement NewFood(iFoodX, iFoodY);
		// Check validity of the NewFood location, it cannot be inside the snake
		bFoodLocationVerified = !TestElementInSnake(NewFood);
		if (bFoodLocationVerified)
		{
			NewFood.SetActive(true);
			return NewFood;
		}
		iTries++;
	}
	return GridElement(0,0);
}

bool Game::TestElementInSnake(const GridElement& ToTest) const
{
	const bool bFound = std::accumulate(m_vSnake.cbegin(), m_vSnake.cend(), false, [&ToTest](bool bEqual, const GridElement SnakeElement)->bool
		{
			if (bEqual)
			{
				return bEqual;
			}
			bEqual = SnakeElement == ToTest;
			return bEqual;
		});
	return bFound;
}
