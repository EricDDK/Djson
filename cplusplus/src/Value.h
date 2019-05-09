#ifndef _DJSON_VALUE_H__
#define _DJSON_VALUE_H__

#include <string>
#include <vector>
#include "Common.h"

DJSON_NAMESPACE_START

class Value
{
public:
	Value();
	virtual ~Value();

	void init();
	void free();


private:
	Djson::JsonType _type = Djson::JsonType::Null;
	union
	{
		double _num;
		std::string _str;
		std::vector<Djson::Value> _array;
		std::vector<std::pair<std::string, Djson::Value>> _object;
	};

};

DJSON_NAMESPACE_END

#endif
