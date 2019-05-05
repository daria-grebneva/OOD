#include "stdafx.h"
#include "CMenu.h"

using namespace std;

void CMenu::AddItem(const string& shortcut, const string& description, const Command& command)
{
	m_items.emplace_back(shortcut, description, command);
}

void CMenu::Run()
{
	ShowInstructions();

	string command;
	bool exit = false;
	while ((cout << ">") && !m_exit)
	{
		try
		{
			getline(cin, command);
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
		cout << "  " << item.shortcut << ": " << item.description << "\n";
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
		it->command(iss);
	}
	else
	{
		cout << "Unknown command\n";
	}

	return m_exit;
}
