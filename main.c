#include <stdio.h>	// fprintf(), FILE*, fopen(), ftell(), fclose()
#include <stdlib.h>	// exit()
#include <wchar.h>	// wchar_t, fgetws(), wprintf()
#include "./lib.h"

int main(int argc, const char **argv){
    setupLocale();
    
    if (argc != 2){
        fprintf(stderr, cWarning "usage: %s filename" cReset "\n", argv[0]);
        exit(1);
    }
    
    FILE *fp = fopen(argv[1], "r");
    if (!fp){
        fprintf(stderr, cError "File: \"%s\" does not exist" cReset "\n", argv[1]);
        exit(1);
    }
    
    wchar_t buffer[bufLen], *p;
    short padding = NUM_DIGITS(getSize(argv[1])); //, nCharL;
    long off = 0, pos = 0;
    
    while (fgetws(buffer, bufLen, fp) != NULL){
        wprintf(L"" cPrimary "%08lx" cReset "| ", off);
        
        p = buffer;
        do{ wprintf(L"%03d ", *p); }while (*++p);
        
        p = buffer;
        wprintf(L"|");
        do{	
		if (*p != '\n') wprintf(L"" cSecondary "%lc" cReset ":%0*ld ", *p, padding, pos);
		else wprintf(L"" cSecondary "\\n" cReset ":%0*ld\n", padding, pos);
		
		++pos;
	}while (*++p);
        
#ifdef _WIN32
        off = ftell(fp) + 1;
#else
        off = ftell(fp);
#endif
    }
    fclose(fp);
    
    return 0;
}