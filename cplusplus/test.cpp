#include <iostream>
#include <stdio.h>
#include <string.h>
#include "src/Json.h"

DJSON_NAMESPACE_USE;

#define EXPECT(expect, actual) \
do {\
    if (expect != actual)\
        fprintf(stderr, "%s:%d: \n", __FILE__, __LINE__);\
}while(0)

int main()
{
	Json j1(nullptr);
	Json j2(1.0);
	Json j3("test");
	Json j4();
	Json j5 = Json::Array{0,1,2,3,4};
	Json j6 = Json::Object{
		{"key1", "Value"},
		{"key2", false },
		{"key3", Json::Array{ 0,1,2,3,4 } }
	};

	std::string str = j6.generate();
	EXPECT(str, "{\"key1\":\"Value\",\"key2\":false,\"key3\":[0,1,2,3,4]}");

	Json j;
	Value v = j.parse(str);
	EXPECT(v.getType(), JsonType::Object);
	EXPECT(v.getObject().at("key1").getString(), "Value");
	EXPECT(v.getObject().at("key2").getType(), JsonType::False);
	EXPECT(v.getObject().at("key3").getType(), JsonType::Array);
	EXPECT(v.getObject().at("key3").getArray().size(), 5);
	EXPECT(v.getObject().at("key3").getArray()[0].getNumber(), 0);

	system("pause");
	return 1;
}