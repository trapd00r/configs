local lsp_zero = require('lsp-zero')

local win = require('lspconfig.ui.windows')
local _default_opts = win.default_opts

require('lspconfig.ui.windows').default_options.border = 'double'

local cmp_lsp = require('cmp_nvim_lsp')
local capabilities = cmp_lsp.default_capabilities(vim.lsp.protocol.make_client_capabilities())

vim.keymap.set('n', 'gi', '<cmd>Telescope lsp_implementations<CR>')

lsp_zero.on_attach(function(client, bufnr)
  -- the line below disables highlights by lsp
  client.server_capabilities.semanticTokensProvider = nil

  local opts = { buffer = bufnr, remap = false }

  -- vim.lsp.buf.signature_help()
  vim.keymap.set("n", "<leader>rn", function() vim.lsp.buf.rename() end, opts)
  vim.keymap.set("n", "<leader>vws", function() vim.lsp.buf.workspace_symbol() end, opts)
  vim.keymap.set("n", "P", function() vim.lsp.buf.hover() end, opts)
  vim.keymap.set("n", "S", function() vim.lsp.buf.signature_help() end, opts)
  vim.keymap.set('n', '<leader>=', '<cmd>lua vim.lsp.buf.formatting()<CR>')
  vim.keymap.set('n', '<leader>ah', '<cmd>lua vim.lsp.buf.hover()<CR>')
  vim.keymap.set('n', '<leader>ai', '<cmd>lua vim.lsp.buf.incoming_calls()<CR>')
  vim.keymap.set('n', '<leader>ao', '<cmd>lua vim.lsp.buf.outgoing_calls()<CR>')
  vim.keymap.set('n', '<leader>ar', '<cmd>lua vim.lsp.buf.rename()<CR>')
  vim.keymap.set('n', '<leader>ee', '<cmd>lua vim.lsp.util.show_line_diagnostics()<CR>')
  vim.keymap.set('n', '<leader>gW', '<cmd>Telescope lsp.workspace.symbols<CR>')
  vim.keymap.set('n', '<leader>gw', '<cmd>lua vim.lsp.buf.document_symbol()<CR>')
  vim.keymap.set('n', 'P', '<cmd>lua vim.lsp.buf.hover()<CR>')
  vim.keymap.set('n', 'gD', '<cmd>lua vim.lsp.buf.declaration()<CR>')
  vim.keymap.set('n', 'gd', '<cmd>Telescope lsp_definitions<CR>')
  vim.keymap.set('n', 'gr', '<cmd>Telescope lsp_references<CR>')
  vim.keymap.set('n', 'gs', '<cmd>lua vim.lsp.buf.signature_help()<CR>')
  vim.keymap.set('n', 'gt', '<cmd>lua vim.lsp.buf.type_definition()<CR>')

  -- goto next diagnostic and display all diagnostics for that line
  vim.keymap.set("n", "<leader>dd", function()
    -- Pass the float option directly to vim.diagnostic.goto_next
    vim.diagnostic.goto_next({ float = { scope = 'line' } })
  end, opts)
  vim.keymap.set("n", "<down>", function()
    -- Pass the float option directly to vim.diagnostic.goto_next
    vim.diagnostic.goto_next({ float = { scope = 'line' } })
  end, opts)
  vim.keymap.set("n", "<up>", function()
    -- Pass the float option directly to vim.diagnostic.goto_next
    vim.diagnostic.goto_prev({ float = { scope = 'line' } })
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
    capabilities = capabilities
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
require('lspconfig').gopls.setup({})
-- require('lspconfig').eslint.setup({})
-- require('lspconfig').rust_analyzer.setup({})
-- require('lspconfig').bashls.setup({})
-- require('lspconfig').clangd.setup({})
-- require('lspconfig').cmake.setup({})
-- require('lspconfig').cssls.setup({})
require('lspconfig').html.setup({})
require('lspconfig').nginx_language_server.setup({})
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
--   capabilities = capabilities,
--   root_dir = require("lspconfig").util.root_pattern(".git", "package.json"),
--   autostart = false,
--   settings = {
--     intelephense = {
--       files = {
--         maxSize = 1000000000
--       },
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

-- clangd fix
local cmp_nvim_lsp = require "cmp_nvim_lsp"
require("lspconfig").clangd.setup {
  capabilities = cmp_nvim_lsp.default_capabilities(),
  cmd = {
    "clangd",
    "--offset-encoding=utf-16",
  },
}



require('lspconfig').phpactor.setup({
  capabilities = capabilities,
  autostart = false,
  settings = {
    phpactor = {
      enable = true,
      completion = {
        fullyQualifyGlobalConstantsAndFunctions = false
      },
      phpdoc = {
        returnVoid = false,
      }
    },
  }
})

require('lspconfig').vimls.setup({
  capabilities = capabilities,
})



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
  capabilities = capabilities,
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
    capabilities = capabilities,
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

require'lspconfig'.elmls.setup {
  capabilities = capabilities,
}

require'lspconfig'.elmls.setup{
  capabilities = capabilities,
}

require('magento2_ls').setup()


-- :LspCapabilities for each active lsp server
vim.api.nvim_create_user_command("LspCapabilities", function()
	local curBuf = vim.api.nvim_get_current_buf()
	local clients = vim.lsp.get_active_clients { bufnr = curBuf }

	for _, client in pairs(clients) do
		if client.name ~= "null-ls" then
			local capAsList = {}
			for key, value in pairs(client.server_capabilities) do
				if value and key:find("Provider") then
					local capability = key:gsub("Provider$", "")
					table.insert(capAsList, "- " .. capability)
				end
			end
			table.sort(capAsList) -- sorts alphabetically
			local msg = "# " .. client.name .. "\n" .. table.concat(capAsList, "\n")
			vim.notify(msg, "trace", {
				on_open = function(win)
					local buf = vim.api.nvim_win_get_buf(win)
					vim.api.nvim_buf_set_option(buf, "filetype", "markdown")
				end,
				timeout = 14000,
			})
			fn.setreg("+", "Capabilities = " .. vim.inspect(client.server_capabilities))
		end
	end
end, {})
