#ifndef _DJSON_JSON_H__
#define _DJSON_JSON_H__

#include "Common.h"
#include "Value.h"
#include "Parser.h"
#include "Generator.h"
#include <memory>

DJSON_NAMESPACE_START

class Json
{
public:
	

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
	Json(std::string&& s);
	Json(const DjsonArray& a);
	Json(DjsonArray&& a);
	Json(const DjsonObject& o);
	Json(DjsonObject&& o);

	Json(void *) = delete;

public:
	const std::string generate();
	const Value parse(const std::string& content);

public:
	void setType(JsonType type) { _json.setType(type); }
	const JsonType getType() const { return _json.getType(); }

	bool getBool() const { assert(_json.getType() == JsonType::kFalse || _json.getType() == JsonType::kTrue); return _json.getType() == JsonType::kTrue ? true : false; }
	double getNumber() const { return _json.getNumber(); }
	const std::string& getString() const { return _json.getString(); }
	const DjsonArray getArray() const { return _json.getArray(); }
	const DjsonObject getObject() const { return _json.getObject(); }
	
	Value getValue() { return _json.getValue(); }

private:
	Djson::Value _json;

};

DJSON_NAMESPACE_END

#endif
