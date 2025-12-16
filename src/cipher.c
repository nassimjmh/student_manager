#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/cipher.h"

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void generateMasterKey(const char* passphrase, unsigned char* key) {
    memset(key, 0, KEY_SIZE);
    
    int passLen = strlen(passphrase);
    if (passLen == 0) return;

    for (int i = 0; i < passLen; i++) {
        unsigned char c = (unsigned char)passphrase[i];
        
        int currentIdx = i % KEY_SIZE;
        int nextIdx = (currentIdx + 1) % KEY_SIZE;
        int prevIdx = (currentIdx - 1 + KEY_SIZE) % KEY_SIZE;

        key[currentIdx] ^= c;
        key[nextIdx] += c;
        key[prevIdx] *= c; 
    }
}

int API_cipher(char* pIn, char* pOut) {
    FILE *fin = fopen(pIn, "rb");
    FILE *fout = fopen(pOut, "wb");

    if (!fin || !fout) {
        fprintf(stderr, "Erreur d'ouverture des fichiers (I/O).\n");
        if (fin) fclose(fin);
        if (fout) fclose(fout);
        return 0;
    }

    char passphrase[256];
    printf("Entrez la phrase de passe pour chiffrer : ");
    if (fgets(passphrase, sizeof(passphrase), stdin)) {
        passphrase[strcspn(passphrase, "\n")] = 0; // Retirer le \n = *Enter*
    }

    unsigned char masterKey[KEY_SIZE];
    generateMasterKey(passphrase, masterKey);

    unsigned char fileKey[KEY_SIZE];
    srand(time(NULL));
    for (int i = 0; i < KEY_SIZE; i++) {
        fileKey[i] = rand() % 256;
    }

    unsigned char encryptedHeader[KEY_SIZE];
    for (int i = 0; i < KEY_SIZE; i++) {
        encryptedHeader[i] = fileKey[i] ^ masterKey[i];
    }
    fwrite(encryptedHeader, 1, KEY_SIZE, fout);

    int c;
    int index = 0;
    while ((c = fgetc(fin)) != EOF) {
        unsigned char chiffr = c ^ fileKey[index % KEY_SIZE];
        fputc(chiffr, fout);
        index++;
    }

    printf("[Succès] Fichier '%s' chiffré vers '%s'.\n", pIn, pOut);

    fclose(fin);
    fclose(fout);
    return 1;
}

int API_decipher(char* pIn, char* pOut) {
    FILE *fin = fopen(pIn, "rb");
    FILE *fout = fopen(pOut, "wb");

    if (!fin || !fout) {
        fprintf(stderr, "Erreur d'ouverture des fichiers (I/O).\n");
        if (fin) fclose(fin);
        if (fout) fclose(fout);
        return 0;
    }

    char passphrase[256];
    printf("Entrez la phrase de passe pour déchiffrer : ");
    // clearBuffer(); 
    if (fgets(passphrase, sizeof(passphrase), stdin)) {
        passphrase[strcspn(passphrase, "\n")] = 0;
    }

    unsigned char masterKey[KEY_SIZE];
    generateMasterKey(passphrase, masterKey);

    unsigned char encryptedHeader[KEY_SIZE];
    if (fread(encryptedHeader, 1, KEY_SIZE, fin) != KEY_SIZE) {
        fprintf(stderr, "Erreur : Fichier trop court ou corrompu.\n");
        fclose(fin);
        fclose(fout);
        return 0;
    }

    unsigned char fileKey[KEY_SIZE];
    for (int i = 0; i < KEY_SIZE; i++) {
        fileKey[i] = encryptedHeader[i] ^ masterKey[i];
    }

    int c;
    int index = 0;
    while ((c = fgetc(fin)) != EOF) {
        unsigned char dechiffr = c ^ fileKey[index % KEY_SIZE];
        fputc(dechiffr, fout);
        index++;
    }

    printf("[Succès] Fichier '%s' déchiffré vers '%s'.\n", pIn, pOut);

    fclose(fin);
    fclose(fout);
    return 1;
}