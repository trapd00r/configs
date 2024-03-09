-- Set up nvim-cmp.
local cmp = require'cmp'

cmp.setup({
  snippet = {
    -- REQUIRED - you must specify a snippet engine
    expand = function(args)
      vim.fn["vsnip#anonymous"](args.body) -- For `vsnip` users.
      -- require('luasnip').lsp_expand(args.body) -- For `luasnip` users.
      -- require('snippy').expand_snippet(args.body) -- For `snippy` users.
      -- vim.fn["UltiSnips#Anon"](args.body) -- For `ultisnips` users.
    end,
  },
  window = {
    completion = cmp.config.window.bordered(),
    documentation = cmp.config.window.bordered(),
  },
  mapping = cmp.mapping.preset.insert({
    --    ['<C-b>'] = cmp.mapping.scroll_docs(-4),
    --    ['<C-f>'] = cmp.mapping.scroll_docs(4),
    --    ['<C-Space>'] = cmp.mapping.complete(),
    --    ['<C-e>'] = cmp.mapping.abort(),
    ['<CR>'] = cmp.mapping.confirm({ select = true }), -- Accept currently selected item. Set `select` to `false` to only confirm explicitly selected items.
  }),
  sources = cmp.config.sources({
    { name = 'nvim_lsp' },
    { name = 'vsnip' },
    { name = 'vsnip' },
    { name = 'copilot' },
    { name = 'buffer' },
    {
      name = "env",
      -- Defaults
      option = {
        path = '.',
        load_shell = true,
        item_kind = cmp.lsp.CompletionItemKind.Variable,
        eval_on_confirm = false,
        show_documentation = true,
        show_content_on_docs = true,
        documentation_kind = 'markdown',
        dotenv_environment = '.*',
--        file_priority = function(a, b)
--          -- Prioritizing local files
--          return a:upper() < b:upper()
      }
    },

  })
})

-- Set configuration for specific filetype.
cmp.setup.filetype('gitcommit', {
  sources = cmp.config.sources({
    { name = 'git' }, -- You can specify the `git` source if [you were installed it](https://github.com/petertriho/cmp-git).
  }, {
    { name = 'buffer' },
  })
})

-- Use buffer source for `/` and `?` (if you enabled `native_menu`, this won't work anymore).
cmp.setup.cmdline({ '/', '?' }, {
  mapping = cmp.mapping.preset.cmdline(),
  sources = {
    { name = 'buffer' }
  }
})

-- Use cmdline & path source for ':' (if you enabled `native_menu`, this won't work anymore).
cmp.setup.cmdline(':', {
  mapping = cmp.mapping.preset.cmdline(),
  sources = cmp.config.sources({
    { name = 'path' }
  }, {
    { name = 'cmdline' }
  })
})


-- nvim-cmp-fonts
-- Only enable `fonts` for `conf` and `config` file types
require "cmp".setup.filetype({ "conf", "config", "zsh", "sh", "bash" },
    { sources = { { name = "fonts"} } })


    local cmp = require("cmp")

-- env variables
cmp.setup {
    sources = {
        {
          name = "env",
          -- Defaults
          option = {
            path = '.',
            load_shell = true,
            item_kind = cmp.lsp.CompletionItemKind.Variable,
            eval_on_confirm = false,
            show_documentation = true,
            show_content_on_docs = true,
            documentation_kind = 'markdown',
            dotenv_environment = '.*',
            file_priority = function(a, b)
              -- Prioritizing local files
              return a:upper() < b:upper()
            end,
          }
        }
    }
}
