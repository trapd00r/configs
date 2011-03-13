
fun! s:get_pkg_comp_start()
  return searchpos( '[^a-zA-Z0-9:_]' , 'bn' , line('.') )
endf

fun! s:get_pkg_comp_base()
  let col = col('.')
  let [ lnum , coln ] = s:get_pkg_comp_start()
  let line = getline('.')
  return strpart( getline('.') , coln , col )
endf


fun! CompleteInstalledCPANModuleList()
  cal PrepareInstalledCPANModuleCache()
  let start_pos = s:get_pkg_comp_start()
  let base      = s:get_pkg_comp_base()
  call s:echo( "filtering..." )
  " let res = filter( copy( g:cpan_installed_pkgs ) , 'v:val =~ "' . base . '"' )
  let res = []
  for p in g:cpan_installed_pkgs 
    if p =~ '^' . base 
      call insert( res , p )
    endif
  endfor
  call complete( start_pos[1]+1 , res )
  return ''
endf

fun! CompleteCPANModuleList()
  if len( g:cpan_pkgs ) == 0 
    cal s:echo("preparing cpan module list...")
    let g:cpan_pkgs = g:get_cpan_module_list(0)
    cal s:echo("done")
  endif
  let start_pos  = s:get_pkg_comp_start()
  let base = s:get_pkg_comp_base()
  cal s:echo("filtering")
  let res = filter( copy( g:cpan_pkgs ) , 'v:val =~ "' . base . '"' )
  cal complete( start_pos[1]+1 , res )
  return ''
endf




" inoremap <C-x><C-m>  <C-R>=CompleteCPANModuleList()<CR>
" inoremap <C-x><C-m>                 <C-R>=CompleteInstalledCPANModuleList()<CR>
" nnoremap <silent> <C-c><C-m>        :OpenCPANWindowS<CR>
" nnoremap <silent> <C-c><C-v>        :OpenCPANWindowSV<CR>
" nnoremap <C-x><C-i>        :call libperl#install_module()<CR>
" nnoremap <C-c>g            :call libperl#tab_open_module_from_cursor()<CR>
