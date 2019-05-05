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

function json.decode(str)
    
end