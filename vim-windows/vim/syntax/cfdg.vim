" Vim syntax file
" Language: CFDG (www.contextfreeart.org)
" Maintainer: Florian Brucker <mail@florianbrucker.de>
" Last Change: 2009-03-14
" Version: 0.3
" License: Vim license, http://www.vim.org/htmldoc/uganda.html
" Remark: Visit www.florianbrucker.de/index.php?p=cfdgsyntaxfile for updates


"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Vim syntax highlighting file for CFDG
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"
" This is a Vim syntax highlighting file for the Context Free language (CFDG).
" See http://www.contextfreeart.org for details on CFDG.
"
"
"""""""""""""""""""""""""""""""""""""""
" General information
"""""""""""""""""""""""""""""""""""""""
" Author: Florian Brucker <mail@florianbrucker.de>
" Version: 0.3
" License: Vim license, http://www.vim.org/htmldoc/uganda.html
"
" Visit www.florianbrucker.de/index.php?p=cfdgsyntaxfile for updates. Please
" report any bugs using the email address given above. Comments/ideas/etc. are
" greatly appreciated, too!
"
"
"""""""""""""""""""""""""""""""""""""""
" Installation
"""""""""""""""""""""""""""""""""""""""
" What follows is an installation instruction for Linux/Unix/etc.
"
" 1. Create the directory ~/.vim/syntax if it doesn't exist
" 2. Copy this file into that directory
"
" You can now enable the syntax file manually for the current buffer using
"
"     :set syntax=cfdg
" 
" If you want the syntax file to be enabled automatically for all files with a
" .cfdg ending, add the following lines to your ~/.vimrc and restart Vim:
"
"     augroup filetypedetect
"     au BufNewFile,BufRead *.cfdg setf cfdg
"     augroup END
"     filetype plugin on
"
"
"""""""""""""""""""""""""""""""""""""""
" Usage
"""""""""""""""""""""""""""""""""""""""
" In addition to syntax highlighting, this file provides some basic commands
" to run cfdg on the file you are currently editing. They are accessible via
" different keyboard shortcuts:
"
" (Note for advanced Vim users: If you've set the 'mapleader' variable of Vim,
" change the '\' in the key bindings below accordingly)
"
" \cc    Compiles the current cfdg file. Note that any changes since the last
"        save are not taken into account.
"
" \cv    Same as \cc, but asks for a variation code first.
"
" \cd    Displays the last image produced by \cc or \cv.
"
" \cb    Like \cc followed by \cd
"
" \ca    Like \cv followed by \cd
"
" 
"""""""""""""""""""""""""""""""""""""""
" Configuration
"""""""""""""""""""""""""""""""""""""""
" There are several configuration settings that you can modify to make this
" syntax file better suit your needs:

" Set this to 1 if you want to enable code folding
let b:code_folding = 0

" Path to cfdg
let b:cfdg_path = '~/bin/cfdg'

" Path to PNG viewer
let b:png_viewer = 'feh'

" Path to SVG viewer
let b:svg_viewer = ''

" Output file type. Must be either 'png' or 'svg'.
let b:output_type = 'png'

" Output file name. Supports the following expansions:
" %f - animation frame number
" %v - variation code (lower case)
" %V - variation code (upper case)
" %s - stem of the current filename (i.e. 'example' if the current filename is example.cfdg')
" %t - output type ('svg' or 'png')
" %% - a single '%'
let b:output_filename = '%s_%v_%f.%t'

" Additional options for CFDG. Note that the output filename (-o) and, if
" necessary, the SVG output option (-V) are automatically set. If you use the
" \cv or \ca commands, the variation code option (-v) is also set.
let b:cfdg_options = '-w 1920 -h 1080'

"
"
"""""""""""""""""""""""""""""""""""""""
" To do
"""""""""""""""""""""""""""""""""""""""
" - Multiple 'p' parameters in ARCTO,ARCREL,CURVETO,CURVEREL,FILL,STROKE
" - animation support
"
"
"""""""""""""""""""""""""""""""""""""""
" Version history
"""""""""""""""""""""""""""""""""""""""
" 0.3: Fixed bug with nested loop blocks
" 0.2: Two small bugfixes
" 0.1: Initial release
"
"
"
"
"
"
"
"
" BELOW HERE THE MAGIC BEGINS. KEEP AWAY UNLESS YOU KNOW WHAT YOU'RE DOING :)
"
"
"
"
"
"
"
"
"
"
"
"
"

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" INITIALIZATION
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

" For VIM version 5.x: Clear all syntax items
" For VIM version 6.x: Quit when a syntax file was already loaded
if version < 600
	syntax clear
