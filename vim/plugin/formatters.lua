require("conform").setup({
  formatters_by_ft = {
    lua = { "stylua" },
    -- Conform will run multiple formatters sequentially
    python = { "isort", "black" },
    -- Use a sub-list to run only the first available formatter
    javascript = {
      { "prettierd", "prettier" }
    },
    php = { "phpcbf" },
  },
})

require("conform").formatters.stylua = {
  prepends_args = { "--indent-type", "spaces", "--indent-width", "2" },
}

require("conform").formatters.phpcbf = {
  prepends_args = { 
    "-q",
    "--standard=PSR2",
    "--stdin-path=$FILENAME",
    "-",
  }
}

vim.api.nvim_create_user_command("Format", function(args)
  local range = nil
  if args.count ~= -1 then
    local end_line = vim.api.nvim_buf_get_lines(0, args.line2 - 1, args.line2, true)[1]
    range = {
      start = { args.line1, 0 },
      ["end"] = { args.line2, end_line:len() },
    }
  end
  require("conform").format({ async = true, lsp_fallback = true, range = range })
end, { range = true })

-- map gq to Format 
-- vim.api.nvim_set_keymap("n", "gq", ":Format<CR>", { noremap = true, silent = true })
-- vim.api.nvim_set_keymap("v", "gq", ":Format<CR>", { noremap = true, silent = true })
