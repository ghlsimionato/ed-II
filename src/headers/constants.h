#ifndef CONSTANTS_H

#define CONSTANTS_H

/* Menu */
#define INSERT 1
#define SEARCH_PK 2
#define SEARCH_SK 3
#define DUMP_FILE 4
#define LOAD_FILES 5
#define QUIT 0
/* Menu debug options */
#define CHECK_SPACE_LIST 6

/* Paths for provided files */
#define DATA_FILE_PATH "./data/input/insere.bin"
#define SEARCH_PK_FILE_PATH "./data/search/busca_p.bin"
#define SEARCH_SK_FILE_PATH "./data/search/busca_s.bin"

/* Paths for created files */
#define OUTPUT_FILE_PATH "./build/output_file.bin"
#define PK_FILE_PATH "./build/pk_index.bin"
#define SK_FILE_PATH "./build/sk_index.bin"

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
