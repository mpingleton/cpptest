# 2. Hello World!

Now let's write a very simple automated test.

## The Code to Test

For an example, let's use the following functions:

```c
int add(int a, int b)
{
	return a + b; // Correct
}

int sub(int a, int b)
{
	return a + b; // OOPS!  This will cause the test to fail!
}
```

## Include

Include the `cpptest.h` for C code, or include the `cpptest.hpp` for C++ code.  In the case of C++ code, you may use the `cpptest` namespace.

C
```c
#include <cpptest.h>
```

C++
```cpp
#include <cpptest.hpp>

using namespace cpptest;
```

## Write the Scenario

### C

In C, a scenario is represented with a function.  The function should have return type `void` and a single parameter of type `struct CTestScenario*`.  Below are three different test scenarios, each within their own function.

```c
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

void testScenarioSub_4_2(struct CTestScenario* pScenario)
{
	int ans = sub(4, 2);
	expectToEqualInt(pScenario, "Should return 2.", ans, 2);
}
```

The call to `expectToEqualInt()` makes an assertion about the expected behavior of the tested code.  In this case, the return values of `add()` and `sub()` should be `4`, `7`, and `2` depending on the scenario.  If the actual return value matches the expected one, the scenario passes.  Otherwise, it fails.

### C++

In C++, a scenario is represented with a class which inherits from the `Scenario` base class.  Below are three scenarios which are equivalent to the ones above.

```cpp
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
```

Here, the method `expectToEqual()` is a part of the `Scenario` base class.  Additionally, it is important that the `test()` method seen above be named exactly so, because it overrides that of its base class.

Any given test scenario must call `expectToEqual()` at least once.  Otherwise, the test fails.

## Create a Section

### C

Next, create a section and add the scenario to it.  In C, the `initSection()` function creates a new section and makes it ready to use.  Next, the `addScenarioToSection()` function call adds the previously-created scenarios and adds them to the section.

```c
struct CTestSection* testSectionAdd()
{
	struct CTestSection* pSection = initSection("add() function");

	addScenarioToSection(pSection, "2+2=4", &testScenarioAdd_2_2);
	addScenarioToSection(pSection, "4+3=7", &testScenarioAdd_4_3);

	return pSection;
}

struct CTestSection* testSectionSub()
{
	struct CTestSection* pSection = initSection("sub() function");

	addScenarioToSection(pSection, "4-2=2", &testScenarioSub_4_2);

	return pSection;
}
```

### C++

In C++, a section is represented with a class which inherits from `Section`.  Scenarios are added to the section in the class's constructor:

```cpp
class AddSection : public Section
{
public:
	AddSection() : Section("add() function")
	{
		add(new Add_2_2());
		add(new Add_4_3());
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
```

## Create a Runner

Next, create an empty test runner:

C
```c
struct CTestRunner runner = {};
initTests(&runner);
```

C++
```cpp
Runner runner = Runner();
```

Then, add the previously-created sections to the runner:

C
```c
addSectionToTest(&runner, testSectionAdd());
addSectionToTest(&runner, testSectionSub());
```

C++
```cpp
runner.add(new AddSection());
runner.add(new SubSection());
```

Run the tests by calling `runTests()` or `run()`.  The `SHOW_EVERYTHING` flag instructs the runner to display the status on of the tests on the terminal as they are executed.

C
```c
runTests(&runner, SHOW_EVERYTHING);
```

C++
```cpp
runner.run(SHOW_EVERYTHING);
```

Once the tests are finished, calling `printTests()` or `print()` will display the test results on the terminal.

C
```c
printTests(&runner, SHOW_EVERYTHING);
```

C++
```cpp
runner.print(SHOW_EVERYTHING);
```

Finally, call `freeTests()` to free the heap memory that was requested by the test runner.  This step is only required in C.

C
```c
freeTests(&runner);
```

Finally, calling `didTestsPass()` or `didPass()` will check if all the tests passed.

C
```c
if (didTestsPass(&runner) == EXPECTATION_PASS)
	return 0;

return 1;
```

C++
```cpp
if (runner.didPass())
	return 0;

return 1;
```

> [!TIP]
> It is recommended to base the `main()` function's return value on the test results.

Below are the steps for working with the test runner within the `main()` function.

C
```c
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
```

C++
```cpp
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
```

## Compile

Compile the code:

### C

```shell
clang helloworld.c -lctest -o helloworld
```

### C++

```shell
clang++ helloworld.cpp -lcpptest -o helloworld
```

> [!NOTE]
> The complete examples for the above-seen code are located in the `examples/helloworld.c` and `examples/helloworld.cpp` files.
