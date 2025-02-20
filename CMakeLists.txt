cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr)
project(my_zephyr_app)

target_sources(nucleof429zi_cicd PRIVATE src/main.c)