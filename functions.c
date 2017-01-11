#include "functions.h"
#define sizearray(a) (sizeof(a) / sizeof((a)[0]))
extern MYSQL conn;
extern MYSQL_RES *sqlres;
extern MYSQL_ROW row;
extern struct user *u;
extern struct gg_session *s;
struct fmt rtf(char *format_i)
{
char *format = NULL;
struct fmt zwrot;
int i, j = 0, len = 0, tmp = 0, attr = 0, color = 0, r = 0, g = 0, b = 0;

len = strlen(format_i);

format = malloc(3);
format[0] = 2;
j = 3;

for (i = 0; i < len; i++)
{
if (format_i[i] == 'b') { attr ^= GG_FONT_BOLD; continue; }
if (format_i[i] == 'i') { attr ^= GG_FONT_ITALIC; continue; }
if (format_i[i] == 'u') { attr ^= GG_FONT_UNDERLINE; continue; }
if (format_i[i] == 'n') { attr = 0x00;  continue; }

if (format_i[i] == 'c')
{
i++;
if (format_i[i] == '.')
{
attr |= GG_FONT_COLOR;
}else{
i--;
attr &= ~GG_FONT_COLOR;
color = 0;
continue;
}
color = 1;
}

if (format_i[i] == '.')
{
i++;
tmp = 0;
while (format_i[i] != '.' && i < len)
{
tmp *= 10;
tmp += (format_i[i] - 48);
i++;
}
if (color == 1 && attr != 0)
{
if (format_i[i] == '.')
{
i++;
r = 0;
while (format_i[i] != '.' && i < len)
{
r *= 10;
r += (format_i[i] - 48);
i++;
}

if (format_i[i] == '.')
{
i++;
g = 0;
while (format_i[i] != '.' && i < len)
{
g *= 10;
g += (format_i[i] - 48);
i++;
}

if (format_i[i] == '.')
{
i++;
b = 0;
while (format_i[i] != '.' && i < len)
{
b *= 10;
b += (format_i[i] - 48);
i++;
}

format = realloc(format, j + 6);
format[j] = tmp & 255;
format[j+1] = (tmp >> 8) & 255;
format[j+2] = attr | GG_FONT_COLOR;
format[j+3] = r;
format[j+4] = g;
format[j+5] = b;
j += 6;
color = 0;
}
}
}
}else{
format = realloc(format, j + 3);
format[j] = tmp & 255;
format[j+1] = (tmp >> 8) & 255;
format[j+2] = attr;
j+=3;
}
attr = 0;
}
}

format[1] = (j - 3) & 255;
format[2] = ((j - 3) >> 8) & 255;

zwrot.format = format;
zwrot.formatlen = j;

return zwrot;
}

int* onlinenum(void)
{
int fields;
int* numbers;
memset(&fields, 0, sizeof(&fields));
mysql_query(&conn, "select `numer` from `userzy` where online = 1");
sqlres = mysql_store_result(&conn);
if(mysql_num_rows(sqlres) == 0)
{
pfprintf("Brak danych do pobrania\n");
}
else
{
fields = mysql_num_fields(sqlres);
while((row = mysql_fetch_row(sqlres)))
numbers = atoi(row[0]);
mysql_free_result(sqlres);
}
return numbers;
}
int* rback(void)
{
}
char* fnick(char* nick, int staff)
{
switch(staff)
{

}
}
void debug(const char* txt, ...)
{


}
void addmsg(const char* text, int rec)
{
int strl = strlen(text);
gg_send_message_html(s, GG_CLASS_MSG, rec, text);
}
int get_ui(int kto)
{
int fields;
pfprintf("Zerowanie pamięci dla wierszy\n");
memset(&fields, 0, sizeof(&fields));
pfprintf("OK\n");
pfprintf("Wykonuję zapytanie\n");
char buf[128];
sprintf(buf, "select * from `userzy` where `numer` = %i", kto);
mysql_query(&conn, buf);
pfprintf("Pobieram wynik\n");
sqlres = mysql_store_result(&conn);
if(mysql_num_rows(sqlres) == 0)
{
pfprintf("Nic tu nie ma\n");
return -1;
}
else
{
pfprintf("Pobieram wiersze\n");
fields = mysql_num_fields(sqlres);
pfprintf("Uzupełniam strukturę użytkownika\n");
if((row = mysql_fetch_row(sqlres)))
{
char who[128];
if(row[9] != NULL) sprintf(who, "%s", row[9]);
u->id = atoi(row[0]);
u->numer = atoi(row[1]);
u->nick = row[2];
u->online = atoi(row[3]);
u->ankieta = atoi(row[4]);
u->staff = atoi(row[5]);
u->ban = atoi(row[6]);
u->czasban = atoi(row[7]);
u->powod = row[8];
u->kto = who;
printf("Za banem");
u->czas = atoi(row[10]);
u->zgoda = row[11];
u->wiadomosci = atoi(row[12]);
u->znaki = atoi(row[13]);
u->wyrazy = atoi(row[14]);
u->wejscia = atoi(row[15]);
u->opis = row[16];
u->echo = row[17];
u->poke = atoi(row[18]);
u->tarcza = atoi(row[19]);
u->tarcza2 = atoi(row[20]);
u->poke2 = atoi(row[21]);
u->poke3 = atoi(row[22]);
u->kostka = atoi(row[23]);
u->kosci = atoi(row[24]);
u->kieszonkowiec = atoi(row[25]);
u->kolo = atoi(row[26]);
u->moneta = atoi(row[27]);
u->lvl = atoi(row[28]);
u->xp = atoi(row[29]);
u->exp = atoi(row[30]);
u->zl = atof(row[31]);
u->wejscie = atoi(row[32]);
u->wyjscie = atoi(row[33]);
u->sprej = atoi(row[34]);
u->spy = atoi(row[35]);
u->karta = atoi(row[36]);
u->karta2 = atoi(row[37]);
u->kartamx = atoi(row[38]);
u->mpoke = atoi(row[39]);
u->okradanie = atoi(row[40]);
u->mtarcza = atoi(row[41]);
u->sejf = atoi(row[42]);
u->zabawy = row[43];
u->rabat = atof(row[44]);
u->zw = atoi(row[45]);
u->bufor = row[46];
u->pass = row[47];
u->method = row[48];
u->czasonline = atoi(row[49]);
u->kicki = atoi(row[50]);
u->changenick = atoi(row[51]);
u->mssv = atoi(row[52]);
return 0;
}
}
pfprintf("Zwalniam zasób\n");
mysql_free_result(sqlres);
}
void pfprintf(char* txt, ...)
{
FILE *f;
if((f = fopen("gg.log", "a")) == NULL)
{
printf("Nie można załadować pliku do zapisu!\n");
}
char buf[2048];
memset(&buf, 0, sizeof(buf));
va_list v;
va_start(v, txt);
vsprintf(buf, txt, v);
va_end(v);
char buf2[2048];
memset(&buf2, 0, sizeof(buf2));
char* mal1 = malloc(sizeof(buf));
char* mal2 = malloc(sizeof(buf2));
sprintf(buf2, "%s", buf);
fprintf(f, "%s\n", buf2);
fclose(f);
fprintf(stdout, "%s", buf2);
free(mal1);
free(mal2);
}

