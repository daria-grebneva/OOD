#include "stdafx.h"
#include "CEditor.h"

using namespace std;
using namespace std::placeholders;

CEditor::CEditor(std::stringstream& output) //-V730
	: m_GumballMachine(make_unique<CMultiGumballMachine>(0, output))
	, m_out(output)
{
	m_menu.AddItem("help", "Help", [this](istream&) { m_menu.ShowInstructions(); });
	m_menu.AddItem("exit", "Exit", [this](istream&) { m_menu.Exit(); });
	AddMenuItem("InsertQuarter", "InsertQuarter", &CEditor::InsertQuarter);
	AddMenuItem("EjectQuarter", "EjectQuarter", &CEditor::EjectQuarter);
	AddMenuItem("TurnCrank", "TurnCrank", &CEditor::TurnCrank);
	AddMenuItem("ToString", "ToString", &CEditor::ToString);
	AddMenuItem("Refill", "Refill", &CEditor::Refill);
}

void CEditor::Start()
{
	m_menu.Run();
}

void CEditor::AddMenuItem(const string& shortcut, const string& description, MenuHandler handler)
{
	m_menu.AddItem(shortcut, description, bind(handler, this, _1));
}

void CEditor::EjectQuarter(std::istream& input)
{
	m_out.str("");
	m_GumballMachine->EjectQuarter();
	std::cout << m_out.str() << std::endl;
}

void CEditor::InsertQuarter(std::istream& input)
{
	m_out.str("");
	m_GumballMachine->InsertQuarter();
	std::cout << m_out.str() << std::endl;
}

void CEditor::TurnCrank(std::istream& input)
{
	m_out.str("");
	m_GumballMachine->TurnCrank();
	std::cout << m_out.str() << std::endl;
}

void CEditor::ToString(std::istream& input)
{
	m_out.str("");
	std::cout << m_GumballMachine->ToString() << std::endl;
	std::cout << m_out.str() << std::endl;
}

void CEditor::Refill(std::istream& input)
{
	m_out.str("");
	unsigned gumBallsCount;
	input >> gumBallsCount;
	m_GumballMachine->Refill(gumBallsCount);
	std::cout << m_out.str() << std::endl;
}
