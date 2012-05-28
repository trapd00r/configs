#!/usr/bin/zsh

setopt \
     aliases                \
  no_all_export             \
     always_last_prompt     \
  no_always_to_end          \
     append_history         \
  no_auto_continue          \
     auto_list              \
     auto_menu              \
  no_auto_name_dirs         \
  no_auto_param_keys        \
     auto_param_slash       \
     auto_pushd             \
     auto_remove_slash      \
  no_auto_resume            \
     autocd                 \
  no_bad_pattern            \
     bare_glob_qual         \
  no_bash_rematch           \
  no_bashautolist           \
  no_beep                   \
  no_bg_nice                \
     brace_ccl              \
     brace_expand           \
  no_bsd_echo               \
     c_bases                \
     case_glob              \
     case_match             \
  no_cdable_vars            \
  no_chase_dots             \
  no_chase_links            \
     check_jobs             \
  no_clobber                \
     complete_aliases       \
     complete_in_word       \
     correct                \
  no_correct_all            \
  no_csh_junkie_history     \
  no_csh_junkie_loops       \
  no_csh_junkie_quotes      \
  no_csh_nullcmd            \
  no_csh_nullglob           \
     debug_before_cmd       \
     dot_glob               \
  no_dvorak                 \
  no_emacs                  \
     equals                 \
  no_err_exit               \
  no_err_return             \
     eval_lineno            \
     exec                   \
     extended_glob          \
  no_extended_history       \
  no_flow_control           \
     function_arg_zero      \
     glob                   \
  no_glob_assign            \
  no_glob_complete          \
  no_glob_dots              \
  no_glob_subst             \
  no_global_rcs             \
     hash_cmds              \
     hash_dirs              \
     hash_list_all          \
  no_hist_allow_clobber     \
  no_hist_beep              \
  no_hist_expire_dups_first \
     hist_find_no_dups      \
     hist_ignore_all_dups   \
     hist_ignore_dups       \
     hist_ignore_space      \
  no_hist_no_functions      \
     hist_no_store          \
  no_hist_reduce_blanks     \
     hist_save_by_copy      \
     hist_save_no_dups      \
  no_hist_subst_pattern     \
  no_hist_verify            \
  no_hup                    \
  no_ignore_braces          \
  no_ignore_eof             \
  no_inc_append_history     \
  no_interactive_comments   \
  no_ksh_arrays             \
  no_ksh_autoload           \
  no_ksh_glob               \
  no_ksh_option_print       \
  no_ksh_typeset            \
  no_ksh_zero_subscript     \
     list_ambiguous         \
  no_list_beep              \
  no_list_packed            \
  no_list_rows_first        \
     list_types             \
     local_options          \
  no_local_traps            \
     long_list_jobs         \
  no_magic_equal_subst      \
  no_mail_warning           \
  no_mark_dirs              \
  no_menu_complete          \
     monitor                \
     multibyte              \
     multios                \
  no_nomatch                \
  no_notify                 \
  no_nullglob               \
  no_numeric_glob_sort      \
     octal_zeroes           \
  no_overstrike             \
  no_path_dirs              \
  no_posix_builtins         \
  no_posix_identifiers      \
  no_print_eight_bit        \
  no_print_exit_value       \
  no_privileged             \
  no_prompt_bang            \
  no_prompt_cr              \
     prompt_percent         \
  no_prompt_sp              \
     prompt_subst           \
     pushd_ignore_dups      \
     pushd_minus            \
  no_pushd_silent           \
  no_pushd_to_home          \
     rc_expand_param        \
  no_rc_quotes              \
  no_rec_exact              \
     rematch_pcre           \
  no_restricted             \
  no_rm_star_silent         \
  no_rm_star_wait           \
  no_sh_file_expansion      \
  no_sh_glob                \
  no_sh_nullcmd             \
  no_sh_option_letters      \
  no_sh_word_split          \
  share_history             \
     short_loops            \
  no_single_line_zle        \
     sun_keyboard_hack      \
     transient_rprompt      \
  no_traps_async            \
  no_typeset_silent         \
     unset                  \
  no_verbose                \
     vi                     \
  no_warn_create_global     \
  no_xtrace                 \
     zle                    \
  no_single_command

autoload -U age
autoload -U compinit
compinit
# url-quote-magic                                                            {{{
autoload -U url-quote-magic

function _url-quote-magic() {
  url-quote-magic;
  _zsh_highlight-zle-buffer
}
zle -N self-insert _url-quote-magic
zle -C most-accessed-file menu-complete _generic

autoload -U url-quote-magic
zle -N self-insert url-quote-magic
#}}}
