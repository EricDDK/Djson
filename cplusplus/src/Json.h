#ifndef _DJSON_JSON_H__
#define _DJSON_JSON_H__

#include "Common.h"
#include "Value.h"

DJSON_NAMESPACE_START

class Json
{
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
	//Json(std::string&& s);
	Json(const DjsonArray& a);
	//Json(DjsonArray&& a);
	Json(const DjsonObject& o);
	//Json(DjsonObject&& o);

	Json(void *) = delete;

	const Json& operator[](const std::string& s) const { return _json.operator[](s); }
	const Json& operator[](size_t index) const { return _json.operator[](index); }
	Json& operator[](const std::string& s) { return _json.operator[](s); }
	Json& operator[](size_t index) { return _json.operator[](index); }

public:
	const std::string generate();
	const Json& parse(const std::string& content);

public:
	void setType(JsonType type) { _json.setType(type); }
	const JsonType getType() const { return _json.getType(); }

	void setNumber(double d) { _json.setNumber(d); }
	void setString(std::string &s) { _json.setString(s); }
	void setArray(const DjsonArray &arr) { _json.setArray(arr); }
	void setObject(const DjsonObject &obj) { _json.setObject(obj); }

	bool getBool() const { assert(_json.getType() == JsonType::kFalse || _json.getType() == JsonType::kTrue); return _json.getType() == JsonType::kTrue ? true : false; }
	double getNumber() const { return _json.getNumber(); }
	const std::string& getString() const { return _json.getString(); }
	const DjsonArray& getArray() const { return _json.getArray(); }
	const DjsonObject& getObject() const { return _json.getObject(); }

	size_t getArraySize() const { return _json.getArraySize(); }
	const Json& getArrayElement(size_t index) const { return _json.getArrayElement(index); }
	
	const Value getValue() { return _json.getValue(); }

private:
	Value _json;

};

bool operator==(const Json&, const Json&);
inline bool operator!=(const Json& lhs, const Json& rhs) { return !(lhs == rhs); }

DJSON_NAMESPACE_END

#endif
