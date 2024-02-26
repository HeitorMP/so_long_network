#!/bin/bash

if [ -x "bin/so_long_server" ]; then
    ./bin/so_long_server &

    echo "Running..."
else
    echo "Server binary not found."
    exit 1
fi
