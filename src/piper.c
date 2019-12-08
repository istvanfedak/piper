#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

char * NILL[] = {NULL};

int piperHelper(int argc, char* argv[], int i, int pp[])
{ 
  if(i + 1 == argc)
  {
    close(STDOUT_FILENO);
    dup(pp[STDOUT_FILENO]);
    close(pp[0]);
    close(pp[1]);

    fprintf(stderr, "%s\n", argv[argc - i]);

    execvp(argc[argv - i], NILL);
    exit(1);
 
  }
  else {
    int p[2];
    if(pipe(p) == -1) {
      fprintf(stderr, "Pipe failed\n");
      exit(1);
    }

    if(fork() == 0)
      piperHelper(argc, argv, i + 1, p);

    else {
      close(STDIN_FILENO);
      close(STDOUT_FILENO);
      dup(p[STDIN_FILENO]);
      dup(pp[STDOUT_FILENO]);
      close(p[0]);
      close(p[1]);
      close(pp[0]);
      close(pp[1]);
      wait(NULL);

      fprintf(stderr, "%s\n", argv[i]);
      execvp(argv[i], NILL);
      exit(1);
    }
  }
  return 0;
}

int piper(int argc, char* argv[], int i)
{
  int p[2];
  if(pipe(p) == -1) {
    fprintf(stderr, "Pipe failed\n");
    exit(1);
  }

  if(fork() == 0)
    piperHelper(argc, argv, i + 1, p);

  else {
    close(STDIN_FILENO);
    dup(p[STDIN_FILENO]);
    close(p[0]);
    close(p[1]);
    wait(NULL);

    fprintf(stderr, "%s\n", argv[argc - i]);
    execvp(argv[argc - i], NILL);
    exit(1);
  }
  return 0;
}

int main(int argc, char * argv[]) {
  return piper(argc, argv, 1);
}

