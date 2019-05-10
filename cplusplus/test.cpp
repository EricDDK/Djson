#include <iostream>
#include <string.h>
#include "src/Value.h"
#include "src/Generator.h"

DJSON_NAMESPACE_USE;

int main()
{
	for (int i = 0; i < 100000; ++i)
	{
		Djson::Value* v = new Djson::Value;
		delete v;
	}
	Value v;
	std::string ss = "aaaa";
	auto a = new Generator(v, ss);
	system("pause");
	return 1;
}