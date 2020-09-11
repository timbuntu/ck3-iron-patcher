/**
 * Tested on game version 1.0.3
 * Backup your savegame in case something goes wrong
 */
#include <stdio.h>
#include <stdlib.h>

#define ERROR_ARGS    1
#define ERROR_ACCESS 2
#define ERROR_DATA    3

char* memmem(char* mem, const size_t memSize, const char* pattern, const size_t patternSize) {
    const char* end = mem + memSize;
    size_t pIndex = 0;

    while(mem < end && pIndex < patternSize) {
        if(*(mem++) == pattern[pIndex])
            ++pIndex;
        else
            pIndex = 0;
    }

    if(pIndex < patternSize-1)
        mem = NULL;
    else
        mem -= pIndex;

    return mem;
}

int main(int argc, char** argv) {
    if(argc < 2) {
        printf("Usage: %s SAVE_FILE\n", argv[0]);
        return ERROR_ARGS;
    }

    FILE* file = fopen(argv[1], "rb+");
    if(!file) {
        puts("Couldn't open file");
        return ERROR_ACCESS;
    }
    fseek(file, 0, SEEK_END);
    size_t fSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* savegame = malloc(fSize);
    fread(&savegame[0], fSize, 1, file);

    const char pattern[] = { 0x01, 0x04, 0x00, 0x50, 0x4b, 0x03, 0x04, 0x14 };
    const unsigned short pSize = 8;
    char* match = memmem(savegame, fSize, pattern, pSize);
    if(!match) {
        puts("Couldn't find neccessary data in savegame. Is it really an Ironman save?");
        return ERROR_DATA;
    }

    size_t offset = match - savegame;
    free(savegame);
    fseek(file, offset, SEEK_SET);
    char zero = 0;
    fwrite(&zero, 1, 1, file);
    fclose(file);
    puts("Successfully put savegame into semi-ironman mode. Ready to be hosted in MP.");
    puts("NOTE: You need to repatch the savegame every time you save and exit.");
    return 0;
}
