#include "Board.h"
#include <cmath>
#include <random>
#include <ctime>
#include <assert.h>
#include "Grid.h"
#include "SpriteCodex.h"


Board::Board(Vei2 _startLoc, Vei2 _boardDim)
	: startLoc(_startLoc), boardDim(_boardDim)
{
	assert(_boardDim.x > 0 && _boardDim.y > 0);

	grids = new Grid * [_boardDim.x * _boardDim.y];

	for (int i = 0; i < boardDim.y; i++)
	{
		for (int j = 0; j < boardDim.x; j++)
		{
			grids[j * boardDim.y + i] = new Grid(Vei2(j, i));
		}
	}

	endLoc = Vei2(startLoc.x + boardDim.x * SpriteCodex::tileSize,
		startLoc.y + boardDim.y * SpriteCodex::tileSize);
}

Board::~Board()
{
	delete[] grids;
}

void Board::Draw(Graphics& gfx)
{
	gfx.DrawRect(
		startLoc.x, startLoc.y,
		endLoc.x, endLoc.y,
		Colors::Gray);

	for (int i = 0; i < boardDim.y; i++)
	{
		for (int j = 0; j < boardDim.x; j++)
		{
			grids[i * boardDim.x + j]->Draw(startLoc, gfx);
		}
	}
}

EGameState Board::ProcessInput(const UserInput& input)
{
	switch (input.inputType)
	{
	case EInputs::E_NONE:
	{
		break;
	}
	case EInputs::E_LEFTCLICK:
	{
		Grid* gridSelected = GetSelectedGrid(input.mouseLoc);
		if (gridSelected && !gridSelected->HasFlag() && gridSelected->CanClick())
		{
			return gridSelected->Reveal();
		}
		break;
	}
	case EInputs::E_RIGHTCLICK:
	{
		Grid* gridSelected = GetSelectedGrid(input.mouseLoc);
		if (gridSelected && gridSelected->CanClick())
		{
			gridSelected->SetFlag();
		}
		break;
	}
	}

	return EGameState::NONE;
}

void Board::SetBombs(int nBombs)
{
	assert(nBombs < boardDim.x * boardDim.y);

	std::mt19937 random((unsigned int)time(nullptr));
	std::uniform_int_distribution<int> xRand(0, boardDim.x - 1);
	std::uniform_int_distribution<int> yRand(0, boardDim.y - 1);

	for (int i = 0; i < nBombs; ++i)
	{
		int valueX = 0;
		int valueY = 0;
		do
		{
			valueX = xRand(random);
			valueY = yRand(random);
		} while (grids[valueY * boardDim.x + valueX]->EGrid == Grid::EGridState::BOMB);

		grids[valueY * boardDim.x + valueX]->EGrid = Grid::EGridState::BOMB;
	}
}


RectI Board::GetRect() const
{
	return RectI{ startLoc, endLoc };
}

Grid* Board::GetSelectedGrid(const Vei2& mouseLoc) const
{
	if (GetRect().IsOverlappingWith(RectI{ mouseLoc, mouseLoc }))
	{
		Vei2 deltaLoc = mouseLoc - startLoc;
		Vei2 gridLoc = deltaLoc / SpriteCodex::tileSize;
		return grids[gridLoc.y * boardDim.x + gridLoc.x];
	}

	return nullptr;
}
