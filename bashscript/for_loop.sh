#!/bin/bash

echo -n "Enter a string: "
read -a string

count=0
for char in "${string[@]}"; do
    echo "string $((count+1)): $char"
    count=$((count+1))
done
