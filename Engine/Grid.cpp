#include "Grid.h"

Grid::Grid(Vei2 _pixelDim, Vei2 _indexLoc)
	: indexLoc(_indexLoc)
{
	pixelDim = _pixelDim;
}

EGameState Grid::Click()
{
	return EGameState();
}

Vei2 Grid::GetPixelDim()
{
	return pixelDim;
}

void Grid::CheckBombsAround()
{
}

bool Grid::CanClick()
{
	return false;
}

void Grid::Draw(Vei2 offset, Graphics& gfx)
{
	
}

Vei2 Grid::pixelDim;