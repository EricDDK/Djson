#ifndef _DJSON_PARSER_H__
#define _DJSON_PARSER_H__

#include "Common.h"
#include "Value.h"

DJSON_NAMESPACE_START

class Parser
{
public:
	Parser(Json &val, const std::string &result);

private:
	void parseWhiteSpace();
	void parseValue();
	void parseLiteral(const char *literal, JsonType t);
	void parseNumber();
	void parseString();
	void parseStringRaw(std::string &tmp);
	void parseHex4(const char* &p, unsigned &u);
	void parseEncodeUTF8(std::string &s, unsigned u);
	void parseArray();
	void parseObject();

private:
	const char* _cur;
	Json _val;

};

DJSON_NAMESPACE_END

#endif
