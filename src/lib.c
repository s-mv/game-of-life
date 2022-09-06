char *arr;

char *rules;

// this is the most inconvinient piece of code I've written
// moral of the story, don't do this
int *arr_len;
int *rules_len;
int *width, *height;

// Variable *var;

// terrible code formatting woohoo
__attribute__((import_name("consoleLog"))) void consoleLog(
    int);  // this is just console.log

void acceptArray(char *a, int len) {
  arr = a;
  *arr_len = len;
}

void acceptVariables(int *offset) {
  width = offset;
  height = offset + 1 * sizeof(int);
  arr_len = offset + 2 * sizeof(int);
  rules_len = offset + 3 * sizeof(int);
}

void updateRules(char *a, int len) {
  rules = a;
  *rules_len = len;
}

char getCell(int x, int y) {
  if (x < 0 || y < 0 || x > *width || y > *height) return 0;
  return arr[y * *width + x];
}

int getNeighbours(int x, int y) {
  return getCell(x - 1, y - 1) + getCell(x - 1, y) + getCell(x - 1, y + 1) +
         getCell(x, y - 1) + getCell(x, y + 1) + getCell(x + 1, y - 1) +
         getCell(x + 1, y) + getCell(x + 1, y + 1);
}

// runs just one frame of the algorithm
void runGameAlgorithm() {
  // just store the changes
  char changes[*arr_len];
  int changes_len = 0;

  for (int i = 0; i < *arr_len; i++) {
    // I love how *height doesn't even matter here
    // unlike in real life I guess
    int x = i % *width;
    int y = i / *width;
    int v = getNeighbours(x, y);

    for (int k = 0; k < *rules_len; k++) {
      // for example for l3=0:
      // if l AND v < 3 AND cell is already dead, only then change
      if (rules[k] == 'l' && v < rules[k + 1] - '0' &&
          !!arr[i] != !!(rules[k + 3] - '0')) {
        changes[changes_len++] = i;
        k += 5;
      } else if (rules[k] == '=' && v == rules[k + 1] - '0' &&
                 !!arr[i] != !!(rules[k + 3] - '0')) {
        changes[changes_len++] = i;
        k += 5;
      } else if (rules[k] == 'm' && v > rules[k + 1] - '0' &&
                 !!arr[i] != !!(rules[k + 3] - '0')) {
        changes[changes_len++] = i;
        k += 5;
      }
    }
  }

  for (int i = 0; changes[i] < changes_len; i++)
    arr[changes[i]] = !arr[changes[i]];
}