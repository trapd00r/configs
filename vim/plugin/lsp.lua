local lsp_zero = require('lsp-zero')

lsp_zero.on_attach(function(client, bufnr)
    -- the line below disables highlights by lsp
    client.server_capabilities.semanticTokensProvider = nil

    local opts = { buffer = bufnr, remap = false }

    vim.keymap.set("n", "gd",          function() vim.lsp.buf.definition() end, opts)
    vim.keymap.set("n", "P",           function() vim.lsp.buf.hover() end, opts)
    vim.keymap.set("n", "<leader>vws", function() vim.lsp.buf.workspace_symbol() end, opts)
    vim.keymap.set("n", "<leader>vd",  function() vim.diagnostic.open_float() end, opts)
    vim.keymap.set("n", "<leader>ca",  function() vim.lsp.buf.code_action() end, opts)
    vim.keymap.set("n", "<leader>rr",  function() vim.lsp.buf.references() end, opts)
    vim.keymap.set("n", "<leader>rn",  function() vim.lsp.buf.rename() end, opts)
    vim.keymap.set("i", "<C-h>",       function() vim.lsp.buf.signature_help() end, opts)
    vim.keymap.set("n", "S",           function() vim.lsp.buf.signature_help() end, opts)

    -- goto next diagnostic and display all diagnostics for that line
    vim.keymap.set("n", "<leader>dd", function()
        -- Pass the float option directly to vim.diagnostic.goto_next
        vim.diagnostic.goto_next({ float = { scope = 'line' } })
    end, opts)

    -- buffer diagnostic
    vim.keymap.set("n", "<leader>DD", function()
        vim.diagnostic.open_float({ scope = 'buffer' })
    end, opts)
end)



-- Mason
require("mason").setup({
    ui = {
        icons = {
            package_installed = "[Y]",
            package_pending = "[P]",
            package_uninstalled = "[N]"
        },
        border = "double",
    }
})

require('mason-lspconfig').setup({
  ensure_installed = {},
  handlers = {
    lsp_zero.default_setup,
  },
})



-- Borders for popups
vim.lsp.handlers["textDocument/hover"] =
  vim.lsp.with(
  vim.lsp.handlers.hover,
  {
    border = "double"
  }
)

vim.lsp.handlers["textDocument/signatureHelp"] =
  vim.lsp.with(
  vim.lsp.handlers.signature_help,
  {
    border = "double"
  }
)
