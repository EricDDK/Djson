#include "Parser.h"

DJSON_NAMESPACE_START

inline void expect(const char * &c, char ch)
{
	assert(*c == ch);
	++c;
}

Parser::Parser(Value &val, const std::string &result)
	:_val(val)
	, _cur(result.c_str())
{
	_val.setType(JsonType::Null);
	parseWhiteSpace();
	parseValue();
	parseWhiteSpace();
	if (*_cur != '\0')
	{
		throw(std::logic_error("parse root error, not end"));
	}
}

void Parser::parseWhiteSpace()
{
	while (*_cur == ' ' || *_cur == '\t' || *_cur == '\n' || *_cur == '\r')
	{
		++_cur;
	}
}

void Parser::parseValue()
{
	switch (*_cur)
	{
	case 'n':
		parseLiteral("null", JsonType::Null);
		return;
	case 't':
		parseLiteral("true", JsonType::True);
		return;
	case 'f':
		parseLiteral("false", JsonType::False);
		return;
	default:
		return;
	}
}

void Parser::parseLiteral(const char *literal, JsonType t)
{
	size_t i = 0;
	while (literal[i] != '\0')
	{
		if (_cur[i] != literal[i])
			throw (std::logic_error("parse invalid value"));
		++i;
	}
	_cur += i;
	_val.setType(t);
}

void Parser::parseNumber()
{
	const char *p = _cur;
	if (*p == '-')
		++p;
	if (*p == '0')
		++p;
	else
	{
		if (!isdigit(*p))
			throw(std::logic_error("parse invalid value"));
		while (isdigit(*++p));
	}
	if (*p == 'e' || *p == 'E') 
	{
		++p;
		if (*p == '+' || *p == '-') 
			++p;
		if (!isdigit(*p)) 
			throw (std::logic_error("parse invalid value"));
		while (isdigit(*++p));
	}
	errno = 0;
	double v = strtod(_cur, NULL);
	if (errno == ERANGE && (v == HUGE_VAL || v == -HUGE_VAL))
		throw (std::logic_error("parse number too big"));
	_val.setNumber(v);
	_cur = p;
}

void Parser::parseString()
{
	std::string s;
	parseStringRaw(s);
	_val.setString(s);
}

void Parser::parseStringRaw(std::string &tmp)
{
	expect(_cur, '\"');
	const char *p = _cur;
	unsigned u = 0, u2 = 0;
	while (*p != '\"') 
	{
		if (*p == '\0')
			throw(std::logic_error("parse miss quotation mark"));
		if (*p == '\\' && ++p) 
		{
			switch (*p++) 
			{
			case '\"': tmp += '\"'; break;
			case '\\': tmp += '\\'; break;
			case '/': tmp += '/'; break;
			case 'b': tmp += '\b'; break;
			case 'f': tmp += '\f'; break;
			case 'n': tmp += '\n'; break;
			case 'r': tmp += '\r'; break;
			case 't': tmp += '\t'; break;
			case 'u':
				parseHex4(p, u);
				if (u >= 0xD800 && u <= 0xDBFF) 
				{
					if (*p++ != '\\')
						throw(std::logic_error("parse invalid unicode surrogate"));
					if (*p++ != 'u')
						throw(std::logic_error("parse invalid unicode surrogate"));
					parseHex4(p, u2);
					if (u2 < 0xDC00 || u2 > 0xDFFF)
						throw(std::logic_error("parse invalid unicode surrogate"));
					u = (((u - 0xD800) << 10) | (u2 - 0xDC00)) + 0x10000;
				}
				parseEncodeUTF8(tmp, u);
				break;
			default: throw (std::logic_error("parse invalid string escape"));
			}
		}
		else if ((unsigned char)*p < 0x20) 
		{
			throw (std::logic_error("parse invalid string char"));
		}
		else tmp += *p++;
	}
	_cur = ++p;
}

void Parser::parseHex4(const char* &p, unsigned &u)
{
	u = 0;
	for (int i = 0; i < 4; ++i) 
	{
		char ch = *p++;
		u <<= 4;
		if (isdigit(ch))
			u |= ch - '0';
		else if (ch >= 'A' && ch <= 'F')
			u |= ch - ('A' - 10);
		else if (ch >= 'a' && ch <= 'f')
			u |= ch - ('a' - 10);
		else 
			throw(std::logic_error("parse invalid unicode hex"));
	}
}

void Parser::parseEncodeUTF8(std::string &s, unsigned u)
{
	if (u <= 0x7F)
		s += static_cast<char> (u & 0xFF);
	else if (u <= 0x7FF) {
		s += static_cast<char> (0xC0 | ((u >> 6) & 0xFF));
		s += static_cast<char> (0x80 | (u & 0x3F));
	}
	else if (u <= 0xFFFF) {
		s += static_cast<char> (0xE0 | ((u >> 12) & 0xFF));
		s += static_cast<char> (0x80 | ((u >> 6) & 0x3F));
		s += static_cast<char> (0x80 | (u & 0x3F));
	}
	else {
		assert(u <= 0x10FFFF);
		s += static_cast<char> (0xF0 | ((u >> 18) & 0xFF));
		s += static_cast<char> (0x80 | ((u >> 12) & 0x3F));
		s += static_cast<char> (0x80 | ((u >> 6) & 0x3F));
		s += static_cast<char> (0x80 | (u & 0x3F));
	}
}

void Parser::parseArray()
{
	expect(_cur, '[');
	parseWhiteSpace();
	std::vector<Value> tmp;
	if (*_cur == ']')
	{
		++_cur;
		_val.setArray(tmp);
		return;
	}
	else
	{
		while (1)
		{
			try
			{
				parseValue();
			}
			catch (std::logic_error)
			{
				_val.setType(JsonType::Null);
				throw;
			}
			tmp.push_back(_val);
			parseWhiteSpace();
			if (*_cur == ',')
			{
				++_cur;
				parseWhiteSpace();
			}
			else if (*_cur == ']')
			{
				++_cur;
				_val.setArray(tmp);
				return;
			}
			else
			{
				_val.setType(JsonType::Null);
				throw (std::logic_error("parse invalid array"));
			}
		}
	}
}

void Parser::parseObject()
{
	expect(_cur, '{');
	parseWhiteSpace();
	std::unordered_map<std::string, Djson::Value> tmp;
	std::string key;
	if (*_cur == '}') {
		++_cur;
		_val.setObject(tmp);
		return;
	}
	while (true)
	{
		if (*_cur != '\"') throw(std::logic_error("parse miss key"));
		try {
			parseStringRaw(key);
		}
		catch (std::logic_error) {
			throw(std::logic_error("parse miss key"));
		}
		parseWhiteSpace();
		if (*_cur++ != ':') throw(std::logic_error("parse miss colon"));
		parseWhiteSpace();
		try {
			parseValue();
		}
		catch (std::logic_error) {
			_val.setType(JsonType::Null);
			throw;
		}
		tmp[key] = _val;
		_val.setType(JsonType::Null);
		key.clear();
		parseWhiteSpace();
		if (*_cur == ',') {
			++_cur;
			parseWhiteSpace();
		}
		else if (*_cur == '}') {
			++_cur;
			_val.setObject(tmp);
			return;
		}
		else {
			_val.setType(JsonType::Null);
			throw(std::logic_error("parse miss comma or curly bracket"));
		}
	}
}

DJSON_NAMESPACE_END