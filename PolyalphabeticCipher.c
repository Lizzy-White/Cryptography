#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int* setKey(char k, int *key, int keySize);
char encrypt(int *key, char c, int keyPos);
char decrypt(int *key, char c, int keyPos);
int setKeyPos(int keyPos, int keySize);

int main(void) {
	int	*key = NULL;
	int keySize = 0, keyPos = -1;
	char e, d, pt, ct, k;

	printf("\nPOLYALPHABETIC CIPHER\n-----------------------------------\n");
	printf("\nEnter an alphabetic key: \n");
	
	while((k = getchar()) != '\n') {
		key = setKey(k, key, ++keySize);
	}
	
	printf("\n\nEnter the plaintext message to encrypt: \n");
		
	while((e = getchar()) != '\n') {
		if(!isspace(e) && !ispunct(e)) {
			keyPos = setKeyPos(keyPos, keySize);	
			pt = encrypt(key, e, keyPos);
			putchar(pt);
		}
		else
			putchar(e);
	}

	keyPos = -1;
	printf("\n\nEnter the ciphertext message to decrypt: \n");
	
	while((d = getchar()) != '\n') {
		if (!isspace(d) && !ispunct(d)) {
			keyPos = setKeyPos(keyPos, keySize);
			ct = decrypt(key, d, keyPos);
			putchar(ct);
		}
		else
			putchar(d);
	}

	printf("\n");
	return 0;
}

int* setKey(char k, int *key, int keySize) {
	if (keySize == 1) 
		key = malloc(sizeof(int));
	else 
		key = realloc(key, sizeof(int)*keySize);
	*(key + keySize - 1) = tolower(k) - 96;
	return key;
}

char encrypt(int *key, char c, int keyPos) {
	if ((tolower(c) + *(key + keyPos)) > 122)
		return (c + *(key + keyPos) - 26);
	return (c + *(key + keyPos));
}

char decrypt(int *key, char c, int keyPos) {
	if((tolower(c) - *(key + keyPos)) < 97)
		return (c - *(key + keyPos) + 26);
	return (c - *(key + keyPos));
}

int setKeyPos(int keyPos, int keySize) {
	keyPos++;
	if (keyPos >= keySize)
		keyPos -= keySize;
	return keyPos;
}
