char *arr;
int arr_len;

char *rules;
int rules_len;

int width, height;

void acceptArray(char *a, int len, int w, int h) {
  arr = a;
  int arr_len = len;
  width = w;
  height = h;
}

void updateRules(char *a, int len) {}

// runs just one frame of the algorithm
void runGameAlgorithm() {
  for (int i = 0; i < arr_len; i++) {
    int x = i % width;
    int y = i / width;
  }
}

int getCell(int i) { return arr[i]; }
void setCell(int i, char value) { arr[i] = value; }