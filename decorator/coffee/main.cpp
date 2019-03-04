#include "stdafx.h"
#include "Beverages.h"
#include "Condiments.h"

#include <functional>
#include <iostream>
#include <string>

using namespace std;

/*
Функциональный объект, создающий лимонную добавку
*/
struct MakeLemon
{
	MakeLemon(unsigned quantity)
		: m_quantity(quantity)
	{
	}

	auto operator()(IBeveragePtr&& beverage) const
	{
		return make_unique<CLemon>(move(beverage), m_quantity);
	}

private:
	unsigned m_quantity;
};

/*
Функция, возвращающая функцию, создающую коричную добавку
*/
function<IBeveragePtr(IBeveragePtr&&)> MakeCinnamon()
{
	return [](IBeveragePtr&& b) {
		return make_unique<CCinnamon>(move(b));
	};
}

/*
Возвращает функцию, декорирующую напиток определенной добавкой
Параметры шаблона:
Condiment - класс добавки, конструктор которого в качестве первого аргумента
принимает IBeveragePtr&& оборачиваемого напитка
Args - список типов прочих параметров конструктора (возможно, пустой)
*/
template <typename Condiment, typename... Args>
auto MakeCondiment(const Args&... args)
{
	// Возвращаем функцию, декорирующую напиток, переданный ей в качестве аргумента
	// Дополнительные аргументы декоратора, захваченные лямбда-функцией, передаются
	// конструктору декоратора через make_unique
	return [=](auto&& b) {
		// Функции make_unique передаем b вместе со списком аргументов внешней функции
		return make_unique<Condiment>(forward<decltype(b)>(b), args...);
	};
}

/*
Перегруженная версия оператора <<, которая предоставляет нам синтаксический сахар
для декорирования компонента
Позволяет создать цепочку оборачивающих напиток декораторов следующим образом:
auto beverage = make_unique<CConcreteBeverage>(a, b, c)
<< MakeCondimentA(d, e, f)
<< MakeCondimentB(g, h);
Функциональные объекты MakeCondiment* запоминают аргументы, необходимые для создания
дополнения, и возвращают фабричную функцию, принимающую оборачиваемый напиток, которая
при своем вызове создаст нужный объект Condiment, передав ему запомненные аргументы.
Использование:
auto beverage =
make_unique<CConcreteBeverage>(a, b, c)
<< MakeCondimentA(d, e, f)
<< MakeCondimentB(g, h);
или даже так:
auto beverage =
make_unique<CConcreteBeverage>
<< MakeCondiment<CondimentA>(d, e, f)
<< MakeCondiment<CondimentB>(g, h);
В последнем случае нет необходимости писать вручную реализации MakeCondimentA и MakeCondimentB, т.к.
необходимую реализацию сгенерирует компилятор
Классический способ оборачивания выглядел бы так:
auto baseBeverage = make_unique<CConcretedBeverage>(a, b, c);
auto wrappedWithCondimentA = make_unique<CCondimentA>(move(baseBeverage), d, e, f);
auto beverage = make_unique<CCondimentB>(move(wrappedWithCondimentA), g, h);
либо так:
auto beverage = make_unique<CCondimentB>(
make_unique<CCondimentA>(
make_unique<CConcreteBeverage>(a, b, c), // Напиток
d, e, f	// доп. параметы CondimentA
),
g, h		// доп. параметры CondimentB
);
unique_ptr<CLemon> operator << (IBeveragePtr && lhs, const MakeLemon & factory)
{
return factory(move(lhs));
}
unique_ptr<CCinnamon> operator << (IBeveragePtr && lhs, const MakeCinnamon & factory)
{
return factory(move(lhs));
}
*/
template <typename Component, typename Decorator>
auto operator<<(Component&& component, const Decorator& decorate)
{
	return decorate(forward<Component>(component));
}

void DialogWithUser()
{
	cout << "Type 1 for coffee\n2 for tea\n3 for milkshake\n";
	int beverageChoice;
	cin >> beverageChoice;

	unique_ptr<IBeverage> beverage;

	switch (beverageChoice)
	{
	case 1:
	{
		cout << "Type 1 for Latte or 2 Cappuccino\n";
		int coffieChoice;
		cin >> coffieChoice;
		cout << "Type 1 for Standart Cup or 2 Double Cup\n";
		int cupChoice;
		cin >> cupChoice;

		PortionType cup = (cupChoice == 2) ? PortionType::Double : PortionType::Standart;

		switch (coffieChoice)
		{
		case 1:
			beverage = make_unique<CLatte>(cup);
			break;
		case 2:
			beverage = make_unique<CCapuccino>(cup);
			break;

		default:
			break;
		}
	}

	break;
	case 2:
	{
		cout << "Type 1 for Red\n2 for Green\n3 for Black\n4 for Herbal\n";
		int teaChoice;
		cin >> teaChoice;
		switch (teaChoice)
		{
		case 1:
			beverage = make_unique<CRedTea>();
			break;
		case 2:
			beverage = make_unique<CGreenTea>();
			break;
		case 3:
			beverage = make_unique<CBlackTea>();
			break;
		case 4:
			beverage = make_unique<CHerbalTea>();
			break;

		default:
			break;
		}
	}

	break;
	case 3:
	{
		cout << "Type 1 for Small\n2 for Standart\n3 for Big\n";
		int milkshakeChoice;
		cin >> milkshakeChoice;
		switch (milkshakeChoice)
		{
		case 1:
			beverage = make_unique<CMilkshake>(MilkshakePortionType::Small);
			break;
		case 2:
			beverage = make_unique<CMilkshake>(MilkshakePortionType::Standart);
			break;
		case 3:
			beverage = make_unique<CMilkshake>(MilkshakePortionType::Big);
			break;

		default:
			break;
		}
	}
	break;
	default:
		return;
		break;
	}

	int condimentChoice;
	bool checkout = false;
	while (!checkout)
	{
		cout << "1 - Lemon\n2 - Cinnamon\n3 - Chocolate\n4 - Cream\n5 - Liqour\n0 - Checkout" << endl;
		cin >> condimentChoice;
		switch (condimentChoice)
		{
		case 0:
			checkout = true;
			break;
		case 1:
			beverage = move(beverage) << MakeCondiment<CLemon>(2);
			break;
		case 2:
			beverage = move(beverage) << MakeCondiment<CCinnamon>();
			break;
		case 3:
		{
			int slies;
			cout << "Write your chocolate slies number (NOT MORE THAN 5)" << endl;
			cin >> slies;
			beverage = move(beverage) << MakeCondiment<CChocolate>(slies);
		}
		break;
		case 4:
			beverage = move(beverage) << MakeCondiment<CCream>();
			break;
		case 5:
		{

			int type;
			cout << "Write 1 for walnut, 2 for chocolate" << endl;
			cin >> type;
			LiquorType liquorType = (type == 1) ? LiquorType::Walnut : LiquorType::Chocolate;
			beverage = move(beverage) << MakeCondiment<CLiquor>(liquorType);
		}
		break;
		default:
			checkout = true;
			break;
		}
	}

	cout << beverage->GetDescription() << ", cost: " << beverage->GetCost() << endl;
}

