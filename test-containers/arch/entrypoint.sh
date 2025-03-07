#!/bin/bash
set -e  # Exit immediately if a command fails

# Activate the virtual environment
source /opt/venv/bin/activate

# Initialize the West workspace only if it hasn't been initialized yet
if [ ! -d "arch-test" ]; then
    west init -m https://github.com/ericodle/nucleof429zi_cicd --mr main arch-test
fi

# Update West
cd arch-test
west update

# Install required Python packages
pip install --no-cache-dir natsort pyelftools junitparser pytest psutil tabulate pyserial anytree ply

# Move into the test directory
cd nucleof429zi_cicd

# Run the tests
west twister -T tests --verbose --integration

# Keep the container running (optional)
exec "$@"
