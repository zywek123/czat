/*
 GgCzacik
Copyright © 2016 Arkadiusz Kozioł
*/
#ifndef GGCFUNC
#define GGCFUNC
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
#include "minIni.h"
#include <sys/utsname.h>
#include <glib.h>
#ifdef GGCFUNC
#include "main.h"
#endif
#define sizearray(a) (sizeof(a) / sizeof((a)[0]))
char* fnick(char* nick,          int  staff);
int* onlinenum(void);
int* rback(void);
void debug(const char* txt, ...);
void addmsg(const char* text, int rec);
int get_ui(int kto);
void pfprintf(char* txt, ...);
int cmp(char* msg1, char* msg2);
char** strsplit(char* text, char* wsk);
char* strglue(char** text, char* wsk);
void msgall(const char* text, int* rec);
struct user
{
int id;
int numer;
char* nick;
int online;
int ankieta;
int staff;
int ban;
int czasban;
char* powod;
char* kto;
int czas;
char* zgoda;
int wiadomosci;
int znaki;
int wyrazy;
int wejscia;
char* opis;
char* echo;
int poke;
int tarcza;
int tarcza2;
int poke2;
int poke3;
int kostka;
int kosci;
int kieszonkowiec;
int kolo;
int moneta;
int lvl;
int xp;
int exp;
float zl;
int wejscie;
int wyjscie;
int sprej;
int spy;
int karta;
int karta2;
int kartamx;
int mpoke;
int okradanie;
int mtarcza;
int sejf;
char* zabawy;
float rabat;
int zw;
char* bufor;
char* pass;
char* method;
int czasonline;
int kicki;
int changenick;
int mssv;
};
struct fmt
{
char *format;
int formatlen;
};
#endif
