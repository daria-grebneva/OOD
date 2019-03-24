#pragma once
#include "IDocument.h"

class DocumentSaver
{
public:
	DocumentSaver(const boost::filesystem::path&);
	void Save() const;

	void SetTitle(const std::string&);
	void InsertItem(const CConstDocumentItem&);

private:
	boost::filesystem::path m_path;

	void SetPath(const boost::filesystem::path& path);
	void CopyImages() const;

	void SaveToHtml() const;

	std::string m_title;
	std::vector<CConstDocumentItem> m_items;

	const std::vector<std::pair<std::string, std::string>> ESCAPES = {
		{ "\"", "&quot;" },
		{ "\'", "&apos;" },
		{ "<", "&lt;" },
		{ ">", "&gt;" },
		{ "&", "&amp;" },
	};

	void ProccessEscapes(std::string& text) const;
};
