#include "stdafx.h"
#include "CDesigner.h"
#include "CPictureDraft.h"
#include "IShapeFactory.h"

using namespace std;

CDesigner::CDesigner(IShapeFactory& factory)
	: m_factory(factory)
{
}

CDesigner::~CDesigner()
{
}

CPictureDraft CDesigner::CreateDraft(std::istream& inputData)
{
	CPictureDraft draft;
	string line;
	while (getline(inputData, line))
	{
		draft.AddShape(m_factory.CreateShape(line));
	}
	return draft;
}
