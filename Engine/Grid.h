#pragma once
#include "Vei2.h"
#include "Graphics.h"
#include "EGameState.h"

class Grid
{
protected:
	enum class ERevealState
	{
		REVEALED,
		NOTREVEALED
	};
	enum class EFlagState
	{
		FLAGGED,
		NOTFLAGGED
	};
	enum class EGridState
	{
		EMPTY,
		BOMB
	};

public:
	Grid() = default;
	Grid(Vei2 indexLoc);

	void Draw(Vei2 offset, Graphics& gfx);
	void SetState(int nBombs = 0);
	void SetFlag();
	EGameState Reveal();
	bool CanClick() const;
private:


	Vei2 indexLoc;
	int nBombsAround = 0;
	ERevealState EReveal = ERevealState::NOTREVEALED;
	EFlagState EFlag = EFlagState::NOTFLAGGED;
	EGridState EGrid = EGridState::EMPTY;
};

