#ifndef _DJSON_VALUE_H__
#define _DJSON_VALUE_H__

#include "Common.h"

DJSON_NAMESPACE_START

class Json;

class Value
{
public:
	Value();
	virtual ~Value();
	Value(const Value &rhs);

	explicit Value(std::nullptr_t);
	explicit Value(bool b);
	explicit Value(int i);
	explicit Value(double d);
	explicit Value(const char* s);
	explicit Value(const std::string& s);
	explicit Value(const DjsonArray& a);
	explicit Value(const DjsonObject& o);

public:
	void init(const Value &rhs);
	void free();

	Value& operator=(const Value &rhs);
	const Json& operator[](const std::string&) const;
	Json& operator[](const std::string&);
	const Json& operator[](size_t index) const;
	Json& operator[](size_t index);

	void setArray(const DjsonArray &arr);
	const DjsonArray& getArray() const;
	void pushbackArrayElement(const Json& val);
	size_t getArraySize() const;
	const Json& getArrayElement(size_t index) const;
	void popBackArrayElement();
	void insertArrayElement(const Json &val, size_t index);
	void eraseArrayElement(size_t index, size_t count);
	void clearArray();

	void setObjectValue(const std::string &key, Json &val);
	void setObject(const DjsonObject &obj);
	void pushObject(const std::string &key, const Json &val);
	const DjsonObject& getObject() const;
	const size_t getObjectSize() const;
	const Json& getObjectValue(const std::string &key) const;
	void clearObject();

	void setType(JsonType t);
	const JsonType getType() const;

	void setNumber(double d);
	double getNumber() const;

	void setString(std::string &d);
	const std::string& getString() const;

	const Value getValue() const;

private:
	Djson::JsonType _type = Djson::JsonType::kNull;
	double _num;
	std::string _str;
	DjsonArray _array;
	DjsonObject _object;
	friend bool operator==(const Value &lhs, const Value &rhs);
};

DJSON_NAMESPACE_END

#endif
