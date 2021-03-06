#include "pch.h"
#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

namespace Fly
{

std::function<void()> FlyWithWings()
{
	int flyingNumber = 0;

	return [flyingNumber]() mutable {
		cout << "I'm flying with wings for " << ++flyingNumber << " times" << endl;
	};
}

void FlyNoWay() {}

} // namespace Fly

namespace Dance
{
void DancingWaltz()
{
	cout << "I'm dancing the waltz!!" << endl;
}

void DancingMinuet()
{
	cout << "I'm dancing minuet!!" << endl;
}

void DanceNoWay() {}

} // namespace Dance

namespace Quack
{
void Quack()
{
	cout << "Quack Quack!!!" << endl;
}

void Squeek()
{
	cout << "Squeek!!!" << endl;
}

void MuteQuack() {}
} // namespace Quack

class Duck
{
public:
	Duck(const function<void()>&& flyBehavior,
		const function<void()>&& quackBehavior,
		const function<void()>&& danceBehavior)
		: m_quackBehavior(quackBehavior)
		, m_danceBehavior(danceBehavior)
	{
		assert(m_quackBehavior);
		assert(m_danceBehavior);
		SetFlyBehavior(flyBehavior);
	}
	void Quack() const
	{
		m_quackBehavior();
	}
	void Swim()
	{
		cout << "I'm swimming" << endl;
	}
	void Fly()
	{
		m_flyBehavior();
	}
	void Dance()
	{
		m_danceBehavior();
	}
	void SetFlyBehavior(const function<void()>& flyBehavior)
	{
		m_flyBehavior = flyBehavior;
	}
	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	function<void()> m_flyBehavior;
	function<void()> m_quackBehavior;
	function<void()> m_danceBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(Fly::FlyWithWings(), Quack::Quack, Dance::DancingWaltz)
	{
	}

	void Display() const override
	{
		cout << "I'm mallard duck" << endl;
	}
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(Fly::FlyWithWings(), Quack::Quack, Dance::DancingMinuet)
	{
	}

	void Display() const override
	{
		cout << "I'm redhead duck" << endl;
	}
};

class DecoyDuck : public Duck
{
public:
	DecoyDuck()
		: Duck(Fly::FlyNoWay, Quack::MuteQuack, Dance::DanceNoWay)
	{
	}

	void Display() const override
	{
		cout << "I'm decoy duck" << endl;
	}
};

class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(Fly::FlyNoWay, Quack::Squeek, Dance::DanceNoWay)
	{
	}

	void Display() const override
	{
		cout << "I'm rubber duck" << endl;
	}
};

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(Fly::FlyNoWay, Quack::Quack, Dance::DanceNoWay)
	{
	}

	void Display() const override
	{
		cout << "I'm model duck" << endl;
	}
};

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck& duck)
{
	DrawDuck(duck);
	duck.Quack();
	duck.Fly();
	duck.Dance();
	cout << endl;
}

void main()
{
	MallardDuck mallardDuck;
	PlayWithDuck(mallardDuck);
	PlayWithDuck(mallardDuck);
	PlayWithDuck(mallardDuck);

	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);

	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);

	DecoyDuck decoyDuck;
	PlayWithDuck(decoyDuck);

	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);
}