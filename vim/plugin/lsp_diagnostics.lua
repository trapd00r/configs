-- disable diagnostics globaly
-- vim.diagnostic.disable()


-- configure the diagnostic
vim.lsp.handlers["textDocument/publishDiagnostics"] = vim.lsp.with(
  vim.lsp.diagnostic.on_publish_diagnostics, {
    -- Enable underline, use default values
    underline = true,
    virtual_text = false,
    signs = true,
    update_in_insert = false,
    -- virtual_text = {
    --   spacing = 2,
    --   severity_limit = "Error",
    -- }
  }
)
