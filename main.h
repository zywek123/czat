/*
GGCzacik PL
Copyright © 2016 Arkadiusz Kozioł
*/
#ifndef GGC
#define GGC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "libgadu.h"
#include <mysql/mysql.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <wait.h>
#include <signal.h>
#include "cmd.h"
#ifdef GGC
#include "functions.h"
#endif
#include "minIni.h"
void check_cfg(void);
void fevent(void);
int main(int argc, char* argv[]);

#endif
