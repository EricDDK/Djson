#include "Value.h"

DJSON_NAMESPACE_START

Value::Value()
	:_num(0)
{

}

Value::~Value()
{
	free();
}

Value::Value(const Value &rhs)
{
	init(rhs);
}

Value& Value::operator=(const Value &rhs)
{
	free();
	init(rhs);
	return *this;
}

void Value::setObject(const std::unordered_map<std::string, Djson::Value> &obj)
{
	if (_type == JsonType::Object)
		_object = obj;
	else
	{
		free();
		_type = JsonType::Object;
		_object = std::unordered_map<std::string, Djson::Value>(obj);
	}
}

const std::unordered_map<std::string, Djson::Value> Value::getObject() const
{
	assert(_type == JsonType::Object);
	return _object;
}

void Value::setArray(const std::vector<Value> &arr)
{
	if (_type == JsonType::Array)
		_array = arr;
	else
	{
		free();
		_type = JsonType::Array;
		_array = std::vector<Value>(arr);
	}
}

const std::vector<Value> Value::getArray() const
{
	assert(_type == JsonType::Array);
	return _array;
}

void Value::pushbackArrayElement(const Value& val)
{
	assert(_type == JsonType::Array);
	_array.push_back(val);
}

const Value& Value::getArrayElement(size_t index) const
{
	assert(_type == JsonType::Array);
	return _array[index];
}

size_t Value::getArraySize() const
{
	assert(_type == JsonType::Array);
	return _array.size();
}

void Value::popbackArrayElement()
{
	assert(_type == JsonType::Array);
	_array.pop_back();
}

void Value::insertArrayElement(const Value &val, size_t index)
{
	assert(_type == JsonType::Array);
	_array.insert(_array.begin() + index, val);
}

void Value::eraseArrayElement(size_t index, size_t count)
{
	assert(_type == JsonType::Array);
	_array.erase(_array.begin() + index, _array.begin() + index + count);
}

void Value::clearArray()
{
	assert(_type == JsonType::Array);
	_array.clear();
}

void Value::setObjectValue(const std::string &key, const Value &val)
{
	assert(_type == JsonType::Object);
	_object[key] = val;
}

const size_t Value::getObjectSize() const
{
	assert(_type == JsonType::Object);
	return _object.size();
}

const Value& Value::getObjectValue(const std::string &key) const
{
	assert(_type == JsonType::Object);
	if (_object.count(key))
		return _object.at(key);
	else
		throw;
}

void Value::clearObject()
{
	assert(_type == JsonType::Object);
	_object.clear();
}

void Value::init(const Value &rhs)
{
	_type = rhs._type;
	_num = 0;
	switch (_type)
	{
	case Djson::JsonType::Number:
		_num = rhs._num;
		break;
	case Djson::JsonType::String:
		_str = std::string(rhs._str);
		break;
	case Djson::JsonType::Array:
		_array = std::vector<Value>(rhs._array);
		break;
	case Djson::JsonType::Object:
		_object = std::unordered_map<std::string, Djson::Value>(rhs._object);
		break;
	default:
		break;
	}
}

void Value::free()
{
	using std::string;
	switch (_type)
	{
	case Djson::JsonType::String:
		//_str.~string();
		_str.clear();
		break;
	case Djson::JsonType::Array:
		//_array.~vector<Value>();
		_array.clear();
		break;
	case Djson::JsonType::Object:
		_object.clear();
		break;
	default:
		break;
	}
}

void Value::setType(JsonType t)
{
	free();
	_type = t;
}

const JsonType Value::getType() const
{
	return _type;
}

void Value::setNumber(double d)
{
	free();
	_num = d;
	_type = JsonType::Number;
}

double Value::getNumber() const
{
	assert(_type == JsonType::Number);
	return _num;
}

void Value::setString(std::string &s)
{
	if (_type == JsonType::String)
		_str = s;
	else
	{
		free();
		_str = s;
		_type = JsonType::String;
	}
}

const std::string& Value::getString() const
{
	assert(_type == JsonType::String);
	return _str;
}

const Value& Value::operator[](const std::string &key) const
{
	if (_object.count(key))
		return _object.at(key);
	throw;
}

Value& Value::operator[](const std::string &key)
{
	if (_object.count(key))
		return _object.at(key);
	throw;
}

bool operator==(const Value &lhs, const Value &rhs)
{
	if (lhs._type != rhs._type)
		return false;
	switch (rhs._type)
	{
	case Djson::JsonType::Null:
		return true;
	case Djson::JsonType::Number:
		return lhs._num == rhs._num;
	case Djson::JsonType::String:
		return lhs._str == rhs._str;
	case Djson::JsonType::Array:
		return lhs._array == rhs._array;
	case Djson::JsonType::Object:
		if (lhs.getObjectSize() != rhs.getObjectSize())
			return false;
		for (int i = 0; i < lhs.getObjectSize(); ++i)
		{

		}
	default:
		return lhs._num == rhs._num;
	}
	return true;
}

bool operator!=(const Value &lhs, const Value &rhs)
{
	return !(lhs == rhs);
}

DJSON_NAMESPACE_END
