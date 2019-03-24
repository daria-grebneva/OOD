#include "stdafx.h"

#include "DocumentSaver.h"

DocumentSaver::DocumentSaver(const boost::filesystem::path& path)
{
	SetPath(path);
}

void DocumentSaver::ProccessEscapes(std::string& text) const
{
	for (auto& it : ESCAPES)
	{
		boost::algorithm::replace_all(text, it.first, it.second);
	}
}

void DocumentSaver::Save() const
{
	CopyImages();
	SaveToHtml();
}

void DocumentSaver::SetTitle(const std::string& title)
{
	m_title = title;
	DocumentSaver::ProccessEscapes(m_title);
}

void DocumentSaver::InsertItem(const CConstDocumentItem& item)
{
	m_items.emplace_back(item);
}

void DocumentSaver::SetPath(const boost::filesystem::path& path)
{
	std::string extension = boost::filesystem::extension(path);
	boost::algorithm::to_lower(extension);

	if (!boost::algorithm::contains(extension, ".html"))
	{
		throw std::logic_error("file should be in .html format");
	}

	m_path = boost::filesystem::complete(path);
	boost::filesystem::path directory = m_path;
	directory.remove_filename();

	if (!boost::filesystem::exists(directory))
	{
		boost::filesystem::create_directory(directory);
	}
}

void DocumentSaver::CopyImages() const
{
	boost::filesystem::path imgDirectory = (m_path.parent_path() /= boost::filesystem::path("images"));
	boost::filesystem::create_directory(imgDirectory);

	for (size_t i = 0; i < m_items.size(); ++i)

	{
		auto item = m_items.at(i);
		if (auto it = item.GetImage())
		{
			boost::filesystem::path currentPath = it->GetPath();
			boost::filesystem::path path = imgDirectory;

			path = path / boost::filesystem::path(currentPath.filename());

			if (!boost::filesystem::exists(path))
			{
				boost::filesystem::copy_file(boost::filesystem::complete(currentPath), path);
			}
		}
	}
}

void DocumentSaver::SaveToHtml() const
{
	std::ofstream html(m_path.string());

	html << "<html>" << std::endl;
	html << "<head>" << std::endl;
	html << "<title>" << m_title << "</title>" << std::endl;
	html << "</head>" << std::endl;
	html << "<body>" << std::endl;

	for (size_t i = 0; i < m_items.size(); ++i)
	{
		auto item = m_items.at(i);
		if (auto image = item.GetImage())
		{
			boost::filesystem::path path = (boost::filesystem::path("images") /= (image->GetPath()).filename());

			html << boost::format(R"(<img src=%1% width="%2%" height="%3%" />)") % path % image->GetWidth() % image->GetHeight() << std::endl;
		}
		else
		{
			auto paragraph = item.GetParagraph();
			std::string text = paragraph->GetText();
			DocumentSaver::ProccessEscapes(text);
			html << boost::format(R"(<p>%1%</p>)") % text << std::endl;
		}
		html << "</body>" << std::endl;
		html << "</html>" << std::endl;
	}
}
