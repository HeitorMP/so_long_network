#!/bin/bash

if [ -x "bin/so_long_server" ] && [ -x "bin/chat_server" ]; then
    ./bin/so_long_server &
    ./bin/chat_server &

    echo "Running..."
else
    echo "File not found."
    exit 1
fi
