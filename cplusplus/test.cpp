#include <iostream>
#include <stdio.h>
#include <string.h>
#include "src/Json.h"

DJSON_NAMESPACE_USE;

#define EXPECT(expect, actual) \
do {\
    if (expect != actual)\
        fprintf(stderr, "%s:%d: ", __FILE__, __LINE__);\
}while(0)

int main()
{
	/*Json j1(nullptr);
	Json j2(1.0);
	Json j3("test");
	Json j4();
	Json j5 = Json::Array{0,1,2,3,4};*/
	Json j6 = Json::Object{
		{"key1", "Value"},
		{"key2", false },
		{"key3", Json::Array{ 0,1,2,3,4 } }
	};

	std::string str = j6.generate();
	EXPECT(str, "{\"key1\":\"Value\",\"key2\":false,\"key3\":[0,1,2,3,4]}");

	Json j;
	Value v = j.parse(str);

	system("pause");
	return 1;
}