#!/bin/bash

# use mod+1, mod+2 etc to switch to workspaces on different monitors
# there is 9 workspaces on all monitors (except laptop's built-in display)
# workspace 6,7 on left monitor is treated like workspace 1,2 so
# we can use the same keybindings to switch to them
# in practice, emulating a more sane workspace setup (ratpoison, sdorfehs)

focused_output=$(i3-msg -t get_workspaces | jq -r '.[] | select(.focused==true).output')
key="$1"

# Docked laptop: MST middle output is present. Undocked: only eDP-1.
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
                echo $((27 + n))  # Laptop screen when docked
            else
                echo "$n"         # Undocked: act as primary
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

# Switch and pin to the focused output (heals workspaces stuck after cable/MST renames)
i3-msg "workspace number $ws, move workspace to output \"$focused_output\""
