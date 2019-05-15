#ifndef _DJSON_VALUE_H__
#define _DJSON_VALUE_H__

#include <string>
#include <vector>
#include <unordered_map>
#include "Common.h"
#include "Json.h"

DJSON_NAMESPACE_START

class Value
{
public:
	Value();
	virtual ~Value();
	Value(const Value &rhs);

	void init(const Value &rhs);
	void free();

	Value& operator=(const Value &rhs);

	void setArray(const DjsonArray &arr);
	const DjsonArray& getArray() const;
	void pushbackArrayElement(const Json& val);
	size_t getArraySize() const;
	const Json& getArrayElement(size_t index) const;
	void popbackArrayElement();
	void insertArrayElement(const Json &val, size_t index);
	void eraseArrayElement(size_t index, size_t count);
	void clearArray();

	void setObjectValue(const std::string &key, const Json &val);
	void setObject(const DjsonObject &obj);
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

	const Json& operator[](const std::string&) const;
	Json& operator[](const std::string&);
	const Json& operator[](size_t index) const;
	Json& operator[](size_t index);

	const Value getValue() { return *this; }
	//void parse(const std::string &content);

public:
	Value(std::nullptr_t) :_type(Djson::JsonType::kNull) {}
	Value(bool b) :_type(b ? Djson::JsonType::kTrue : Djson::JsonType::kFalse) {}
	Value(int i) :Value(1.0 * i) {}
	Value(double d) :_type(Djson::JsonType::kNumber), _num(d) {}
	Value(const char* s) :_type(Djson::JsonType::kString), _str(s) {}
	Value(const std::string& s) :_type(Djson::JsonType::kString), _str(s) {}
	Value(const DjsonArray& a) :_type(Djson::JsonType::kArray), _array(a) {}
	Value(const DjsonObject& o) :_type(Djson::JsonType::kObject), _object(o) {}

	/*Value(std::string&& s) :_type(Djson::JsonType::kString), _str(std::move(s)) {}
	Value(DjsonArray&& a) :_type(Djson::JsonType::kArray), _array(std::move(a)) {}
	Value(DjsonObject&& o) :_type(Djson::JsonType::kObject), _object(std::move(o)) {}*/

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
