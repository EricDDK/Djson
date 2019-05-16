#ifndef _DJSON_JSON_H__
#define _DJSON_JSON_H__

#include "Common.h"
#include "Value.h"

DJSON_NAMESPACE_START

class Json
{
public:
	const std::string generate();
	const Json& parse(const std::string& content);
	
public:
	template<typename T>
	void add(const std::string& key, const T& t)
	{
		assert(getType() == JsonType::kObject);
		_json.pushObject(key, Json(t));
	}

	template<typename T>
	void add(const T& t)
	{
		assert(getType() == JsonType::kArray);
		_json.pushbackArrayElement(Json(t));
	}

public:
	Json() :Json(nullptr) {};
	~Json() {}
	Json(const Json& j);
	Json& operator=(const Json& j);

	// ctor for the various types of JSON value
	Json(std::nullptr_t);
	Json(bool b);
	Json(int i);
	Json(double d);
	Json(const char* c);
	Json(const std::string& s);
	Json(const DjsonArray& a);
	Json(const DjsonObject& o);

	Json(void *) = delete;

	const Json& operator[](const std::string& s) const;
	const Json& operator[](size_t index) const;
	Json& operator[](const std::string& s);
	Json& operator[](size_t index);

public:
	void setType(JsonType type);
	const JsonType getType() const;

	void setNumber(double d);
	void setString(std::string &s);
	void setArray(const DjsonArray &arr);
	void setObject(const DjsonObject &obj);

	bool getBool() const; 
	double getNumber() const;
	const std::string& getString() const;
	const DjsonArray& getArray() const;
	const DjsonObject& getObject() const;

	size_t getArraySize() const;
	const Json& getArrayElement(size_t index) const;

	const Value getValue();

private:
	Value _json;

};

bool operator==(const Json&, const Json&);
inline bool operator!=(const Json& lhs, const Json& rhs) { return !(lhs == rhs); }

DJSON_NAMESPACE_END

#endif
