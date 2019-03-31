#pragma once
#include "IHistory.h"
#include "IParagraph.h"
#include <memory>

class CParagraphImpl;

class CParagraph : public IParagraph
{
public:
	CParagraph(IHistory& history, const std::string& text);
	std::string GetText() const override;
	void SetText(const std::string& text) override;

private:
	std::string m_text;
	IHistory& m_history;
};
