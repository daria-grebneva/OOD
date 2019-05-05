#pragma once
#include "CMenu.h"
#include "CMultiGumballMachine.h"

class CEditor
{
public:
	CEditor(std::stringstream& output);

	void Start();

private:
	// Указатель на метод класса CEditor, принимающий istream& и возвращающий void
	typedef void (CEditor::*MenuHandler)(std::istream& in);

	void AddMenuItem(const std::string& shortcut, const std::string& description, MenuHandler handler);

	void InsertQuarter(std::istream&);
	void EjectQuarter(std::istream&);
	void TurnCrank(std::istream&);
	void ToString(std::istream&);
	void Refill(std::istream&);

	CMenu m_menu;
	std::unique_ptr<CMultiGumballMachine> m_GumballMachine;
	std::stringstream& m_out;
};
