/*****************************************************************************
 * List of header files used.
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

/*****************************************************************************
 * List of preprocessing directives used.
******************************************************************************/
int MAX_LENGTH = 128;

/******************************************************************************
 * compress() function description:
 * The 'compress()' function involves taking runs (consecutive data elements)
 * and replacing them by just one data value and count. 
 * For example, 'AAAB' will be represented as '3AB' - through encoding.   
 *
 * Inputs:
 * - None.
 *
 * Outputs:
 * - None.
******************************************************************************/
char *compress(char *decompressString) {
  /* Gets each character from the input string, declared 
  as 'decompressString'. */
  char characterGetter;
  /* 'counter': Counts how many times a letter reccurs.
  'locationInString': Shows us where we are currently in the string, 
  and allows us to place characters into the outputString correctly. */ 
  int counter = 1, locationInString = 0; 
  /* The string pointer that will be returned. */
  char* compressedString = malloc(MAX_LENGTH);

  /* Keep going until the next character retrieved is not the null character, 
  also set 'characterGetter' to be equal to the next char in the string. */
  while ((characterGetter = *decompressString++) != '\0') { 
    /* Check if the next character is different then the one held by 
    'characterGetter'. */
    if (characterGetter != *decompressString) { 
      /* Set 'encodedString' character at 'locationInString', equal to the 
      counter. */
        if (counter > 1) {
        /* Location in string is updated with how many bits have been written
        to the output to keep track of where we are adding data to. */
            locationInString += sprintf(compressedString + 
            locationInString, "%d", counter); 
        }
        /* The first iteration of while loop sets the character at 
        'locationInString++' in the string to the first character.
        Subsequent loops in 'locationInString' incrementing ensures that 
        the data is placed into the correct position. */
        *(compressedString + locationInString++) = characterGetter;
        /* Reset the counter as the next character is not the same as the
        currently held character by 'characterGetter'. */
        counter = 0;
    }
    /* Increment the counter. */
    counter++;
  }
  /* Adding the null character to the end of the string then returning it. */
  *(compressedString + locationInString) = '\0';
    
  return compressedString;
}

/******************************************************************************
 * decompress() function description: 
 * The 'decompress()' function involves taking the encoded runs and 
 * reconstructing them back to how the data was originally - before 
 * compression. For example, '3AB' will be represented as 'AAAB' - through
 * decoding. 
 *
 * Inputs:
 * - 'char' pointer of the compressed string.
 *
 * Outputs:
 * - 'char' pointer of the uncompressed string.
******************************************************************************/
char *decompress(char *compressedString) {
  char characterGetter, characterToPrint;
  int counter = 0, locationInString = 0;
  char* decompressedString = malloc(MAX_LENGTH);

  /* While the next character in the string to be decompressed is
  not the null character: */
  while ((characterGetter = *compressedString++) != '\0') {
    int i;

    /* Check to see if 'characterGetter' holds a number. */
    if (characterGetter == '2' || characterGetter == '3' ||
    characterGetter == '4' || characterGetter == '5' || 
    characterGetter == '6' || characterGetter == '7' || 
    characterGetter == '8' || characterGetter == '9') {

    /* If so, the counter gets set to the 'char' being retrieved, 
    minus '0'. */      
    counter = characterGetter - '0';
    characterToPrint = *(compressedString);

      /* While 'i' is less than the counter, reallocate the memory 
      location - towards the 'char' that's needed to be printed. */      
      for (i = 0; i < counter - 1; i++) {
        *(decompressedString + locationInString) = characterToPrint;
        locationInString++;
      }
      /* If the 'characterGetter' doesn't hold a number, reallocate the memory 
      location - towards the 'char' that's needed to be retrieved. */
    } else {
        *(decompressedString + locationInString) = characterGetter;
        locationInString++;
      }
   }
   /* Mark the string has having been fully decompressed, via null 
   terminator, i.e. the end of the string is declared. */
   *(decompressedString + locationInString) = '\0';

   return decompressedString;
}