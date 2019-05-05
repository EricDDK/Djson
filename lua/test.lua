--[[
    
    Author: Eric.Ding
]]

local function testEncode()
    local o = {
        code = 1,
        data = "sssss",
        func = {
            code = 2,
            data = nil
        }
    }
    local str = json.encode(o)
    print("testEncode => ", str)
end

local function testDecode()
    local str = "{\"code\":1,\"data\":\"sssss\"}"
    local o = json.decode(str)
    print("testDecode 1 => ", o.code, o.data)

    str = "{\"code\":1,\"func\":{\"code\":2},\"code2\":2,\"data\":\"sssss\",\"code1\":1}"
    o = json.decode(str)
    print("testDecode 2 => ", o.code, o.data, o.func.code)
end

local function test()
    testEncode()
    testDecode()
end

test()