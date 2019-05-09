#include <iostream>
#include <string.h>
#include "src/Value.h"

DJSON_NAMESPACE_USE;

int main()
{
	for (int i = 0; i < 100000; ++i)
	{
		Djson::Value* v = new Djson::Value;
		delete v;
	}
	system("pause");
	return 1;
}