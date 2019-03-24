#include "stdafx.h"
#include "Editor.h"
#include "Document.h"
#include "Menu.h"

using namespace std;
using namespace std::placeholders;

CEditor::CEditor() //-V730
	: m_document(make_unique<CDocument>())
{
	m_menu.AddItem("help", "Help", [this](istream&) { m_menu.ShowInstructions(); });
	m_menu.AddItem("exit", "Exit", [this](istream&) { m_menu.Exit(); });
	AddMenuItem("setTitle", "Changes title. Args: <new title>", &CEditor::SetTitle);
	m_menu.AddItem("list", "Show document", bind(&CEditor::List, this, _1));
	AddMenuItem("undo", "Undo command", &CEditor::Undo);
	AddMenuItem("redo", "Redo undone command", &CEditor::Redo);
	AddMenuItem("insertParagraph", "Insert Paragraph <position>|end <text>", &CEditor::InsertParagraph);
	AddMenuItem("save", "Save <path>", &CEditor::Save);
	AddMenuItem("replaceText", "ReplaceText <position> <text>", &CEditor::ReplaceText);
	AddMenuItem("deleteItem", "DeleteItem <position>", &CEditor::DeleteItem);
	AddMenuItem("insertImage", "InsertImage <position>|end <width> <height> <path>", &CEditor::InsertImage);
	AddMenuItem("resizeImage", "ResizeImage <position>|end <width> <height>", &CEditor::ResizeImage);
}

void CEditor::Start()
{
	m_menu.Run();
}

void CEditor::AddMenuItem(const string& shortcut, const string& description, MenuHandler handler)
{
	m_menu.AddItem(shortcut, description, bind(handler, this, _1));
}

void CEditor::SetTitle(istream& in)
{
	string head;
	string tail;

	if (in >> head)
	{
		getline(in, tail);
	}
	string title = head + tail;

	m_document->SetTitle(title);
}

void CEditor::InsertParagraph(std::istream& input)
{
	std::string text;
	std::string position;

	if (!((input >> position) && std::getline(input, text)))
	{
		throw std::invalid_argument("please enter insertParagraph <position>|end <text>");
	}

	boost::optional<size_t> index = boost::none;
	if (position != "end")
	{
		index.emplace(stoi(position));
	}

	m_document->InsertParagraph(text, index);
}

void CEditor::InsertImage(std::istream& input)
{
	std::string path;
	std::string position;
	int width = 0;
	int height = 0;

	if (!((input >> position) && (input >> width) && (input >> height) && (std::getline(input, path))))
	{
		throw std::invalid_argument("please enter insertImage <position> | end <width> <height> <path>");
	}

	boost::optional<size_t> index = boost::none;
	if (position != "end")
	{
		index.emplace(stoi(position));
	}
	boost::algorithm::trim_left(path);
	m_document->InsertImage(boost::filesystem::path(path), width, height, index);
}

void CEditor::ReplaceText(std::istream& input)
{
	size_t index;
	std::string text;

	if (!((input >> index) && std::getline(input, text)))
	{
		throw std::invalid_argument("please enter replaceText <position> <text>");
	}

	auto paragraph = m_document->GetItem(index).GetParagraph();

	if (!paragraph)
	{
		throw std::logic_error("it is not a paragraph");
	}

	boost::algorithm::trim_left(text);
	paragraph->SetText(text);
}

void CEditor::DeleteItem(std::istream& input)
{
	size_t index;
	if (!(input >> index))
	{
		throw std::invalid_argument("please enter deleteItem <position>");
	}

	m_document->DeleteItem(index);
}

void CEditor::List(istream&)
{
	cout << "-------------" << endl;
	cout << m_document->GetTitle() << endl;
	auto itemsCount = m_document->GetItemsCount();

	for (size_t i = 0; i < itemsCount; ++i)
	{
		std::cout << i << ". ";
		auto item = m_document->GetItem(i);

		if (auto paragraph = item.GetParagraph())
		{
			std::cout << "Paragraph: " << paragraph->GetText() << std::endl;
		}

		if (auto image = item.GetImage())
		{
			std::cout << "Image: " << image->GetWidth() << " " << image->GetHeight() << " " << image->GetPath() << std::endl;
		}
	}
	cout << "-------------" << endl;
}

void CEditor::ResizeImage(std::istream& input)
{
	size_t index;
	int width = 0;
	int height = 0;

	if (!((input >> index) && (input >> width) && (input >> height)))
	{
		throw std::invalid_argument("please enter resizeImage <position> <width> <height>");
	}
	auto image = m_document->GetItem(index).GetImage();

	if (!image)
	{
		throw std::logic_error("not an image");
	}

	image->Resize(width, height);
}

void CEditor::Undo(istream&)
{
	if (m_document->CanUndo())
	{
		m_document->Undo();
	}
	else
	{
		cout << "Can't undo" << endl;
	}
}

void CEditor::Redo(istream&)
{
	if (m_document->CanRedo())
	{
		m_document->Redo();
	}
	else
	{
		cout << "Can't redo" << endl;
	}
}

void CEditor::Save(std::istream& input)
{
	std::string path;
	std::getline(input, path);
	boost::algorithm::trim_left(path);
	m_document->Save(path);
}
