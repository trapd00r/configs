local cmp_lsp = require('cmp_nvim_lsp')
local capabilities = cmp_lsp.default_capabilities(vim.lsp.protocol.make_client_capabilities())

vim.keymap.set('n', 'gi', '<cmd>Telescope lsp_implementations<CR>')

-- Keybindings on LspAttach
vim.api.nvim_create_autocmd('LspAttach', {
  callback = function(ev)
    local client = vim.lsp.get_client_by_id(ev.data.client_id)
    if client then
      -- disable highlights by lsp
      client.server_capabilities.semanticTokensProvider = nil
    end

    local opts = { buffer = ev.buf, remap = false }

    vim.keymap.set("n", "<leader>rn", function() vim.lsp.buf.rename() end, opts)
    vim.keymap.set("n", "<leader>vws", function() vim.lsp.buf.workspace_symbol() end, opts)
    vim.keymap.set("n", "P", function() vim.lsp.buf.hover() end, opts)
    vim.keymap.set("n", "S", function() vim.lsp.buf.signature_help() end, opts)
    vim.keymap.set('n', '<leader>=', '<cmd>lua vim.lsp.buf.formatting()<CR>', opts)
    vim.keymap.set('n', '<leader>ah', '<cmd>lua vim.lsp.buf.hover()<CR>', opts)
    vim.keymap.set('n', '<leader>ai', '<cmd>lua vim.lsp.buf.incoming_calls()<CR>', opts)
    vim.keymap.set('n', '<leader>ao', '<cmd>lua vim.lsp.buf.outgoing_calls()<CR>', opts)
    vim.keymap.set('n', '<leader>ar', '<cmd>lua vim.lsp.buf.rename()<CR>', opts)
    vim.keymap.set('n', '<leader>ee', '<cmd>lua vim.lsp.util.show_line_diagnostics()<CR>', opts)
    vim.keymap.set('n', '<leader>gW', '<cmd>Telescope lsp.workspace.symbols<CR>', opts)
    vim.keymap.set('n', '<leader>gw', '<cmd>lua vim.lsp.buf.document_symbol()<CR>', opts)
    vim.keymap.set('n', 'gD', '<cmd>lua vim.lsp.buf.declaration()<CR>', opts)
    vim.keymap.set('n', 'gd', '<cmd>Telescope lsp_definitions<CR>', opts)
    vim.keymap.set('n', 'gr', '<cmd>Telescope lsp_references<CR>', opts)
    vim.keymap.set('n', 'gs', '<cmd>lua vim.lsp.buf.signature_help()<CR>', opts)
    vim.keymap.set('n', 'gt', '<cmd>lua vim.lsp.buf.type_definition()<CR>', opts)

    -- goto next diagnostic and display all diagnostics for that line
    vim.keymap.set("n", "<leader>dd", function()
      vim.diagnostic.goto_next({ float = { scope = 'line' } })
    end, opts)
    vim.keymap.set("n", "<down>", function()
      vim.diagnostic.goto_next({ float = { scope = 'line' } })
    end, opts)
    vim.keymap.set("n", "<up>", function()
      vim.diagnostic.goto_prev({ float = { scope = 'line' } })
    end, opts)

    -- buffer diagnostic
    vim.keymap.set("n", "<leader>DD", function()
      vim.cmd.Telescope('diagnostics')
    end, opts)
    vim.keymap.set("n", "<left>", function()
      vim.cmd.Telescope('diagnostics')
    end, opts)
    vim.keymap.set("n", "<right>", function()
      vim.cmd.Telescope('diagnostics')
    end, opts)
  end,
})


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
})


-- Diagnostic signs
vim.diagnostic.config({
  signs = {
    text = {
      [vim.diagnostic.severity.ERROR] = '✘',
      [vim.diagnostic.severity.WARN] = '▲',
      [vim.diagnostic.severity.HINT] = '⚑',
      [vim.diagnostic.severity.INFO] = '»',
    },
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


---------------------
-- LSP server configs
---------------------

vim.lsp.config('lua_ls', {
  capabilities = capabilities,
  on_init = function(client)
    if client.workspace_folders then
      local path = client.workspace_folders[1].name
      if vim.uv.fs_stat(path..'/.luarc.json') or vim.uv.fs_stat(path..'/.luarc.jsonc') then
        return
      end
    end

    client.config.settings.Lua = vim.tbl_deep_extend('force', client.config.settings.Lua, {
      runtime = {
        version = 'LuaJIT'
      },
      workspace = {
        checkThirdParty = false,
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
})

vim.lsp.config('html', {
  capabilities = capabilities,
})

---------------------
-- I'm using 2 language servers for perl because they have different features
---------------------

-- Perl Language Server, pls
vim.lsp.config('perlpls', {
  capabilities = capabilities,
  cmd = { '/home/scp1/bin/pls' },
  settings = {
    pls = {
      inc = { '/home/scp1/lib/perl5' },
    }
  }
})

-- Perl Navigator
vim.lsp.config('perlnavigator', {
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
})

-- Elm - disable diagnostics (too noisy while typing)
vim.lsp.config('elmls', {
  capabilities = capabilities,
  handlers = {
    ['textDocument/publishDiagnostics'] = function() end,
  },
})

-- Enable servers
vim.lsp.enable('lua_ls')
vim.lsp.enable('html')
vim.lsp.enable('perlpls')
vim.lsp.enable('perlnavigator')
vim.lsp.enable('elmls')


require('magento2_ls').setup()


-- :LspCapabilities for each active lsp server
vim.api.nvim_create_user_command("LspCapabilities", function()
	local curBuf = vim.api.nvim_get_current_buf()
	local clients = vim.lsp.get_clients { bufnr = curBuf }

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
