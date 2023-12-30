#pragma once
#include "Vei2.h"
#include "Graphics.h"
#include "Grid.h"
#include "RectI.h"
#include "UserInput.h"

class Board
{
public:
	Board() = default;
	Board(Vei2 _startLoc, Vei2 _boardDim);
	Board& operator= (const Board& other) = delete;
	~Board();
public:
	void Draw(Graphics& gfx);
	EGameState ProcessInput(const UserInput& input);
	void SetBombs(const int nBombs = 0);
private:
	RectI GetRect() const;
	Grid* GetSelectedGrid(const Vei2& mouseLoc) const;
private:
	Vei2 startLoc;
	Vei2 endLoc;
	Vei2 boardDim;

	Grid** grids;
	//bool* bombGrids;
};