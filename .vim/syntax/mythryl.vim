" Vim syntax file
" Language:     Mythryl
" Maintainer:   Jeffrey Lau <vim@NOSPAMjlau.tk>
" Last Change:	2010 Feb 15 (<- most likely out-dated)
" Remark:	included by the Mythryl-script syntax
"
" Filenames:    *.api, *.pkg
" URL:          http://github.com/zoonfafer/vim-mythryl
" Creation:	2009 Oct 07
" 
" TODO:
"	- (High priority / more interesting)
"	- Implement "expensive" & "cheap" modes.  Pick one for the default.
"	- Match regular expression escape characters inside .// ?
"	- Match type declaration.  E.g. ... : String
"	- Match type declaration *in various contexts* (HARD?)
"	- Match package sealing.  E.g. package foo : (weak) Foo ...
"	- Match thunk variable.  E.g. #foobar
"	- Match tuple projection variable.  E.g. #2 (a, b)
"	- Differentiate between {single,multi}-case (<- HARD) {fun,fn,except}.
"	- Match multi-case {fun,fn,except} with their corresponding "end"s.
"	- Differentiate the "where" cases:
"		* list comprehension: [ ... for ... in ... where ... ]
"		* generic package... where x == y ... { }
"		* where ... end (by itself, it's NOT HARD)
"	- if ... elif ... else ... fi (NOT HARD)
"	- case ... esac (EASY)
"	- stipulate ... herein (NOT HARD)
"	- Mythryl's OO syntax: class ...
"	- Show syntax errors for stray "end", "elif", "else", "fi", "esac",
"	  "herein", thunk variables
"	- Differentiate between predefined symbols & custom symbols, e.g. "->"
"	  is built-in, whereas "-->" is custom (it has an extra "-" in front.)
"	- Share regexp definitions with make6, esp. with lowercase &
"	  mixedcase ID.
"	  Also share (a subset of) error definitions.
"	- (low priority)


" For version 5.x: Clear all syntax items
" For version 6.x: Quit when a syntax file was already loaded
if version < 600
	syntax clear
elseif exists("b:current_syntax")
	finish
endif

" Mythryl is case-sensitive
syn case match


"==============================================================
" Vim Syntax Clusters
"--------------------------------------------------------------

syn cluster myComments contains=
	\ myOnelineComment,
	\ myMultilineComment

syn cluster myNumbers contains=
	\ myInt,
	\ myHex,
	\ myUnsignedInt,
	\ myUnsignedHex,
	\ myFloat,
	\ myOct

syn cluster myParenBlocks contains=
	\ myParenBlock,
	\ myParenBlockInThunk


" Note:  This cluster contains every syntax class that has to be
" contained in other syntax classes.
syn cluster myNotTop contains=
	\ myTabError " tab errors can only occur in strings, etc.


"==============================================================
" Keywords
"--------------------------------------------------------------

" Potentially context-sensitive
if !exists("my_expensive")

	syn keyword myKeyword	abstype also and as case class elif
	syn keyword myKeyword	else end eqtype esac except fi
	syn keyword myKeyword	fn for fprintf generic_api
	syn keyword myKeyword	herein if include lazy method
	syn keyword myKeyword	my or overload printf
	syn keyword myKeyword	rec sharing sprintf stipulate
	syn keyword myKeyword	sharing stipulate
	syn keyword myKeyword	val where with withtype

	" alternate highlighting rules for these keywords
	syn keyword myDefine	api package fun

else

	syn keyword myKeyword	abstype also and as class class2
	syn keyword myKeyword	eqtype
	syn match myKeyword	"for"
	syn keyword myKeyword	include
	syn keyword myKeyword	or
	syn keyword myKeyword	sharing
	syn keyword myKeyword	with withtype
	syn keyword mySpecialFunc	printf sprintf fprintf

endif


syn match myKeyChar	";"
syn match myKeyChar	"="
syn match myKeyChar	"=>"

""" Comma
" Note: The comma keyword can only occur inside: "", '', #[], [], (), {}
syn match myCommaError	","
syn match myCommaError	",\%(\_s*,\)\+" contained containedin=ALL

syn match myKeyChar	"," contained containedin=
	\ myParenBlock,
	\ myBraceBlock,
	\ myList,
	\ myVector


" Potentially context-sensitive
if !exists("my_expensive")

	syn match myKeyChar	":"
	syn match myKeyChar	"|"
	syn match myKeyChar	"_" contained containedin=@myParenBlocks

endif


"==============================================================
" Comments and Documentation
"--------------------------------------------------------------

syn keyword myTodo contained containedin=@myComments
	\ TODO FIXME NOTE XXX OPTIMISE OPTIMIZE

syn match myOnelineComment contains=myTodo
	\ "#\%(#\|!\|\s\+\).*\|#$"

syn match mySharpBang
	\ "\%^#!.*"

syn region myMultilineComment fold
	\ contains=myTodo,
	\          myMultilineComment
	\ start="/\*"
	\ end="\*/"


"==============================================================
" Lowercase Identifiers
" Used In:	value, function and package name
" Note:		lower_case
"--------------------------------------------------------------

let s:LowercaseId = "[a-z][_'a-z0-9]*"
execute "syn match myLowercaseName contains=NONE" .
	\ ' "' . s:LowercaseId . '"'

execute "syn match myPackageName" .
	\ ' "' . s:LowercaseId . '\%(::\)\@="'

execute "syn match myPackageColonColon " .
	\ ' "\%(' . s:LowercaseId . '\)\@<=::"'

""" my / val
syn match myError	"\<my\>"
syn match myError	"\<val\>"
syn match myKeyword	"\%(\%(my\|val\)\_s*\)\@<!my\>"
syn match myKeyword	"\%(\%(my\|val\)\_s*\)\@<!val\>"


