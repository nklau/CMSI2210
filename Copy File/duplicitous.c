/*
 *  file: duplicitous.c
 *  practice with File I/O by doing the following:
 *
 *    read the command line arguments
 *    if none are present, output a usage message of how to run the
 *       program next time
 *    also if none are present, ask the user for a file name
 *    also if none are present, ask the user for an integer between 1 and 10
 *       this will be used for the number of times to copy file contents
 *    regardless of input method, set the filename into a variable called
 *       'filename'
 *    also regardless of input method, set the integer into a variable
 *       called "copies"
 *    try to open the input file and report any errors that occur
 *    if the file opens OK, read the first line from the file
 *    convert the number on the line from a string to an int; this is the
 *       count of lines to be copied to the output file ~ call this 'count'
 *    display a message: file %s is open will copy %d lines
 *    now create an output file name, using the name output.txt
 *    open the output file and report any errors that occur
 *    read each line of the input file, writing it to the output file
 *    when count lines have been written to the output, write a newline
 *       to the output file
 *    call the rewind() function to move the input file pointer back to the
 *       start of the input file JUST AFTER the first line
 *    read each line of the input file again, writing it to the output file
 *    repeat steps 14, 15, and 16 for copies times
 *    close both files
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/*
 * helper method to output instructions for the user for next time
 */
void instructions() {
   printf("\n\nThis is a file copier program.\n");
   printf("It copies a block of text multiple times to an output file.\n" );
   printf("The input file name should be given as an argument.\n" );
   printf("If one is not provided, you will be asked for it.\n" );
   printf("You must also enter a number of times to copy the text block.\n" );
   printf("The number must be an integer value 1 through 10 inclusive.\n" );
   printf("If a number is not provided, you will be asked for it.\n" );
   printf("\n\n" );
}

/*
 * main method
 *    entry point
 *    "Speak friend and enter"
 */
int main(int argc, char * argv[]) {

   char filename[250];
   char copyLine[10];

   int blocksize = 0;
   int copyCount = 0;

   if (argc >= 2) {
      strcpy(filename, argv[1]);
      copyCount = atoi(argv[2]);
      fflush(stdout);
   }

   while(filename[1] == 0 || copyCount < 1 || copyCount > 10) {
      instructions();
      printf("Enter a file name: ");
      fflush(stdout);
      fflush(stdin);
      scanf("%s", filename);
      fflush(stdout);
      printf("Enter a number from 1 through 10: ");
      fflush(stdin);
      scanf("%d", &copyCount);
   }

  /*
   * open the input file and check open error
   */
   FILE *toCopy = fopen(filename, "r");
   if (toCopy) {
      printf("...proceeding with file copy on file %s.\n", filename);
      printf("...copying file block %d times.\n", copyCount);
   } else {
      printf("%s is not a valid file.\n", filename);
      exit(0);
   }

  /*
   * read the first line of the input file to get the readline count
   */
  if (fgets(copyLine, 10, toCopy) != NULL) {
      blocksize = atoi(copyLine);
      if (blocksize == 0) {
         printf("First line of file should be a number.\n");
         exit(0);
      }
   }

   printf("File %s is open, will copy %d lines\n", filename, blocksize);

  /*
   * open the output file and check open error
   */
   FILE *outputFile = fopen("output.txt", "w");
   if (outputFile == NULL) {
      printf("File 'output.txt' cannot be opened for output.\n");
      exit(0);
   }

  /*
   * read that many lines from the input file and
   *  write them to the output file
   */
  for (int i = 0; i < copyCount; i++) {
      for (int j = 0; j < blocksize; j++) {
         if (fgets(copyLine, 100, toCopy) != NULL) {
            fputs(copyLine, outputFile);
         }
      }
      fputs("\n", outputFile);
      rewind(toCopy);
      fgets(copyLine, 10, toCopy);
   }

  /*
   * clean up after yourself
   */
   fclose(toCopy);
   fclose(outputFile);

   exit(0);
}
