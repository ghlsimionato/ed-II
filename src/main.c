#include <stdio.h>

#include "./headers/io.h"
#include "./headers/structs.h"

#define INSERT 1
#define REMOVE 2
#define COMPACT_FILE 3
#define DUMP_FILE 4
#define LOAD_FILES 5
#define QUIT 0

#define DATA_FILE_PATH "./data/input/insere.bin"
#define OUTPUT_FILE_PATH "./data/output_file.bin"

#define TRUE 1
#define FALSE 0

int main() {
  int menuChoice, quitMenu = FALSE;

  do {
    printf("\nMAIN MENU:\n");
    printf("\n\t1. Insert data");
    printf("\n\t2. Remove by ID");
    printf("\n\t3. Compact file");
    printf("\n\t4. Hex dump file");
    printf("\n\t5. Load files");
    printf("\n\t0. Quit\n\n");
    printf("\tInsert option: ");
    scanf("%d", &menuChoice);

    switch (menuChoice) {
      case INSERT:
        printf("\nInserting Data\n");
        // updateHeader(head, openFile(OUTPUT_FILE_PATH, "w+"));
        // head = getFileHeader(openFile(OUTPUT_FILE_PATH, "r"));
        // printf("head.offset=%d", head.offest);
        break;

      case REMOVE:
        printf("\nRemoving data\n");
        break;

      case COMPACT_FILE:
        printf("\nCompacting file\n");
        break;
      
      case DUMP_FILE:
        printf("\nDumping file\n");
        break;

      case LOAD_FILES:
        readDataFile(openFile(DATA_FILE_PATH, "r"));
        break;

      case QUIT:
        printf("\nQuiting\n");
        quitMenu = TRUE;
        break;

      default:
        printf("\nInvalid Option\n");
    }
  } while (quitMenu == FALSE);

  return 0;
}