""" Identifier Error
syn match myIdentifierError contains=NONE
	\ "[a-z][_'a-z0-9]*[A-Z][_'a-zA-Z0-9]*"

syn match myIdentifierError contains=NONE
	\ "_[a-z][_'a-z0-9]*"


"==============================================================
" Fixity Declarations
" Example:	infix  val a;
" Example:	infixr  my b;
" Example:	nonfix  my (+++);
"--------------------------------------------------------------

syn region myFixityDeclaration transparent
	\ matchgroup=myFixity
	\ start="\<\%(infixr\|infix\|nonfix\)\%(\_s\+\%(val\|my\)\>\)\@="
	\ skip="\_s\+"
	\ matchgroup=myKeyword
	\ end="\%(val\|my\)\>"


"==============================================================
" Raising Exceptions
" Example:	raise exception ABC "hihihi";
"--------------------------------------------------------------

syn match myException	"\<exception\>"

syn region myRaiseException transparent
	\ matchgroup=myRaise
	\ start="\<raise\_s\+\%(exception\)\@="
	\ skip="\_s\+"
	\ matchgroup=myKeyword
	\ end="exception\>"


"==============================================================
" Type variable
" Note:		must precede "myType"
"--------------------------------------------------------------

syn match myTypeVariable
	\ contains=myTypeVariable
	\ "_\?[A-Z][0-9]*'*\%([A-Z]\)\@!"

syn match myTypeVariable
	\ contains=myTypeVariable
	\ "[A-Z]\%(_[a-z][a-z'_0-9]*\)\{0,1}\%([A-Z]\)\@!"

" TODO: put it in "myNotTop" when the region/match "myTypeDecl" is implemented.
syn match myArrow
	\ contained
	\ containedin=myTypeDecl
	\ "->"


"==============================================================
" Value constructor
" Used In:	Constructor, exception names
" Note:		UPPER_CASE
"--------------------------------------------------------------

let s:UppercaseId = "[A-Z]['_0-9]*[A-Z][A-Z'_0-9]*"
execute "syn match myConstructor" .
	\ ' "' . s:UppercaseId . '"'


"==============================================================
" Type constructor
" Used In:	Type and API (signature) names
" Note:		Mixed_Case
" Note:		MUST supercede both lower_case & UPPER_CASE !!!
"--------------------------------------------------------------

let s:MixedcaseId = "[A-Z]\\%(\\%(_[A-Z'_0-9]\\|[A-Z'0-9]\\)[A-Za-z'_0-9]*\\)\\?[a-z][A-Za-z'_0-9]*"
execute "syn match myTypeOrApiName" .
	\ ' "' . s:MixedcaseId . '"'


"==============================================================
" Normal String, Shell Command and Character
"--------------------------------------------------------------

function! s:MakeStringsEscapeId( delim )
	let delim = a:delim
	return
		\ '\\\%(\\\|\^[@A-F\[\\\]^_?]\|[' .
		\ delim .
		\ 'abfnrtv]\|[01]\d\d\|2\%([0-4]\d\|5[0-5]\)\)'
endfunc

""" String
" Note: Mythryl doesn't allow tab characters in strings...
execute 'syn match myStringEscape contained containedin=myString'
	\ ' +' . s:MakeStringsEscapeId( "\"" ) . '+'

syn match myStringEscape contained containedin=myString
	\ +\\$+

syn match myStringEscape contained containedin=myString
	\ +^\_s*\\+

syn region myString fold contains=myStringEscape
	\ matchgroup=myStringDelimiter
	\ start="\""
	\ skip="\\\\\|\\\""
	\ end="\""

syn match myTabError contained containedin=myString,myChar +\t+

