#define NO_CHANGE (42)

char *arr;
int arr_len;

char *rules = "l2=0 m3=0 =3=1";  // default rules
int rules_len = 15;

int width, height;

void acceptArray(char *a, int len, int w, int h) {
  arr = a;
  int arr_len = len;
  width = w;
  height = h;
}

void updateRules(char *a, int len) {}

char getCell(int x, int y);
int getNeighbours(int x, int y);

// runs just one frame of the algorithm
void runGameAlgorithm() {
  // just store the changes
  char changes[arr_len];
  int no_change_len;

  for (int i = 0; i < arr_len; i++) {
    // I love how height doesn't even matter here
    // unlike in real life I guess
    int x = i % width;
    int y = i / width;
    int v = getNeighbours(x, y);
  }
  changes[no_change_len] = NO_CHANGE;

  for (int i = 0; changes[i] != NO_CHANGE; i++)
    arr[changes[i]] = !arr[changes[i]];
}

char getCell(int x, int y) {
  if (x < 0 || y < 0 || x > width || y > height) return 0;
  return arr[y * width + x];
}

int getNeighbours(int x, int y) {
  return getCell(x - 1, y - 1) + getCell(x - 1, y) + getCell(x - 1, y + 1) +
         getCell(x, y - 1) + getCell(x, y + 1) + getCell(x + 1, y - 1) +
         getCell(x + 1, y) + getCell(x + 1, y + 1);
}