int main()
{
	DialogWithUser();
	cout << endl;
	{
		// Наливаем чашечку латте
		auto latte = make_unique<CLatte>();
		// добавляем корицы
		auto cinnamon = make_unique<CCinnamon>(move(latte));
		// добавляем пару долек лимона
		auto lemon = make_unique<CLemon>(move(cinnamon), 2);
		// добавляем пару кубиков льда
		auto iceCubes = make_unique<CIceCubes>(move(lemon), 2, IceCubeType::Dry);
		// добавляем 2 грамма шоколадной крошки
		auto chocolateCrumbs = make_unique<CChocolateCrumbs>(move(iceCubes), 2);
		// добавляем 6 кусочков шоколада, но нельзя так много, поэтому добавится только пять
		auto beverage = make_unique<CChocolate>(move(chocolateCrumbs), 6);

		// Выписываем счет покупателю
		cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	}

	{
		auto beverage = make_unique<CChocolateCrumbs>( // Внешний слой: шоколадная крошка
			make_unique<CIceCubes>( // | под нею - кубики льда
				make_unique<CLemon>( // | | еще ниже лимон
					make_unique<CCinnamon>( // | | | слоем ниже - корица
						make_unique<CLatte>()), // | | |   в самом сердце - Латте
					2), // | | 2 дольки лимона
				2, IceCubeType::Dry), // | 2 кубика сухого льда
			2); // 2 грамма шоколадной крошки

		// Выписываем счет покупателю
		cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	}

	// Подробнее рассмотрим работу MakeCondiment и оператора <<
	{
		// lemon - функция, добавляющая "2 дольки лимона" к любому напитку
		auto lemon2 = MakeCondiment<CLemon>(2);
		// iceCubes - функция, добавляющая "3 кусочка льда" к любому напитку
		auto iceCubes3 = MakeCondiment<CIceCubes>(3, IceCubeType::Water);

		auto tea = make_unique<CTea>();

		// декорируем чай двумя дольками лимона и тремя кусочками льда
		auto lemonIceTea = iceCubes3(lemon2(move(tea)));
		/* Предыдущая строка выполняет те же действия, что и следующий код:
		auto lemonIceTea =
		make_unique<CIceCubes>(
		make_unique<CLemon>(
		move(tea),
		2),
		2, IceCubeType::Water);
		*/

		auto oneMoreLemonIceTea = make_unique<CTea>() // Берем чай
			<< MakeCondiment<CLemon>(2) // добавляем пару долек лимона
			<< MakeCondiment<CIceCubes>(3, IceCubeType::Water); // и 3 кубика льда
		/*
																Предыдущая конструкция делает то же самое, что и следующая:
																auto oneMoreLemonIceTea =
																MakeCondiment<CIceCubes>(3, IceCubeType::Water)(
																MakeCondiment<CLemon>(2)(make_unique<CTea>())
																);
																*/
	}

	// Аналог предыдущего решения с добавкой синтаксического сахара
	// обеспечиваемого операторами << и функцией MakeCondiment
	{
		auto beverage = make_unique<CLatte>() // Наливаем чашечку латте,
			<< MakeCondiment<CCinnamon>() // оборачиваем корицей,
			<< MakeCondiment<CLemon>(2) // добавляем пару долек лимона
			<< MakeCondiment<CIceCubes>(2, IceCubeType::Dry) // брасаем пару кубиков сухого льда
			<< MakeCondiment<CChocolateCrumbs>(2); // посыпаем шоколадной крошкой

		// Выписываем счет покупателю
		cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	}

	{
		auto beverage = make_unique<CMilkshake>() // Наливаем молочный коктейль
			<< MakeCondiment<CSyrup>(SyrupType::Maple) // заливаем кленовым сиропом
			<< MakeCondiment<CCoconutFlakes>(8); // посыпаем кокосовой стружкой

		// Выписываем счет покупателю
		cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	}
}
