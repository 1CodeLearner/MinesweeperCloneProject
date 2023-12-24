#pragma once
#include "Vei2.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Grid.h"
#include "RectI.h"


class Board
{
public:
	Board() = default;
	Board(Vei2 _startLoc, Vei2 _boardDim);
	Board& operator= (const Board& other) = delete;
	~Board();
public:
	void Draw(Graphics& gfx);
	EGameState ProcessInput(Mouse& mouse);
private:
	RectI GetRect() const;
	Grid* GetSelectedGrid(Mouse& mouse) const;
private:
	Vei2 startLoc;
	Vei2 endLoc;
	Vei2 boardDim;
	Grid** grids;
	bool* bombGrids;
};