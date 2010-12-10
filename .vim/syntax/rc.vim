" Vim syntax file
" Language:     rc
" Maintainer:   Andy Spencer <andy753421@gmail.com>, 
" Weakish Jiang <weakish@gmail.com>
" Last Change:  2009-12-26 

"Credits
"""""""""""""
" Most of the work is done by Andy.  I have only made some minor changes:
" * make this syntax highlight works with Byron Rakitzis' reimplementation.
" * edit rcHereDoc match pattern to get <<EOF >output highlighted correctly.
" -- weakish
"
"Info
""""""""""
"
" This syntax file works with both Byron Rakitzis' reimplementation and
" plan9port's implementation.  
" (There is a tradeoff: less powerful `(ba)sh like substitution` syntax
" error detection. For a pure syntax file" for p9p, see:
" http://lug.rose-hulman.edu/svn/misc/trunk/config/spenceal/vim/ )
"
"Usage
"""""""""""
" Copy rc.vim to ~/.vim/syntax/rc.vim
" or c:\program files\vim\vimfiles\syntax\rc.vim (if you are on Windows)
" (Optional) Add this line in your .vimrc:
" au BufRead,BufNewFile *.rc set filetype=rc
"
"Other Tips
""""""""""""""
" If you want to use rc shell as the embedded shell in vim,
" you may add these lines to your .vimrc:
" set shell=/usr/bin/rc\ -l
" " or /bin/rc or /usr/local/bin/rc or /opt/local/bin/rc, etc
" set shellcmdflag=-c
" set shellpipe=>[2=1]\|\ tee
" set shellredir=>%s\ >[2=1]
" (This syntax is for Byron R's rc, p9p rc may differ.)
"
"Bug Report
""""""""""""""
" http://bitbucket.org/weakish/weakishscripts/issues/
"Hack
""""""""""""""
" A test file is available at
" http://bitbucket.org/weakish/weakishscripts/src/tip/test.rc

" For version 5.x: Clear all syntax items
" For version 6.x: Quit when a syntax file was already loaded
if version < 600
  syntax clear
elseif exists("b:current_syntax")
  finish
endif

" I'm lazy, if someone knows how to do proper syncing, they can fix this
" Rc script should be small anyway..
syn sync fromstart


" Based on the sections of rc(1)

"Top levels
"""""""""""
" Ignore valid start/ends for now
" List = top level
syn cluster rcList contains=@rcSimple,@rcArgument,@rcRedirect,@rcCompound

"Command Lines
""""""""""""""
syn cluster rcSimple   contains=rcTermin,rcContinue,rcComment

syn match   rcTermin    "[;&]"
syn match   rcContinue "\\$"
syn match   rcComment  "#.*"


"Arguments and Variables
""""""""""""""""""""""""
" Arguments should be proceeded by additional arguments, not commands, etc
syn cluster rcArgument   contains=@rcBuiltins,@rcArgument2
syn cluster rcArgument2  contains=rcWord,@rcSimple,rcNumber,rcPattern,rcQuoted,rcSubQuote,rcParens,rcVar,rcSubst,rcSub,rcJoin

syn match   rcWord       "[^#;&|^$=`'{}()<>\[\] \t\r]"               skipwhite nextgroup=@rcArgument2


syn match   rcNumber     "\<\d\+\>"                         skipwhite nextgroup=@rcArgument2

syn match   rcPattern    "[*?]"                             skipwhite nextgroup=@rcArgument2
syn region  rcPattern    matchgroup=rcOperator   start="\[" skip="\\\]" end="\]" skipwhite nextgroup=@rcArgument2 keepend contains=rcPatternBdy,
syn match   rcPatternBdy ".*"                               contained contains=rcPatternKey
syn match   rcPatternKey "\[\@<=\~\|[^\[]\zs-\ze[^\]]"      contained " ? and - in [?..] [a-c]

syn region  rcQuoted     matchgroup=rcQuoted     start="'"  skip="''" end="'"       skipwhite nextgroup=@rcArgument2 contains=rcQuote
syn match   rcQuote      "''"                               contained

syn region  rcParens     matchgroup=rcOperator   start="(" end=")" skipwhite nextgroup=@rcArgument2 contains=@rcArgument

syn match   rcVar        "\$[^ \t(]\w*"                      skipwhite nextgroup=rcVarList,@rcArgument2 contains=rcVarSpecial
syn match   rcVar        "\$[#"^]\S\w*\ze[^(]"               skipwhite nextgroup=@rcArgument2 contains=rcVarOper,rcVarSPecial
syn region  rcVarList    matchgroup=rcIdentifier start="(" end=")" skipwhite nextgroup=@rcArgument2 contains=@rcArgument contained
syn match   rcVarOper    +[#"^]+                             contained
syn match   rcVarSpecial "\v\$?<(home|ifs|path|pid|prompt|status|contained)>" contained
" Todo: Make error for $"foo(

syn region  rcSubst      matchgroup=rcInclude    start="[`<>]{" end="}" skipwhite nextgroup=@rcArgument2 contains=@rcList
syn region  rcSubst      matchgroup=rcInclude    start="`(" end=")" skipwhite nextgroup=@rcArgument2 contains=@rcArgument
syn match   rcSub        "`\<\S\+\>"     
syn match   rcJoin       "\^"                               skipwhite nextgroup=@rcArgument2 contains=rcError
syn match   rcError      "\v(^|\^)\s*\^|\^\ze\s*($|#|;|\^)" skipwhite nextgroup=@rcArgument2
" Todo: Error on ^$


"I/O Redirection
""""""""""""""""
syn cluster rcRedirect  contains=rcRedir,rcHereDoc

