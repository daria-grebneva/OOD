// MultiGumballMachine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CMenu.h"
#include "CMultiGumballMachine.h"

int main()
{
	std::stringstream os;
	os.str("");
	CMenu menu(os);
	menu.Run();
	return 0;
}
