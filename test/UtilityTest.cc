#include <cppunit/extensions/HelperMacros.h>
#include "../src/Utility.hh"

class UtilityTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(UtilityTest);
	CPPUNIT_TEST(splitTest);
	CPPUNIT_TEST_SUITE_END();
public:
	void
	setUp() 
	{}

	void
	tearDown()
	{}

	void
	splitTest()
	{
		std::string toSplit = "0;1;2;3;;4;5;6;7;8;9;";
		auto splitVector = split(toSplit, ';');
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(10), splitVector.size());
		int currentNum = 0;
		for (auto elem : splitVector) {
			CPPUNIT_ASSERT_EQUAL(currentNum++, std::stoi(elem));
		}
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(UtilityTest);
