#!/bin/bash

# Update package lists
pkg update

# Install necessary packages
pkg install -y build-essential clang git

# Clone the betty repository
git clone https://github.com/holbertonschool/Betty.git

# Navigate to the Betty directory
cd Betty

# Install betty style configuration
./install.sh

