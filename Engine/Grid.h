#pragma once
#include "Vei2.h"
#include "Graphics.h"
#include "EGameState.h"

class Grid
{
protected:
	enum class EInputState
	{
		IS_NOTCLICKED,
		IS_CLICKED
	};

	enum class EGridState
	{
		GS_EMPTY,
		GS_FLAG,
		GS_BOMB
	};

public:
	Grid() = default;
	Grid(Vei2 indexLoc);
public:
	bool CanClick() const;
	void Draw(Vei2 offset,Graphics& gfx);
	EGameState Click();
private:
	void CheckBombsAround();
private:
	Vei2 indexLoc;
	int nBombsAround = 0;
	EInputState EInputS = EInputState::IS_NOTCLICKED;
	EGridState EGridS = EGridState::GS_EMPTY;
};

