#include "stdafx.h"
#include "CCanvas.h"
#include "CDesigner.h"
#include "CPainter.h"
#include "CShapeFactory.h"
#include <fstream>
#include <strstream>

int main()
{
	try
	{
		const std::string inputFileName = "house.txt";
		std::ifstream fin(inputFileName);

		if (!fin.is_open())
		{
			throw std::exception("Can not open file");
		}

		CShapeFactory shape;
		CDesigner designer(shape);

		CPictureDraft pictureDraft = designer.CreateDraft(fin);

		sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGTH), "Shapes");
		CCanvas canvas(window);
		CPainter painter;

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear(sf::Color::White);

			painter.DrawPicture(pictureDraft, canvas);

			window.display();
		}

		return 0;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << "\n";
	}
	return 0;
}
