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
	Grid() = default;;
	Grid(Vei2 _pixelDim, Vei2 indexLoc);
public:
	bool CanClick();
	void Draw(Vei2 offset,Graphics& gfx);
	EGameState Click();
	static Vei2 GetPixelDim();
private:
	void CheckBombsAround();
private:
	static Vei2 pixelDim;
	Vei2 indexLoc;
	int nBombsAround = 0;
	EInputState EInputS = EInputState::IS_NOTCLICKED;
	EGridState EGridS = EGridState::GS_EMPTY;
};

