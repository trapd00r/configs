local ls = require("luasnip")
-- some shorthands...
local snip = ls.snippet
local node = ls.snippet_node
local text = ls.text_node
local insert = ls.insert_node
local func = ls.function_node
local choice = ls.choice_node
local dynamicn = ls.dynamic_node

local date = function() return { os.date('%Y-%m-%d') } end
local time = function() return { os.date('%H:%M:%S') } end
local date_time = function() return { os.date('%Y-%m-%d %H:%M:%S') } end

ls.add_snippets(nil, {
    all = {
        snip({
            trig = "date",
            namr = "Date",
            dscr = "Date in the form of YYYY-MM-DD",
        }, {
            func(date, {}),
        }),
        snip({
            trig = "time",
            namr = "Time",
            dscr = "Time in the form of HH:MM:SS",
        }, {
            func(time, {}),
        }),
        snip({
            trig = "xnow",
            namr = "Date and Time",
            dscr = "Date and Time in the form of YYYY-MM-DD HH:MM:SS",
        }, {
            func(date_time, {}),
        }),
    },
})

