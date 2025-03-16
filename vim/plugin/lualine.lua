-- Plugin: lualine


vim.cmd('highlight BlameHighlight gui=none guifg=#808080 ctermfg=145 ctermbg=233 cterm=none')

local function Blame()
  local git_blame = require('gitblame')
  if git_blame.is_blame_text_available() then
    return git_blame.get_current_blame_text()
  else
    return ''
  end
end


local function FileLsColored()
  -- Get the current file name
  local filename = vim.fn.expand('%:.')
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
    icons_enabled = true,
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
    lualine_c = {
      'branch', 'diff', 'diagnostics', ' | ',
      { Blame, color = 'BlameHighlight' }
    },

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

  inactive_winbar = {
    lualine_a = {},
    lualine_b = {},
    lualine_c = {'filename'},
    lualine_x = {},
    lualine_y = {},
    lualine_z = {}
  },
  extensions = {}
}
