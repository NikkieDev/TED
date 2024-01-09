#ifndef FS_H
#define FS_H

//win32
void create_win_dump();
void fetch_win_executable();

//unix
int create_lin_dump();
void fetch_lin_exec();

void reinstall();

#endif