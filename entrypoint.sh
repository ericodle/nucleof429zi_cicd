#!/bin/bash
set -e  # Exit immediately if a command fails

# Activate the virtual environment
source /opt/venv/bin/activate

# Initialize the West workspace
if [ ! -d "my-workspace" ]; then
    west init -m https://github.com/ericodle/nucleof429zi_cicd --mr main my-workspace
fi

# Update West
cd my-workspace
west update

# Install required Python packages
pip install --no-cache-dir natsort pyelftools junitparser pytest psutil tabulate pyserial anytree ply

# Move into the test directory
cd nucleof429zi_cicd

# Run the tests
west twister -T tests --verbose --integration

# Keep the container running (optional)
exec "$@"
