#ifndef _DJSON_VALUE_H__
#define _DJSON_VALUE_H__

#include <string>
#include <vector>
#include <unordered_map>
#include "Common.h"

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
	void pushbackArrayElement(const Value& val);
	size_t getArraySize() const;
	const Value& getArrayElement(size_t index) const;
	void popbackArrayElement();
	void insertArrayElement(const Value &val, size_t index);
	void eraseArrayElement(size_t index, size_t count);
	void clearArray();

	void setObjectValue(const std::string &key, const Value &val);
	void setObject(const std::unordered_map<std::string, Djson::Value> &obj);
	const std::unordered_map<std::string, Djson::Value> getObject() const { return _object; }
	const size_t getObjectSize() const;
	const Value& getObjectValue(const std::string &key) const;
	void clearObject();

	void setType(JsonType t);
	JsonType getType() const;

	void setNumber(double d);
	double getNumber() const;

	void setString(std::string &d);
	const std::string& getString() const;

	const Value& operator[](const std::string&) const;
	Value& operator[](const std::string&);

private:
	Djson::JsonType _type = Djson::JsonType::Null;
	union
	{
		double _num;
		std::string _str;
		std::vector<Djson::Value> _array;
		//std::vector<std::pair<std::string, Djson::Value>> _object;
		std::unordered_map<std::string, Djson::Value> _object;
	};
	friend bool operator==(const Value &lhs, const Value &rhs);
};

DJSON_NAMESPACE_END

#endif
