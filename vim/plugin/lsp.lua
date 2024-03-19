local lsp_zero = require('lsp-zero')

-- Not all language servers provide the same capabilities. To ensure you only set
-- keymaps if the language server supports a feature, you can guard the keymap
-- calls behind capability checks:
-- >lua
--     vim.api.nvim_create_autocmd('LspAttach', {
--       callback = function(args)
--         local client = vim.lsp.get_client_by_id(args.data.client_id)
--         if client.server_capabilities.hoverProvider then
--           vim.keymap.set('n', 'K', vim.lsp.buf.hover, { buffer = args.buf })
--         end
--       end,
--     })
-- <
--
-- To learn what capabilities are available you can run the following command in
-- a buffer with a started LSP client:
--
-- >vim
--     :lua =vim.lsp.get_active_clients()[1].server_capabilities

local win = require('lspconfig.ui.windows')
local _default_opts = win.default_opts

require('lspconfig.ui.windows').default_options.border = 'double'



lsp_zero.on_attach(function(client, bufnr)
    -- the line below disables highlights by lsp
    client.server_capabilities.semanticTokensProvider = nil

    local opts = { buffer = bufnr, remap = false }

    vim.keymap.set("n", "gd",          function() vim.lsp.buf.definition() end, opts)
    vim.keymap.set("n", "P",           function() vim.lsp.buf.hover() end, opts)
    vim.keymap.set("n", "<leader>vws", function() vim.lsp.buf.workspace_symbol() end, opts)
    vim.keymap.set("n", "<leader>vd",  function() vim.diagnostic.open_float() end, opts)
    -- vim.keymap.set("n", "<leader>ca",  function() vim.lsp.buf.code_action() end, opts)
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
    -- vim.keymap.set("n", "<leader>DD", function()
    --     vim.diagnostic.open_float({ scope = 'buffer' })
    -- end, opts)
    vim.keymap.set("n", "<leader>DD", function()
        vim.cmd.Telescope('diagnostics')
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


require'lspconfig'.lua_ls.setup {
  on_init = function(client)
    local path = client.workspace_folders[1].name
    if vim.loop.fs_stat(path..'/.luarc.json') or vim.loop.fs_stat(path..'/.luarc.jsonc') then
      return
    end

    client.config.settings.Lua = vim.tbl_deep_extend('force', client.config.settings.Lua, {
      runtime = {
        -- Tell the language server which version of Lua you're using
        -- (most likely LuaJIT in the case of Neovim)
        version = 'LuaJIT'
      },
      globals = {
        -- Include the `vim` global so the language server knows about Neovim
        'vim'
      },
      -- Make the server aware of Neovim runtime files
      workspace = {
        checkThirdParty = false,
        -- library = {
        --   vim.env.VIMRUNTIME
        --   -- Depending on the usage, you might want to add additional paths here.
        --   -- "${3rd}/luv/library"
        --   -- "${3rd}/busted/library",
        -- }
        -- or pull in all of 'runtimepath'. NOTE: this is a lot slower
        library = vim.api.nvim_get_runtime_file("", true)

      }
    })
  end,
  settings = {
    Lua = {
      completion = {
        callSnippet = "Replace"
      }
    }
  }
}

require('lspconfig').tsserver.setup({})
-- require('lspconfig').eslint.setup({})
-- require('lspconfig').rust_analyzer.setup({})
-- require('lspconfig').bashls.setup({})
-- require('lspconfig').clangd.setup({})
-- require('lspconfig').cmake.setup({})
-- require('lspconfig').cssls.setup({})
require('lspconfig').html.setup({})
-- require('lspconfig').marksman.setup({})
-- require('lspconfig').pylsp.setup({})
-- require('lspconfig').ruby_ls.setup({})
-- require('lspconfig').yamlls.setup({})
-- require('lspconfig').autotools_ls.setup({})
-- require('lspconfig').dockerls.setup({})
-- require('lspconfig').elmls.setup({})
-- require('lspconfig').jsonls.setup({})
-- require('lspconfig').julials.setup({})
-- require('lspconfig').lemminx.setup({})
-- require('lspconfig').tailwindcss.setup({})
-- require('lspconfig').htmx.setup({})
-- require('lspconfig').intelephense.setup({})
-- require('lspconfig').intelephense.setup({
--   capabilities = capabilities, -- from the local capabilities variable in the above snippet
--   settings = {
--     intelephense = {
--       telemetry = {
--         enabled = false,
--       },
--       completion = {
--         fullyQualifyGlobalConstantsAndFunctions = false
--       },
--       phpdoc = {
--         returnVoid = false,
--       }
--     },
--   }
-- })



lsp_zero.set_sign_icons({
  error = '✘',
  warn = '▲',
  hint = '⚑',
  info = '»',
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

---------------------
-- I'm using 2 language servers for perl because they have different features
---------------------

-- Perl Language Server, pls
local config = {
  cmd = { '/home/scp1/bin/pls' }, -- complete path to where PLS is located
  settings = {
    pls = {
      inc = { '/home/scp1/lib/perl5'},  -- add list of dirs to @INC
--      cwd = { '/my/projects' },   -- working directory for PLS
      -- perlcritic = { enabled = true, perlcriticrc = '/my/projects/.perlcriticrc' },  -- use perlcritic and pass a non-default location for its config
      -- syntax = { enabled = true, perl = '/usr/bin/perl', args = { 'arg1', 'arg2' } }, -- enable syntax checking and use a non-default perl binary
      -- perltidy = { perltidyrc = '/my/projects/.perltidyrc' } -- non-default location for perltidy's config
    }
  }
}
require'lspconfig'.perlpls.setup(config)

-- Perl Navigator
require'lspconfig'.perlnavigator.setup{
    settings = {
      perlnavigator = {
          perlPath = 'perl',
          enableWarnings = true,
          perltidyProfile = '',
          perlcriticProfile = '',
          perlcriticEnabled = false,
      }
    }
}