syn match   rcRedir     "[<>]\v(\[\d+\=?\d*])?\ze([^{]|$)"  skipwhite nextgroup=@rcArgument contains=rcNumber
syn match   rcRedir     ">>"                                skipwhite nextgroup=@rcArgument

syn region  rcHereDoc   matchgroup=rcOperator    start="<<\z([^<> ]\+\)"   end="^\z1$" contains=rcVar
syn region  rcHereDoc   matchgroup=rcOperator    start="<<'\z(.*\)'" end="^\z1$"
" Todo: what's with ^'s in here docs?
" Todo: <<'>' >output or <<' 'EOF >output still doesn't get highlighted
" correct, but I guess peopel are unlikely to write such scripts. 

"Compound Commands
""""""""""""""""""
" Todo: What to do when only one command is accepted, e.g. while() <command>
syn cluster rcCompound   contains=rcPipe,rcLogical,rcInverted,rcSubShell,rcIf,rcIfNot,rcElse,rcFor,rcWhile,rcSwitch,rcBrace,rcFunction,rcAssign

syn match   rcPipe       "|\v(\[\d+(\=\d+)?])?"                                contains=rcNumber
syn match   rcLogical    "\(&&\|||\)"

syn region  rcIf         matchgroup=rcConditional start="if\s*("   end=")"     contains=@rcList
syn match   rcIfNot      "\<if\s\+not\>"
" Todo: error on if(..) <command> <command> if not
"       use: matchgroup=rcIfNot end="if not"?
syn match   rcElse       "\<else\>" 

syn region  rcFor        matchgroup=rcRepeat      start="for\s*("   end=")"    contains=rcForIn,@rcArgument

syn keyword rcForIn      in                                                    contained
" Todo: for(in)

syn region  rcWhile      matchgroup=rcRepeat      start="while\s*(" end=")"    contains=@rcList

syn region  rcSwitch     matchgroup=rcConditional start="switch\s*(" end=")"   skipwhite nextgroup=rcSwitchBody contains=@rcArgument
syn region  rcSwitchBody matchgroup=rcConditional start="{"         end="}"    contains=@rcList,rcSwitchCase
syn keyword rcSwitchCase case                                                  contained

syn region  rcBrace      matchgroup=rcOperator    start="{"         end="}"    contains=@rcList

syn match   rcFunction   "\v<fn\s+\w+>"                                        contains=rcNote skipwhite nextgroup=rcFnBody
syn region  rcFnBody     matchgroup=rcFunction    start="{"         end="}"    contained contains=rcNote,@rcList
syn keyword rcNote       sighup sigint sigalrm sigexit return                         contained

syn match   rcAssign     "\w\+\ze\s*="                                         skipwhite nextgroup=@rcArgument contains=rcVarSpecial