""" Shell
syn region myString fold contains=myStringEscape
	\ matchgroup=myStringDelimiter
	\ start="`"
	\ skip="\\\\\|\\`"
	\ end="`"


""" Character
let s:CharEscapeId = s:MakeStringsEscapeId( '''' )
execute 'syn match myCharEscape contained containedin=myChar' .
	\ ' +' . s:CharEscapeId . '+'

syn match myCharError	+'[^']*'+

execute 'syn region myChar contains=myCharEscape' .
	\ ' matchgroup=myCharDelimiter' .
	\ ' start=+''\%(\%(.\|' . s:CharEscapeId . '\)''\)\@=+' .
	\ ' skip=+\\\\\|\\''+' .
	\ " end=+'+"


"==============================================================
" Numbers
"--------------------------------------------------------------

syn match myInt		"-\?\d\+"
syn match myUnsignedInt	"-\?0u\d\+"
syn match myHex		"-\?0x[0-9a-fA-F]\+"
syn match myUnsignedHex	"-\?0ux[0-9a-fA-F]\+"
syn match myFloat	"-\?\d\+\%(\.\d\+\)\?\%([eE]-\?\d\+\)\?"
syn match myOct		"-\?0[0-7]\+"


"==============================================================
" Various Block-level Delimiters
"--------------------------------------------------------------

syn region myParenBlock transparent skipwhite skipnl
	\ contains=ALLBUT,@myNotTop
	\ matchgroup=myParen
	\ start="(" skip="\\\\\|\\)" end=")"

syn region myBraceBlock	transparent skipwhite skipnl
	\ contains=ALLBUT,@myNotTop
	\ matchgroup=myBrace
	\ start=+{\_s+rs=e-1
	\ start=+\%([A-Z]\{2,}\)\@<={+
	\ end=+}+

""" Note: dotdotdot inside braces only
syn match myDotdotdotError	"\.\.\.\%(\_s*,\)*"
syn match myDotdotdot contained containedin=myBraceBlock
	\ "\%(,\_s*\)\@<=\.\.\."

syn region myList transparent
	\ contains=ALLBUT,@myNotTop
	\ matchgroup=mySquareBracket
	\ start=+\[+ skip=+\\\\\|\\]+ end=+\]+

syn region myVector transparent
	\ contains=ALLBUT,@myNotTop
	\ matchgroup=myVectorBracket
	\ start=+#\[+ skip=+\\\\\|\\]+ end=+\]+

syn region myThunk fold
	\ contains=ALLBUT,@myNotTop
	\ matchgroup=myThunkBrace
	\ start="\.{" skip="\\\\\|\\}" end="}"


"==============================================================
" Miscellaneous Modifiers
"--------------------------------------------------------------

syn region myPackageGenericity transparent
	\ matchgroup=myDefine
	\ start="\<generic\%(\_s\+package\>\)\@="
	\ skip="\_s\+"
	\ matchgroup=NONE
	\ end="\%(package\>\)\@="


"==============================================================
" Vim Syntax Synchronisation
" Note:		Umm, I don't really understand syncing...
"--------------------------------------------------------------

" syn sync minlines=500 linebreaks=500
syn sync match myBraceSync grouphere myBraceBlock "\<{\>"
syn sync match myBraceSync groupthere NONE "\<}\>"

syn sync match myParenSync grouphere myParenBlock "\<(\>"
syn sync match myParenSync groupthere NONE "\<)\>"


"==============================================================
" Highlighting commands
"--------------------------------------------------------------
" Define the default highlighting.
" For version 5.7 and earlier: only when not done already
" For version 5.8 and later: only when an item doesn't have highlighting yet
if version >= 508 || !exists("did_my_syntax_inits")
	if version < 508
		let did_my_syntax_inits = 1
		command -nargs=+ HL hi link <args>
	else
		command -nargs=+ HL hi def link <args>
	endif

	""" Keywords
	HL myKeyword		Keyword
	HL myDotdotdot		Keyword
	HL mySpecialFunc	Keyword

	HL myKeyChar		Keyword
	HL myDefine		Define
	HL myFixity		Define
	HL myException		Define
	HL myRaise		Operator
	HL myArrow		Define

	""" Comment
	HL myOnelineComment	myComment
	HL myMultilineComment	myComment
	HL myComment		Comment
	HL mySharpBang		Preproc
	HL myTodo		Todo

	""" Various block-level delimiters
	if !exists("my_no_highlight_brackets")
	HL myBrace		Label
	HL myParen		Label
	HL mySquareBracket	Label
	endif
	HL myThunkBrace		Identifier
	HL myVectorBracket	Delimiter

	""" Identifiers
	if exists("my_highlight_all_lowercase_id")
	HL myLowercaseName	Function
	endif

	HL myPackageName	Identifier
	HL myPackageColonColon	Special

	HL myConstructor	String
	HL myTypeOrApiName	Type
	HL myTypeVariable	Special

	""" String, regexp, char
	HL myString		String
	HL myStringDelimiter	Delimiter
	HL myStringEscape	Special

	HL myChar		String
	HL myCharDelimiter	Label
	HL myCharEscape		Special

	""" Numbers
	HL myInt		myNumber
	HL myUnsignedInt	myNumber
	HL myHex		myNumber
	HL myUnsignedHex	myNumber
	HL myFloat		myNumber
	HL myOct		myNumber
	HL myNumber		Number

	""" Errors
	HL myIdentifierError	myError
	HL myDotdotdotError	myError
	HL myTabError		myError
	HL myCharError		myError
	HL myCommaError		myError
	HL myError		Error

	delcommand HL
endif

let b:current_syntax = "mythryl"

" vim: ts=8
