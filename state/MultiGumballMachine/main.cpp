// MultiGumballMachine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CEditor.h"

int main()
{
	std::stringstream output;
	CEditor editor(output);

	editor.Start();
	return 0;
}
