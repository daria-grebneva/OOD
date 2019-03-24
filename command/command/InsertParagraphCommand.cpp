#include "stdafx.h"
#include "InsertParagraphCommand.h"
#include "Paragraph.h"

CInsertParagraphCommand::CInsertParagraphCommand(std::shared_ptr<IParagraph>&& paragraph, std::vector<CDocumentItem>& items, boost::optional<size_t> position)
	: m_paragraph(paragraph)
	, m_items(items)
	, m_position(position)
{
}

void CInsertParagraphCommand::DoExecute()
{
	if (m_position > m_items.size())
	{
		throw std::invalid_argument("number of position more than number of elements");
	}

	if (m_position == boost::none)
	{
		m_items.emplace_back(CDocumentItem(nullptr, m_paragraph));
	}
	else
	{
		m_items.emplace(m_items.begin() + m_position.get(), CDocumentItem(nullptr, m_paragraph));
	}
}

void CInsertParagraphCommand::DoUnexecute()
{
	if (m_position == boost::none)
	{
		m_items.pop_back();
	}
	else
	{
		m_items.erase(m_items.begin() + m_position.get());
	}
}
