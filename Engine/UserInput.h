#pragma once
#include "Vei2.h"

enum class EInputs
{
	E_LEFTCLICK,
	E_RIGHTCLICK,
	E_NONE
};

struct UserInput
{
	void ResetInput()
	{
		inputType = EInputs::E_NONE;
		mouseLoc = { 0,0 };
	}
	void SetInput(EInputs input, Vei2 mousePos)
	{
		inputType = input;
		mouseLoc = mousePos;
	}

	bool isHoldingLeft = false;
	bool isHoldingRight = false;

	EInputs inputType = EInputs::E_NONE;
	Vei2 mouseLoc = { 0,0 };
};

