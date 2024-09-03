#!/bin/bash

# Start three instances of the server with different port numbers and folder names
./myserver 9090 0 server1_folder &
./myserver 9091 0 server2_folder &
./myserver 9092 0 server3_folder &

# Wait for all servers to finish (optional)
wait