elseif exists("b:current_syntax")
	finish
endif 


"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" GENERAL SETTINGS
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

" CFDG is case sensitive
syntax case match


" CFDG files are normally rather short, so this is OK
syntax sync fromstart


" We need '|' for |hue, |sat, etc. Add '.' for being able to recognize numbers
" starting with a '.'
setlocal iskeyword+=\|,.


"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" CODE FOLDING
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

if b:code_folding
	set foldmethod=syntax
endif


"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" SYNTAX
""""""""""""""""""""""""""""

" top-level keywords 
syntax keyword cfdg_keyword startshape nextgroup=cfdg_rule_name skipwhite skipnl skipempty
syntax keyword cfdg_keyword include nextgroup=cfdg_include skipwhite skipnl skipempty
syntax match cfdg_include /"\w\+"\|\<\w\+\>/ contained
syntax keyword cfdg_keyword background nextgroup=cfdg_adjustement_block skipwhite skipnl skipempty
syntax keyword cfdg_keyword tile nextgroup=cfdg_adjustment_block skipwhite skipnl skipempty

" Rule and rule name declaration
syntax keyword cfdg_keyword rule nextgroup=cfdg_rule_name_declaration skipwhite skipnl skipempty
syntax match cfdg_rule_name_declaration /\<\w\+\>/ contained nextgroup=cfdg_rule_block,cfdg_probability skipwhite skipnl skipempty
syntax match cfdg_probability /\<\d*\(\.\d\+\)\=/ contained nextgroup=cfdg_rule_block skipwhite skipnl skipempty
hi def link cfdg_probability cfdg_number


" Set matchgroup to the same group to avoid that the opening brace is matched
" as a contained cfdg_block
if b:code_folding
	syntax region cfdg_rule_block matchgroup=cfdg_rule_block start=/{/ end=/}/ contained contains=cfdg_rule_name,cfdg_primitive,cfdg_loop_count,cfdg_rule_block fold
else
	syntax region cfdg_rule_block matchgroup=cfdg_rule_block start=/{/ end=/}/ contained contains=cfdg_rule_name,cfdg_primitive,cfdg_loop_count,cfdg_rule_block
endif


" A cfdg_adjustment_block is a { } or [ ] block of shape adjustments
syntax region cfdg_adjustment_block start=/{/ end=/}/ contained
syntax region cfdg_adjustment_block start=/\[/ end=/\]/ contained


" A shape replacement (name of a rule). It is followed by a list of shape
" adjustments.
syntax match cfdg_rule_name /\<\w\+\>/ contained nextgroup=cfdg_adjustment_block skipwhite skipnl skipempty
syntax keyword cfdg_primitive SQUARE CIRCLE TRIANGLE contained nextgroup=cfdg_adjustment_block skipwhite skipnl skipempty


" Parameters in shape adjustment blocks (geometry)
syntax keyword cfdg_param x y z s size r rotate f flip skew contained containedin=cfdg_adjustment_block


" Parameters in shape adjustment blocks (color)
syntax keyword cfdg_param h hue \|h \|hue sat saturation \|sat \|saturation b brightness \|b \|brightness a alpha \|a \|alpha containedin=cfdg_adjustment_block nextgroup=cfdg_number_bar skipwhite skipnl skipempty


" Numbers in adjustment blocks
syntax match cfdg_number /-\=\<\d*\(\.\d\+\)\=\>/ contained containedin=cfdg_adjustment_block
syntax match cfdg_number_bar /-\=\<\d*\(\.\d\+\)\=\(\>\||\@=\)/ contained nextgroup=cfdg_bar "no skips
syntax match cfdg_bar /|/ contained
hi def link cfdg_bar cfdg_param
hi def link cfdg_number_bar cfdg_number


" Loop count
syntax match cfdg_loop_count /\<\d\+\>/ contained nextgroup=cfdg_loop_asterisk skipwhite skipnl skipempty
syntax match cfdg_loop_asterisk /\*/ contained nextgroup=cfdg_adjustment_block skipwhite skipnl skipempty


" Comments
syntax match cfdg_comment /\/\/.*/ containedin=ALL
syntax region cfdg_comment start=/\/\*/ end=/\*\// containedin=ALL


" Path and path name declaration
syntax keyword cfdg_keyword path nextgroup=cfdg_path_name_declaration skipwhite skipnl skipempty
syntax match cfdg_path_name_declaration /\<\w\+\>/ contained nextgroup=cfdg_path_block skipwhite skipnl skipempty

if b:code_folding
	syntax region cfdg_path_block matchgroup=cfdg_path_block start=/{/ end=/}/ contained contains=@cfdg_path_tool,cfdg_loop_count fold
else
	syntax region cfdg_path_block matchgroup=cfdg_path_block start=/{/ end=/}/ contained contains=@cfdg_path_tool,cfdg_loop_count 
endif


" Path operations
syntax keyword cfdg_move MOVETO MOVEREL nextgroup=cfdg_pblock_move skipwhite skipnl skipempty
syntax keyword cfdg_line LINETO LINEREL nextgroup=cfdg_pblock_move skipwhite skipnl skipempty
syntax keyword cfdg_arc ARCTO ARCREL nextgroup=cfdg_pblock_arc skipwhite skipnl skipempty
syntax keyword cfdg_curve CURVETO CURVEREL nextgroup=cfdg_pblock_curve skipwhite skipnl skipempty
syntax keyword cfdg_closepoly CLOSEPOLY nextgroup=cfdg_pblock_closepoly skipwhite skipnl skipempty


" Link all path operations to cfdg_path_operation
hi def link cfdg_move cfdg_path_operation
hi def link cfdg_line cfdg_path_operation
hi def link cfdg_arc cfdg_path_operation
hi def link cfdg_curve cfdg_path_operation
hi def link cfdg_closepoly cfdg_path_operation


" Path commands
syntax keyword cfdg_fill FILL nextgroup=cfdg_pblock_fill skipwhite skipnl skipempty
syntax keyword cfdg_stroke STROKE nextgroup=cfdg_pblock_stroke skipwhite skipnl skipempty


" Link all path commands to cfdg_path_command
hi def link cfdg_fill cfdg_path_command
hi def link cfdg_stroke cfdg_path_command


" Link path commands and path operations to cfdg_path_tool
hi def link cfdg_path_command cfdg_path_tool
hi def link cfdg_path_operation cfdg_path_tool


" All path commands and path operations
syntax cluster cfdg_path_tool contains=cfdg_move,cfdg_line,cfdg_arc,cfdg_curve,cfdg_closepoly,cfdg_stroke,cfdg_fill


" Parameter blocks of the path tools
syntax region cfdg_pblock_move start=/{/ end=/}/ contained 
syntax region cfdg_pblock_arc start=/{/ end=/}/ contained 
syntax region cfdg_pblock_curve start=/{/ end=/}/ contained 
syntax region cfdg_pblock_closepoly start=/{/ end=/}/ contained 
syntax region cfdg_pblock_fill start=/{/ end=/}/ contained 
syntax region cfdg_pblock_stroke start=/{/ end=/}/ contained 


" Cluster for all the param blocks of path operators (except CLOSEPOLY)
syntax cluster cfdg_opblocks contains=cfdg_pblock_move,cfdg_pblock_arc,cfdg_pblock_curve


" Cluster for all param blocks of all path tools
syntax cluster cfdg_pblocks contains=cfdg_pblock_.*


" Parameter names in path tool blocks
syntax keyword cfdg_param x y contained containedin=@cfdg_opblocks

syntax keyword cfdg_param p param contained containedin=cfdg_pblock_arc nextgroup=cfdg_arc_param skipwhite skipnl skipempty
syntax keyword cfdg_param p param contained containedin=cfdg_pblock_stroke nextgroup=cfdg_stroke_param skipwhite skipnl skipempty
syntax keyword cfdg_param p param contained containedin=cfdg_pblock_fill nextgroup=cfdg_fill_param skipwhite skipnl skipempty

syntax keyword cfdg_arc_param cw large contained
syntax keyword cfdg_stroke_param miterjoin roundjoin beveljoin buttcap roundcap squarecap contained
syntax keyword cfdg_fill_param evenodd contained

syntax keyword cfdg_param rx ry r contained containedin=cfdg_pblock_arc

syntax keyword cfdg_param x1 x2 y1 y2 contained containedin=cfdg_pblock_curve

syntax keyword cfdg_param width contained containedin=cfdg_pblock_stroke


" Link all param types to cfdg_param
hi def link cfdg_arc_param cfdg_param
hi def link cfdg_fill_param cfdg_param
hi def link cfdg_stroke_param cfdg_param


" Numbers in path blocks
syntax match cfdg_number /-\=\<\d*\(\.\d\+\)\=/ contained containedin=@cfdg_pblocks


" Expressions and functions
syntax keyword cfdg_expression \( \) \^ \- \+ \* \/ sin cos tan cot asin acos atan acot sinh cosh tanh asinh acosh atanh log log10 sqrt exp abs atan2 mod rand_static contained containedin=@cfdg_pblocks,cfdg_adjustment_block


"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" HIGHLIGHTING
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

hi def link cfdg_keyword statement

hi def link cfdg_rule_name_declaration underlined
hi def link cfdg_path_name_declaration underlined

hi def link cfdg_rule_name identifier
hi def link cfdg_primitive type
hi def link cfdg_path_tool type

hi def link cfdg_loop_count identifier
hi def link cfdg_comment comment

hi def link cfdg_param statement

hi def link cfdg_number number

hi def link cfdg_include string

hi def link cfdg_expression identifier



"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" KEYMAPS
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

" Holds the name of the last output file. This is automatically set by
" CFDG_compile() and used by CFDG_display().
let b:last_output_filename = ''

" Builds the filename from b:output_filename by making the necessary
" expansions.
fun! CFDG_get_output_filename()
	let last_dot = strridx(@%, '.')
	let stem = strpart(@%, 0, last_dot)
	let name = substitute(b:output_filename, '%s', stem, 'g')
	let name = substitute(name, '%t', b:output_type, 'g')
	return name
endf


" Compiles the current buffer (as of last save). There is one optional
" argument, the variation code.
fun! CFDG_compile(...)
	" Build command
	let this_file = shellescape(@%, 1)
	let output_file = shellescape(CFDG_get_output_filename(), 1)
	let options = '-o ' . output_file . ' '
	if b:output_type == 'svg'
		let options = options . '-V '
	endif
	if a:0 > 0
		" First optional argument is the variation code
		if strlen(a:1) > 0
			let options = options . '-v ' . a:1 . ' '
		endif
	endif
	let options = options . b:cfdg_options
	let command = '! ' . b:cfdg_path . ' ' . this_file . ' ' . options

	" Call command and analyse output to find the name of the output file
	let b:last_output_filename = ''
	redir => cfdg_output
	exe command
	redir END
	let lines = split(cfdg_output, '\n')
	for line in lines
		if strpart(line, 0, 23) == "The output file name is"
			let b:last_output_filename = strpart(line, 24, strlen(line) - 25)
			break
		endif
	endfor
endf


" Asks the user for a variation code until a valid code or '' is entered. The
" last input is returned.
fun! CFDG_ask_for_variation_code()
	while 1
		let code = toupper(input('Enter variation code (up to 6 letters from A-Z): '))
		if code == ''
			return ''
		elseif strlen(code) > 6
			echo "\nError: The code can not be longer than 6 letters."
		elseif match(code, '\U') != -1
			echo "\nError: Only the letters A-Z are allowed."
		else
			return code
		endif
	endwhile
endf


" Displays the output file (as of last compile)
fun! CFDG_display()
	if b:last_output_filename == ''
		echo "There is no output file. Please compile first."
		return
	endif
	let type = strpart(b:last_output_filename, strlen(b:last_output_filename) - 3)
	if type == 'png'
		if b:png_viewer == ''
			echo 'No PNG viewer set. Set b:png_viewer to the path of your PNG viewer.'
		else
			exe 'silent ! ' . b:png_viewer . ' ' . b:last_output_filename . ' &'
		endif
	elseif type == 'svg'
		if b:svg_viewer == ''
			echo 'No SVG viewer set. Set b:svg_viewer to the path of your SVG viewer.'
		else
			exe 'silent ! ' . b:svg_viewer . ' ' . b:last_output_filename . ' &'
		endif
	else
		echo "Unknown output file type '" . type . "'"
	endif
endf


" Keymap for compile
nmap  <buffer> <Leader>cc :call CFDG_compile()<CR>


" Keymap for compile with variation
nmap  <buffer> <Leader>cv :call CFDG_compile(CFDG_ask_for_variation_code())<CR>


" Keymap for display
nmap  <buffer>  <Leader>cd :call CFDG_display()<CR>


" Keymap for compile & display
nmap  <buffer>  <Leader>cb :call CFDG_compile() \| call CFDG_display()<CR>


" Keymap for compile with variation code & display
nmap  <buffer>  <Leader>ca :call CFDG_compile(CFDG_ask_for_variation_code()) \| call CFDG_display()<CR>


" Keymap for switching to PNG output type
"nmap <buffer> <Leader>cp :let b:output_type='png' \| echo "Output type is now PNG"<CR>


" Keymap for switching to SVG output type
"nmap <buffer> <Leader>cs :let b:output_type='svg' \| echo "Output type is now SVG"<CR>


"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" CLEAN UP
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

" Register our syntax
let b:current_syntax = "cfdg"
