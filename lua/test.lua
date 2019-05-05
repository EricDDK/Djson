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
    
end

local function test()
    testEncode()
    testDecode()
end

test()