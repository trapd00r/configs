require("notify").setup({
    -- background_colour = "NotifyBackground",
    -- fps = 30,
    icons = {
        DEBUG = "D",
        ERROR = "E",
        INFO = "I",
        TRACE = "T",
        WARN = "W"
    },
    level = 2,
    minimum_width = 50,
    render = "default",
    stages = "static",
    timeout = 5000,
    top_down = true

})