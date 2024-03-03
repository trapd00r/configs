-- Configuration for plugins
-- Plugin: gitsigns.nvim
require('gitsigns').setup {
  signs = {
    add          = { text = '│' },
    change       = { text = '│' },
    delete       = { text = '_' },
    topdelete    = { text = '‾' },
    changedelete = { text = '~' },
    untracked    = { text = '┆' },
  },
  signcolumn = false,  -- Toggle with `:Gitsigns toggle_signs`
  numhl      = false, -- Toggle with `:Gitsigns toggle_numhl`
  linehl     = false, -- Toggle with `:Gitsigns toggle_linehl`
  word_diff  = false, -- Toggle with `:Gitsigns toggle_word_diff`
  watch_gitdir = {
    follow_files = true
  },
  auto_attach = true,
  attach_to_untracked = false,
  current_line_blame = true, -- Toggle with `:Gitsigns toggle_current_line_blame`
  current_line_blame_opts = {
    virt_text = true,
    virt_text_pos = 'eol', -- 'eol' | 'overlay' | 'right_align'
    delay = 1000,
    ignore_whitespace = false,
    virt_text_priority = 100,
  },
  current_line_blame_formatter = '<author>, <author_time:%Y-%m-%d> - <summary>',
  sign_priority = 6,
  update_debounce = 100,
  status_formatter = nil, -- Use default
  max_file_length = 40000, -- Disable if file is longer than this (in lines)
  preview_config = {
    -- Options passed to nvim_open_win
    border = 'single',
    style = 'minimal',
    relative = 'cursor',
    row = 0,
    col = 1
  },
  yadm = {
    enable = false
  },
}

-- Plugin: lualine

local function FileLsColored()
  -- Get the current file name
  local filename = vim.fn.expand('%:t')
  local extension = vim.fn.expand('%:e')

  HLgroup = '%#LsColorLuaLine#'
  -- Define colors based on file extension
  if extension == 'sh' then
    vim.cmd('highlight LsColorLuaLine ctermfg=172 ctermbg=232 cterm=none')
  elseif extension == 'lua' then
    vim.cmd('highlight LsColorLuaLine ctermfg=81 guifg=Blue')
  elseif extension == 'vim' then
    vim.cmd('highlight LsColorLuaLine ctermfg=106 ctermbg=232 cterm=none')
  elseif extension == 'txt' then
    vim.cmd('highlight LsColorLuaLine ctermfg=188 ctermbg=232 cterm=none')
  elseif extension == 'css' or extension == 'sass' then
    vim.cmd('highlight LsColorLuaLine ctermfg=125 ctermbg=232 cterm=none')
  elseif extension == 'csv' then
    vim.cmd('highlight LsColorLuaLine ctermfg=078 ctermbg=232 cterm=none')
  elseif extension == 'js' or extension == 'jsp' then
    vim.cmd('highlight LsColorLuaLine ctermfg=074 ctermbg=232 cterm=none')
  elseif extension == 'json' then
    vim.cmd('highlight LsColorLuaLine ctermfg=178 ctermbg=232 cterm=none')
  elseif extension == 'log' then
    vim.cmd('highlight LsColorLuaLine ctermfg=190 ctermbg=232 cterm=none')
  elseif extension == 'markdown' or extension == 'md' then
    vim.cmd('highlight LsColorLuaLine ctermfg=190 ctermbg=232 cterm=bold')
  elseif extension == 'README' or extension == 'CHANGES' then
    vim.cmd('highlight LsColorLuaLine ctermfg=190 ctermbg=232 cterm=bold')
  elseif extension == 'php' then
    vim.cmd('highlight LsColorLuaLine ctermfg=081 ctermbg=232 cterm=none')
  elseif extension == 'Makefile' or string.match(extension, '^Makefile%.PL?$') then
    vim.cmd('highlight LsColorLuaLine ctermfg=196 ctermbg=232 cterm=none')
  elseif extension == 'pl' then
    vim.cmd('highlight LsColorLuaLine ctermfg=208 ctermbg=232 cterm=none')
  elseif extension == 'pm' then
    vim.cmd('highlight LsColorLuaLine ctermfg=203 ctermbg=232 cterm=none')
  elseif extension == 'sql' or extension == 'sqlite' then
    vim.cmd('highlight LsColorLuaLine ctermfg=222 ctermbg=232 cterm=none')
  elseif extension == 't' then
    vim.cmd('highlight LsColorLuaLine ctermfg=114 ctermbg=232 cterm=none')
  elseif extension == 'tt' then
    vim.cmd('highlight LsColorLuaLine ctermfg=173 ctermbg=232 cterm=none')
  elseif string.match(extension, 'html?$') then
    vim.cmd('highlight LsColorLuaLine ctermfg=132 ctermbg=232 cterm=none')
  elseif string.match(extension, 'php?$') then
    vim.cmd('highlight LsColorLuaLine ctermfg=081 ctermbg=232 cterm=none')
  else
    HLgroup = '%#Normal#' -- Set to Normal highlight group for other extensions
  end



  -- Return the colored filename
  return HLgroup .. filename .. '%#Normal#'
end


