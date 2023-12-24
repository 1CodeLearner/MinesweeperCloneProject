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
	void ProcessInput(Mouse& mouse);
private:
	RectI GetRect() const;
private:
	Vei2 startLoc;
	Vei2 boardDim;
	Grid** grids;
};