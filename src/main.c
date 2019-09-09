#include <stdio.h>

#include "./headers/io.h"
#include "./headers/structs.h"
#include "./headers/constants.h"
#include "./headers/insert.h"
#include "./headers/remove.h"

int main() {
  int menuChoice, quitMenu = FALSE;
  struct Register * test;

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
      // Not all logic was implemented
        handleUserInsert();
        break;

      case REMOVE:
        // Apparently working
        cleanStdin();
        printf("Insert ID: ");
        removeRegister(getStringFromUser(4));
        break;

      case COMPACT_FILE:
        printf("\nCompacting file\n");
        break;
      
      case DUMP_FILE:
        dumpFile(DATA_FILE_PATH, READ_WRITE_BIN);
        break;

      case LOAD_FILES:
        // does not load the remove.bin
        // does not mark which registers were inserted
        insertDataFromFile();
        break;

      case QUIT:
        printf("\nQuiting\n");
        quitMenu = TRUE;
        break;

      // Cases for testing
      case CHECK_SPACE_LIST:
        iterateThroughSpaceList(openFile(OUTPUT_FILE_PATH, READ_BIN));
        break;

      default:
        printf("\nInvalid Option\n");
    }
  } while (quitMenu == FALSE);

  return 0;
}
