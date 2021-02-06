#include "pch.h"
#include "CppUnitTest.h"
#include "../SpaceshIT!/Vector.h"

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
}
