#ifndef FS_H
#define FS_H
#endif

// windows only
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

void create_win_dump();
void fetch_win_executable();

#else // unix only
#endif // Global
