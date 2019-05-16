#include "Json.h"
#include "Parser.h"
#include "Generator.h"
#include "Value.h"

DJSON_NAMESPACE_START

const std::string Json::generate()
{
	std::string result;
	Generator(*this, result);
	return result;
}

const Json& Json::parse(const std::string& content)
{
	Parser(*this, content);
	return *this;
}

Json::Json(const Json& rhs)
{
	setType(rhs.getType());
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
}

Json& Json::operator=(const Json& rhs)
{
	Json tmp(rhs);
	std::swap(_json, tmp._json);
	return *this;
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
Json::Json(const DjsonArray& a)
	: _json(Value(a)) {}
Json::Json(const DjsonObject& o)
	: _json(Value(o)) {}

const Json& Json::operator[](const std::string& s) const 
{ 
	return _json.operator[](s); 
}

const Json& Json::operator[](size_t index) const 
{ 
	return _json.operator[](index); 
}

Json& Json::operator[](const std::string& s) 
{ 
	return _json.operator[](s); 
}

Json& Json::operator[](size_t index) 
{ 
	return _json.operator[](index); 
}

void Json::setType(JsonType type) 
{ 
	_json.setType(type); 
}

const JsonType Json::getType() const
{
	return _json.getType();
}

void Json::setNumber(double d)
{
	_json.setNumber(d);
}

void Json::setString(std::string &s)
{
	_json.setString(s);
}

void Json::setArray(const DjsonArray &arr)
{
	_json.setArray(arr);
}

void Json::setObject(const DjsonObject &obj)
{
	_json.setObject(obj);
}

bool Json::getBool() const
{
	assert(_json.getType() == JsonType::kFalse || _json.getType() == JsonType::kTrue); return _json.getType() == JsonType::kTrue ? true : false;
}

double Json::getNumber() const
{
	return _json.getNumber();
}

const std::string& Json::getString() const
{
	return _json.getString();
}

const DjsonArray& Json::getArray() const
{
	return _json.getArray();
}

const DjsonObject& Json::getObject() const
{
	return _json.getObject();
}

size_t Json::getArraySize() const
{
	return _json.getArraySize();
}

const Json& Json::getArrayElement(size_t index) const
{
	return _json.getArrayElement(index);
}

const Value Json::getValue()
{
	return _json.getValue();
}


bool operator==(const Json& lhs, const Json& rhs) {
	if (lhs.getType() != rhs.getType())
		return false;
	switch (lhs.getType()) {
	case JsonType::kNull: return true;
	case JsonType::kNumber: return lhs.getNumber() == rhs.getNumber();
	case JsonType::kString: return lhs.getString() == rhs.getString();
	case JsonType::kArray: return lhs.getArray() == rhs.getArray();
	default:return lhs.getObject() == rhs.getObject();
	}
}

DJSON_NAMESPACE_END