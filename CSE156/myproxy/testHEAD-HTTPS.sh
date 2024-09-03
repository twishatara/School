#!/bin/bash

# The address of your proxy server
PROXY_URL="127.0.0.1:8080"

# Array of target URLs you want to request through your proxy
declare -a TARGET_URLS=("www.google.com" "www.github.com" "www.ucsc.edu")

# Number of requests to send for each URL
REQUEST_COUNT=10

for url in "${TARGET_URLS[@]}"; do
    echo "Sending requests to $url"
    for i in $(seq 1 $REQUEST_COUNT); do
        echo "  Request $i"
        curl -I -x $PROXY_URL $url
        echo -e "\n" # New line for readability
    done
    echo -e "Completed requests for $url\n"
done