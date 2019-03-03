#include "stdafx.h"
#include "../factory/Designer.h"
#include "../factory/IShapeFactory.h"
#include "../factory/PictureDraft.h"
#include <sstream>

using namespace std;

class CMockShape : public CShape
{
public:
	CMockShape(const string& descr)
		: descr(descr)
	{
	}
	string descr;
};

struct MockShapeFactory : IShapeFactory
{
	vector<string> shapeDescriptions;
	// Inherited via IShapeFactory
	unique_ptr<CShape> CreateShape(const std::string& description) override
	{
		// «апротоколировали описание созданной фигуры
		shapeDescriptions.push_back(description);
		return make_unique<CMockShape>(description);
	}
};

struct Designer_
{
	MockShapeFactory factory;
	CDesigner designer = CDesigner(factory);
};
TEST_CASE("Designer", "[Designer]")
{
	SECTION("when_creating_draf")
	{
		SECTION("returns_empty_draft_when_input_is_empty")
		{
			//istringstream input;
			MockShapeFactory factory;
			CDesigner designer = CDesigner(factory);
			//auto draft = designer.CreateDraft(input);
			//REQUIRE(draft.IsEmpty());
			//REQUIRE(input.eof());
		}
	}
}
