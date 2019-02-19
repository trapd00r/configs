" vim:sw=2:cc&:smc&:fdm=marker:fmr="<,">:fdls=1:fdl=0:fml=2:fen:et:
"    File: $HOME/etc/vim/nancy/090-syntax.vim
"  Author: Magnus Woldrich <m@japh.se>
" Updated: 2016-09-16 08:19:13


"hi! clear
"hi Normal ctermfg=fg ctermbg=bg cterm=bolditalic
"< debsources 
hi debsourcesDistrKeyword ctermfg=208
hi debsourcesUri          ctermfg=032
">
"< vim
hi Error             ctermfg=089  ctermbg=250  cterm=bolditalicreverse
hi Search            ctermfg=197  ctermbg=053  cterm=none
hi Visual            ctermfg=197  ctermbg=053  cterm=reverse
hi IncSearch         ctermfg=053  ctermbg=197  cterm=bolditalic
hi CursorLine        ctermfg=none ctermbg=234
hi ColorColumn       ctermfg=231  ctermbg=234  cterm=none
hi link ColorColumn  CursorLine
hi CursorColumn      ctermfg=fg   ctermbg=234  cterm=none       term=bold
hi FoldColumn        ctermfg=031  ctermbg=233   cterm=italicbold term=bold
hi Folded            ctermfg=248  ctermbg=bg   cterm=italic      term=bold
hi LineNr            ctermfg=145  ctermbg=234   cterm=italic      term=none
hi Statement                                  cterm=italic      term=bold
hi CursorLineNr      ctermfg=232 ctermbg=160   cterm=bolditalic term=bold
hi vimSet                                     cterm=italic      term=bold
hi vimSetEqual       ctermfg=015              cterm=none        term=none
hi vimSetMod         ctermfg=160              cterm=bolditalic  term=none
hi vimSetSep         ctermfg=161              cterm=none        term=none
hi vimHiKeyList      ctermfg=fg  ctermbg=bg   cterm=none        term=none
hi vimFgBgAttrib     ctermfg=fg  ctermbg=bg   cterm=none        term=none
hi vimFgBg           ctermfg=fg  ctermbg=bg   cterm=none        term=none
hi vimCmdSep         ctermfg=179 ctermbg=bg   cterm=none        term=none
"hi vimHiAttrib       ctermfg=220 ctermbg=bg   cterm=none        term=none
"hi vimHiAttribList   ctermfg=220 ctermbg=bg   cterm=none        term=none
"hi vimNumber      xxx cterm=bold ctermfg=33
hi VimSynMtchCchar   ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimAuSyntax       ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimAugroup        ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimAugroupError   ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimAutoCmdSfxList ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimAutoCmdSpace   ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimAutoEventList  ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimClusterName    ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimCollClass      ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimCollection     ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimCommentTitle   ctermfg=218 ctermbg=bg  cterm=bold     term=bold
hi vimEcho           ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimEscapeBrace    ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimExecute        ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimExtCmd         ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimFBVar          ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimFiletype       ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimFilter         ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimFuncBlank      ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimFuncBody       ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimFunction       ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimGroupList      ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimGroupName      ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimHiBang         ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimHiClear        ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimHiCtermColor   ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimHiFontname     ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimHiGuiFontname  ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimHiLink         ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimIf             ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimIsCommand      ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimMapLhs         ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimMapRhs         ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimMapRhsExtend   ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimMenuBang       ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimMenuMap        ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimMenuPriority   ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimMenuRhs        ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimNormCmds       ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimOperParen      ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimPatRegion      ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimRegion         ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimSubstPat       ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimSubstRange     ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimSubstRep       ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimSubstRep4      ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimSynKeyRegion   ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimSynLine        ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimSynMatchRegion ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimSynPatMod      ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimSynRegion      ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimSyncLinebreak  ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimSyncLinecont   ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimSyncLines      ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimSyncMatch      ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimSyncRegion     ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimUserCmd        ctermfg=fg  ctermbg=bg  cterm=none     term=none
hi vimVar            ctermfg=fg  ctermbg=bg  cterm=none     term=none
"hi vimHiCTerm     xxx ctermfg=1
"hi vimHiTermcap   xxx cleared
"hi vimCommentTitleLeader xxx cleared
"hi vimGlobal      xxx cleared
"hi vimAugroupSyncA xxx cleared
"hi vimComment     xxx links to Comment
"hi vimScriptDelim xxx links to Comment
"hi vimParenSep    xxx links to Delimiter
"hi vimSep         xxx links to Delimiter
"hi vimSubstDelim  xxx links to Delimiter
"hi vimBracket     xxx links to Delimiter
"hi vimOperError   xxx links to Error
"hi vimUserCmdError xxx links to Error
"hi vimElseIfErr   xxx links to Error
"hi vimSynError    xxx links to Error
"hi vimSyncError   xxx links to Error
"hi vimError       xxx links to Error
"hi vimFold        xxx links to Folded
"hi vimFuncName    xxx links to Function
"hi vimSpecFile    xxx links to Identifier
"hi vimFuncVar     xxx links to Identifier
"hi vimUserFunc    xxx links to Normal
"hi vimMark        xxx links to Number
"hi vimOper        xxx links to Operator
"hi vimOption      xxx links to PreProc
"hi vimEnvvar      xxx links to PreProc
"hi vimMenuName    xxx links to PreProc
"hi vimHLMod       xxx links to PreProc
"hi vimNotation    xxx links to Special
"hi vimContinue    xxx links to Special
"hi vimFuncSID     xxx links to Special
"hi vimUserAttrbCmpltFunc xxx links to Special
"hi vimSubstFlags  xxx links to Special
"hi vimGroupSpecial xxx links to Special
"hi vimSynOption   xxx links to Special
"hi vimRegister    xxx links to SpecialChar
"hi vimCmplxRepeat xxx links to SpecialChar
"hi vimCtrlChar    xxx links to SpecialChar
"hi vimPatSep      xxx links to SpecialChar
"hi vimSubstSubstr xxx links to SpecialChar
"hi vimCommand     xxx links to Statement
"hi vimSearchDelim xxx links to Statement
"hi vimKeyword     xxx links to Statement
"hi vimStatement   xxx links to Statement
"hi vimString      xxx links to String
"hi vimTodo        xxx links to Todo
"hi vimAutoEvent   xxx links to Type
"hi vimGroup       xxx links to Type
"hi vimPattern     xxx links to Type
"hi vimSynCase     xxx links to Type
"hi vimSynReg      xxx links to Type
"hi vimSyncC       xxx links to Type
"hi vimSyncKey     xxx links to Type
"hi vimSyncNone    xxx links to Type
"hi vimHiTerm      xxx links to Type
"hi vimSpecial     xxx links to Type
"hi vimWarn        xxx links to WarningMsg
"hi vimBehaveModel xxx links to vimBehave
"hi vimMapMod      xxx links to vimBracket
"hi vimAutoCmd     xxx links to vimCommand
"hi vimLet         xxx links to vimCommand
"hi vimMap         xxx links to vimCommand
"hi vimSyntax      xxx links to vimCommand
"hi vimBehave      xxx links to vimCommand
"hi vimFTCmd       xxx links to vimCommand
"hi vimSubst       xxx links to vimCommand
"hi vimAugroupKey  xxx links to vimCommand
"hi vimFuncKey     xxx links to vimCommand
"hi vimAbb         xxx links to vimCommand
"hi vimEchoHL      xxx links to vimCommand
"hi vimHighlight   xxx links to vimCommand
"hi vimNorm        xxx links to vimCommand
"hi vimNotFunc     xxx links to vimCommand
"hi vimUserCommand xxx links to vimCommand
"hi vimMapBang     xxx links to vimCommand
"hi vimAutoSet     xxx links to vimCommand
"hi vimCondHL      xxx links to vimCommand
"hi vimLineComment xxx links to vimComment
"hi vimMtchComment xxx links to vimComment
"hi vimElseif      xxx links to vimCondHL
"hi vimErrSetting  xxx links to vimError
"hi vimBehaveError xxx links to vimError
"hi vimFTError     xxx links to vimError
"hi vimFunctionError xxx links to vimError
"hi vimFunc        xxx links to vimError
"hi vimSubstFlagErr xxx links to vimError
"hi vimCollClassErr xxx links to vimError
"hi vimMapModErr   xxx links to vimError
"hi vimSynCaseError xxx links to vimError
"hi vimHiCtermError xxx links to vimError
"hi vimHiKeyError  xxx links to vimError
"hi vimEmbedError  xxx links to vimError
"hi vimKeyCodeError xxx links to vimError
"hi vimMapModKey   xxx links to vimFuncSID
"hi vimHLGroup     xxx links to vimGroup
"hi vimEchoHLNone  xxx links to vimGroup
"hi vimSyncGroupName xxx links to vimGroupName
"hi vimSyncGroup   xxx links to vimGroupName
"hi vimHiGroup     xxx links to vimGroupName
"hi vimFgBgAttrib  xxx links to vimHiAttrib
"hi vimHiStartStop xxx links to vimHiTerm
"hi vimHiCtermFgBg xxx links to vimHiTerm
"hi vimHiGui       xxx links to vimHiTerm
"hi vimHiGuiFont   xxx links to vimHiTerm
"hi vimHiGuiFgBg   xxx links to vimHiTerm
"hi vimAuHighlight xxx links to vimHighlight
"hi vimUnmap       xxx links to vimMap
"hi vimMenuMod     xxx links to vimMapMod
"hi vimAddress     xxx links to vimMark
"hi vimPlainMark   xxx links to vimMark
"hi vimMenuNameMore xxx links to vimMenuName
"hi vimMarkNumber  xxx links to vimNumber
"hi vimHiGuiRgb    xxx links to vimNumber
"hi vimUserAttrbKey xxx links to vimOption
"hi vimAutoCmdOpt  xxx links to vimOption
"hi vimPatSepErr   xxx links to vimPatSep
"hi vimPatSepZ     xxx links to vimPatSep
"hi vimPatSepR     xxx links to vimPatSep
"hi vimPlainRegister xxx links to vimRegister
"hi vimSpecFileMod xxx links to vimSpecFile
"hi vimKeyCode     xxx links to vimSpecFile
"hi vimUserAttrb   xxx links to vimSpecial
"hi vimUserAttrbCmplt xxx links to vimSpecial
"hi vimSynType     xxx links to vimSpecial
"hi vimInsert      xxx links to vimString
"hi vimSetString   xxx links to vimString
"hi vimCommentString xxx links to vimString
"hi vimPatSepZone  xxx links to vimString
"hi vimNotPatSep   xxx links to vimString
"hi vimStringCont  xxx links to vimString
"hi vimSubstTwoBS  xxx links to vimString
"hi vimSynRegPat   xxx links to vimString
"hi vimSynPatRange xxx links to vimString
"hi vimSearch      xxx links to vimString
"hi vimSubst1      xxx links to vimSubst
"hi vimSynKeyContainedin xxx links to vimSynContains
"hi vimSynContains xxx links to vimSynOption
"hi vimSynNextgroup xxx links to vimSynOption
"hi vimGroupAdd    xxx links to vimSynOption
"hi vimGroupRem    xxx links to vimSynOption
"hi vimSynKeyOpt   xxx links to vimSynOption
"hi vimSynMtchOpt  xxx links to vimSynOption
"hi vimSynRegOpt   xxx links to vimSynOption
"hi vimSynMtchGrp  xxx links to vimSynOption
"hi vimSynNotPatRange xxx links to vimSynRegPat
"hi vimFTOption    xxx links to vimSynType
"hi vimBufnrWarn   xxx links to vimWarn



