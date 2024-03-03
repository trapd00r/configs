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

-- Plugin: winbar
require('winbar').setup({
    enabled = true,

    show_file_path = true,
    show_symbols = true,

    colors = {
        path = '', -- You can customize colors like #c946fd
        file_name = '',
        symbols = '',
    },

    icons = {
        file_icon_default = '',
        seperator = '>',
        editor_state = '●',
        lock_icon = '',
    },

    exclude_filetype = {
        'help',
        'startify',
        'dashboard',
        'packer',
        'neogitstatus',
        'NvimTree',
        'Trouble',
        'alpha',
        'lir',
        'Outline',
        'spectre_panel',
        'toggleterm',
        'qf',
    }
})

