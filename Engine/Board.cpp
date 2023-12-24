#include "Board.h"

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
	gfx.DrawRect(startLoc.x, startLoc.y,
		startLoc.x + boardDim.x * SpriteCodex::tileSize,
		startLoc.y + boardDim.y * SpriteCodex::tileSize,
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
}

RectI Board::GetRect() const
{
	//modify this
	return RectI();
}
