#include "stdafx.h"
#include "Beverages.h"
#include "Condiments.h"

#include <functional>
#include <iostream>
#include <string>

using namespace std;

/*
�������������� ������, ��������� �������� �������
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
�������, ������������ �������, ��������� �������� �������
*/
function<IBeveragePtr(IBeveragePtr&&)> MakeCinnamon()
{
	return [](IBeveragePtr&& b) {
		return make_unique<CCinnamon>(move(b));
	};
}

/*
���������� �������, ������������ ������� ������������ ��������
��������� �������:
Condiment - ����� �������, ����������� �������� � �������� ������� ���������
��������� IBeveragePtr&& �������������� �������
Args - ������ ����� ������ ���������� ������������ (��������, ������)
*/
template <typename Condiment, typename... Args>
auto MakeCondiment(const Args&... args)
{
	// ���������� �������, ������������ �������, ���������� �� � �������� ���������
	// �������������� ��������� ����������, ����������� ������-��������, ����������
	// ������������ ���������� ����� make_unique
	return [=](auto&& b) {
		// ������� make_unique �������� b ������ �� ������� ���������� ������� �������
		return make_unique<Condiment>(forward<decltype(b)>(b), args...);
	};
}

/*
������������� ������ ��������� <<, ������� ������������� ��� �������������� �����
��� ������������� ����������
��������� ������� ������� ������������� ������� ����������� ��������� �������:
auto beverage = make_unique<CConcreteBeverage>(a, b, c)
<< MakeCondimentA(d, e, f)
<< MakeCondimentB(g, h);
�������������� ������� MakeCondiment* ���������� ���������, ����������� ��� ��������
����������, � ���������� ��������� �������, ����������� ������������� �������, �������
��� ����� ������ ������� ������ ������ Condiment, ������� ��� ����������� ���������.
�������������:
auto beverage =
make_unique<CConcreteBeverage>(a, b, c)
<< MakeCondimentA(d, e, f)
<< MakeCondimentB(g, h);
��� ���� ���:
auto beverage =
make_unique<CConcreteBeverage>
<< MakeCondiment<CondimentA>(d, e, f)
<< MakeCondiment<CondimentB>(g, h);
� ��������� ������ ��� ������������� ������ ������� ���������� MakeCondimentA � MakeCondimentB, �.�.
����������� ���������� ����������� ����������
������������ ������ ������������ �������� �� ���:
auto baseBeverage = make_unique<CConcretedBeverage>(a, b, c);
auto wrappedWithCondimentA = make_unique<CCondimentA>(move(baseBeverage), d, e, f);
auto beverage = make_unique<CCondimentB>(move(wrappedWithCondimentA), g, h);
���� ���:
auto beverage = make_unique<CCondimentB>(
make_unique<CCondimentA>(
make_unique<CConcreteBeverage>(a, b, c), // �������
d, e, f	// ���. �������� CondimentA
),
g, h		// ���. ��������� CondimentB
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
		// �������� ������� �����
		auto latte = make_unique<CLatte>();
		// ��������� ������
		auto cinnamon = make_unique<CCinnamon>(move(latte));
		// ��������� ���� ����� ������
		auto lemon = make_unique<CLemon>(move(cinnamon), 2);
		// ��������� ���� ������� ����
		auto iceCubes = make_unique<CIceCubes>(move(lemon), 2, IceCubeType::Dry);
		// ��������� 2 ������ ���������� ������
		auto chocolateCrumbs = make_unique<CChocolateCrumbs>(move(iceCubes), 2);
		// ��������� 6 �������� ��������, �� ������ ��� �����, ������� ��������� ������ ����
		auto beverage = make_unique<CChocolate>(move(chocolateCrumbs), 6);

		// ���������� ���� ����������
		cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	}

	{
		auto beverage = make_unique<CChocolateCrumbs>( // ������� ����: ���������� ������
			make_unique<CIceCubes>( // | ��� ��� - ������ ����
				make_unique<CLemon>( // | | ��� ���� �����
					make_unique<CCinnamon>( // | | | ����� ���� - ������
						make_unique<CLatte>()), // | | |   � ����� ������ - �����
					2), // | | 2 ������ ������
				2, IceCubeType::Dry), // | 2 ������ ������ ����
			2); // 2 ������ ���������� ������

		// ���������� ���� ����������
		cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	}

	// ��������� ���������� ������ MakeCondiment � ��������� <<
	{
		// lemon - �������, ����������� "2 ������ ������" � ������ �������
		auto lemon2 = MakeCondiment<CLemon>(2);
		// iceCubes - �������, ����������� "3 ������� ����" � ������ �������
		auto iceCubes3 = MakeCondiment<CIceCubes>(3, IceCubeType::Water);

		auto tea = make_unique<CTea>();

		// ���������� ��� ����� �������� ������ � ����� ��������� ����
		auto lemonIceTea = iceCubes3(lemon2(move(tea)));
		/* ���������� ������ ��������� �� �� ��������, ��� � ��������� ���:
		auto lemonIceTea =
		make_unique<CIceCubes>(
		make_unique<CLemon>(
		move(tea),
		2),
		2, IceCubeType::Water);
		*/

		auto oneMoreLemonIceTea = make_unique<CTea>() // ����� ���
			<< MakeCondiment<CLemon>(2) // ��������� ���� ����� ������
			<< MakeCondiment<CIceCubes>(3, IceCubeType::Water); // � 3 ������ ����
		/*
																���������� ����������� ������ �� �� �����, ��� � ���������:
																auto oneMoreLemonIceTea =
																MakeCondiment<CIceCubes>(3, IceCubeType::Water)(
																MakeCondiment<CLemon>(2)(make_unique<CTea>())
																);
																*/
	}

	// ������ ����������� ������� � �������� ��������������� ������
	// ��������������� ����������� << � �������� MakeCondiment
	{
		auto beverage = make_unique<CLatte>() // �������� ������� �����,
			<< MakeCondiment<CCinnamon>() // ����������� �������,
			<< MakeCondiment<CLemon>(2) // ��������� ���� ����� ������
			<< MakeCondiment<CIceCubes>(2, IceCubeType::Dry) // ������� ���� ������� ������ ����
			<< MakeCondiment<CChocolateCrumbs>(2); // �������� ���������� �������

		// ���������� ���� ����������
		cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	}

	{
		auto beverage = make_unique<CMilkshake>() // �������� �������� ��������
			<< MakeCondiment<CSyrup>(SyrupType::Maple) // �������� �������� �������
			<< MakeCondiment<CCoconutFlakes>(8); // �������� ��������� ��������

		// ���������� ���� ����������
		cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	}
}
