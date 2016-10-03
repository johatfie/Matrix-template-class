#ifndef testDriver_H
#define testDriver_H

#include <stdexcept>

#include <exception>

#include <iostream>
using std::cout;
using std::endl;


class testDriver
{
public:
	testDriver(void);
	~testDriver(void);

	void testFunction( bool );

private:
	int testCount;

};

#endif