require('lualine').setup {
  options = {
    icons_enabled = false,
    theme = 'ayu_dark',
    component_separators = { left = '>', right = '<'},
    section_separators = { left = ' ', right = ' '},  
    disabled_filetypes = {
      statusline = {},
      winbar = {},
    },
    ignore_focus = {},
    always_divide_middle = true,
    globalstatus = false,
    refresh = {
      statusline = 1000,
      tabline = 1000,
      winbar = 1000,
    }
  },
  sections = {
    lualine_a = {'mode'},
    lualine_b = {FileLsColored},
--    lualine_a = {'searchcount'},
--    lualine_a = {'FileNameStatusLine'},
--    lualine_a = {'filename'},
    lualine_c = {'branch', 'diff', 'diagnostics'},
--    lualine_c = {'filename'},
 --   lualine_c = {'FileNameStatusLine'},
    lualine_x = {'encoding', 'fileformat', 'filetype'},
    lualine_y = {'progress'},
    lualine_z = {'searchcount'}
  },
  inactive_sections = {
    lualine_a = {},
    lualine_b = {},
    lualine_c = {'filename'},
    lualine_x = {'location'},
    lualine_y = {},
    lualine_z = {}
  },
  tabline = {},
  winbar = {},
  inactive_winbar = {},
  extensions = {}
}


-- Plugin: dressing.nvim
require("dressing").setup({
  input = {
    -- Set to false to disable the vim.ui.input implementation
    enabled = true,

    -- Default prompt string
    default_prompt = "Input",

    -- Trim trailing `:` from prompt
    trim_prompt = true,

    -- Can be 'left', 'right', or 'center'
    title_pos = "left",

    -- When true, <Esc> will close the modal
    insert_only = true,

    -- When true, input will start in insert mode.
    start_in_insert = true,

    -- These are passed to nvim_open_win
    border = "rounded",
    -- 'editor' and 'win' will default to being centered
    relative = "cursor",

    -- These can be integers or a float between 0 and 1 (e.g. 0.4 for 40%)
    prefer_width = 40,
    width = nil,
    -- min_width and max_width can be a list of mixed types.
    -- min_width = {20, 0.2} means "the greater of 20 columns or 20% of total"
    max_width = { 140, 0.9 },
    min_width = { 20, 0.2 },

    buf_options = {},
    win_options = {
      -- Disable line wrapping
      wrap = false,
      -- Indicator for when text exceeds window
      list = true,
      listchars = "precedes:…,extends:…",
      -- Increase this for more context when text scrolls off the window
      sidescrolloff = 0,
    },

    -- Set to `false` to disable
    mappings = {
      n = {
        ["<Esc>"] = "Close",
        ["<CR>"] = "Confirm",
      },
      i = {
        ["<C-c>"] = "Close",
        ["<CR>"] = "Confirm",
        ["<Up>"] = "HistoryPrev",
        ["<Down>"] = "HistoryNext",
      },
    },

    override = function(conf)
      -- This is the config that will be passed to nvim_open_win.
      -- Change values here to customize the layout
      return conf
    end,

    -- see :help dressing_get_config
    get_config = nil,
  },
  select = {
    -- Set to false to disable the vim.ui.select implementation
    enabled = true,

    -- Priority list of preferred vim.select implementations
    backend = { "telescope", "fzf_lua", "fzf", "builtin", "nui" },

    -- Trim trailing `:` from prompt
    trim_prompt = true,

    -- Options for telescope selector
    -- These are passed into the telescope picker directly. Can be used like:
    -- telescope = require('telescope.themes').get_ivy({...})
    telescope = nil,

    -- Options for fzf selector
    fzf = {
      window = {
        width = 0.5,
        height = 0.4,
      },
    },

    -- Options for fzf-lua
    fzf_lua = {
      -- winopts = {
      --   height = 0.5,
      --   width = 0.5,
      -- },
    },

    -- Options for nui Menu
    nui = {
      position = "50%",
      size = nil,
      relative = "editor",
      border = {
        style = "rounded",
      },
      buf_options = {
        swapfile = false,
        filetype = "DressingSelect",
      },
      win_options = {
        winblend = 0,
      },
      max_width = 80,
      max_height = 40,
      min_width = 40,
      min_height = 10,
    },

    -- Options for built-in selector
    builtin = {
      -- Display numbers for options and set up keymaps
      show_numbers = true,
      -- These are passed to nvim_open_win
      border = "rounded",
      -- 'editor' and 'win' will default to being centered
      relative = "editor",

      buf_options = {},
      win_options = {
        cursorline = true,
        cursorlineopt = "both",
      },

      -- These can be integers or a float between 0 and 1 (e.g. 0.4 for 40%)
      -- the min_ and max_ options can be a list of mixed types.
      -- max_width = {140, 0.8} means "the lesser of 140 columns or 80% of total"
      width = nil,
      max_width = { 140, 0.8 },
      min_width = { 40, 0.2 },
      height = nil,
      max_height = 0.9,
      min_height = { 10, 0.2 },

      -- Set to `false` to disable
      mappings = {
        ["<Esc>"] = "Close",
        ["<C-c>"] = "Close",
        ["<CR>"] = "Confirm",
      },

      override = function(conf)
        -- This is the config that will be passed to nvim_open_win.
        -- Change values here to customize the layout
        return conf
      end,
    },

    -- Used to override format_item. See :help dressing-format
    format_item_override = {},

    -- see :help dressing_get_config
    get_config = nil,
  },
})
