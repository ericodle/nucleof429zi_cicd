# Zephyr nucleof429zi_cicd app

make_minimum_required(VERSION 3.22.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(app LANGUAGES C)

# Add main.c and morse.c to the list of source files
target_sources(app PRIVATE src/main.c src/morse.c)
