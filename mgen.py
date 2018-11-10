#!/usr/bin/python3
import msquared as m2

mgen = m2.MGen("./", project_include_dirs="./include")

# Main library.
# sources = m2.wrap("src/", [], ".cpp")
# mgen.add_library("", sources=sources, install_directory="/usr/local/lib/")

# Install header
mgen.add_install("./include/interfaces/STest", install_directory="/usr/local/include/Stealth/")

# Add test executable
mgen.add_executable("test", sources="test/test.cpp", libraries="")

# Write a makefile.
mgen.write()
