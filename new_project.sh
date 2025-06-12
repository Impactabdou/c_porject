#!/bin/bash

# Script to create a standard C project structure
# Author Abderrahmene Kabar

if [ -z "$1" ]; then
  echo "Usage: $0 <project_name>"
  exit 1
fi

project_name="$1"
current_dir=$(pwd)
project_path="$current_dir/$project_name"

if [[ -d "$project_path" ]]; then
  echo "Project already exists in $current_dir"
  echo "Wanna remove ? (y/n)"
  read remove_project

  if [[ -z "$remove_project" ]]; then 
    echo "Okey then :/"
  elif [[ "$remove_project" == "y" ]]; then 
    echo "Removing project :)"
    rm -rf "$project_path"
  else 
    echo "Exiting without any changes"
    exit 1
  fi
fi

echo "Creating project: $project_name"
mkdir -p "$project_path"/{include,src,bin,obj,build,docs}
cp ~/Documents/c_project/utils/default_skin_makefile "$project_path/Makefile"
cp ~/Documents/c_project/utils/default_readme.md "$project_path/README.md"
echo "Project created at: $project_path"

