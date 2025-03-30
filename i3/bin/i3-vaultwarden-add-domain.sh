#!/bin/bash
# add login to Bitwarden

source ~/.secret_zshrc

log_debug() {
    echo "[DEBUG] $*" >&2
}

# Prompt for domain
domain=$(rofi -normal-window -dmenu -p "Add Domain:")
[ -z "$domain" ] && notify-send "Bitwarden" "Cancelled" && exit
log_debug "Domain: $domain"

# Prompt for username; it can be empty
username=$(rofi -normal-window -dmenu -p "Username:")
# [ -z "$username" ] && notify-send "Bitwarden" "Cancelled" && exit
log_debug "Username: $username"

# Prompt for password (hidden input)
password=$(rofi -normal-window -password -dmenu -p "Password:")
[ -z "$password" ] && notify-send "Bitwarden" "Cancelled" && exit
log_debug "Password: (hidden)"

# Build valid JSON
payload=$(jq -n --arg domain "$domain" --arg username "$username" --arg password "$password" '{
    object: "item",
    type: 1,
    name: $domain,
    favorite: false,
    notes: null,
    reprompt: 0,
    login: {
        username: $username,
        password: $password,
        totp: null,
        uris: [{ uri: ("http://" + $domain) }]
    }
}')

log_debug "JSON payload:"
echo "$payload" >&2

# Encode & Create
encoded=$(echo "$payload" | bw encode --session "$BW_SESSION")
log_debug "Encoded payload: $encoded"

result=$(echo "$encoded" | bw create item --session "$BW_SESSION" 2>&1)
status=$?

if [ $status -eq 0 ]; then
    notify-send "Bitwarden" "Saved login for $domain"
    log_debug "Success: $result"
else
    notify-send "Bitwarden" "Failed to save entry"
    log_debug "Bitwarden error: $result"
fi

