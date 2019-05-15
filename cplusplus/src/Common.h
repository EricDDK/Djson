#ifndef _DJSON_COMMON_H__
#define _DJSON_COMMON_H__

#include <assert.h>
#include <string.h>
#include <vector>

#define DJSON_NAMESPACE_START namespace Djson {
#define DJSON_NAMESPACE_END }
#define DJSON_NAMESPACE_USE using namespace Djson ;

DJSON_NAMESPACE_START

#define DjsonArray std::vector<Djson::Value>
#define DjsonObject std::unordered_map<std::string, Djson::Value>

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
