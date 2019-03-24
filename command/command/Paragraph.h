#pragma once
#include "History.h"
#include "IParagraph.h"
#include <memory>

class CParagraphImpl;

class CParagraph : public IParagraph
{
public:
	CParagraph(CHistory& history, const std::string& text);
	std::string GetText() const override;
	void SetText(const std::string& text) override;

private:
	std::string m_text;
	CHistory& m_history;
};
