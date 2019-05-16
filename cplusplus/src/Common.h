#ifndef _DJSON_COMMON_H__
#define _DJSON_COMMON_H__

#include <assert.h>
#include <string>
#include <vector>
#include <unordered_map>

#define DJSON_NAMESPACE_START namespace Djson {
#define DJSON_NAMESPACE_END }
#define DJSON_NAMESPACE_USE using namespace Djson ;

#define DjsonArray std::vector<Djson::Json>
#define DjsonObject std::unordered_map<std::string, Djson::Json>

DJSON_NAMESPACE_START

enum class JsonType
{
	kNull,
	kTrue,
	kFalse,
	kNumber,
	kString,
	kArray,
	kObject
};

DJSON_NAMESPACE_END

#endif
