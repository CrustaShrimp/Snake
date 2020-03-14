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
	// Method:    SetGameNotPlaying
	// FullName:  Game::SetGameNotPlaying
	// Access:    public 
	// Returns:   void
	// Qualifier:
	//************************************
	void SetGameNotPlaying() { m_bGameRunning = false; }

	//************************************
	// Method:    Play
	// FullName:  Game::Play
	// Access:    public 
	// Returns:   void
	// Qualifier:
	//************************************
	void Play();

	//************************************
	// Method:    AllowedToUnpause
	// FullName:  Game::AllowedToUnpause
	// Access:    public 
	// Returns:   bool
	// Qualifier: const
	//************************************
	bool AllowedToUnpause() const;

	//************************************
	// Method:    IsPlaying
	// FullName:  Game::IsPlaying
	// Access:    public 
	// Returns:   bool
	// Qualifier: const
	//************************************
	bool IsPlaying() const;

	//************************************
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
	// Qualifier: 
	//************************************
	bool IsGameOver();

	//************************************
	// Method:    SetDirection
	// FullName:  Game::SetDirection
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: const DIRECTION eDirection
	//************************************
	void SetDirection(const DIRECTION eDirection);

	//************************************
	// Method:    TogglePause
	// FullName:  Game::TogglePause
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: const bool bForcedPause
	//************************************
	void TogglePause(const bool bForcedPause);

	//************************************
	// Method:    GetRunning
	// FullName:  Game::GetRunning
	// Access:    public 
	// Returns:   bool
	// Qualifier: const
	//************************************
	bool GetPaused() const { return m_bPaused; }

	//************************************
	// Method:    GetSoundEnabled
	// FullName:  Game::GetSoundEnabled
	// Access:    public 
	// Returns:   bool
	// Qualifier: const
	//************************************
	bool GetSoundEnabled() const { return m_bSoundEnabled; }

	//************************************
	// Method:    SetSoundEnabled
	// FullName:  Game::SetSoundEnabled
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: const bool bEnabled
	//************************************
	void SetSoundEnabled(const bool bEnabled) { m_bSoundEnabled = bEnabled; }
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
	bool											m_bPaused;
	bool											m_bGameOver;
	bool											m_bNewDirectionSet;
	bool											m_bSoundEnabled;
};