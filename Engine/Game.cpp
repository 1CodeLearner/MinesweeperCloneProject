/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "Board.h"
#include "UserInput.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	board(
		Vei2(100, 100),
		Vei2(10, 10)
	)
{
	board.SetBombs(10);
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (wnd.mouse.LeftIsPressed())
	{
		if (!userInput.isHoldingLeft)
		{
			auto loc = wnd.mouse.GetPos();
			userInput.SetInput(EInputs::E_LEFTCLICK, Vei2{ loc.second, loc.first });
			userInput.isHoldingLeft = true;
		}
		else
		{
		}
	}
	else userInput.isHoldingLeft = false;

	if (wnd.mouse.RightIsPressed())
	{
		if (!userInput.isHoldingRight)
		{
			auto loc = wnd.mouse.GetPos();
			userInput.SetInput(EInputs::E_RIGHTCLICK, Vei2{ loc.second, loc.first });
			userInput.isHoldingRight = true;
		}
		else
		{
		}
	}
	else userInput.isHoldingRight = false;

	EGameState state = board.ProcessInput(userInput);
	switch (state)
	{
	case EGameState::NONE:
	{
		break;
	}
	case EGameState::PLAYING:
	{
		board.CheckBombsAround(Board::GetSelectedGridDim(userInput.mouseLoc));
		break;
	}
	case EGameState::GAMEOVER:
	{
		break;
	}
	}

	userInput.ResetInput();
}

void Game::ComposeFrame()
{
	board.Draw(gfx);
}
