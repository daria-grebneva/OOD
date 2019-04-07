
#include "stdafx.h"
#include "CGroupShape.h"
#include "CEllipse.h"
#include "CTriangle.h"
#include "CRectangle.h"
#include "CommonTypes.h"


int main()
{
	CGroupShape groupShape;
	groupShape.InsertShape(std::make_shared<CTriangle>(PointD{ 0, 0 }, 10.f, 10.f));
    return 0;
}

