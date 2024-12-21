#!/bin/bash

# Function to send a single request
send_request() {
    curl -i -X GET 127.0.0.1/compute
    echo -e "\nRequest sent."
}

# Loop indefinitely
while true; do
    # Send a request in the background
    send_request &

    # Generate a random delay between 5 and 10 seconds
    delay=$((RANDOM % 6 + 5))
    echo "Waiting for $delay seconds before spawning the next request..."

    # Wait for the random delay
    sleep $delay
done

