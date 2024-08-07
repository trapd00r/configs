-- snippets for dumping data structures in various languages
local ls = require("luasnip")
local snip = ls.snippet
local insert = ls.insert_node
local func = ls.function_node

local dumps = {
    php = function() return { '\\dahbug::dump(' } end,
    perl = function() return { 'print Dumper(' } end,
}

local dump_conditional = function()
    local filetype = vim.bo.filetype
    local dump_func = dumps[filetype]
    if dump_func then
        return dump_func()
    else
        return {} -- default case, if needed
    end
end

ls.add_snippets(nil, {
    all = {
        snip({
            trig = "dd",
            namr = "Dumper",
            dscr = "Conditional dump based on filetype",
        }, {
            func(dump_conditional, {}),
            insert(0), -- Insertion point after the function
        }),
    },
    -- You can add additional snippets for other filetypes or contexts here
})
