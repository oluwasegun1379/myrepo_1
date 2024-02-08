#!/bin/bash

# Step 1: Commit changes
echo "Committing changes..."
git add .
echo "Enter commit message: "
read commit_message
git commit -m "$commit_message"

# Step 2: Pull changes
echo "Pulling latest changes..."
git pull

# Step 3: Check for conflicts
conflict_files=$(git status --porcelain | grep '^UU' | cut -c4-)

# Step 4: Resolve conflicts
if [ -n "$conflict_files" ]; then
  echo "Conflict detected. Resolving conflicts..."
  git mergetool
  git add .
  git commit -m "Conflict resolution"
fi

# Step 5: Push changes
echo "Pushing changes..."
git push

echo "Script completed."

