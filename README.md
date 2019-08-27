# ed-II
C Projects for Data Structure class

# Deps
It is suggested to install the "build-essential" (use apt-get or your dist package manager)

# Build
To build the project run "make build"
Run ./insurance-reg
The created file will be in ./data as "output_file.bin"

# Clean
To remove object files run make clean
To remove the DB files and build run clean-build 
To remove both run make clean-all

# Debugging
NOTE: gdb is required to debug
If you're using VSCode in Linux, launch "make and debug" to debug the project
Else, use gdb with the path to the executable (gdb ./build/insurance-reg)

# TODO
Create insert function
