#include <cppunit/extensions/HelperMacros.h>
#include "../src/Logic.hh"

class LogicTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(LogicTest);
	CPPUNIT_TEST(testRotate);
	CPPUNIT_TEST_SUITE_END();
public:
	void
	setUp() 
	{}

	void
	tearDown()
	{}

	void
	testRotate()
	{
		Shape testShape = {{Color::green, Color::magic}, {Color::red, Color::grey}};
		Shape rotatedShape = rotate(testShape);
		CPPUNIT_ASSERT_EQUAL(Color::red, rotatedShape.at(0).at(0));
		CPPUNIT_ASSERT_EQUAL(Color::green, rotatedShape.at(0).at(1));
		CPPUNIT_ASSERT_EQUAL(Color::grey, rotatedShape.at(1).at(0));
		CPPUNIT_ASSERT_EQUAL(Color::magic, rotatedShape.at(1).at(1));

		rotatedShape = rotate(rotatedShape);
		CPPUNIT_ASSERT_EQUAL(Color::grey, rotatedShape.at(0).at(0));
		CPPUNIT_ASSERT_EQUAL(Color::red, rotatedShape.at(0).at(1));
		CPPUNIT_ASSERT_EQUAL(Color::magic, rotatedShape.at(1).at(0));
		CPPUNIT_ASSERT_EQUAL(Color::green, rotatedShape.at(1).at(1));

		rotatedShape = rotate(rotatedShape);
		CPPUNIT_ASSERT_EQUAL(Color::magic, rotatedShape.at(0).at(0));
		CPPUNIT_ASSERT_EQUAL(Color::grey, rotatedShape.at(0).at(1));
		CPPUNIT_ASSERT_EQUAL(Color::green, rotatedShape.at(1).at(0));
		CPPUNIT_ASSERT_EQUAL(Color::red, rotatedShape.at(1).at(1));

		rotatedShape = rotate(rotatedShape);
		CPPUNIT_ASSERT_EQUAL(testShape.at(0).at(0), rotatedShape.at(0).at(0));
		CPPUNIT_ASSERT_EQUAL(testShape.at(0).at(1), rotatedShape.at(0).at(1));
		CPPUNIT_ASSERT_EQUAL(testShape.at(1).at(0), rotatedShape.at(1).at(0));
		CPPUNIT_ASSERT_EQUAL(testShape.at(1).at(1), rotatedShape.at(1).at(1));
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(LogicTest);
