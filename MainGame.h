#pragma once
#include "GridElement.h"
#include <set>
#include <vector>

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

	// Method:    GetSnake
	// FullName:  Game::GetSnake
	// Access:    public 
	// Returns:   const std::vector<GridElement>* const
	// Qualifier: const
	//************************************
	const std::vector<GridElement>* const GetSnake() const { return &m_vSnake; }

	//************************************
	// Method:    GetFoodRef
	// FullName:  Game::GetFoodRef
	// Access:    public 
	// Returns:   const GridElement&
	// Qualifier: const
	//************************************
	const GridElement& GetFoodRef() const { return m_Food; }

	//************************************
	// Method:    GetScore
	// FullName:  Game::GetScore
	// Access:    public 
	// Returns:   int
	// Qualifier: const
	//************************************
	int GetScore() const { return m_iScore; }

		//************************************
	// Method:    IsGameOver
	// FullName:  Game::IsGameOver
	// Access:    private 
	// Returns:   bool
	// Qualifier: const
	//************************************
	bool IsGameOver() const { return m_bGameOver; }

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
	bool											m_bGameOver;
	bool											m_bNewDirectionSet;
};