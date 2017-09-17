#include <cppunit/extensions/HelperMacros.h>

class SampleTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(SampleTest);
	CPPUNIT_TEST(sampleTest);
	CPPUNIT_TEST_SUITE_END();
public:
	void
	setUp() 
	{}

	void
	tearDown()
	{}

	void
	sampleTest()
	{
		CPPUNIT_ASSERT_EQUAL(1, 1);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(SampleTest);
