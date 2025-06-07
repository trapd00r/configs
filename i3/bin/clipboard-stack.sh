# Clipboard stack file
STACK_FILE="$HOME/.cache/clipboard-stack"
MAX_ITEMS=50

mkdir -p "$(dirname "$STACK_FILE")"
touch "$STACK_FILE"

# Use NUL as separator for multiline safety
SEP="\0"

# Function to check if input is valid UTF-8 text
is_text() {
    echo -n "$1" | iconv -f UTF-8 -t UTF-8 > /dev/null 2>&1
}

# Function to add new entry to stack (NUL-delimited)
add_to_stack() {
    local entry="$1"
    # Remove duplicates
    if grep -zFxq -- "$entry" "$STACK_FILE"; then
        notify-send "Clipboard Stack" "Duplicate skipped"
        return
    fi
    # Add to top
    printf '%s' "$entry" | cat - "$STACK_FILE" > "$STACK_FILE.tmp"
    mv "$STACK_FILE.tmp" "$STACK_FILE"
    # Limit stack size
    entries=$(tr '\0' '\n' < "$STACK_FILE" | head -n $MAX_ITEMS | tr '\n' '\0')
    printf '%s' "$entries" > "$STACK_FILE"
}

# Clear the clipboard stack
clear_stack() {
    > "$STACK_FILE"
    notify-send "Clipboard Stack" "Stack cleared!"
}

# Monitor clipboard and primary selection
monitor() {
    local last_clip=""
    local last_primary=""
    while true; do
        clip=$(xclip -o -selection clipboard 2>/dev/null)
        if [[ -n "$clip" && "$clip" != "$last_clip" ]]; then
            if is_text "$clip"; then
                add_to_stack "$clip"
                last_clip="$clip"
            fi
        fi
        primary=$(xclip -o -selection primary 2>/dev/null)
        if [[ -n "$primary" && "$primary" != "$last_primary" ]]; then
            if is_text "$primary"; then
                add_to_stack "$primary"
                last_primary="$primary"
            fi
        fi
        sleep 0.5
    done
}

# Pick from stack and copy to clipboard
pick() {
    if [[ ! -s "$STACK_FILE" ]]; then
        notify-send "Clipboard Stack" "No entries yet!"
        exit 1
    fi
    # Show stack with CLEAR CLIPBOARD at the bottom
    entries=$(tr '\0' '\n' < "$STACK_FILE")
    choice=$( (echo "$entries"; echo '<span background="red" foreground="white"><b>CLEAR CLIPBOARD</b></span>') | rofi -dmenu -i -markup-rows -p "Clipboard stack" -l 10)
    if [[ "$choice" == *CLEAR\ CLIPBOARD* ]]; then
        clear_stack
        exit 0
    fi
    if [[ -n "$choice" ]]; then
        echo -n "$choice" | xclip -selection clipboard
        echo -n "$choice" | xclip -selection primary
        notify-send "Clipboard Stack" "Copied to clipboard!"
    fi
}

case "$1" in
    monitor)
        monitor
        ;;
    pick)
        pick
        ;;
    clear)
        clear_stack
        ;;
    *)
        echo "Usage: $0 {monitor|pick|clear}"
        exit 1
        ;;
esac 