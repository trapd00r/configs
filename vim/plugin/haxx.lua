
-- fix bug https://github.com/neovim/neovim/issues/21856
vim.api.nvim_create_autocmd({ "VimLeave" }, {
  callback = function()
--    vim.fn.jobstart('notify-send "lol"', {detach=true})
  end,
})
