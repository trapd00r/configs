# Create a global cache variable
typeset -gA _ZSH_HIGHLIGHT_URL_HIGHLIGHTER_CACHE

# Set the default styles
: ${ZSH_HIGHLIGHT_STYLES[url-good]:=fg=green}
: ${ZSH_HIGHLIGHT_STYLES[url-bad]:=fg=red}

# Set the default timeout
: ${ZSH_HIGHLIGHT_URL_HIGHLIGHTER_TIMEOUT:=0.25}

autoload -Uz add-zsh-hook
add-zsh-hook precmd _zsh_highlight_url_clear_cache

# Clears the url highlighter cache
_zsh_highlight_url_clear_cache()
{
  _ZSH_HIGHLIGHT_URL_HIGHLIGHTER_CACHE=()
}


_zsh_highlight_url_highlighter_predicate()
{
  _zsh_highlight_buffer_modified
}


_zsh_highlight_url_highlighter()
{
  local -a match mbegin mend
  local -a MATCH MBEGIN MEND
  local -a matches match matches_starts matches_ends
  local start end match_count
  local status_code
  
  local remaining_buffer="$BUFFER"
  local buffer_length=$#BUFFER
  local offset=0
  
  until [[ -z "$remaining_buffer" ]]; do
    if [[ "$remaining_buffer" =~ '(https?://([^ ]+[.])+([^ ]+)) ' ]]; then
      start=$((mbegin[1]-1))
      end=$mend[1]
      matches+=$match[1]
      matches_starts+=$((start + offset))
      matches_ends+=$((end + offset))
      remaining_buffer="$BUFFER[$end,$#remaining_buffer]"
      offset+=$((end - 1))
    else
      remaining_buffer=""
    fi
  done

  local match_count=$#matches
  local i
  
  for ((i=1; $i <= $match_count; i++)); do
    match=$matches[$i]
    # debug "Match: $match"
    if [[ -n "$_ZSH_HIGHLIGHT_URL_HIGHLIGHTER_CACHE[$match]" ]]; then
      # debug 'Cache hit'
      status_code=$_ZSH_HIGHLIGHT_URL_HIGHLIGHTER_CACHE[$match]
    else
      # debug 'Fetching'
      status_code=$(curl -sIL -m ${ZSH_HIGHLIGHT_URL_HIGHLIGHTER_TIMEOUT} -w '%{http_code}' "$matches[$i]" -o /dev/null)
      # debug $status_code
      # Cache the result so we don't have to check again on this line
      _ZSH_HIGHLIGHT_URL_HIGHLIGHTER_CACHE[$match]=$status_code
    fi
    if [[ "$status_code" == "200" ]]; then
      region_highlight+=("$matches_starts[$i] $matches_ends[$i] ${ZSH_HIGHLIGHT_STYLES[url-good]}")
    else
      region_highlight+=("$matches_starts[$i] $matches_ends[$i] ${ZSH_HIGHLIGHT_STYLES[url-bad]}")
    fi
  done
}

# Just commenting out for now
# function debug()
# {
#   echo $1 >> /tmp/url-output.log
# }
