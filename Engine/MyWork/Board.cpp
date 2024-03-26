#include "Board.h"
#include <cmath>
#include <random>
#include <ctime>
#include <assert.h>
#include <vector>
#include "Grid.h"
#include "../SpriteCodex.h"


Board::Board(Vei2 _startLoc, Vei2 _boardDim)
{
	assert(_boardDim.x > 0 && _boardDim.y > 0);

	startLoc = _startLoc;
	boardDim = _boardDim;

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

void Board::CheckBombsAround(const Vei2& centerLoc)
{
	int left = 1;
	int right = 1;
	int top = 1;
	int bottom = 1;

	if (centerLoc.x - 1 < 0)
	{
		left = 0;
	}
	if (centerLoc.x + 1 >= boardDim.x)
	{
		right = 0;
	}
	if (centerLoc.y - 1 < 0)
	{
		top = 0;
	}
	if (centerLoc.y + 1 >= boardDim.y)
	{
		bottom = 0;
	}

	std::vector<Vei2> emptyGridsLoc;
	int totalCount = 0;
	for (int i = centerLoc.y - top; i <= centerLoc.y + bottom; ++i)
	{
		for (int j = centerLoc.x - left; j <= centerLoc.x + right; ++j)
		{
			Grid* workingGrid = grids[i * boardDim.x + j];
			if (!workingGrid->HasBomb())
			{
				emptyGridsLoc.emplace_back(j, i);
			}
			++totalCount;
		}
	}

	if (emptyGridsLoc.size() == totalCount)
	{
		for (auto gridLoc : emptyGridsLoc)
		{
			//CheckBombsAround(gridLoc);
			grids[gridLoc.y * boardDim.x + gridLoc.x]->Reveal();
		}
	}
	else
	{
		int nBombs = totalCount - static_cast<int>(emptyGridsLoc.size());
		grids[centerLoc.y * boardDim.x + centerLoc.x]->nBombsAround = nBombs;
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
		Vei2 gridLoc = GetSelectedGridDim(mouseLoc);
		return grids[gridLoc.y * boardDim.x + gridLoc.x];
	}

	return nullptr;
}

inline Vei2 Board::GetSelectedGridDim(const Vei2& mouseLoc)
{
	Vei2 deltaLoc = mouseLoc - startLoc;
	return deltaLoc / SpriteCodex::tileSize;
}


Vei2 Board::startLoc = {0,0};
Vei2 Board::endLoc = {0,0};
Vei2 Board::boardDim = {0,0};
