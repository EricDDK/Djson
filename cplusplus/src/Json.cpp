#include "Json.h"

DJSON_NAMESPACE_START

Json::Json(const Json& rhs)
{
	switch (rhs.getType())
	{
	case JsonType::Number:
		_json = std::make_unique<Value>(rhs.getNumber());
		break;
	case JsonType::String:
		_json = std::make_unique<Value>(rhs.getString());
		break;
	case JsonType::Array:
		_json = std::make_unique<Value>(rhs.getArray());
		break;
	case JsonType::Object:
		_json = std::make_unique<Value>(rhs.getObject());
		break;
	default:
		break;
	}
	setType(rhs.getType());
}

Json::Json(std::nullptr_t)
	:_json(std::make_unique<Djson::Value>(nullptr)) {}
Json::Json(bool b)
	: _json(std::make_unique<Djson::Value>(b)) {}
Json::Json(int i)
	: _json(std::make_unique<Djson::Value>(1.0 * i)) {}
Json::Json(double d)
	: _json(std::make_unique<Djson::Value>(d)) {}
Json::Json(const char* c)
	: _json(std::make_unique<Djson::Value>(c)) {}
Json::Json(const std::string& s)
	: _json(std::make_unique<Djson::Value>(s)) {}
Json::Json(std::string&& s)
	: _json(std::make_unique<Djson::Value>(std::move(s))) {}
Json::Json(const Array& a)
	: _json(std::make_unique<Djson::Value>(a)) {}
Json::Json(Array&& a)
	: _json(std::make_unique<Djson::Value>(std::move(a))) {}
Json::Json(const Object& o)
	: _json(std::make_unique<Djson::Value>(o)) {}
Json::Json(Object&& o)
	: _json(std::make_unique<Djson::Value>(std::move(o))) {}

std::string Json::generate() const
{
	std::string result;
	Generator(_json->getValue(), result);
	return result;
}

Value Json::parse(const std::string& content)
{
	Value v = _json->getValue();
	Parser(v, content);
	return v;
}

DJSON_NAMESPACE_END