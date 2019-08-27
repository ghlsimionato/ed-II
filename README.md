# ed-II
C Projects for Data Structure class

# Deps
It is suggested to install the `build-essential` (use apt-get or your dist package manager)

# Build
To build the project run `make build`
Run ./insurance-reg
The created file will be in `./data` as `output_file.bin`

# Clean
To remove object files run `make clean`
To remove the DB files and build run `make clean-build` 
To remove both run `make clean-all`

# Debugging
NOTE: gdb is required to debug
If you're using VSCode in Linux, launch (start debugging) `make and debug` to debug the project
Else, use gdb with the path to the executable `gdb ./build/insurance-reg`

# TODO
1. Create insert function
  - Need to create separators for each register inserted
  - Index table
  - Next available spot in header
  - first-fit
2. Create delete function
  - Mark space to possibly be reused
3. Create hex dump
4. Properly load from file
  - Load all the data into a struct array and insert one by one (each register can be skipped if user wants)
  - Mark loaed register as "loaded" ? (Not sure if this is required)

# Quality-Of-Life Improvements
- gitignore build folder
- improve make clean
- add .PHONY
- makefile create build dir if it doesn't exist (the executable should not be commited)
