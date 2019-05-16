#include "Value.h"
#include "Json.h"

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

Value::Value(std::nullptr_t)
	:_type(Djson::JsonType::kNull) {}
Value::Value(bool b) 
	:_type(b ? Djson::JsonType::kTrue : Djson::JsonType::kFalse) {}
Value::Value(int i) 
	:Value(1.0 * i) {}
Value::Value(double d) 
	:_type(Djson::JsonType::kNumber), _num(d) {}
Value::Value(const char* s) 
	:_type(Djson::JsonType::kString), _str(s) {}
Value::Value(const std::string& s)
	:_type(Djson::JsonType::kString), _str(s) {}
Value::Value(const DjsonArray& a) 
	:_type(Djson::JsonType::kArray), _array(a) {}
Value::Value(const DjsonObject& o) 
	:_type(Djson::JsonType::kObject), _object(o) {}

void Value::init(const Value &rhs)
{
	_type = rhs._type;
	_num = 0;
	switch (_type)
	{
	case Djson::JsonType::kNumber:
		_num = rhs._num;
		break;
	case Djson::JsonType::kString:
		_str = std::string(rhs._str);
		break;
	case Djson::JsonType::kArray:
		_array = DjsonArray(rhs._array);
		break;
	case Djson::JsonType::kObject:
		_object = DjsonObject(rhs._object);
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
	case Djson::JsonType::kString:
		_str.clear();
		break;
	case Djson::JsonType::kArray:
		_array.clear();
		break;
	case Djson::JsonType::kObject:
		_object.clear();
		break;
	default:
		break;
	}
}


Value& Value::operator=(const Value &rhs)
{
	free();
	init(rhs);
	return *this;
}

const Json& Value::operator[](const std::string &key) const
{
	assert(_type == JsonType::kObject);
	if (_object.count(key))
		return _object.at(key);
	throw;
}

Json& Value::operator[](const std::string &key)
{
	assert(_type == JsonType::kObject);
	if (_object.count(key))
		return _object.at(key);
	throw;
}

const Json& Value::operator[](size_t index) const
{
	assert(_type == JsonType::kArray);
	assert(_array.size() > index);
	return _array[index];
}

Json& Value::operator[](size_t index)
{
	assert(_type == JsonType::kArray);
	assert(_array.size() > index);
	return _array[index];
}

void Value::setObject(const DjsonObject &obj)
{
	if (_type == JsonType::kObject)
		_object = obj;
	else
	{
		free();
		_type = JsonType::kObject;
		_object = DjsonObject(obj);
	}
}

void Value::pushObject(const std::string &key, const Json &val)
{
	if (_type == JsonType::kObject)
		_object.insert(_object.end(), { key, val });
}

const DjsonObject& Value::getObject() const
{
	assert(_type == JsonType::kObject);
	return _object;
}

void Value::setArray(const DjsonArray &arr)
{
	if (_type == JsonType::kArray)
		_array = arr;
	else
	{
		free();
		_type = JsonType::kArray;
		_array = DjsonArray(arr);
	}
}

const DjsonArray& Value::getArray() const
{
	assert(_type == JsonType::kArray);
	return _array;
}

void Value::pushbackArrayElement(const Json& val)
{
	assert(_type == JsonType::kArray);
	_array.push_back(val);
}

const Json& Value::getArrayElement(size_t index) const
{
	assert(_type == JsonType::kArray);
	return _array[index];
}

size_t Value::getArraySize() const
{
	assert(_type == JsonType::kArray);
	return _array.size();
}

void Value::popBackArrayElement()
{
	assert(_type == JsonType::kArray);
	_array.pop_back();
}

void Value::insertArrayElement(const Json &val, size_t index)
{
	assert(_type == JsonType::kArray);
	_array.insert(_array.begin() + index, val);
}

void Value::eraseArrayElement(size_t index, size_t count)
{
	assert(_type == JsonType::kArray);
	_array.erase(_array.begin() + index, _array.begin() + index + count);
}

void Value::clearArray()
{
	assert(_type == JsonType::kArray);
	_array.clear();
}

void Value::setObjectValue(const std::string &key, Json &val)
{
	assert(_type == JsonType::kObject);
	_object[key] = val;
}

const size_t Value::getObjectSize() const
{
	assert(_type == JsonType::kObject);
	return _object.size();
}

const Json& Value::getObjectValue(const std::string &key) const
{
	assert(_type == JsonType::kObject);
	if (_object.count(key))
		return _object.at(key);
	else
		throw;
}

void Value::clearObject()
{
	assert(_type == JsonType::kObject);
	_object.clear();
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
	_type = JsonType::kNumber;
}

double Value::getNumber() const
{
	assert(_type == JsonType::kNumber);
	return _num;
}

void Value::setString(std::string &s)
{
	if (_type == JsonType::kString)
		_str = s;
	else
	{
		free();
		_str = s;
		_type = JsonType::kString;
	}
}

const std::string& Value::getString() const
{
	assert(_type == JsonType::kString);
	return _str;
}

const Value Value::getValue() const 
{ 
	return *this; 
}

bool operator==(const Value &lhs, const Value &rhs)
{
	if (lhs._type != rhs._type)
		return false;
	switch (rhs._type)
	{
	case Djson::JsonType::kNull:
		return true;
	case Djson::JsonType::kNumber:
		return lhs._num == rhs._num;
	case Djson::JsonType::kString:
		return lhs._str == rhs._str;
	case Djson::JsonType::kArray:
		return lhs._array == rhs._array;
	case Djson::JsonType::kObject:
		if (lhs.getObjectSize() != rhs.getObjectSize())
			return false;
		return lhs._object == rhs._object;
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
