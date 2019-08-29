# ed-II
C Projects for Data Structure class

# Deps
It is suggested to install the `build-essential` package (contains gcc, gdb and all the essential build tools) (use apt-get or your dist package manager)

# Build
To build the project run `make build`
Run ./insurance-reg
The created file will be in `./data` as `output_file.bin`

# Clean
To to clean all built files, run `make clean`
To remove only the build dir run `make clean-build` 
To remove only the obj dir run `make clean-obj`

# Debugging
NOTE: gdb is required to debug
If you're using VSCode in Linux, launch (start debugging) `make and debug` to debug the project
Else, use gdb with the path to the executable `gdb ./build/insurance-reg`

# TODO
1. Create insert function
  - ~~Need to create separators for each register inserted (somewhat done)~~
  - ~~Iterate through available spots list~~
  - ~~first-fit logic~~
2. Create delete function
  - Mark space to be reused
  - Update file header with offset to deleted register
3. Create hex dump
4. Properly load from file
  - Load all the data into a struct array and insert one by one (each register can be skipped if user wants) (somewhat done)
  - Mark loaed register as "loaded" ? (Not sure if this is required)

# Quality-Of-Life Improvements
- improve make clean
- add .PHONY rules to makefile
- create logger function that checks env variables to log
