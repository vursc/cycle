#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void help() {
  puts("Usage:");
  puts("  cycle <exp> [flags]");
  puts("    Cycles the expression");
  puts("  cycle {-h, --help}");
  puts("    Prints the help message");
  puts("Flags:");
  puts("  -ab, -abc, -abcd, -xy, -xyz");
  puts("    Specifies which set of variables to cycle on (default is -abc)");
  puts("  -add, -mul");
  puts("    Specifies what operation to do with the cycle (default is -add)");
}

int main(int argc, char** argv) {
  if (argc == 1) {
    puts("Too few parameters.");
    help();
    return EXIT_FAILURE;
  }
  if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
    puts("This is cycle, a command-line utility for writing cyclic TeX math.");
    help();
    return EXIT_SUCCESS;
  }
  char st = 'a';
  int sl = 3;
  enum { MODE_ADD, MODE_MUL } mode = MODE_ADD;
  for (int i = 2; i < argc; i = i + 1) {
    if (!strcmp(argv[i], "-ab")) {
      st = 'a';
      sl = 2;
    } else if (!strcmp(argv[i], "-abc")) {
      st = 'a';
      sl = 3;
    } else if (!strcmp(argv[i], "-abcd")) {
      st = 'a';
      sl = 4;
    } else if (!strcmp(argv[i], "-xy")) {
      st = 'x';
      sl = 2;
    } else if (!strcmp(argv[i], "-xyz")) {
      st = 'x';
      sl = 3;
    } else if (!strcmp(argv[i], "-add")) {
      mode = MODE_ADD;
    } else if (!strcmp(argv[i], "-mul")) {
      mode = MODE_MUL;
    } else {
      printf("Unknown argument: %s\n", argv[i]);
      help();
      return EXIT_FAILURE;
    }
  }

  int len = strlen(argv[1]);
  for (int l = 0; l < sl; l = l + 1) {
    if (l && mode == MODE_ADD) {
      putchar(' ');
      putchar('+');
      putchar(' ');
    }
    char skip = 0;
    for (int i = 0; i < len; i = i + 1) {
      char cycled = 0;
      if (argv[1][i] == '\\') {
        skip = 1;
      } else {
        if (skip) {
          if (isalpha(argv[1][i])) {
            skip = 1;
          } else {
            skip = 0;
          }
        } else {
          if (st <= argv[1][i] && argv[1][i] < st + sl) {
            putchar(st + (argv[1][i] - st + l) % sl);
            cycled = 1;
          }
        }
      }
      if (!cycled) {
        putchar(argv[1][i]);
      }
    }
  }
  return EXIT_SUCCESS;
}

