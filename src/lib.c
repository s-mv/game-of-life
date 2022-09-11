char old_arr[100 * 100];

char rules[1024];

int arr_len;
int rules_len;
int width, height;
char new_arr[100 * 100];

// terrible code formatting woohoo
__attribute__((import_name("consoleLog"))) void consoleLog(
    int);  // this is just console.log

char *acceptArray(int w, int h) {
  width = w;
  height = h;
  arr_len = w * h;
  return old_arr;
}

void copyArray(char *to_be_copied, char *to_copy_to, int len) {
  for (int i = 0; i < len; i++) {
    to_copy_to[i] = to_be_copied[i];
  }
}

void updateRules(char *a, int len) {
  for (int i = 0; i < len; i++) rules[i] = a[i];
  rules_len = len;
}

char getCell(int x, int y) {
  if (x < 0 || y < 0 || x > width || y > height) return 0;
  return old_arr[y * width + x];
}

int getNeighbours(int x, int y) {
  return getCell(x - 1, y - 1) + getCell(x - 1, y) + getCell(x - 1, y + 1) +
         getCell(x, y - 1) + getCell(x, y + 1) + getCell(x + 1, y - 1) +
         getCell(x + 1, y) + getCell(x + 1, y + 1);
}

// runs just one frame of the algorithm
void runGameAlgorithm() {
  copyArray(old_arr, new_arr, arr_len);

  for (int i = 0; i < arr_len; i++) {
    // I love how height doesn't even matter here
    // unlike in real life I guess
    int x = i % width;
    int y = i / width;
    int v = getNeighbours(x, y);
    // for example for l3=0:
    // if l AND v < 3 AND cell is already dead, only then change
    for (int k = 0; k <= rules_len; k += 5) {
      if ((rules[k] == 'l' && v < rules[k + 1] - '0' &&
           !!old_arr[i] != !!(rules[k + 3] - '0')) ||
          (rules[k] == '=' && v == rules[k + 1] - '0' &&
           !!old_arr[i] != !!(rules[k + 3] - '0')) ||
          (rules[k] == 'm' && v > rules[k + 1] - '0' &&
           !!old_arr[i] != !!(rules[k + 3] - '0'))) {
        if (new_arr[i] == 1) consoleLog(new_arr[i]);
        new_arr[i] = new_arr[i] ? 0 : 1;
      }
    }
  }

  copyArray(new_arr, old_arr, arr_len);  // this is so tedious, read end notes
}
// NOTES
// I HATE THIS I HATE THIS
// my original plan was to have a LOCAL array called changes
// it would hold only the indices that had changed, not everything
// but C WASM memory allocation is bad