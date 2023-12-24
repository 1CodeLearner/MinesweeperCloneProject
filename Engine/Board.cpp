#include "Board.h"
#include <cmath>
#include "SpriteCodex.h"

Board::Board(Vei2 _startLoc, Vei2 _boardDim)
	: startLoc(_startLoc), boardDim(_boardDim)
{
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
	/*for (Grid grid : grids)
	{
		grid.Draw(StartLoc, gfx);
	}*/
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

void Board::ProcessInput(Mouse& mouse)
{

	if (mouse.RightIsPressed())
	{
		auto value = mouse.GetPos();
		Vei2 inputLoc = Vei2(value.first, value.second);

		if( GetRect().IsOverlappingWith(RectI{inputLoc, inputLoc}) )
		{
			Vei2 deltaLoc = inputLoc - startLoc; 
			Vei2 gridLoc = deltaLoc / SpriteCodex::tileSize;
			Grid* test = grids[gridLoc.y * boardDim.x + gridLoc.x];
			test->CanClick();
		}
	}

}

RectI Board::GetRect() const
{
	return RectI{ startLoc, endLoc };
}
