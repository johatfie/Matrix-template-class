#include "testDriver.h"

testDriver::testDriver(void)
:testCount(0)
{
}

testDriver::~testDriver(void)
{
}

void testDriver::testFunction( bool result )
{
	if(result)
	{
		cout << "Test " << testCount++ << ": passed" << endl;
	}
	else
	{
		cout << "Test " << testCount++ << ": failed!" << endl;
		throw std::exception();
	}
}

