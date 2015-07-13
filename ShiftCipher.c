#include <stdio.h>
#include <stdlib.h>

int setKey(int k);
char encrypt(int key, char c);
char decrypt(int key, char c);

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("\nOutput file needed.  Exiting...\n");
		return 0;
	}

	int k, key;
	char e, d, pt, ct;
	FILE *output = fopen(argv[1], "w");

	printf("\nSHIFT CIPHER\n-----------------------------------\n");
	printf("\nEnter a numeric key: ");
	scanf("%d", &k);
	
	key = setKey(k);
	
	getchar();

	printf("\n\nEnter the plaintext message to encrypt: \n");
		
	while((e = getchar()) != '\n') {
		ct = encrypt(key, e);
		putchar(ct);
		putc(ct, output);
	}

	printf("\n\nEnter the ciphertext message to decrypt: \n");
	
	while((d = getchar()) != '\n') {
		pt = decrypt(key, d);
		putchar(pt);
	}
	
	fclose(output);

	printf("\n");
	return 0;
}

int setKey(int k) {
	return (abs(k) % 26);
}

char encrypt(int key, char c) {
	if (isspace(c) != 0 || ispunct(c) != 0)
		return c;
	else if ((tolower(c) + key) > 122)
		return (c + key - 26);
	return (c + key);
}

char decrypt(int key, char c) {
	if (isspace(c) != 0 || ispunct(c) != 0)
		return c;
	else if((tolower(c) - key) < 97)
		return (c - key + 26);
	return (c - key);
}
