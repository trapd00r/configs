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

vim.api.nvim_set_keymap('n', '<leader>DD', ':call v:lua.toggle_diagnostics()<CR>', { noremap = true, silent = true })


-- gq using lsp, single line
-- local function format_current_line()
--   -- Get the current buffer number
--   local bufnr = vim.api.nvim_get_current_buf()
--
--   -- Get the current line number
--   local line = vim.fn.line(".")
--
--   -- Format the current line using vim.lsp.buf.format
--   vim.lsp.buf.format({ bufnr, bufnr }, { line, line })
-- end

-- -- or do Vgq
-- vim.keymap.set("n", "gq", format_current_line, { noremap = true })
--
-- -- gq using lsp, visual selection
-- vim.keymap.set("v", "gq", vim.lsp.buf.format, { remap = false })
--
-- -- format entire buffer
-- vim.keymap.set('n', '<leader>GQ', vim.lsp.buf.format, { noremap = true })




-- Function to format current line using LSP or fallback to formatprg
-- local function format_current_line()
--   -- Get the current buffer number
--   local bufnr = vim.api.nvim_get_current_buf()
--
--   -- Check if there are any LSP clients attached that support formatting
--   local clients = vim.lsp.get_active_clients({ bufnr = bufnr })
--   local has_formatter = false
--   for _, client in ipairs(clients) do
--     if client.server_capabilities.documentFormattingProvider then
--       has_formatter = true
--       break
--     end
--   end
--
--   if has_formatter then
--     -- Get the current line number
--     local line = vim.fn.line(".")
--     -- Try LSP formatting
--     local success = pcall(vim.lsp.buf.format, { bufnr = bufnr, range = { start = { line - 1, 0 }, ["end"] = { line, 0 } } })
--     if not success then
--       vim.cmd("normal! gqq")
--     end
--   else
--     -- No LSP formatter available, use formatprg
--     vim.cmd("normal! gqq")
--   end
-- end
--
-- -- Set the keymap for 'gq' in normal mode
-- vim.keymap.set("n", "gq", format_current_line, { noremap = true })
--
-- -- For visual mode, try LSP formatting for the selection or fallback to formatprg
-- local function format_selection()
--   -- Get the current buffer number
--   local bufnr = vim.api.nvim_get_current_buf()
--
--   -- Check if there are any LSP clients attached that support formatting
--   local clients = vim.lsp.get_active_clients({ bufnr = bufnr })
--   local has_formatter = false
--   for _, client in ipairs(clients) do
--     if client.server_capabilities.documentFormattingProvider then
--       has_formatter = true
--       break
--     end
--   end
--
--   if has_formatter then
--     local success = pcall(vim.lsp.buf.format)
--     if not success then
--       vim.cmd("normal! gv")
--       vim.cmd("normal! gq")
--     end
--   else
--     -- No LSP formatter available, use formatprg
--     vim.cmd("normal! gv")
--     vim.cmd("normal! gq")
--   end
-- end
--
-- -- Set the keymap for 'gq' in visual mode
-- vim.keymap.set("v", "gq", format_selection, { noremap = true })
--
-- -- Format the entire buffer using LSP formatting
-- vim.keymap.set('n', '<leader>GQ', vim.lsp.buf.format, { noremap = true })
