#!/bin/bash

# Add changes to the staging area
git add .

# Prompt the user to enter a commit message
echo -n "Enter your commit message: "
read -r mes

# Check if the commit message is empty
if [ -z "$mes" ]; then
	echo "Auto adding commit message as (Updated)."
	git commit -m "Updated"
else
	git commit -m "$mes"
fi

# Commit the changes with the provided commit message

# Push the changes to the remote repository
git push
