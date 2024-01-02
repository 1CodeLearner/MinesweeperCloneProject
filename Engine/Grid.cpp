#include "Grid.h"
#include "SpriteCodex.h"

Grid::Grid(Vei2 _indexLoc)
	: indexLoc(_indexLoc)
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
	if (HasFlag()) return EGameState::NONE;

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

bool Grid::HasBomb() const
{
	return EGrid == EGridState::BOMB;
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
			switch (nBombsAround)
			{
			case 0:
			{
				SpriteCodex::DrawTile0(offset + drawLoc, gfx);
				break;
			}
			case 1:
			{
				SpriteCodex::DrawTile1(offset + drawLoc, gfx);
				break;
			}
			case 2:
			{
				SpriteCodex::DrawTile2(offset + drawLoc, gfx);
				break;
			}
			case 3:
			{
				SpriteCodex::DrawTile3(offset + drawLoc, gfx);
				break;
			}
			case 4:
			{
				SpriteCodex::DrawTile4(offset + drawLoc, gfx);
				break;
			}
			case 5:
			{
				SpriteCodex::DrawTile5(offset + drawLoc, gfx);
				break;
			}
			case 6:
			{
				SpriteCodex::DrawTile6(offset + drawLoc, gfx);
				break;
			}
			case 7:
			{
				SpriteCodex::DrawTile7(offset + drawLoc, gfx);
				break;
			}
			case 8:
			{
				SpriteCodex::DrawTile8(offset + drawLoc, gfx);
				break;
			}
			}
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

