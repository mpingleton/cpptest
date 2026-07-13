// clang helloworld.c -lctest -o helloworld

#include <cpptest.h>

int add(int a, int b)
{
	return a + b;
}

int sub(int a, int b)
{
	return a + b; // OOPS!  This will cause the test to fail!
}

void testScenarioAdd_2_2(struct CTestScenario* pScenario)
{
	int ans = add(2, 2);
	expectToEqualInt(pScenario, "Should return 4.", ans, 4);
}

void testScenarioAdd_4_3(struct CTestScenario* pScenario)
{
	int ans = add(4, 3);
	expectToEqualInt(pScenario, "Should return 7.", ans, 7);
}

struct CTestSection* testSectionAdd()
{
	struct CTestSection* pSection = initSection("add() function");

	addScenarioToSection(pSection, "2+2=4", &testScenarioAdd_2_2);
	addScenarioToSection(pSection, "4+3=7", &testScenarioAdd_4_3);

	return pSection;
}

void testScenarioSub_4_2(struct CTestScenario* pScenario)
{
	int ans = sub(4, 2);
	expectToEqualInt(pScenario, "Should return 2.", ans, 2);
}

struct CTestSection* testSectionSub()
{
	struct CTestSection* pSection = initSection("sub() function");

	addScenarioToSection(pSection, "4-2=2", &testScenarioSub_4_2);

	return pSection;
}

int main(int argc, char** argv)
{
	struct CTestRunner runner = {};
	initTests(&runner);

	addSectionToTest(&runner, testSectionAdd());
	addSectionToTest(&runner, testSectionSub());

	runTests(&runner, SHOW_EVERYTHING);
	printTests(&runner, SHOW_EVERYTHING);

	freeTests(&runner);

	if (didTestsPass(&runner) == EXPECTATION_PASS)
		return 0;

	return 1;
}
