#pragma once
#include "AbstractCommand.h"
#include "DocumentItem.h"

class CDeleteItemCommand : public CAbstractCommand
{
public:
	CDeleteItemCommand(std::vector<CDocumentItem>& items, size_t index);
	~CDeleteItemCommand();

private:
	void DoExecute() override;
	void DoUnexecute() override;

	std::vector<CDocumentItem>& m_items;
	std::shared_ptr<CDocumentItem> m_item;
	size_t m_index;
};
