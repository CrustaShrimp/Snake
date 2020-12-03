#pragma once
#include "GridElement.h"
#include <set>
#include <vector>

class CGridElement;
struct GridNumberComparison;

class CGame
{
public:
    enum class EDIRECTION
    {
        UNDEFINED = -1,
        UP,
        RIGHT,
        DOWN,
        LEFT
    };

    CGame();

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
    void SetGameNotPlaying() noexcept
    {
        m_bGameRunning = false;
    }

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
    bool AllowedToUnpause() const noexcept
    {
        return m_bGameRunning && m_bPaused && !m_bGameOver;
    }

    //************************************
    // Method:    IsPlaying
    // FullName:  Game::IsPlaying
    // Access:    public 
    // Returns:   bool
    // Qualifier: const
    //************************************
    bool IsPlaying() const noexcept
    {
        return m_bGameRunning && !m_bPaused && !m_bGameOver;
    }

    //************************************
    // Method:    GetSnake
    // FullName:  Game::GetSnake
    // Access:    public 
    // Returns:   const std::vector<GridElement>* const
    // Qualifier: const
    //************************************
    const std::vector<CGridElement>* const GetSnake() const noexcept
    {
        return &m_vSnake;
    }

    //************************************
    // Method:    GetFoodRef
    // FullName:  Game::GetFoodRef
    // Access:    public 
    // Returns:   const GridElement&
    // Qualifier: const
    //************************************
    const CGridElement& GetFoodRef() const noexcept
    {
        return m_Food;
    }

    //************************************
    // Method:    GetScore
    // FullName:  Game::GetScore
    // Access:    public 
    // Returns:   int
    // Qualifier: const
    //************************************
    int GetScore() const noexcept
    {
        return m_iScore;
    }

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
    void SetDirection(const EDIRECTION eDirection);

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
    bool GetPaused() const noexcept
    {
        return m_bPaused;
    }

    //************************************
    // Method:    GetSoundEnabled
    // FullName:  Game::GetSoundEnabled
    // Access:    public 
    // Returns:   bool
    // Qualifier: const
    //************************************
    bool GetSoundEnabled() const noexcept
    {
        return m_bSoundEnabled;
    }

    //************************************
    // Method:    SetSoundEnabled
    // FullName:  Game::SetSoundEnabled
    // Access:    public 
    // Returns:   void
    // Qualifier:
    // Parameter: const bool bEnabled
    //************************************
    void SetSoundEnabled(const bool bEnabled) noexcept
    {
        m_bSoundEnabled = bEnabled;
    }
private:
    //************************************
    // Method:    GenerateFood
    // FullName:  Game::GenerateFood
    // Access:    private 
    // Returns:   GridElement
    // Qualifier: const
    //************************************
    CGridElement GenerateFood() const;


    //************************************
    // Method:    TestElementInSnake
    // FullName:  Game::TestElementInSnake
    // Access:    private 
    // Returns:   bool
    // Qualifier: const
    // Parameter: const GridElement & ToTest
    //************************************
    bool TestElementInSnake(const CGridElement& ToTest) const;

    int                         m_iScore;
    std::vector<CGridElement>   m_vSnake;
    CGridElement                m_Food;
    EDIRECTION                  m_eDirection;
    bool                        m_bInitialized;
    bool                        m_bGameRunning;
    bool                        m_bPaused;
    bool                        m_bGameOver;
    bool                        m_bNewDirectionSet;
    bool                        m_bSoundEnabled;
};