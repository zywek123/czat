/**
* GGCzacik
* Copyright © 2017 Arkadiusz Kozioł
**/
#ifndef CMDH
#define CMDH
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
#include "functions.h"
#include "minIni.h"
#include "main.h"
int preprocess_cmd(char* cmd_name);

void cmd_ver(void);
#endif

