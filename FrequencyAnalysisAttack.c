#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct table {
	char c;
	float frequency;
	struct table *next;
} table;


table* readInFile(table *alphabet, char *filename);
table* loadTable(table *alphabet, char c, float freq, int flag);
int countFrequency(FILE *input, float charCount[]);
char decrypt(char c, int key);
table* addLetter(char c, float freq);
void computeFrequency(int numChars, float charCount[]);
void pickTopShifts(table *inputFrequencies, int shifts[]);

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("\nInput file needed. Exiting...\n");
		return 0;
	}

	FILE *input = fopen(argv[1], "r");
	char pt, c;
	int i = 0, numChars, shifts[3] = {0};
   	float charCount[26] = {0};
	table *alphabet = NULL;
	
	alphabet = readInFile(alphabet, "letterFrequencies.txt");
	
	numChars = countFrequency(input, charCount);
	computeFrequency(numChars, charCount);

	printf("\nFREQUENCY ANALYSIS ATTACK ON THE SHIFT CIPHER"
			"\n--------------------------------------");

	table *inputFrequencies = NULL;
	
	int a = 0;
	while (a < 26) {
		inputFrequencies = loadTable(inputFrequencies, a+97, charCount[a], 0);
		a++;
	}
	
	pickTopShifts(inputFrequencies, shifts);
	table *temp = inputFrequencies;

	printf("\nTESTING TOP 3 SHIFT POSSIBILITIES\n");
	for (i = 0; i < 3; i++) {
		rewind(input);
		printf("\nDecryption %d/3; Shift :%d\t", i+1, shifts[i]-4);
		while((c = getc(input)) != EOF){
			pt = decrypt(c, shifts[i]-4);
			putchar(pt);
		}
	}

	printf("\n");
	fclose(input);
	return 0;
}

table* readInFile(table *alphabet, char *filename) {
	FILE *file = fopen(filename, "r");
	int i = 0;
	char c;
	float f;

	while (i++ < 26) {
		fscanf(file, "%c %f\n", &c, &f);
		alphabet = loadTable(alphabet, c, f, 1);
	}

	fclose(file);
	return alphabet;
}

table* loadTable(table *alphabet, char c, float freq, int flag) {
	table *curr = alphabet;
	table *prev = NULL;
	if (alphabet == NULL){ 
		alphabet = addLetter(c, freq);
	}
	else if ((c < alphabet->c && flag) || (freq > alphabet->frequency && !flag)) {
		alphabet = addLetter(c, freq);
		alphabet->next = curr;
	}
	else {
        prev = alphabet;
		curr = curr->next;
		while (curr != NULL && ((c > curr->c && flag) || (freq < curr->frequency && !flag))) {
			prev = curr;
			curr = curr->next;
		}
		prev->next = addLetter(c, freq);
		prev = prev->next;
		prev->next = curr;
	}

	return alphabet;
}

table* addLetter(char c, float freq) {
	table *newLetter = malloc(sizeof(table));
	newLetter->c = c;
	newLetter->frequency = freq;
	newLetter->next = NULL;
	return newLetter;
}

char decrypt(char c, int key) {
	if (isspace(c) != 0 || ispunct(c) != 0)
		return c;
	else if ((tolower(c) - key) < 97)
		return (c - key + 26);
	return (c - key);
}

int countFrequency(FILE *input, float charCount[]) {
	int numChars = 0;
	char c;
	while ((c = getc(input)) != EOF) {
		numChars++;
		if (isspace(c) != 0 || ispunct(c) != 0)
			continue;
		charCount[tolower(c) - 97]++;
	}
	return numChars;
}

void computeFrequency(int numChars, float charCount[]) {
	int i = 0;
	for (i = 0; i < 26; i++) 
		charCount[i]/=numChars;
}

void pickTopShifts(table *inputFrequencies, int shifts[]) {
	table *curr = inputFrequencies;
	int i = 0; 
	while (i < 3) {
		shifts[i] = curr->c - 97;
		curr = curr->next;
		i++;
	}
}

