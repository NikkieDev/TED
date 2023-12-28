#ifndef FS_H
#define FS_H
#endif

// windows only
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

void create_windows_dump();

#else // unix only
#endif // Global
