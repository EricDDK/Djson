#ifndef _DJSON_GENERATOR_H__
#define _DJSON_GENERATOR_H__

#include "Common.h"
#include "Value.h"

DJSON_NAMESPACE_START

class Generator
{
public:
	Generator(const Value &val, std::string &result);

private:
	void stringifyValue(const Value &val);
	void stringifyString(const std::string &str);

private:
	std::string _result;

};

DJSON_NAMESPACE_END

#endif
