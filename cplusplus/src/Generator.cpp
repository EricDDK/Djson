#include "Generator.h"
#include <sstream>

DJSON_NAMESPACE_START

Generator::Generator(const Json &j, std::string &result)
	:_result("")
{
	stringifyValue(j);
	result = _result;
}

void Generator::stringifyValue(const Json &val)
{
	switch (val.getType())
	{
	case JsonType::kNull:
		_result += "null";
		break;
	case JsonType::kTrue:
		_result += "true";
		break;
	case JsonType::kFalse:
		_result += "false";
		break;
	case JsonType::kNumber:
	{
		char buffer[32];
		sprintf(buffer, "%.17g", val.getNumber());
		_result += buffer;
	}
	break;
	case JsonType::kString:
		stringifyString(val.getString());
		break;
	case JsonType::kArray:
		_result += '[';
		for (size_t i = 0; i < val.getArraySize(); ++i)
		{
			if (i > 0)
				_result += ',';
			stringifyValue(val.getArrayElement(i));
		}
		_result += ']';
		break;
	case JsonType::kObject:
	{
		_result += '{';
		size_t i = 0;
		for (auto &o : val.getObject())
		{
			if (i > 0)
				_result += ',';
			stringifyString(o.first);
			_result += ':';
			stringifyValue(o.second);
			++i;
		}
		_result += '}';
	}
	break;
	default:
		break;
	}
}

void Generator::stringifyString(const std::string &str)
{
	_result += '\"';
	for (auto it = str.begin(); it < str.end(); ++it)
	{
		switch (*it)
		{
		case '\"':
			_result += "\\\"";
			break;
		case '\\':
			_result += "\\\\";
			break;
		case '\b':
			_result += "\\b";
			break;
		case '\f':
			_result += "\\f";
			break;
		case '\n':
			_result += "\\n";
			break;
		case '\r':
			_result += "\\r";
			break;
		case '\t':
			_result += "\\t";
			break;
		default:
			if (*it < 0x20)
			{
				char buffer[7];
				sprintf(buffer, "\\u%04X", *it);
				_result += buffer;
			}
			else
				_result += *it;
			break;
		}
	}
	_result += '\"';
}

DJSON_NAMESPACE_END