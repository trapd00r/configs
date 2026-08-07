#!/bin/bash

# Move current window to previous workspace on the same monitor
# Alt+Shift+h will move window to previous workspace on focused monitor

current_workspace=$(i3-msg -t get_workspaces | jq -r '.[] | select(.focused==true) | .num')
focused_output=$(i3-msg -t get_workspaces | jq -r '.[] | select(.focused==true).output')

docked() {
    xrandr --query | grep -qE '^DP-[34]-1-5 connected'
}

case "$focused_output" in
    DP-2|DP-4-1-5|DP-3-1-5)
        min_ws=1; max_ws=9
        ;;
    DP-0|DP-3|DP-1)
        min_ws=10; max_ws=18
        ;;
    DP-5|DP-4-1-6|DP-3-1-6)
        min_ws=19; max_ws=27
        ;;
    eDP-1)
        if docked; then
            min_ws=28; max_ws=36
        else
            min_ws=1; max_ws=9
        fi
        ;;
    HDMI-0)
        min_ws=28; max_ws=36
        ;;
    *)
        echo "No matching output for workspace navigation: $focused_output"
        exit 1
        ;;
esac

if [ "$current_workspace" -le "$min_ws" ]; then
    prev_workspace=$max_ws
else
    prev_workspace=$((current_workspace - 1))
fi

i3-msg "move container to workspace number $prev_workspace, workspace number $prev_workspace, move workspace to output \"$focused_output\""
