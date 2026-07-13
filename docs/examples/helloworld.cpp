// clang++ helloworld.cpp -lcpptest -o helloworld

#include <cpptest.hpp>

using namespace cpptest;

int add(int a, int b)
{
	return a + b;
}

int sub(int a, int b)
{
	return a + b; // OOPS!  This will cause the test to fail!
}

class Add_2_2 : public Scenario
{
public:
	Add_2_2() : Scenario("2+2=4")
	{}

	void test()
	{
		int ans = add(2, 2);
		expectToEqual("", "Should return 4.", ans, 4);
	}
};

class Add_4_3 : public Scenario
{
public:
	Add_4_3() : Scenario("4+3=7")
	{}

	void test()
	{
		int ans = add(4, 3);
		expectToEqual("", "Should return 7.", ans, 7);
	}
};

class AddSection : public Section
{
public:
	AddSection() : Section("add() function")
	{
		add(new Add_2_2());
		add(new Add_4_3());
	}
};

class Sub_4_2 : public Scenario
{
public:
	Sub_4_2() : Scenario("4-2=2")
	{}

	void test()
	{
		int ans = sub(4, 2);
		expectToEqual("", "Should return 2.", ans, 2);
	}
};

class SubSection : public Section
{
public:
	SubSection() : Section("sub() function")
	{
		add(new Sub_4_2());
	}
};

int main(int argc, char** argv)
{
	Runner runner = Runner();
	runner.add(new AddSection());
	runner.add(new SubSection());

	runner.run(SHOW_EVERYTHING);
	runner.print(SHOW_EVERYTHING);

	if (runner.didPass())
		return 0;

	return 1;
}
