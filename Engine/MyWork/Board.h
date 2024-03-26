#pragma once
#include "../Vei2.h"
#include "../Graphics.h"
#include "Grid.h"
#include "../RectI.h"
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
	void CheckBombsAround(const Vei2& centerLoc);
private:
	RectI GetRect() const;
	Grid* GetSelectedGrid(const Vei2& mouseLoc) const;
public:
	static Vei2 GetSelectedGridDim(const Vei2& mouseLoc);
private:
	static Vei2 startLoc;
	static Vei2 endLoc;
	static Vei2 boardDim;

	Grid** grids;
};