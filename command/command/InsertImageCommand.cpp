#include "stdafx.h"
#include "InsertImageCommand.h"
#include "Image.h"

CInsertImageCommand::CInsertImageCommand(CHistory& history, std::vector<CDocumentItem>& items, const boost::filesystem::path& path, int width, int height, const std::string& tmpDirectoryName, boost::optional<size_t> position)
	: m_items(items)
	, m_position(position)

{
	SetImage(history, path, width, height, tmpDirectoryName);
}

CInsertImageCommand::~CInsertImageCommand()
{
	if (!m_executed)
	{
		boost::system::error_code errorCode;
		boost::filesystem::remove(m_image->GetPath(), errorCode);
		if (errorCode)
		{
			std::cout << errorCode.message() << std::endl;
		}
	}
}

void CInsertImageCommand::DoExecute()
{
	if (m_position > m_items.size())
	{
		throw std::invalid_argument("number of position more than number of elements");
	}

	if (m_position == boost::none)
	{
		m_items.emplace_back(CDocumentItem(m_image, nullptr));
	}
	else
	{
		m_items.emplace(m_items.begin() + m_position.get(), CDocumentItem(m_image, nullptr));
	}
}

void CInsertImageCommand::DoUnexecute()
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

bool CInsertImageCommand::CheckWrongExtension(const std::string& extensionFile)
{
	return (extensionFile != ".png" && extensionFile != ".jpg" && extensionFile != ".gif" && extensionFile != ".webp");
}

void CInsertImageCommand::SetImage(CHistory& history, const boost::filesystem::path& path, int width, int height, const std::string& directory)
{
	boost::filesystem::path imagesDirectory = boost::filesystem::path(directory);
	boost::filesystem::create_directory(imagesDirectory);

	std::string extension = boost::filesystem::extension(path);
	boost::algorithm::to_lower(extension);

	if (CInsertImageCommand::CheckWrongExtension(extension))
	{
		throw std::logic_error("please check your extension <.png> <.jpg> <.gif> <.webp>");
	}

	std::string fileName = boost::filesystem::unique_path().string() + extension;

	boost::filesystem::path imagesPath = imagesDirectory.stem();
	imagesPath /= boost::filesystem::path(fileName);

	boost::filesystem::copy_file(path, (imagesDirectory /= boost::filesystem::path(fileName)));
	m_image = std::make_shared<CImage>(history, imagesPath.generic_string(), width, height);
}
