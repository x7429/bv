#include <math.h> // log10()
#include <locale.h> // setlocale()

// ANSI COLORS
#define cWarning "\033[33m"
#define cError "\033[31m"
#define cPrimary "\033[36m"
#define cSecondary "\033[32m"
#define cReset "\033[00m"

#define bufLen 64
#define NUM_DIGITS(n) ((n) == 0 ? 1 : (short)(log10(n) + 1))

// WIN
#ifdef _WIN32
#include <windows.h> // ...

void setupLocale(){
    setlocale(LC_ALL, ".UTF8");
    // SetConsoleCP(CP_UTF8); // Input codepage (cin, scanf, etc.)
    SetConsoleOutputCP(CP_UTF8); // Output codepage (cout, printf, etc.)
}
long getSize(const char *filename){
    HANDLE fileHandle = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    long fileSize = -1;

    if (fileHandle != INVALID_HANDLE_VALUE){
        fileSize = GetFileSize(fileHandle, NULL);
        CloseHandle(fileHandle);
    }

    return fileSize;
}

// LIN
#else
#include <sys/stat.h> // struct stat, lstat()

void setupLocale(){ setlocale(LC_ALL, ""); }
long getSize(const char *filename){
    struct stat inode;
    if (lstat(filename, &inode) == 0) return inode.st_size;
    
    return -1;
}

#endif
