#!/bin/bash

# switch workspaces properly on different outputs

# Get the name of the active output
focused_output=$(i3-msg -t get_workspaces | jq -r '.[] | select(.focused==true).output')

case "$focused_output" in
    "DP-0")  # Left Monitor
        case "$1" in
            1) i3-msg workspace number 6 ;;  # Mod+1 switches to workspace 6
            2) i3-msg workspace number 7 ;;  # Mod+2 switches to workspace 7
        esac
        ;;
    "DP-5")  # Top Monitor
        case "$1" in
            1) i3-msg workspace number 8 ;;  # Mod+1 switches to workspace 8
            2) i3-msg workspace number 9 ;;  # Mod+2 switches to workspace 9
        esac
        ;;
    "DP-2")  # Middle Monitor
        case "$1" in
            1) i3-msg workspace number 1 ;;  # Mod+1 switches to workspace 1
            2) i3-msg workspace number 2 ;;  # Mod+2 switches to workspace 2
            3) i3-msg workspace number 3 ;;
            4) i3-msg workspace number 4 ;;
            5) i3-msg workspace number 5 ;;
        esac
        ;;
    "HDMI-0")  # Behind Monitor
        echo "HDMI-0 output not configured for specific workspace switches." ;;
    *)
        echo "No matching output for keybinding"
        ;;
esac

