# Djson
a light weight json serialization library used lua/c++

# Djson-c++:
## parse
```
std::string str = "{\"key1\":\"Value\",\"key2\":false,\"key3\":[0,1,2,3,4]}";
Djson::Json j;
Value v = j.parse(str);
```

## generate
```
Djson::Json j1(nullptr);
Djson::Json j2(1.0);
Djson::Json j3("test");
Djson::Json j4();
Djson::Json j5 = Djson::Json::Array{ 0,1,2,3,4 };
Djson::Json j6 = Djson::Json::Object{
  { "key1", "Value" },
  { "key2", false },
  { "key3", Djson::Json::Array{ 0,1,2,3,4 } }
};
Djson::Json j7 = Djson::Json::Object{
  { "key1", j6.getValue() }
};
```

# Djson-lua:
require("json")
```
local str = "{\"code\":1,\"func\":{\"code\":2},\"code2\":2,\"data\":\"sssss\",\"code1\":1}"
local data = json.decode(str)  -- parse
str = json.encode(data)  -- generate
```

# Test:
Djson-c++: 230 seconds
Djson-lua: 3600 secends
cjson: 160 seconds

