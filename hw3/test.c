#include <stdio.h>
#include <string.h>
#include "globals.h"

char fontBuffer[MAXFONTSIZE];
char* cGramLookup[MAXNUMCGRAMS];
int cGramWidth[MAXNUMCGRAMS];

void printCGram(const char c);
int readFontBuffer(const char *fontFile);

int main()
{
	char *fontFile = "/home/hotan/school/C/testhw3/cse30.font"; //change this path 
	readFontBuffer(fontFile);
	printCGram('c');
	return 0;

}
/* Reads the font file and copies the cGram symbols into the fontBuffer
 * array, recording the starting location and the max width of each cGram
 * in the cGramLookup and cGramWidth arrays. Note that these 2 arrays are
 * indexed with an offset of -FIRSTCHAR (i.e. char 'a' data will be in
 * cGramLookup['a' - FIRSTCHAR], etc.) */
int readFontBuffer(const char *fontFile) {
	FILE *fontFilePtr;
	char *fontLine;
	char *fontBufferPtr = fontBuffer;
	
	// Variable to index into cGramLookup and cGramWidth as cGrams are read from the font file
	int charIdx = 0;
	
	// Variable to keep track of the longest line per cGram, reset to 0 per cGram
	int maxWidth = 0;

	// This opens the file m and handles file IO errors
	if((fontFilePtr = fopen(fontFile, "r")) == NULL) {
		return -1;
	}

	// We found it easier to handle the very first cGram separately; feel free to change!
	cGramLookup[charIdx] = fontBufferPtr;

	while((fontLine = fgets(fontBufferPtr, MAXFONTLINESIZE, fontFilePtr)) != NULL) {
		fontBufferPtr += strlen(fontLine);
		maxWidth += (strlen(fontLine));
		if(*fontLine == FONTDELIM){

			cGramWidth[charIdx++] = maxWidth-(strlen(fontLine));
			if(charIdx == MAXNUMCGRAMS) break;
			cGramLookup[charIdx] = fontBufferPtr;
			maxWidth = 0;
		}
	}

	// The file is closed after use
	fclose(fontFilePtr);
	return 0;
}


/* Looks up the specified char's cGram and prints it to stdout. */
void printCGram(const char c) {
	char* cGram = cGramLookup[c-FIRSTCHAR];
	for(int i = 0; i < cGramWidth[c-FIRSTCHAR];i++){
		printf("%c", *cGram++);
	}
}
