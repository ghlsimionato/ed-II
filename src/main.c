#include <stdio.h>

#include "./headers/io.h"
#include "./headers/structs.h"
#include "./headers/constants.h"
#include "./headers/insert.h"
#include "./headers/remove.h"

int main() {
  int menuChoice, quitMenu = FALSE;
  char * string;
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
        handleUserInsert();
        break;

      case REMOVE:
        // readFileRegisters();
        // string = getStringFromUser(4);
        removeRegister(getStringFromUser(4));

        printf("\nRemoving data\n");
        break;

      case COMPACT_FILE:
        printf("\nCompacting file\n");
        break;
      
      case DUMP_FILE:
        printf("\nDumping file\n");
        break;

      case LOAD_FILES:
        test = readDataFile(openFile(DATA_FILE_PATH, READ_BIN));
        // int regCount = sizeof (*test) / sizeof (struct Register);
        for (int i = 0; i < 8; i++) {
          insertRegister(test[i]);
        }
        free(test);
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
