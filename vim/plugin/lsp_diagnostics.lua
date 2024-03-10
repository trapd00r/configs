-- disable diagnostics globaly
-- vim.diagnostic.disable()


-- configure the diagnostic
vim.lsp.handlers["textDocument/publishDiagnostics"] = vim.lsp.with(
  vim.lsp.diagnostic.on_publish_diagnostics, {
    -- Enable underline, use default values
    underline = true,
    virtual_text = false,
    signs = false,
    update_in_insert = false,
  }
)

local cmp_nvim_lsp = require "cmp_nvim_lsp"

