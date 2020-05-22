#include <stdio.h>

int main() {
  int n, count=0, cnt=0;
  float x;
  float num=2147483647;
  (void) scanf("%d", &n);
  while (n>0) {
    cnt++;
    (void) scanf("%f", &x);
    if (x<=num) {
      num=x;
      count++;
    }
    n--; 
  }
  if (count==cnt) {
    printf("1\n");
  } else {
    printf("0\n");
  }  
  return 0;
}
