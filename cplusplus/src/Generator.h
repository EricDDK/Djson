#ifndef _DJSON_GENERATOR_H__
#define _DJSON_GENERATOR_H__

#include "Common.h"
#include "Json.h"

DJSON_NAMESPACE_START

class Generator
{
public:
	Generator(const Json &val, std::string &result);

private:
	void stringifyValue(const Json &val);
	void stringifyString(const std::string &str);

private:
	std::string _result;

};

DJSON_NAMESPACE_END

#endif
