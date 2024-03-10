local lsp_zero = require('lsp-zero')

-- lsp_zero.on_attach(function(client, bufnr)
--   -- the line below disables highlights by lsp
--   client.server_capabilities.semanticTokensProvider = nil
--
--   local opts = {buffer = bufnr, remap = false}
--
--   vim.keymap.set("n", "gd",          function() vim.lsp.buf.definition() end, opts)
--   vim.keymap.set("n", "P",           function() vim.lsp.buf.hover() end, opts)
--   vim.keymap.set("n", "<leader>vws", function() vim.lsp.buf.workspace_symbol() end, opts)
--   vim.keymap.set("n", "<leader>vd",  function() vim.diagnostic.open_float() end, opts)
--   vim.keymap.set("n", "<leader>ca",  function() vim.lsp.buf.code_action() end, opts)
--   vim.keymap.set("n", "<leader>rr",  function() vim.lsp.buf.references() end, opts)
--   vim.keymap.set("n", "<leader>rn",  function() vim.lsp.buf.rename() end, opts)
--   vim.keymap.set("i", "<C-h>",       function() vim.lsp.buf.signature_help() end, opts)
--   vim.keymap.set("n", "S",           function() vim.lsp.buf.signature_help() end, opts)
--
--
--   vim.keymap.set("n", "<leader>dd",
--     function()
--
--                 --
--       vim.diagnostic.goto_next(float = {scope = 'line'})
--       vim.diagnostic.goto_next(
--         float = {
--           scope = 'line',
--         }
--     )
--     end, opts)
-- end)

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
        --   float: (boolean or table, default true) If "true", call
        --   |vim.diagnostic.open_float()| after moving. If a table, pass
        --   the table as the {opts} parameter to
        --   |vim.diagnostic.open_float()|. Unless overridden, the float
        --   will show diagnostics at the new cursor position (as if
        --   "cursor" were passed to the "scope" option).
        vim.diagnostic.goto_next({
          float = {
            scope = 'line' },
          }
        )
    end, opts)

    -- buffer diagnostic
    vim.keymap.set("n", "<leader>DD", function()
        vim.diagnostic.open_float({
            scope = 'buffer',
        })
    end, opts)
end)



-- lua language server
require('lspconfig').lua_ls.setup({})


-- mason
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



-- borders for popups
-- border can be none, single, double, shadow
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