"syn match wsEOL display '\v[ ]+$' conceal cchar=O
"hi wsEOL      ctermfg=196 ctermbg=none cterm=bold
">
"< vimperator
hi vimperatorSet ctermfg=102 ctermbg=bg cterm=none
"syn match wsEOL display '\v[ ]+$' conceal cchar=O
"hi wsEOL      ctermfg=196 ctermbg=none cterm=bold
">
"< sh
hi shDoubleQuote ctermfg=022 ctermbg=none cterm=bold
hi shFunctionOne ctermfg=230 ctermbg=bg   cterm=italic
hi shOption      ctermfg=208 ctermbg=bg   cterm=none
hi shVariable    ctermfg=208 ctermbg=bg   cterm=none
hi shOperator    ctermfg=085 ctermbg=none cterm=bold
hi shSingleQuote ctermfg=131 ctermbg=234  cterm=none
hi shString      ctermfg=137 ctermbg=234  cterm=none
hi shExprRegion  ctermfg=214 ctermbg=none cterm=bolditalic
hi shCommandSub  ctermfg=181 ctermbg=none cterm=none
hi link   shShellVariables Identifier

syn match shLogicalAnd '[&]\{2}'
hi link   shLogicalAnd shConditional
">
"< zsh
hi link zshVariableDef     Identifier
hi link zshOperator        Operator
hi      zshSubstDelim      ctermfg=125 ctermbg=none cterm=italicbold
hi      zshSubst           ctermfg=137 ctermbg=none cterm=italic
hi      zshStringDelimiter ctermfg=202 ctermbg=none cterm=italic
hi      zshNumber          ctermfg=033 ctermbg=none cterm=italicbold
hi      zshRedir           ctermfg=051 ctermbg=none cterm=bold
">
"< make
hi makeTarget   ctermfg=166 cterm=bold
hi makeCommands ctermfg=246
">
"< ncmpcpp
"syn match ncmpcppVar '\v^\w+'
"syn match ncmpcppStr '\v\s*\=\s*"\zs.+\ze"'
"
"syn match  ncmpcppComment '\v^\s*#.*$'
"syn region ncmpcppComment start=/#/ end=/\n/
"
"hi link ncmpcppVar     Identifier
"hi link ncmpcppStr     String
"hi link ncmpcppComment Comment
">
"< minesweeper
hi MineSweeperBomb   ctermbg=124 ctermfg=234 cterm=bold
hi MineSweeperField  ctermbg=234 ctermfg=234 cterm=italic
hi MineSweeperFlag   ctermbg=234 ctermfg=092 cterm=bold
hi MineSweeperStatus ctermbg=234 ctermfg=064 cterm=bold
hi MineSweeperHatena ctermbg=234 ctermfg=085 cterm=bold
hi MineSweeper0      ctermbg=236 ctermfg=242 cterm=none
hi MineSweeper1      ctermbg=234 ctermfg=022 cterm=none
hi MineSweeper2      ctermbg=234 ctermfg=160 cterm=none
hi MineSweeper3      ctermbg=234 ctermfg=197 cterm=bold
hi MineSweeper4      ctermbg=234 ctermfg=220 cterm=bold
">
"< perl
hi perlVarPlain ctermfg=10 cterm=none
">

hi markdownJekyllFrontMatter    ctermfg=137
hi markdownJekyllLiquidBlockTag ctermfg=197 cterm=italic

highlight GitGutterAdd    ctermfg=34 
highlight GitGutterChange ctermfg=198
highlight GitGutterDelete ctermfg=160
