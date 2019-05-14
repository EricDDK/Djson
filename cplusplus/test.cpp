#include <iostream>
#include <stdio.h>
#include <string.h>
#include "src/Json.h"

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC   
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DBG_NEW
#endif
#endif  // _DEBUG
#endif


DJSON_NAMESPACE_USE;

#define EXPECT(expect, actual) \
do {\
    if (expect != actual)\
        fprintf(stderr, "%s:%d: \n", __FILE__, __LINE__);\
}while(0)

void test1()
{
	Djson::Json j1(nullptr);
	Djson::Json j2(1.0);
	Djson::Json j3("test");
	Djson::Json j4();
	Djson::Json j5 = Djson::Json::Array{ 0,1,2,3,4 };
	Djson::Json j6 = Djson::Json::Object{
		{ "key1", "Value" },
		{ "key2", false },
		{ "key3", Djson::Json::Array{ 0,1,2,3,4 } }
	};
	Djson::Json j7 = Djson::Json::Object{
		{ "key1", j6.getValue() }
	};

	std::string str = j6.generate();
	EXPECT(str, "{\"key1\":\"Value\",\"key2\":false,\"key3\":[0,1,2,3,4]}");

	Djson::Json j;
	Value v = j.parse(str);
	EXPECT(v.getType(), Djson::JsonType::Object);
	EXPECT(v.getObject().at("key1").getString(), "Value");
	EXPECT(v.getObject().at("key2").getType(), Djson::JsonType::False);
	EXPECT(v.getObject().at("key3").getType(), Djson::JsonType::Array);
	EXPECT(v.getObject().at("key3").getArray().size(), 5);
	EXPECT(v.getObject().at("key3").getArray()[0].getNumber(), 0);
}

int main()
{
	test1();

#ifdef _MSC_VER
	_CrtDumpMemoryLeaks();
#endif
	system("pause");
	return 1;
}
