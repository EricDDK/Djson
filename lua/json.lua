--[[
    
    Author: Eric.Ding
]]

json = json or {}

local _encodeMap = {
    ["nil"] = function(object)
        return "null"
    end,
    ["string"] = function(object)
        return '"' .. object .. '"'
    end,
    ["number"] = function(object)
        return tostring(object)
    end,
    ["boolean"] = function(object)
        return tostring(object)
    end,
    ["function"] = function(object)
        return "null"
    end,
}

local function isArray(t)
    local maxIndex = 0
    for k,v in pairs(t) do
        if type(k) == "number" and math.floor(k)==k and 1<=k then
            maxIndex = math.max(k, maxIndex)
        else
            return false
        end
    end
    return true, maxIndex
end

--[[
    encode the json object
    @param: object: lua object
    @return: json: string
]]
function json.encode(object)
    if object == nil then
        return "null"
    end
    
    local objectType
    objectType = type(object)

    if _encodeMap[objectType] then
        return _encodeMap[objectType](object)
    else
        if objectType == "table" then
            local t = {}
            local bArray, maxCount = isArray(object)
            if bArray then
                for i=1,maxCount do
                    table.insert(t, json.encode(object[i]))
                end
            else
                for k,v in pairs(object) do
                    table.insert(t, '"' .. tostring(k) .. '":' .. json.encode(v))
                end
            end
            if bArray then
                return '[' .. table.concat(t, ',') .. ']'
            else
                return '{' .. table.concat(t, ',') .. '}'
            end
        end
    end
end

local _whiteSpaceChars = " \n\r\t"
local _numberChars = "+-0123456789.e"
local _otherChars = {
    ["true"] = true,
    ["false"] = false,
    ["null"] = nil
}
local _otherNames = {"true","false","null"}

local function scanWhiteSpace(str, startPos)
    local len = string.len(str)
    while string.find(_whiteSpaceChars, string.sub(str, startPos, startPos), 1, true) and startPos <= len do
        startPos = startPos + 1
    end
    return startPos
end

local function decodeNumber(str, startPos)
    local endPos = startPos + 1
    local len = string.len(str)
    while string.find(_numberChars, string.sub(str, endPos, endPos), 1, true) and endPos <= len do
        endPos = endPos + 1
    end
    local stringCommand = load("return " .. string.sub(str,startPos, endPos - 1))
    return stringCommand(), endPos
end

local function decodeString(str, startPos)
    local startChar = string.sub(str, startPos, startPos)
    local endPos = startPos + 1
    local len = string.len(str)
    local isEnd = false
    repeat
        local curChar = string.sub(str, endPos, endPos)
        isEnd = curChar == startChar
        endPos = endPos + 1
    until isEnd
    local stringCommand = load("return " .. string.sub(str,startPos, endPos - 1))
    return stringCommand(), endPos
end

local function decodeArray(str, startPos)
    local array = {}	-- The return array
    local len = string.len(str)
    startPos = startPos + 1
    while true do
        local curChar = string.sub(str, startPos, startPos)
        if curChar == ']' then
            return array, startPos + 1
        end
        if curChar == ',' then
            startPos = startPos + 1
        end
        local object = json.decode(str, startPos)
        table.insert(array,object)
    end
end

local function decodeObject(str, startPos)
    local object = {}
    local len = string.len(str)
    local key, value
    startPos = startPos + 1
    while true do
        local curChar = string.sub(str, startPos, startPos)
        if curChar == '}' then
            return object, startPos + 1
        end
        if curChar == ',' then
            startPos = startPos + 1
        end
        key, startPos = json.decode(str, startPos)
        startPos = startPos + 1
        value, startPos = json.decode(str, startPos)
        object[key]=value
    end
end

local function decodeOther(str, startPos)
    for k,v in pairs(_otherNames) do
        if string.sub(str, startPos, startPos + string.len(v) -1 ) == v then
            return _otherChars[v], startPos + string.len(v)
        end
    end
end

function json.decode(str, pos)
    pos = pos or 1
    local cur = string.sub(str, pos, pos)
    -- number
    if string.find(_numberChars, cur, 1, true) then
        return decodeNumber(str, pos)
    end
    -- string
    if cur == '"' or cur == [[']] then
        return decodeString(str, pos)
    end
    -- object
    if cur == '{' then
        return decodeObject(str, pos)
    end
    -- table
    if cur == '[' then
        return decodeArray(str, pos)
    end
    return decodeOther(str, pos)
end