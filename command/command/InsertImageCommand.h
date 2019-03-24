#pragma once
#include "AbstractCommand.h"
#include "DocumentItem.h"
#include "History.h"

class CInsertImageCommand : public CAbstractCommand
{
public:
	CInsertImageCommand(CHistory& history, std::vector<CDocumentItem>& items, const boost::filesystem::path& path, int width, int height,
		const std::string& tmpDirectoryName,
		boost::optional<size_t> position = boost::none);

	~CInsertImageCommand() override;

private:
	void DoExecute() override;
	void DoUnexecute() override;
	bool CheckWrongExtension(const std::string& extensionFile);
	std::vector<CDocumentItem>& m_items;
	boost::optional<size_t> m_position;
	std::shared_ptr<IImage> m_image;

	void SetImage(CHistory& history, const boost::filesystem::path& path, int width, int height, const std::string& tmpDirectoryName);
};
