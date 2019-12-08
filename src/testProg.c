#include <stdio.h>



int getString(char arr[], int size, FILE * fp)
{
  char c;
  int i;
  for(i = 0; i < size; i++) {
    c = getc(fp);
    if(c == '\n' || c == '\0' || c == EOF)
      return i;
    arr[i] = c;
  }
  return i;
}

int main() {
  char buff[256];
  getString(buff, sizeof(buff), stdin);
  fprintf(stdout,"%s\n", buff);
  return 0;
}
