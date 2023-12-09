#include "Board.h"

Board::Board(Vei2 _startLoc, Vei2 _pixelDim, Vei2 _boardDim)
	: startLoc(_startLoc), pixelDim(_pixelDim), boardDim(_boardDim)
{
	grids = new Grid*[_boardDim.x * _boardDim.y];

	for (int i = 0; i < boardDim.y; i++)
	{
		for (int j = 0; j < boardDim.x; j++)
		{
			grids[j * boardDim.y + i] = new Grid(
				Vei2(_pixelDim.x / boardDim.x,
					_pixelDim.y / boardDim.y),
				Vei2(j,i));
		}
	}
}

Board::~Board()
{
	delete [] grids;
}

void Board::Draw(Graphics& gfx)
{
	/*for (Grid grid : grids)
	{
		grid.Draw(StartLoc, gfx);
	}*/

	for(int i = 0; i < boardDim.y; i++)
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
	return RectI(
		startLoc.x, 
		startLoc.y, 
		pixelDim.x, 
		pixelDim.y
	);
}
