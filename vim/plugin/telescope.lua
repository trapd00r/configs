local actions = require("telescope.actions")

require("telescope").setup {
  pickers = {
    find_files = {
      hidden = true,
      theme = 'ivy'
    },
    --        live_grep = {
    --            layout_strategy = 'horizontal',
    --            theme = 'dropdown'
    --        },
    --        lsp_references = {
    --            theme = 'dropdown'
    --        },
    --        diagnostics = {
    --            theme = 'dropdown'
    --        },
    --        current_buffer_fuzzy_find = {
    --            theme = 'dropdown'
    --        }
  },
  defaults = {
    --        layout_strategy = 'center',
    layout_strategy = 'vertical',
    layout_config = {
      --            width = 0.75,
      --            height = 0.75,
      prompt_position = "top",
      --            preview_cutoff = 120
    },
    sorting_strategy = 'ascending',
    --        layout_config = {
    --            center = {
    --                anchor = 'S'
    --            }
    --        },
    file_ignore_patterns = {
      ".git/"
    },
    mappings = {
      i = {
        ["<C-j>"] = require("telescope.actions").move_selection_next,
        ["<C-k>"] = require("telescope.actions").move_selection_previous,
        ["<esc>"] = actions.close
      }
    }
  },
  extensions = {
    ['ui-select'] = {
      require("telescope.themes").get_dropdown()
    },
    repo = {
      theme = "dropdown",
      list = {
        search_dirs = {
          "~/personal/",
          "~/.config/",
          [[~/.local/share/nvim/]]
        }
      }
    },
    project = {
      theme = 'dropdown'
    },
    file_browser = {
      theme = "ivy",
      hijack_netrw = true
    }
  }
}

