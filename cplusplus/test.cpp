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
	Djson::Json j4(44);
	Djson::Json j5 = DjsonArray{ 0,1,2,3,4 };
	Djson::Json j6 = DjsonObject{
		{ "key1", "Value" },
		{ "key2", false },
		{ "key3", DjsonArray{ 0,1,2,3,4 } }
	};

	std::string str = j6.generate();
	EXPECT(str, "{\"key1\":\"Value\",\"key2\":false,\"key3\":[0,1,2,3,4]}");

	str = "{\"key1\":  \"Value\",\"key2\":false   , \"key3\":[  0, 1,      2,3,4]}";
	Djson::Json j;
	Djson::Json v = j.parse(str);
	EXPECT(v.getType(), Djson::JsonType::kObject);
	EXPECT(v.getObject().at("key1").getString(), "Value");
	EXPECT(v.getObject().at("key2").getType(), Djson::JsonType::kFalse);
	EXPECT(v.getObject().at("key3").getType(), Djson::JsonType::kArray);
	EXPECT(v.getObject().at("key3").getArray().size(), 5);
	EXPECT(v.getObject().at("key3").getArray()[0].getNumber(), 0);
}

void test2()
{
	Djson::Json j1 = DjsonObject{
		{ "key1", "Value" },
		{ "key2", 3.15 },
		{ "key3", DjsonArray{ 0,1,2,3 } }
	};
	Djson::Json j2 = DjsonArray{ 1,1,1,1,1,1,1,1 };
	j2.add(-500);
	Djson::Json j3 = DjsonObject{
		{ "key1", j1 }
	};
	j3.add("key2", j2);
	j3.add("key3", 55000);
	j2 = Djson::Json(nullptr);

	std::string str = j3.generate();
	EXPECT(str, "{\"key1\":{\"key1\":\"Value\",\"key2\":3.1499999999999999,\"key3\":[0,1,2,3]},\"key2\":[1,1,1,1,1,1,1,1,-500],\"key3\":55000}");

	Djson::Json j;
	Djson::Json v = j.parse(str);
	EXPECT(v.getType(), Djson::JsonType::kObject);
	EXPECT(v.getObject().at("key1").getObject().at("key1").getString(), "Value");
	EXPECT(v.getObject().at("key1").getObject().at("key2").getNumber(), 3.15);
}

void test3()
{
	
}

void testOther()
{
	Djson::Json j1 = DjsonObject{
		{ "key1", "Value" },
		{ "key2", 3.15 },
		{ "key3", DjsonArray{ 0,1,2,3 } }
	};
	Djson::Json j2 = Djson::Json(j1);
	EXPECT(j1, j2);
}

int main()
{
	test1();
	test2();
	test3();

	testOther();

#ifdef _MSC_VER
	_CrtDumpMemoryLeaks();
#endif
	system("pause");
	return 1;
}
