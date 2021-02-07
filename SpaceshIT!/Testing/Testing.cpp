#include "pch.h"
#include "CppUnitTest.h"
#include "../SpaceshIT!/Vector.h"
#include "../SpaceshIT!/Stack.h"
#include "../SpaceshIT!/Map.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(vectorTesting)
	{
	public:
		
		TEST_METHOD(vectorPushBackTest)
		{
			Vector<int> testVector;
			for (int i = 0; i < 11; i++)
				testVector.push_back(i);
			Assert::AreEqual(testVector.at(3), 3);
		}

		TEST_METHOD(vectorConstructor)
		{
			int input = 7;
			Vector<int> testVector(3, input);

			Assert::AreEqual(testVector.at(0), 7);
			Assert::AreEqual(testVector.at(1), 7);
			Assert::AreEqual(testVector.at(2), 7);
		}

		TEST_METHOD(vectorConstructor2)
		{
			int input = 7;
			Vector<int> testVector(3, input);

			Assert::AreEqual(testVector.at(0), 7);
			Assert::AreEqual(testVector.at(1), 7);
			Assert::AreEqual(testVector.at(2), 7);
		}

		TEST_METHOD(vectorFront)
		{
			int input = 7;
			Vector<int> testVector(3, input);

			Assert::AreEqual(testVector.front(), 7);
		}

		TEST_METHOD(vectorBack)
		{
			int input = 7;
			Vector<int> testVector(3, input);
			int new_value = 25;
			testVector.push_back(new_value);

			Assert::AreEqual(testVector.back(), new_value);
		}

		TEST_METHOD(vectorInsert)
		{
			int input = 7;
			Vector<int> testVector(3, input);
			int new_value = 25;
			testVector.insert(1, new_value);

			Assert::AreEqual(testVector.at(1), new_value);
		}

		TEST_METHOD(vectorErase)
		{
			int input = 7;
			Vector<int> testVector(3, input);
			int new_value = 25;
			testVector.insert(1, new_value);
			testVector.erase(0);

			Assert::AreEqual(testVector.at(0), new_value);
		}
	};
	TEST_CLASS(stackTesting)
	{
	public:

		TEST_METHOD(stackisEmpty)
		{
			Stack<int> stack = Stack<int>();
			Assert::AreEqual(stack.isEmpty(), true);
		}

		TEST_METHOD(stackpushStack)
		{
			Stack<int> stack = Stack<int>();
			Assert::AreEqual(stack.push(0), true);
		}

		TEST_METHOD(stackpopStack)
		{
			Stack<int> stack = Stack<int>();
			stack.push(0);
			Assert::AreEqual(stack.pop(), true);
		}

		TEST_METHOD(stackgetTop)
		{
			Stack<int> stack = Stack<int>();
			stack.push(0);
			Assert::AreEqual(stack.getTop(), 0);
		}

		TEST_METHOD(stackgetSize)
		{
			Stack<int> stack = Stack<int>();
			stack.push(0);
			Assert::AreEqual(stack.getSize(), 1);
		}
	};
	TEST_CLASS(mapTesting)
	{
	public:

		TEST_METHOD(mapInsertion)
		{
			Map<std::string, int> map = Map<std::string, int>();
			pair<std::string, int> temp = pair<std::string, int>{ "test", 0 };
			Assert::AreEqual(map.insert(&temp), true);
		}

		TEST_METHOD(mapErase)
		{
			Map<std::string, int> map = Map<std::string, int>();
			pair<std::string, int> temp = pair<std::string, int>{ "test", 0 };
			map.insert(&temp);
			Assert::AreEqual(map.erase("test"), true);
		}

		TEST_METHOD(mapOperator)
		{
			Map<std::string, int> map = Map<std::string, int>();
			pair<std::string, int> temp = pair<std::string, int>{ "test", 0 };
			map.insert(&temp);
			Assert::AreEqual(map["test"], 0);
		}

		TEST_METHOD(mapAt)
		{
			Map<std::string, int> map = Map<std::string, int>();
			pair<std::string, int> temp = pair<std::string, int>{ "test", 0 };
			map.insert(&temp);
			Assert::AreEqual(map.at("test"), 0);
		}

		TEST_METHOD(mapchange)
		{
			Map<std::string, int> map = Map<std::string, int>();
			pair<std::string, int> temp = pair<std::string, int>{ "test", 0 };
			map.insert(&temp);
			pair<std::string, int> temp1 = pair<std::string, int>{ "test", 1 };
			pair<std::string, int>* temp2 = &temp1;
			Assert::AreEqual(map.Change(temp2), true);
		}

		TEST_METHOD(mapIsEmpty)
		{
			Map<std::string, int> map = Map<std::string, int>();
			Assert::AreEqual(map.isEmpty(), true);
		}

		TEST_METHOD(MapGetAmount)
		{
			Map<std::string, int> map = Map<std::string, int>();
			Assert::AreEqual(map.getAmount(), 0);
		}
	};
}
