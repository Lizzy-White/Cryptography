#include <stdio.h>
#include <ctype.h>

char decrypt(char c, int key);

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("\nInput file needed. Exiting...\n");
		return 0;
	}

	FILE *input = fopen(argv[1], "r");
	char c, pt;

	printf("\nBRUTE FORCE ATTACK ON THE SHIFT CIPHER"
			"\n--------------------------------------"
			"\nPossible Decryptions:");

	for (int i = 0; i < 26; i++) {
		printf("\nDecryption %d/26:\t", i+1);
		while((c = getc(input)) != EOF){
			pt = decrypt(c, i);
			putchar(pt);
		}
		rewind(input);
	}	

	printf("\n");
	fclose(input);
	return 0;
}

char decrypt(char c, int key) {
	if (isspace(c) != 0 || ispunct(c) != 0)
		return c;
	else if ((tolower(c) - key) < 97)
		return (c - key + 26);
	return (c - key);
}
