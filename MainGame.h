#pragma once
#include "GridElement.h"
#include <set>
#include <vector>

extern const int g_iGridSizePlusOne;

class GridElement;
struct GridNumberComparison;

class Game
{
public:
	enum class DIRECTION
	{
		UNDEFINED = -1,
		UP,
		RIGHT,
		DOWN,
		LEFT
	};

	Game();
	~Game();
	
	//************************************
	// Method:    InitialiseGame
	// FullName:  Game::InitialiseGame
	// Access:    public 
	// Returns:   void
	// Qualifier:
	//************************************
	void InitialiseGame();


	//************************************
	// Method:    Play
	// FullName:  Game::Play
	// Access:    public 
	// Returns:   void
	// Qualifier:
	//************************************
	void Play();

	//************************************
	// Method:    SetDirection
	// FullName:  Game::SetDirection
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: const DIRECTION eDirection
	//************************************
	void SetDirection(const DIRECTION eDirection);


private:
	//************************************
	// Method:    GenerateFood
	// FullName:  Game::GenerateFood
	// Access:    private 
	// Returns:   GridElement
	// Qualifier: const
	//************************************
	GridElement GenerateFood() const;


	//************************************
	// Method:    TestElementInSnake
	// FullName:  Game::TestElementInSnake
	// Access:    private 
	// Returns:   bool
	// Qualifier: const
	// Parameter: const GridElement & ToTest
	//************************************
	bool TestElementInSnake(const GridElement& ToTest) const;


	int												m_iScore;
	std::vector<GridElement>						m_vSnake;
	GridElement										m_Food;
	DIRECTION										m_eDirection;
	bool											m_bInitialized;
	bool											m_bGameRunning;
};