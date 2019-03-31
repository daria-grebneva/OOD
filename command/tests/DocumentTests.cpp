#include "stdafx.h"
#include "../command/Document.h"
#include "../command/Editor.h"
#include "../command/History.h"
#include "../command/Image.h"
#include "../command/InsertImageCommand.h"
#include "../command/Menu.h"
#include "../command/Paragraph.h"
#include "Constants.h"

TEST_CASE("CDocument", "[CDocument]")
{
	CDocument document;

	class CEditorList
	{
	public:
		CEditorList(){};

		void List(std::ostream& strstm, CDocument* m_document)
		{
			strstm << m_document->GetTitle() << std::endl;
			auto itemsCount = m_document->GetItemsCount();

			for (size_t i = 0; i < itemsCount; ++i)
			{
				strstm << i << ". ";
				auto item = m_document->GetItem(i);

				if (auto paragraph = item.GetParagraph())
				{
					strstm << "Paragraph: " << paragraph->GetText() << std::endl;
				}

				if (auto image = item.GetImage())
				{
					strstm << "Image: " << image->GetWidth() << " " << image->GetHeight() << " " << image->GetPath() << std::endl;
				}
			}
		}
	};

	SECTION("check set title")
	{
		std::string title = "New Title";
		document.SetTitle(title);
		REQUIRE(document.GetTitle() == title);
	}

	SECTION("check insert paragraph")
	{
		std::string paragraph = "New Paragraph";
		document.InsertParagraph(paragraph, 0);
		std::string str = "\n0. Paragraph: New Paragraph\n";
		std::stringstream strstm;
		std::stringstream strstmList;
		strstm << str;
		CEditorList editor;
		editor.List(strstmList, &document);
		REQUIRE(strstmList.str() == strstm.str());
	}

	SECTION("check insert with wrong position")
	{
		std::string paragraph = "New Paragraph";
		REQUIRE_THROWS(document.InsertParagraph(paragraph, 2));
	}

	SECTION("check insert image")
	{
		CEditorList editor;
		std::string path = ("E:/1.jpg");
		boost::algorithm::trim_left(path);
		const boost::filesystem::path imgPath = boost::filesystem::path(path);
		document.InsertImage(imgPath, 100, 100, 0);
		auto img = document.GetItem(0).GetImage();

		std::stringstream strstm;
		strstm << "\n0. Image: " << img->GetWidth() << " " << img->GetHeight() << " \"" << img->GetPath().string() << "\"\n";
		std::stringstream strstmList;
		editor.List(strstmList, &document);
		REQUIRE(strstmList.str() == strstm.str());
	}

	SECTION("check insert image with wrong position")
	{
		std::string path = (IMAGE_PATH);
		boost::algorithm::trim_left(path);
		const boost::filesystem::path imgPath = boost::filesystem::path(path);

		REQUIRE_THROWS(document.InsertImage(imgPath, 100, 100, 2));
	}

	SECTION("check insert image with wrong path")
	{
		std::string path = ("E:/3.jpg");
		boost::algorithm::trim_left(path);
		const boost::filesystem::path imgPath = boost::filesystem::path(path);

		REQUIRE_THROWS(document.InsertImage(imgPath, 100, 100, 0));
	}

	SECTION("check insert image with wrong extension")
	{
		std::string path = boost::filesystem::change_extension(IMAGE_PATH, ".doc").string();
		boost::algorithm::trim_left(path);
		const boost::filesystem::path imgPath = boost::filesystem::path(path);

		REQUIRE_THROWS(document.InsertImage(imgPath, 100, 100, 0));
	}

	SECTION("check get item")
	{
		CEditorList editor;
		std::string path = (IMAGE_PATH);
		boost::algorithm::trim_left(path);
		const boost::filesystem::path imgPath = boost::filesystem::path(path);
		document.InsertImage(imgPath, 100, 100, 0);
		auto img = document.GetItem(0).GetImage();

		std::stringstream strstm;
		strstm << "\n0. Image: " << img->GetWidth() << " " << img->GetHeight() << " \"" << img->GetPath().string() << "\"\n";
		std::stringstream strstmList;
		editor.List(strstmList, &document);
		REQUIRE(strstmList.str() == strstm.str());
		REQUIRE(strstmList.str() == strstm.str());
	}

	SECTION("check items count")
	{
		std::string paragraph = "New Paragraph";
		document.InsertParagraph(paragraph, 0);
		document.InsertParagraph(paragraph, 1);
		document.InsertParagraph(paragraph, 2);
		document.InsertParagraph(paragraph, 3);
		REQUIRE(document.GetItemsCount() == 4);
	}

	SECTION("check get item")
	{
		std::string paragraph = "New Paragraph";
		document.InsertParagraph(paragraph, 0);
		document.InsertParagraph(paragraph, 1);
		document.InsertParagraph(paragraph, 2);
		document.InsertParagraph(paragraph, 3);
		REQUIRE(document.GetItemsCount() == 4);
	}

	SECTION("check undo")
	{
		std::string title = "New Title";
		document.SetTitle(title);
		document.Undo();
		REQUIRE(document.GetTitle() == "");
	}

	SECTION("check redo")
	{
		std::string title = "New Title";
		document.SetTitle(title);
		document.Undo();
		REQUIRE(document.GetTitle() == "");
		document.Redo();
		REQUIRE(document.GetTitle() == "New Title");
	}

	SECTION("check can redo")
	{
		std::string title = "New Title";
		document.SetTitle(title);
		REQUIRE_FALSE(document.CanRedo());
	}

	SECTION("check can undo")
	{
		std::string title = "New Title";
		document.SetTitle(title);
		document.Undo();

		REQUIRE_FALSE(document.CanUndo());
	}

	SECTION("check delete item")
	{
		std::string paragraph = "New Paragraph";
		document.InsertParagraph(paragraph, 0);
		REQUIRE(document.GetItemsCount() == 1);
		document.DeleteItem(0);
		REQUIRE(document.GetItemsCount() == 0);
	}

	SECTION("check file save")
	{
		boost::filesystem::remove(FILE_PATH);
		REQUIRE_FALSE(boost::filesystem::exists(FILE_PATH));
		std::string paragraph = "New Paragraph";
		document.InsertParagraph(paragraph, 0);
		document.Save(FILE_PATH);
		REQUIRE(boost::filesystem::exists(FILE_PATH));
		boost::system::error_code errorCode;
		boost::filesystem::remove(FILE_PATH, errorCode);
		if (errorCode)
		{
			std::cout << errorCode.message() << std::endl;
		}
	}


	SECTION("check escapes on saving")
	{
		std::string paragraph = "<!--title-->";
		CDocument document;
		document.InsertParagraph(paragraph, 0);

		document.Save(FILE_PATH);
		std::ifstream ifs(FILE_PATH);
		std::stringstream buffer;

		buffer << ifs.rdbuf();

		std::stringstream str;

		str << "<html>" << std::endl;
		str << "<head>" << std::endl;
		str << "<title></title>" << std::endl;
		str << "</head>" << std::endl;
		str << "<body>" << std::endl;
		str << "<p>&lt;!--title--&gt;</p>" << std::endl;
		str << "</body>" << std::endl;
		str << "</html>" << std::endl;

		REQUIRE(buffer.str() == str.str());
	}
}
