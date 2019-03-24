#pragma once
#include "Document.h"
#include "Menu.h"

class CEditor
{
public:
	CEditor();

	void Start();

private:
	// Указатель на метод класса CEditor, принимающий istream& и возвращающий void
	typedef void (CEditor::*MenuHandler)(std::istream& in);

	void AddMenuItem(const std::string& shortcut, const std::string& description, MenuHandler handler);

	void SetTitle(std::istream&);
	void List(std::istream&);
	void Undo(std::istream&);
	void Redo(std::istream&);
	void InsertParagraph(std::istream&);
	void Save(std::istream&);
	void ReplaceText(std::istream&);
	void DeleteItem(std::istream&);
	void InsertImage(std::istream&);
	void ResizeImage(std::istream&);

	CMenu m_menu;
	std::unique_ptr<IDocument> m_document;
};
