#ifndef FS_H
#define FS_H

//win32
  #if defined(WIN32)
    void create_win_dump();
    void fetch_win_executable();
  #endif
//unix

  #ifdef __unix__
    void linux_install();
    int create_lin_dump();
    void fetch_lin_exec();

    void uninstall();
    void reinstall();
  #endif

#endif