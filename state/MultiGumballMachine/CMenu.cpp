#include "stdafx.h"
#include "CMenu.h"

using namespace std;
CMenu::CMenu(std::stringstream& output)
	: m_GumballMachine(make_unique<CMultiGumballMachine>(0, output))
	, m_out(output)
{
	InitializeItems();
}

void CMenu::InitializeItems()
{
	AddItem("help", "Help", [this](istream&) { ShowInstructions(); });
	AddItem("exit", "Exit", [this](istream&) { Exit(); });
	AddItem("InsertQuarter", "InsertQuarter", [this](istream&) { InsertQuarter(); });
	AddItem("EjectQuarter", "EjectQuarter", [this](istream&) { EjectQuarter(); });
	AddItem("TurnCrank", "TurnCrank", [this](istream&) { TurnCrank(); });
	AddItem("ToString", "ToString", [this](istream&) { ToString(); });
	AddItem("Refill", "Refill", [this](istream& args) { Refill(args); });
}

void CMenu::AddItem(const string& shortcut, const string& description, const Command& command)
{
	m_items.emplace_back(shortcut, description, command);
}

void CMenu::EjectQuarter()
{
	m_GumballMachine->EjectQuarter();
	std::cout << m_out.str() << std::endl;
}

void CMenu::InsertQuarter()
{
	m_GumballMachine->InsertQuarter();
	std::cout << m_out.str() << std::endl;
}

void CMenu::TurnCrank()
{
	m_GumballMachine->TurnCrank();
	std::cout << m_out.str() << std::endl;
}

void CMenu::ToString()
{
	std::cout << m_GumballMachine->ToString() << std::endl;
	std::cout << m_out.str() << std::endl;
}

void CMenu::Refill(std::istream& args)
{
	unsigned gumBallsCount;
	args >> gumBallsCount;
	m_GumballMachine->Refill(gumBallsCount);
	std::cout << m_out.str() << std::endl;
}

void CMenu::Run()
{
	ShowInstructions();

	string command;
	bool exit = false;
	while ((cout << ">")
		&& getline(cin, command) && !m_exit)
	{
		try
		{
			exit = ExecuteCommand(command);
			if (exit)
			{
				return;
			}
		}
		catch (exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}

void CMenu::ShowInstructions() const
{
	cout << "Commands list:\n";
	for (auto& item : m_items)
	{
		std::cout << "  " << item.shortcut << ": " << item.description << "\n";
	}
}

void CMenu::Exit()
{
	m_exit = true;
}

bool CMenu::ExecuteCommand(const string& command)
{
	istringstream iss(command);
	string name;
	iss >> name;

	m_exit = false;
	auto it = boost::find_if(m_items, [&](const Item& item) {
		return item.shortcut == name;
	});
	if (it != m_items.end())
	{
		m_out.str("");
		it->command(iss);
	}
	else
	{
		cout << "Unknown command\n";
	}
	return m_exit;
}
