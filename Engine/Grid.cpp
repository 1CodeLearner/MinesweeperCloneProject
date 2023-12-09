#include "Grid.h"
#include "SpriteCodex.h"

Grid::Grid(Vei2 _indexLoc)
	: indexLoc(_indexLoc)
{
}

EGameState Grid::Click()
{
	return EGameState();
}

void Grid::CheckBombsAround()
{
}

bool Grid::CanClick() const
{
	return false;
}

void Grid::Draw(Vei2 offset, Graphics& gfx)
{
	Vei2 drawLoc(SpriteCodex::tileSize * indexLoc.x,
		SpriteCodex::tileSize * indexLoc.y);

	SpriteCodex::DrawTile0(offset + drawLoc, gfx);
}
