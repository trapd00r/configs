#!/bin/bash

# Clipboard stack file
STACK_FILE="$HOME/.cache/clipboard-stack"
MAX_ITEMS=50

mkdir -p "$(dirname "$STACK_FILE")"
touch "$STACK_FILE"

# Function to check if input is valid UTF-8 text
is_text() {
    # iconv will fail if input is not valid UTF-8
    echo -n "$1" | iconv -f UTF-8 -t UTF-8 > /dev/null 2>&1
}

# Function to add new entry to stack
add_to_stack() {
    local entry="$1"
    # Remove duplicates
    grep -vxF -- "$entry" "$STACK_FILE" > "$STACK_FILE.tmp" || true
    mv "$STACK_FILE.tmp" "$STACK_FILE"
    # Add to top
    echo "$entry" | cat - "$STACK_FILE" > "$STACK_FILE.tmp"
    mv "$STACK_FILE.tmp" "$STACK_FILE"
    # Limit stack size
    head -n $MAX_ITEMS "$STACK_FILE" > "$STACK_FILE.tmp"
    mv "$STACK_FILE.tmp" "$STACK_FILE"
}

# Monitor clipboard and primary selection
monitor() {
    local last_clip=""
    local last_primary=""
    while true; do
        # Clipboard
        clip=$(xclip -o -selection clipboard 2>/dev/null)
        if [[ -n "$clip" && "$clip" != "$last_clip" ]]; then
            if is_text "$clip"; then
                add_to_stack "$clip"
                last_clip="$clip"
            fi
        fi
        # Primary
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
    choice=$(cat "$STACK_FILE" | rofi -dmenu -i -p "Clipboard stack" -l 10)
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
    *)
        echo "Usage: $0 {monitor|pick}"
        exit 1
        ;;
esac 