#include <stdio.h>

int main() {
  int n;
  float x;
  float min=2147483647;
  (void) scanf("%d", &n);
  while (n>0) {
    (void) scanf("%f", &x);
    if (x<min) {
      min=x;
    }
    n--; 
  }
  printf("%f\n", min);
  return 0;
}
