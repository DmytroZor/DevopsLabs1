#!/bin/bash

# Function to start a container on a specific CPU core
start_container() {
  local container=$1
  local core=$2
  if docker ps -a --format '{{.Names}}' | grep -q "$container"; then
    if ! docker ps --format '{{.Names}}' | grep -q "$container"; then
      docker rm "$container"
    else
      echo "$container is already running."
      return
    fi
  fi
  echo "Starting $container on core $core..."
  docker run -d --name "$container" --cpuset-cpus="$core" zorenkod/httpserver:latest
  sleep 10
}

# Function to get the CPU usage of a container
get_cpu_usage() {
  local container=$1
  docker stats "$container" --no-stream --format "{{.CPUPerc}}" | sed 's/%//'
}

# Function to update running containers
update_containers() {
  echo "Checking for new image version..."
  if docker pull zorenkod/httpserver:latest | grep -q 'Downloaded newer image'; then
    echo "New image version detected. Updating containers..."
    declare -A core_map=( ["srv1"]=0 ["srv2"]=1 ["srv3"]=2 )
    for container in srv1 srv2 srv3; do
      if docker ps --format '{{.Names}}' | grep -q "$container"; then
        echo "Updating $container..."
        docker stop "$container"
        docker rm "$container"
        start_container "$container" "${core_map[$container]}"
        sleep 10
      fi
    done
  fi
}

# Main loop
last_check=$(date +%s)
while true; do
  start_container srv1 0
  echo "Monitoring srv1..."
  if docker ps --format '{{.Names}}' | grep -q srv1; then
    usage1=$(get_cpu_usage srv1)
    sleep 60
    usage2=$(get_cpu_usage srv1)
    if (( $(echo "$usage1 > 80" | bc -l) && $(echo "$usage2 > 80" | bc -l) )); then
      echo "srv1 is busy. Starting srv2..."
      start_container srv2 1
    fi
  fi

  if docker ps --format '{{.Names}}' | grep -q srv2; then
    usage1=$(get_cpu_usage srv2)
    sleep 60
    usage2=$(get_cpu_usage srv2)
    if (( $(echo "$usage1 > 80" | bc -l) && $(echo "$usage2 > 80" | bc -l) )); then
      echo "srv2 is busy. Starting srv3..."
      start_container srv3 2
    elif (( $(echo "$usage1 < 10" | bc -l) && $(echo "$usage2 < 10" | bc -l) )); then
      echo "srv2 is idle. Stopping it..."
      docker stop srv2
      docker rm srv2
    fi
  fi

  if docker ps --format '{{.Names}}' | grep -q srv3; then
    usage1=$(get_cpu_usage srv3)
    sleep 60
    usage2=$(get_cpu_usage srv3)
    if (( $(echo "$usage1 < 10" | bc -l) && $(echo "$usage2 < 10" | bc -l) )); then
      echo "srv3 is idle. Stopping it..."
      docker stop srv3
      docker rm srv3
    fi
  fi

  current_time=$(date +%s)
  if (( current_time - last_check >= 600 )); then
    update_containers
    last_check=$current_time
  fi

  sleep 20
done
