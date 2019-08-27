#include <stdio.h>

#include "./headers/env.h"
#include "./headers/io.h"
#include "./headers/structs.h"
#include "./headers/constants.h"
#include "./headers/insert.h"

int main(int argc, char ** argv) {
  int menuChoice, quitMenu = FALSE;

  setEnvVars(argc, argv);

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
        testFunction();
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
        readDataFile(openFile(DATA_FILE_PATH, READ_BIN));
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
