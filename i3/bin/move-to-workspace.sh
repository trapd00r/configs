#!/bin/bash

# Move current window to workspace 1-9 on the current monitor
# Alt+1-9 will move window to workspace 1-9 on the focused monitor

# Get the name of the active output
focused_output=$(i3-msg -t get_workspaces | jq -r '.[] | select(.focused==true).output')

move_to_workspace() {
    local target_workspace
    case "$1" in
        "DP-0"|"DP-3"|"DP-1")  # Left monitor on desktop or laptop
            case "$2" in
                1) target_workspace=10 ;;
                2) target_workspace=11 ;;
                3) target_workspace=12 ;;
                4) target_workspace=13 ;;
                5) target_workspace=14 ;;
                6) target_workspace=15 ;;
                7) target_workspace=16 ;;
                8) target_workspace=17 ;;
                9) target_workspace=18 ;;
            esac
            ;;
        "DP-5"|"DP-4-1-6"|"DP-3-1-6")  # Top monitor on desktop or laptop
            case "$2" in
                1) target_workspace=19 ;;
                2) target_workspace=20 ;;
                3) target_workspace=21 ;;
                4) target_workspace=22 ;;
                5) target_workspace=23 ;;
                6) target_workspace=24 ;;
                7) target_workspace=25 ;;
                8) target_workspace=26 ;;
                9) target_workspace=27 ;;
            esac
            ;;
        "DP-2"|"DP-4-1-5" | "eDP-1" | "DP-3-1-5" )  # Middle monitor on desktop or laptop, or undocked laptop screen
            case "$2" in
                1) target_workspace=1 ;;
                2) target_workspace=2 ;;
                3) target_workspace=3 ;;
                4) target_workspace=4 ;;
                5) target_workspace=5 ;;
                6) target_workspace=6 ;;
                7) target_workspace=7 ;;
                8) target_workspace=8 ;;
                9) target_workspace=9 ;;
            esac
            ;;
        "HDMI-0")  # Behind monitor on desktop
            case "$2" in
                1) target_workspace=28 ;;
                2) target_workspace=29 ;;
                3) target_workspace=30 ;;
                4) target_workspace=31 ;;
                5) target_workspace=32 ;;
                6) target_workspace=33 ;;
                7) target_workspace=34 ;;
                8) target_workspace=35 ;;
                9) target_workspace=36 ;;
            esac
            ;;
        *)
            echo "No matching output for keybinding."
            return 1
            ;;
    esac
    
    i3-msg move container to workspace number $target_workspace
    i3-msg workspace number $target_workspace
}

# Check if we are on desktop or laptop based on available outputs
if xrandr | grep -q "DP-2"; then
    # Desktop setup
    move_to_workspace "$focused_output" "$1"
elif xrandr | grep -q "eDP-1"; then
    # Laptop setup
    move_to_workspace "$focused_output" "$1"
else
    notify-send "i3 workspace move" "No known setup detected."
    echo "No known setup detected."
fi

