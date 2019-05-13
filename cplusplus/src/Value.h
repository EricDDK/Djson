#ifndef _DJSON_VALUE_H__
#define _DJSON_VALUE_H__

#include <string>
#include <vector>
#include <unordered_map>
#include "Common.h"
//#include "Parser.h"

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

	void setArray(const std::vector<Value> &arr);
	const std::vector<Value> getArray() const;
	void pushbackArrayElement(const Value& val);
	size_t getArraySize() const;
	const Value& getArrayElement(size_t index) const;
	void popbackArrayElement();
	void insertArrayElement(const Value &val, size_t index);
	void eraseArrayElement(size_t index, size_t count);
	void clearArray();

	void setObjectValue(const std::string &key, const Value &val);
	void setObject(const std::unordered_map<std::string, Djson::Value> &obj);
	const std::unordered_map<std::string, Djson::Value> getObject() const;
	const size_t getObjectSize() const;
	const Value& getObjectValue(const std::string &key) const;
	void clearObject();

	void setType(JsonType t);
	const JsonType getType() const;

	void setNumber(double d);
	double getNumber() const;

	void setString(std::string &d);
	const std::string& getString() const;

	const Value& operator[](const std::string&) const;
	Value& operator[](const std::string&);

	Value getValue() { return *this; }
	//void parse(const std::string &content);

public:
	Value(std::nullptr_t) :_type(Djson::JsonType::Null) {}
	Value(bool b) :_type(b ? Djson::JsonType::True : Djson::JsonType::False) {}
	Value(int i) :Value(1.0 * i) {}
	Value(double d) :_type(Djson::JsonType::Number), _num(d) {}
	Value(const char* s) :_type(Djson::JsonType::String), _str(s) {}
	Value(const std::string& s) :_type(Djson::JsonType::String), _str(s) {}
	Value(const std::vector<Djson::Value>& a) :_type(Djson::JsonType::Array), _array(a) {}
	Value(const std::unordered_map<std::string, Djson::Value>& o) :_type(Djson::JsonType::Object), _object(o) {}

	Value(std::string&& s) :_type(Djson::JsonType::String), _str(std::move(s)) {}
	Value(std::vector<Djson::Value>&& a) :_type(Djson::JsonType::Array), _array(std::move(a)) {}
	Value(std::unordered_map<std::string, Djson::Value>&& o) :_type(Djson::JsonType::Object), _object(std::move(o)) {}

private:
	Djson::JsonType _type = Djson::JsonType::Null;
	double _num;
	std::string _str;
	std::vector<Djson::Value> _array;
	std::unordered_map<std::string, Djson::Value> _object;
	friend bool operator==(const Value &lhs, const Value &rhs);
};

DJSON_NAMESPACE_END

#endif
