#ifndef CONSTANTS_H

#define CONSTANTS_H

/* Menu */
#define INSERT 1
#define REMOVE 2
#define COMPACT_FILE 3
#define DUMP_FILE 4
#define LOAD_FILES 5
#define QUIT 0
/* Menu debug options */
#define CHECK_SPACE_LIST 6

/* Paths */
#define DATA_FILE_PATH "./data/input/insere.bin"
#define REMOVE_DATA_FILE_PATH "./data/input/remove.bin"
#define OUTPUT_FILE_PATH "./build/output_file.bin"
#define INSERTED_REG_PATH "./build/inserted_registers.bin"
#define REMOVED_REG_PATH "./build/removed_registers.bin"

/* File modes */
#define READ_BIN "rb"
#define READ_WRITE_BIN "rb+"
#define WRITE_READ_BIN "wb+"

/* Strings */
#define STR_MATCH 0

/* Boolean */
#define TRUE 1
#define FALSE 0

/* Registers */
#define REG_SIZE 137

#endif
