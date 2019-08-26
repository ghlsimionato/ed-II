#include <stdio.h>
#include <stdlib.h>

#define INSERT 1
#define REMOVE 2
#define QUIT 0

#define TRUE 1
#define FALSE 0

struct Register {
  char id[3], name[50], insurance[50], type[50];
};

struct Register readData(FILE * input);
int insertData(FILE* input, struct Register inputData);
int removeData(FILE* input, int byteOffset);
int compactFile();

int firstFit();

int main() {
  FILE * input = fopen("insere.bin", "r+");
  struct Register registerInstance;
  int menuChoice, quitMenu = FALSE;

  if (input == NULL) {
    printf("File not recognized");

    return 1;
  }

  registerInstance = readData(input);
  printf("%s", registerInstance.id);

  do {
    printf("\n1. Insert\n2. Remove\n0. Quit\n");
    scanf("%d", &menuChoice);

    switch (menuChoice) {
      case INSERT:
        insertData(input, registerInstance);
        break;

      case REMOVE:
        printf("Removing data");
        break;

      case QUIT:
        printf("Quiting");
        quitMenu = TRUE;
        break;

      default:
        printf("Invalid Option");
    }
  } while (quitMenu == FALSE);

  return 0;
}

int insertData(FILE* input, struct Register inputData) {
  return 1;
}

struct Register readData(FILE * input) {
  struct Register data;

  fread(&data, sizeof(char), 153, input);

  return data;
};
