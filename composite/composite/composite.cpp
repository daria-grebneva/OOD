
#include "stdafx.h"
#include "CCanvas.h"
#include "CEllipse.h"
#include "CGroupShape.h"
#include "CRectangle.h"
#include "CSlide.h"
#include "CTriangle.h"
#include "CUtils.h"
#include "CommonTypes.h"

std::shared_ptr<CGroupShape> MakePicture()
{
	auto picture = std::make_shared<CGroupShape>();

	auto earth = std::make_shared<CRectangle>(PointD{ 0, 0 }, 700, 320);
	earth->GetFillStyle()->SetColor(Colors::BROWN);
	earth->GetLineStyle()->SetColor(Colors::BLACK);
	earth->GetLineStyle()->SetLineThickness(2);

	auto sky = std::make_shared<CRectangle>(PointD{ 20, 20 }, 657, 270);
	sky->GetFillStyle()->SetColor(Colors::LIGHT_BLUE);
	sky->GetLineStyle()->SetColor(Colors::WHITE);
	sky->GetLineStyle()->SetLineThickness(5);

	auto aliens = std::make_shared<CEllipse>(PointD{ 250, 70 }, 60, 20);
	aliens->GetFillStyle()->SetColor(Colors::DARK_BROWN);
	aliens->GetLineStyle()->SetColor(Colors::WHITE);
	aliens->GetLineStyle()->SetLineThickness(15);

	auto aliens1 = std::make_shared<CTriangle>(PointD{ 310, 100 }, PointD{ 290, 200 }, PointD{ 270, 200 });
	aliens1->GetFillStyle()->SetColor(Colors::YELLOW);
	aliens1->GetLineStyle()->SetColor(Colors::BLACK);

	auto aliens3 = std::make_shared<CTriangle>(PointD{ 310, 100 }, PointD{ 320, 240 }, PointD{ 300, 240 });
	aliens3->GetFillStyle()->SetColor(Colors::YELLOW);
	aliens3->GetLineStyle()->SetColor(Colors::BLACK);

	auto aliens4 = std::make_shared<CTriangle>(PointD{ 310, 100 }, PointD{ 350, 200 }, PointD{ 330, 200 });
	aliens4->GetFillStyle()->SetColor(Colors::YELLOW);
	aliens4->GetLineStyle()->SetColor(Colors::BLACK);

	auto aliens2 = std::make_shared<CEllipse>(PointD{ 280, 50 }, 30, 20);
	aliens2->GetFillStyle()->SetColor(Colors::BLACK);

	picture->InsertShape(earth, 0);
	picture->InsertShape(sky, 1);
	picture->InsertShape(aliens, 3);
	picture->InsertShape(aliens2, 4);
	picture->InsertShape(aliens1, 5);
	picture->InsertShape(aliens3, 6);
	picture->InsertShape(aliens4, 7);
	std::cout << "Frame: " << picture->GetFrame().height << " " << picture->GetFrame().width << std::endl;

	return picture;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Shapes");
	CCanvas canvas(window);
	auto slide = new CSlide(700, 700);
	auto picture = MakePicture();
	std::cout << "Shapes count: " << picture->GetGroup()->GetShapesCount() << std::endl;
	slide->AddShape(picture);
	auto group = picture->GetGroup();

	//group->GetShapeAtIndex(4)->GetFillStyle()->SetColor(Colors::YELLOW);

	//group->GetLineStyle()->SetColor(Colors::YELLOW);
	//group->GetFillStyle()->SetColor(Colors::YELLOW);

	group->SetFrame({ 50, 50, 800, 400 });

	//group->RemoveShapeAtIndex(0);
	//std::cout << "Shapes count deleting figure: " << group->GetShapesCount() << std::endl;

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
