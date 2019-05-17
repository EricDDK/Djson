# Djson
a light weight json serialization library used lua/c++
<p align="left">
    <a href="https://isocpp.org/">
        <img src="https://img.shields.io/badge/language-C%2B%2B11-blue.svg">
    </a>
    <a href="https://www.lua.org/">
        <img src="https://img.shields.io/badge/language-lua%205.1-red.svg">
    </a>
    <a href="https://travis-ci.org/felixguendling/cista">
        <img src="https://travis-ci.org/felixguendling/cista.svg?branch=master">
    </a>
    <a href="https://coveralls.io/github/felixguendling/cista?branch=master">
        <img src="https://s3.amazonaws.com/assets.coveralls.io/badges/coveralls_80.svg">
    </a>
    <a href="https://opensource.org/licenses/MIT" >
        <img src="https://img.shields.io/apm/l/vim-mode.svg">
    </a>
</p>

# Djson-c++:
## parse
```
std::string str = "{\"key1\":\"Value\",\"key2\":false,\"key3\":[0,1,2,3,4]}";
Djson::Json j;
Json v = j.parse(str);
```

## generate
```
Djson::Json j1(nullptr);
Djson::Json j2(1.0);
Djson::Json j3("test");
Djson::Json j4();
Djson::Json j5 = DjsonArray{ 0,1,2,3,4 };
Djson::Json j6 = DjsonObject{
  { "key1", "Value" },
  { "key2", false },
  { "key3", DjsonArray{ 0,1,2,3,4 } }
};
Djson::Json j7 = DjsonObject{
  { "key1", j6 }
};
```

## create & add
```
Djson::Json j2 = DjsonArray{ 1,1,1,1,1,1,1,1 };
j2.add(-500);
```
```
Djson::Json j3 = DjsonObject{
  { "key1", j1 }
};
j3.add("key2", j2);
j3.add("key3", 55000);
```

## compare
```
Djson::Json j1 = DjsonObject{
  { "key1", "Value" },
  { "key2", 3.15 },
  { "key3", DjsonArray{ 0,1,2,3 } }
};
Djson::Json j2 = Djson::Json(j1);
if (j1 == j2)
{
  // Todo
}
```
## -------------------------------------------------------------------

# Djson-lua:
require("json")
```
local str = "{\"code\":1,\"func\":{\"code\":2},\"code2\":2,\"data\":\"sssss\",\"code1\":1}"
local data = json.decode(str)  -- parse
str = json.encode(data)  -- generate
```

# Test:
* Djson-c++: 230 seconds 
* Djson-lua: 3600 secends 
* cjson: 160 seconds 

