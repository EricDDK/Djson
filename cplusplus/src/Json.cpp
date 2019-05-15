#include "Json.h"

DJSON_NAMESPACE_START

Json::Json(const Json& rhs)
{
	switch (rhs.getType())
	{
	case JsonType::kNumber:
		_json = Value(rhs.getNumber());
		break;
	case JsonType::kString:
		_json = Value(rhs.getString());
		break;
	case JsonType::kArray:
		_json = Value(rhs.getArray());
		break;
	case JsonType::kObject:
		_json = Value(rhs.getObject());
		break;
	default:
		break;
	}
	setType(rhs.getType());
}

Json::Json(std::nullptr_t)
	:_json(Value(nullptr)) {}
Json::Json(bool b)
	: _json(Value(b)) {}
Json::Json(int i)
	: _json(Value(1.0 * i)) {}
Json::Json(double d)
	: _json(Value(d)) {}
Json::Json(const char* c)
	: _json(Value(c)) {}
Json::Json(const std::string& s)
	: _json(Value(s)) {}
Json::Json(std::string&& s)
	: _json(Value(std::move(s))) {}
Json::Json(const DjsonArray& a)
	: _json(Value(a)) {}
Json::Json(DjsonArray&& a)
	: _json(Value(std::move(a))) {}
Json::Json(const DjsonObject& o)
	: _json(Value(o)) {}
Json::Json(DjsonObject&& o)
	: _json(Value(std::move(o))) {}

const std::string Json::generate()
{
	std::string result;
	Generator(_json.getValue(), result);
	return result;
}

const Value Json::parse(const std::string& content)
{
	Value v = _json.getValue();
	Parser(v, content);
	return v;
}

DJSON_NAMESPACE_END