"Built-in Commands
""""""""""""""""""
" Todo: only at the beginning of the command
syn cluster rcBuiltins contains=rcPrefixes,rcBuiltinMatch,rcBuiltinKeyword,coreutils,p9putils
syn match   rcPrefixes       "[!@]"
syn match   rcBuiltinMatch   skipwhite nextgroup=@rcArgument2 "[.~]"
syn keyword rcBuiltinKeyword skipwhite nextgroup=@rcArgument2 break builtin cd echo eval exec exit flag limit newpgrp rfork shift umask wait whatis 
syn keyword coreutils        skipwhite nextgroup=@rcArgument2 dd cp df du ln ls mv rm tr wc cat dir cut env pwd seq tty yes date echo expr head tail sort stty sync true vdir dirname chgrp chmod chown false mkdir mknod rmdir sleep touch uname chroot mkfifo mktemp readlink basename DIR_COLORS du id nl od pr tr wc dir cut env fmt ptx seq tac tee sum tty who yes arch comm expr fold head join link nice shuf tail sort test stat uniq vdir unexpand dirname chcon cksum nohup paste pinky shred sleep split touch tsort uname users sha1sum truncate logname base64 timeout chroot csplit factor expand hostid md5sum sha224sum sha256sum mkfifo mktemp sha384sum sha512sum printf runcon stdbuf unlink whoami printenv pathchk dircolors readlink install basename
syn keyword p9putils         skipwhite nextgroup=@rcArgument2 9 B E g p u 9a 9c 9l 9p bc cb db dc dd ed du lc mc ls mk pr ps rc rm tr wc xd 9ar 9fs awd awk cal cat bmp cmp dns eqn fmt gif hoc ico img jpg lex man pbd pic png ppm psu psv rio sam sed seq sig tar tbl tcs tee src srv sum vac web win zip yuv troff2png dnsquery Mail acid acme date comm core crop dial dict diff echo file freq grap hget grep hist gzip ipso join kill mapd look news nobs page plot read scat slay tail sort test time stop tpic tref vcat uniq vnfs yacc cmapcube secstored troff2html sftpcache delatex cleanname devdraw Getdir 9term 9660srv factotum disknfs adict ascii astro bzip2 fsize graph gview iconv idiff resample label mkdir mount mtime nroff plumb proof ramfs sleep spell split sprog stack start stats togif toico topng toppm touch troff vacfs tweak units unvac unutf unzip usage wmail netfileget netfileput doctype acidtypes htmlroff samsave samterm dsa2pub dsa2ssh secuser ndbmkhash sha1sum rsa2csr rsa2pub rsa2ssh rsafill listen1 ndbipquery ndbquery auxstats snarfer lookman tcolors Netfiles calendar aescbc codereview strings bundle colors deroff dnstcp dsagen factor fontsrv ndbmkdb fortune tr2post getflags gunzip import secstore pemdecode md5sum mk9660 pemencode netkey passwd vbackup primes psdownload unicode unmount rsagen vmount vwhois xshove acmeevent yesterday vmount0 ndbmkhosts asn12dsa asn12rsa statusbar htmlfmt netfilestat auxclog wintext rsa2x509 9pfuse readcons plumber basename 9pserve dump9660 namespace bunzip2 psfonts dnsdebug

" Misc
""""""
syn region rcSubQuote matchgroup=rcQuoted start="rc\s\+-c\s*'"hs=e-1 skip="''" end="'" skipwhite nextgroup=@rcArgument2 contains=rcQuote,@rcList

"Errors
"""""""
syn match rcError "[\]})]"
syn match rcError "\$(.\{-})\|\${.\{-}}\|\d\+>\(&\d\+\)\?\|`[^{]\{-}`\s\|{.*,.*}"

" Ignore bash
" Bad ${}, 2>&1, `foo`,
" TODO: {foo,bar}.txt (use: (foo bar)^.txt
"       {foo; bar} is ok
"       $() is for variables

" Highlighting
hi def link rcTermin         Operator
hi def link rcContinue       Operator
hi def link rcComment        Comment
"Arguments and Variables     
hi def link rcNumber         Number
hi def link rcPattern        PreProc
hi def link rcQuoted         String
hi def link rcQuote          Delimiter
hi def link rcVar            Identifier
hi def link rcVarOper        SpecialChar
hi def link rcVarSpecial     Keyword
hi def link rcJoin           Special
"I/O Redirection             
hi def link rcRedir          Operator
hi def link rcHereDoc        String
"Compound Commands           
hi def link rcPipe           Operator
hi def link rcLogical        Operator
hi def link rcIfNot          Conditional
hi def link rcElse           Conditional
hi def link rcNote           Keyword
hi def link rcAssign         Identifier
hi def link rcPrefixes       Macro     
"Built-in Commands           
hi def link rcBuiltinKeyword Keyword
hi def link rcBuiltinMatch   Keyword
hi def link coreutils        Keyword
hi def link p9putils         Keyword

" Ends of regions
hi def link rcIdentifier     Identifier
hi def link rcPreProc        PreProc
hi def link rcInclude        Include
hi def link rcSub            Include
hi def link rcKeyword        Keyword
hi def link rcOperator       Operator
hi def link rcRepeat         Repeat
hi def link rcConditional    Conditional
hi def link rcFunction       Function

" Specials inside regions
hi def link rcForIn          Keyword
hi def link rcSwitchCase     Label
hi def link rcPatternKey     SpecialChar

" Errors
hi def link rcError          Error

let b:current_syntax = "rc"
