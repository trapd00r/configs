-- Install parsers (no-op if already installed)
require'nvim-treesitter'.install {
  "c", "lua", "vim", "vimdoc", "query",
  "perl", "php", "python", "ruby", "rust", "bash", "json", "yaml", "toml",
  "html", "css", "scss", "javascript", "typescript", "markdown", "regex",
  "cpp", "cmake", "dockerfile", "go",
}
