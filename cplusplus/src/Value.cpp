#include "Value.h"

DJSON_NAMESPACE_START

Value::Value()
	//:_num(0)
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

void Value::setObject(const std::vector<std::pair<std::string, Value>> &obj)
{
	if (_type == JsonType::Object)
		_object = obj;
	else
	{
		free();
		_type = JsonType::Object;
		_object = std::vector<std::pair<std::string, Value>>(obj);
	}
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
	auto index = findObjectIndex(key);
	if (index > 0)
		_object[index].second = val;
	else
		_object.push_back(make_pair(key, val));
}

const size_t Value::getObjectSize() const
{
	assert(_type == JsonType::Object);
	return _object.size();
}

const std::string& Value::getObjectKey(size_t index) const
{
	assert(_type == JsonType::Object && index < _object.size());
	return _object[index].first;
}

const Value& Value::getObjectValue(size_t index) const
{
	assert(_type == JsonType::Object && index < _object.size());
	return _object[index].second;
}


long long Value::findObjectIndex(const std::string &key)
{
	assert(_type == JsonType::Object);
	for (int i = 0; i < _object.size(); ++i) {
		if (_object[i].first == key)
			return i;
	}
	return -1;
}

void Value::removeObjectValue(size_t index)
{
	assert(_type == JsonType::Object);
	_object.erase(_object.begin() + index, _object.begin() + index + 1);
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
	case Djson::JsonType::String:
		_str = std::string(rhs._str);
		break;
	case Djson::JsonType::Array:
		_array = std::vector<Value>(rhs._array);
		break;
	case Djson::JsonType::Object:
		_object = std::vector<std::pair<std::string, Value>>(rhs._object);
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
		_str.~string();
		break;
	case Djson::JsonType::Array:
		_array.~vector<Value>();
		break;
	case Djson::JsonType::Object:
		_object.~vector<std::pair<std::string, Value>>();
		break;
	default:
		break;
	}
}

void Value::setType(JsonType t)
{
	_type = t;
}

JsonType Value::getType() const
{
	return _type;
}

void Value::setNumber(double d)
{
	assert(_type == JsonType::Number);
	_num = d;
}

double Value::getNumber() const
{
	assert(_type == JsonType::Number);
	return _num;
}

void Value::setString(std::string &d)
{
	assert(_type == JsonType::String);
	_str = d;
}

const std::string& Value::getString() const
{
	assert(_type == JsonType::String);
	return _str;
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
