-- fix bug https://github.com/neovim/neovim/issues/21856
vim.api.nvim_create_autocmd({ "VimLeave" }, {
  callback = function()
--    vim.fn.jobstart('notify-send "lol"', {detach=true})
  end,
})

-- toggle diagnostics
vim.g.diagnostics_active = true
function _G.toggle_diagnostics()
  if vim.g.diagnostics_active then
    vim.g.diagnostics_active = false
--    vim.lsp.diagnostic.clear(0)
    vim.lsp.handlers["textDocument/publishDiagnostics"] = function() end
  else
    vim.g.diagnostics_active = true
    vim.lsp.handlers["textDocument/publishDiagnostics"] = vim.lsp.with(
      vim.lsp.diagnostic.on_publish_diagnostics, {
        virtual_text = true,
        signs = true,
        underline = true,
        update_in_insert = false,
      }
    )
  end
end

vim.api.nvim_set_keymap('n', '<leader>DD', ':call v:lua.toggle_diagnostics()<CR>',  {noremap = true, silent = true})
