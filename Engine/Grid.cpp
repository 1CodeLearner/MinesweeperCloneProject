#include "Grid.h"
#include "SpriteCodex.h"

Grid::Grid(Vei2 _indexLoc)
	: indexLoc(_indexLoc)
{
}

void Grid::SetState(int nBomb)
{
}

bool Grid::HasFlag() const
{
	return 	EFlag == EFlagState::FLAGGED;
}

void Grid::SetFlag()
{
	switch (EFlag)
	{
	case EFlagState::FLAGGED:
	{
		EFlag = EFlagState::NOTFLAGGED;
		break;
	}
	case EFlagState::NOTFLAGGED:
		EFlag = EFlagState::FLAGGED;
		break;
	}
}

EGameState Grid::Reveal()
{
	EReveal = ERevealState::REVEALED;

	switch (EGrid)
	{
	case EGridState::EMPTY:
	{
		return EGameState::PLAYING;
	}
	case EGridState::BOMB:
	{
		return EGameState::GAMEOVER;
	}
	}

	return EGameState::NONE;
}

bool Grid::CanClick() const
{
	switch (EReveal)
	{
	case ERevealState::NOTREVEALED:
	{
		return true;
	}
	case ERevealState::REVEALED:
	{
		return false;
	}
	}

	return false;
}

void Grid::Draw(Vei2 offset, Graphics& gfx)
{
	Vei2 drawLoc(SpriteCodex::tileSize * indexLoc.x,
		SpriteCodex::tileSize * indexLoc.y);

	SpriteCodex::DrawTile0(offset + drawLoc, gfx);

	switch (EReveal)
	{
	case ERevealState::NOTREVEALED:
	{
		if (EFlag == EFlagState::FLAGGED)
		{
			SpriteCodex::DrawTileFlag(offset + drawLoc, gfx);
		}

		SpriteCodex::DrawTileButton(offset + drawLoc, gfx);
		break;
	}
	case ERevealState::REVEALED:
	{
		switch (EGrid)
		{
		case EGridState::EMPTY:
		{
			break;
		}
		case EGridState::BOMB:
		{
			SpriteCodex::DrawTileBomb(offset + drawLoc, gfx);
			break;
		}
		}
		break;
	}
	}




}

