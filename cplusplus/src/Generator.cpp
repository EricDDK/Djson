#include "Generator.h"

DJSON_NAMESPACE_START

Generator::Generator(const Value &val, std::string &result)
	:_result(result)
{
	stringifyValue(val);
}

void Generator::stringifyValue(const Value &val)
{
	switch (val.getType())
	{
	case JsonType::Null:
		_result += "null";
		break;
	case JsonType::True:
		_result += "true";
		break;
	case JsonType::False:
		_result += "false";
		break;
	case JsonType::Number:
	{
		char buffer[32] = { 0 };
		sprintf(buffer, "%.17g", val.getNumber());
		_result += buffer;
	}
	break;
	case JsonType::String:
		stringifyString(val.getString());
		break;
	case JsonType::Array:
		_result += '[';
		for (int i = 0; i < val.getArraySize(); ++i)
		{
			if (i > 0)
				_result += ',';
			stringifyValue(val.getArrayElement(i));
		}
		_result += ']';
		break;
	case JsonType::Object:
		_result += '{';
		for (int i = 0; i < val.getObjectSize(); ++i)
		{
			if (i > 0)
				_result += ',';
			stringifyString(val.getObjectKey(i));
			_result += ':';
			stringifyValue(val.getObjectValue(i));
		}
		_result += '}';
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
				char buffer[7] = { 0 };
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