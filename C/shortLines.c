// Garett MacGowan 10197107
// Areege Chaudhary 10197607

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

int sigNumber = 0;
int count = 0;
char *argv1, *argv2;

void intCatcher(int signo) {
  printf("The program is exiting early because control-C was typed!\n");
  remove(argv2);
  exit(0);
} //end catcher

void usr1Catcher(int signo) {
  if (sigNumber < 3) {
    printf("Input file: %s\tOutput file: %s\n", argv1, argv2);
    sigNumber++;
  } //end if
} //end catcher

void usr2Catcher(int signo) {
  if (sigNumber < 3) {
    printf("This program has read %d lines from the input file so far.", count);
    sigNumber++;
  } // end if
} // end catcher

int main (int argc, char *argv[]) {
  argv1 = argv[1];
  argv2 = argv[2];
  // link signals to catchers
  signal(SIGINT, intCatcher);
  signal(SIGUSR1, usr1Catcher);
  signal(SIGUSR2, usr2Catcher);

  FILE *f1, *f2;
  f1 = fopen(argv[1], "r");
  f2 = fopen(argv[2], "w");
  char *error;
  long int desiredLength = strtol(argv[3], &error, 10);

  if (*error != '\n' && *error != '\0') {
    fprintf(stderr, "Line length is not in numerical format!\n");
    exit(1);
  } // end if
  if (desiredLength < 0) {
    fprintf(stderr, "Line length is not greater than zero!\n");
    exit(2);
  } //end if
  desiredLength += 1;
  if (argc != 4) {
    fprintf(stderr, "There should be three command line arguments!\n");
    exit(3);
  } //end if
  if (f1 == NULL) {
    fprintf(stderr, "Error: %s\n", strerror(errno));
    exit(4);
  } //end if 
  if (f2 == NULL) {
    fprintf(stderr, "Error: %s\n", strerror(errno));
    exit(5);
  } //end if
  else {
    char c[desiredLength];
    char dump[4095];
    char *readFail;
    int writeFail;
    while (readFail = fgets(c, desiredLength, f1)) {
      if (c[0] == '\n') {
	count++;
	continue;
      } //end if
      if (strchr(c, '\n')) {
	count++;
	printf("%s", c);
	writeFail = fputs(c, f2);
      } //end if
      else {
	count++;
	printf("%s\n", c);
        writeFail = fputs(strcat(c, "\n"), f2);
      } //end else
      if (strchr(c, '\n')) {
	fgets(dump, 4095, f1); // dump remaining characters.
      } //end if
      if (writeFail == EOF) {
	fprintf(stderr, "Error: %s\n", strerror(errno));
      } //end if
    } //end while
    if ((readFail == NULL) && (errno != 0)) {
      fprintf(stderr, "Error: %s\n", strerror(errno));
      exit(6);
    } //end if
  } //end else
  return 0;
} //end main
