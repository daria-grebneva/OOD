#pragma once
#include "CMultiGumballMachine.h"

class CMenu
{
public:
	CMenu(std::stringstream& output);
	typedef std::function<void(std::istream& args)> Command;
	void AddItem(const std::string& shortcut, const std::string& description, const Command& command);

	void Run();

	void ShowInstructions() const;

	void Exit();

private:
	bool ExecuteCommand(const std::string& command);
	void InitializeItems();
	void InsertQuarter();
	void EjectQuarter();
	void TurnCrank();
	void ToString();
	void Refill(std::istream&);

	struct Item
	{
		Item(const std::string& shortcut, const std::string& description, const Command& command)
			: shortcut(shortcut)
			, description(description)
			, command(command)
		{
		}

		std::string shortcut;
		std::string description;
		Command command;
	};
	std::vector<Item> m_items;
	bool m_exit = false;
	std::unique_ptr<CMultiGumballMachine> m_GumballMachine;
	std::stringstream& m_out;
};
