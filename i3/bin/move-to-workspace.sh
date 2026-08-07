#!/bin/bash

# Move current window to workspace 1-9 on the current monitor
# Alt+1-9 will move window to workspace 1-9 on the focused monitor

focused_output=$(i3-msg -t get_workspaces | jq -r '.[] | select(.focused==true).output')
key="$1"

docked() {
    xrandr --query | grep -qE '^DP-[34]-1-5 connected'
}

workspace_for() {
    local output="$1" n="$2"
    case "$output" in
        DP-0|DP-3|DP-1)  # Left
            echo $((9 + n))
            ;;
        DP-5|DP-4-1-6|DP-3-1-6)  # Top
            echo $((18 + n))
            ;;
        DP-2|DP-4-1-5|DP-3-1-5)  # Middle
            echo "$n"
            ;;
        eDP-1)
            if docked; then
                echo $((27 + n))
            else
                echo "$n"
            fi
            ;;
        HDMI-0)  # Behind (desktop)
            echo $((27 + n))
            ;;
        *)
            return 1
            ;;
    esac
}

ws=$(workspace_for "$focused_output" "$key") || {
    echo "No matching output for keybinding: $focused_output"
    exit 1
}

i3-msg "move container to workspace number $ws, workspace number $ws, move workspace to output \"$focused_output\""
