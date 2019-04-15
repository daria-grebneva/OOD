
#include "stdafx.h"
#include "CCanvas.h"
#include "CEllipse.h"
#include "CGroupShape.h"
#include "CRectangle.h"
#include "CSlide.h"
#include "CTriangle.h"
#include "CommonTypes.h"

std::shared_ptr<CGroupShape> MakePicture()
{
	auto picture = std::make_shared<CGroupShape>();

	auto earth = std::make_shared<CRectangle>(PointD{ 0, 0 }, 700, 320);
	earth->GetFillStyle()->SetColor(CShape::ColorToHex("4c2825ff"));
	earth->GetLineStyle()->SetColor(CShape::ColorToHex("000000ff"));

	auto sky = std::make_shared<CRectangle>(PointD{ 20, 20 }, 657, 270);
	sky->GetFillStyle()->SetColor(CShape::ColorToHex("c6e5e5ff"));
	sky->GetLineStyle()->SetColor(CShape::ColorToHex("ffffffff"));
	sky->GetLineStyle()->SetLineThikness(5);

	auto aliens = std::make_shared<CEllipse>(PointD{ 250, 70 }, 60, 20);
	aliens->GetFillStyle()->SetColor(CShape::ColorToHex("331b18ff"));
	aliens->GetLineStyle()->SetColor(CShape::ColorToHex("ffffffff"));
	aliens->GetLineStyle()->SetLineThikness(15);

	auto aliens1 = std::make_shared<CTriangle>(PointD{ 310, 100 }, PointD{ 290, 200 }, PointD{ 270, 200 });
	aliens1->GetFillStyle()->SetColor(CShape::ColorToHex("ffff00ff"));
	aliens1->GetLineStyle()->SetColor(CShape::ColorToHex("000000ff"));

	auto aliens3 = std::make_shared<CTriangle>(PointD{ 310, 100 }, PointD{ 320, 240 }, PointD{ 300, 240 });
	aliens3->GetFillStyle()->SetColor(CShape::ColorToHex("ffff00ff"));
	aliens3->GetLineStyle()->SetColor(CShape::ColorToHex("000000ff"));

	auto aliens4 = std::make_shared<CTriangle>(PointD{ 310, 100 }, PointD{ 350, 200 }, PointD{ 330, 200 });
	aliens4->GetFillStyle()->SetColor(CShape::ColorToHex("ffff00ff"));
	aliens4->GetLineStyle()->SetColor(CShape::ColorToHex("000000ff"));

	auto aliens2 = std::make_shared<CEllipse>(PointD{ 280, 50 }, 30, 20);
	aliens2->GetFillStyle()->SetColor(CShape::ColorToHex("000000ff"));

	picture->InsertShape(earth, 0);
	picture->InsertShape(sky, 1);
	picture->InsertShape(aliens, 3);
	picture->InsertShape(aliens2, 2);
	picture->InsertShape(aliens1, 2);
	picture->InsertShape(aliens3, 2);
	picture->InsertShape(aliens4, 2);

	return picture;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Shapes");
	CCanvas canvas(window);
	auto slide = new CSlide(700, 700);
	auto picture = MakePicture();
	std::cout << "Shapes count: " << picture->GetGroup()->GetShapesCount() << std::endl;
	slide->AddShape(picture);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::White);

		slide->Draw(canvas);

		window.display();
	}

	return 0;
}
