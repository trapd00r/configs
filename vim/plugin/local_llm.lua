
require('gen').setup({
    -- model = "llama3", -- The default model to use.
    -- model = "mistral",
    -- model = "codellama:13b",
    -- model = "codellama:34b",
    -- model = "qwen2.5-coder",
    -- model = "codeqwen",
    -- model = "deepseek-coder-v2",
    model = "deepseek-coder-v2:16b-lite-instruct-q5_K_S",
    quit_map = "q", -- set keymap to close the response window
    retry_map = "<c-r>", -- set keymap to re-send the current prompt
    accept_map = "<c-cr>", -- set keymap to replace the previous selection with the last result
    host = "192.168.1.12", -- The host running the Ollama service.
    port = "11435", -- The port on which the Ollama service is listening.
    -- display_mode = "float", -- The display mode. Can be "float" or "split" or "horizontal-split".
    display_mode = "split", -- The display mode. Can be "float" or "split" or "horizontal-split".
    show_prompt = false, -- Shows the prompt submitted to Ollama.
    show_model = true, -- Displays which model you are using at the beginning of your chat session.
    no_auto_close = true, -- Never closes the window automatically.
    file = false, -- Write the payload to a temporary file to keep the command short.
    hidden = false, -- Hide the generation window (if true, will implicitly set `prompt.replace = true`), requires Neovim >= 0.10
    init = function(options) pcall(io.popen, "ollama serve > /dev/null 2>&1 &") end,
    -- Function to initialize Ollama
    command = function(options)
        local body = {model = options.model, stream = true}
        return "curl --silent --no-buffer -X POST http://" .. options.host .. ":" .. options.port .. "/api/chat -d $body"
    end,
    -- The command for the Ollama service. You can use placeholders $prompt, $model and $body (shellescaped).
    -- This can also be a command string.
    -- The executed command must return a JSON object with { response, context }
    -- (context property is optional).
    -- list_models = '<omitted lua function>', -- Retrieves a list of model names
    debug = false -- Prints errors and the command which is run.
})

require('gen').prompts['Elaborate_Text'] = {
  prompt = "Elaborate the following text:\n$text",
  replace = true
}

require('gen').prompts['Fix_Code'] = {
  prompt = "Fix the following code. Only output the result in format :34b",
        model = "qwen2.5-coder",
        quit_map = "q", -- set keymap to close the response window
        retry_map = "<c-r>", -- set keymap to re-send the current prompt
        accept_map = "<c-cr>", -- set keymap to replace the previous selection with the last result
        host = "192.168.1.12", -- The host running the Ollama service.
        port = "11435", -- The port on which the Ollama service is listening.
        display_mode = "float", -- The display mode. Can be "float" or "split" or "horizontal-split".
        show_prompt = false, -- Shows the prompt submitted to Ollama.
        show_model = true, -- Displays which model you are using at the beginning of your chat session.
        no_auto_close = true, -- Never closes the window automatically.
        file = false, -- Write the payload to a temporary file to keep the command short.
        hidden = false, -- Hide the generation window (if true, will implicitly set `prompt.replace = true`), requires Neovim >= 0.10
        init = function(options) pcall(io.popen, "ollama serve > /dev/null 2>&1 &") end,
        -- Function to initialize Ollama
        command = function(options)
            local body = {model = options.model, stream = true}
            return "curl --silent --no-buffer -X POST http://" .. options.host .. ":" .. options.port .. "/api/chat -d $body"
        end,
        -- The command for the Ollama service. You can use placeholders $prompt, $model and $body (shellescaped).
        -- this can also be a command string.
        -- The executed command must return a JSON object with { response, context }
        -- (context property is optional).
        -- list_models = '<omitted lua function>', -- Retrieves a list of model names
        debug = false -- Prints errors and the command which is run.
    }


require('gen').prompts['Elaborate_Text'] = {
  prompt = "Elaborate the following text:\n$text",
  replace = true
}

require('gen').prompts['Fix_Code'] = {
  prompt = "Fix the following code. Only output the result in format ```$filetype\n...\n```:\n```$filetype\n$text\n```",
  replace = true,
  extract = "```$filetype\n(.-)```"
}


require('gen').prompts['Translate'] = {
  prompt = "Translate the following to $input, keeping all the formatting and replacing the original words. Do not say anything else. I ONLY want the translated words, replacing the original ones and it is VERY important to keep the original formatting, including newlines or special characters like used in code, json etc. Also be smart about the translations; know your context:\n$text",
  replace = true,
  extract = "```$filetype\n(.-)```"
}

require('gen').prompts['Magento - Ask'] = {
  prompt = "You are a skilled Magento developer. You like clean code and you are very experienced with Magento. You are asked to solve the following problem. What do you do?\n$input",
  replace = true,
  -- extract = "```$filetype\n(.-)```"
}

require('gen').prompts['Magento - Write'] = {
  prompt = "You are a skilled Magento developer. \
    You like clean code and best practices.      \
    Solve the following problem or implement asked functioanlity without any additional information. \
    Output the result without syntax errors.     \
    You must NEVER, ever use markdown code blocks or backticks surrounding the code. \
    You MUST just output the code. \
    You must import the neccessary \\Magento modules that you will use, this is very important. \
    Before returning the response, make ABSOLUTELY SURE that there is no triple backticks or markdown code blocks surrounding the code. \
    When you are about to return the response, make sure that the code is not surrounded by triple backticks or markdown code blocks. \
    When you are about to return the response, first remove the first line and the last line. \
    This is EXTREMELY important. \
    Solve this: $input",
  replace = false,
  extract = "```$filetype\n(.-)```"
}

require('gen').prompts['Format - sw=2'] = {
  prompt = "You are a skilled developer. \
    You use spaces and not tabs \
    You use 2 spaces for indentation \
    Reformat the input according to instructions. \
    Return the code as you got it, so nothing else and no backticks. \
    Here is the code:\n $text",
  replace = true,
  extract = "```$filetype\n(.-)```"
}


vim.keymap.set({ 'n', 'v' }, '<C-s>', ':Gen<CR>')
vim.keymap.set({ 'n', 'v' }, '<C-d>', ':lua require("gen").select_model()<CR>')
