#ifndef _DJSON_COMMON_H__
#define _DJSON_COMMON_H__

#include <assert.h>
#include <string.h>
#include <vector>

#define DJSON_NAMESPACE_START namespace Djson {
#define DJSON_NAMESPACE_END }
#define DJSON_NAMESPACE_USE using namespace Djson ;

DJSON_NAMESPACE_START

	enum class JsonType : int
	{
		Null,
		True,
		False,
		Number,
		String,
		Array,
		Object
	};

DJSON_NAMESPACE_END



#endif
