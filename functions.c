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
char buf[256];
sprintf(buf, "select `numer` from `userzy` where `online` = 1 and not `numer` =%d", u->numer);
mysql_query(&conn, buf);
sqlres = mysql_store_result(&conn);
if(mysql_num_rows(sqlres) == 0)
{
pfprintf("Brak danych do pobrania\n");
}
else
{
fields = mysql_num_fields(sqlres);
while((row = mysql_fetch_row(sqlres)))
*numbers = *row[0];
mysql_free_result(sqlres);
}
return numbers;
}
int* rback(void)
{
int fields;
int* numbers;
memset(&fields, 0, sizeof(&fields));
char buf[256];
sprintf(buf, "select `numer` from `userzy` where `online` = 1");
mysql_query(&conn, buf);
sqlres = mysql_store_result(&conn);
if(mysql_num_rows(sqlres) == 0)
{
pfprintf("Brak danych do pobrania\n");
}
else
{
fields = mysql_num_fields(sqlres);
while((row = mysql_fetch_row(sqlres)))
*numbers = *row[0];
mysql_free_result(sqlres);
}
return numbers;
}
char* fnick(char* nick, int staff)
{
char* ret;
memset(&ret, 0, sizeof(&ret));
char* unick;
memset(&unick, 0, sizeof(&unick));
switch(staff)
{
case 1:
	    unick = "$";
	    break;
	 case 2:
	    unick = "$";
	    break;
	 case 3:
	    unick = "$";
	    break;
	 case 4:
	    unick = "$";
	    break;
	 case 5:
	    unick = "+";
	    break;
	 case 6:
	    unick = "+";
	    break;
         case 7:
	    unick = "+";
	    break;
	 case 8:
	    unick = "+";
	    break;
	 case 9:
	    unick = "+";
	    break;
	 case 10:
	    unick = "%";
	    break;
	 case 11:
	    unick = "%";
	    break;
	 case 12:
	    unick = "%";
	    break;
	 case 13:
	    unick = "%";
	    break;
	 case 14:
            unick = "%";
	    break;
	 case 15:
	    unick = "@";
	    break;
	 case 16:
	    unick = "@";
	    break;
	 case 17:
	    unick = "@";
	    break;
	 case 18:
	    unick = "@";
	    break;
	 case 19:
	    unick = "@";
	    break;
         case 20:
	    unick = "~";
	    break;
	 case 21:
	    unick = "~";
	    break;
	 case 22:
	    unick = "~";
	    break;
	 case 23:
	    unick = "~";
	    break;
	 case 24:
	    unick = "~";
	    break;
	 case 25:
	    unick = "~";
	    break;
	 case 27:
	    unick = "~";
	    break;
	 case 28:
	    unick = "~";
	    break;
	 case 29:
	    unick = "~";
	    break;
	 case 30:
	    unick = "~";
	    break;
	 case 31:
	    unick = "~";
	    break;
	 case 32:
	    unick = "~";
	    break;
	 case 33:
	    unick = "~";
	    break;
         case 34:
	    unick = "~";
	    break;
	 case 35:
	    unick = "~";
	    break;
	 case 36:
	    unick = "~";
	    break;
	 case 37:
	    unick = "~";
	    break;
	 case 38:
	    unick = "~";
	    break;
	 case 39:
	    unick = "~";
	    break;
	 case 40:
	    unick = "~";
	    break;
	 case 41:
	    unick = "~";
	    break;
	 case 42:
	    unick = "~";
	    break;
	 case 43:
	    unick = "~";
	    break;
	 case 44:
	    unick = "~";
	    break;
	 case 45:
	    unick = "~";
	    break;
	 case 46:
	    unick = "~";
	    break;
         case 47:
	    unick = "~";
	    break;
	 case 48:
	    unick = "~";
	    break;
	 case 49:
	    unick = "~";
	    break;
	 case 50:
	    unick = "#";
	    break;
	 case 51:
	    unick = "#";
	    break;
	 case 52:
	    unick = "#";
	    break;
	 case 53:
	    unick = "#";
	    break;
	 case 54:
            unick = "#";
	    break;
	 case 55:
	    unick = "#";
	    break;
	 case 56:
	    unick = "#";
	    break;
	 case 57:
	    unick = "#";
	    break;
	 case 58:
	    unick = "#";
	    break;
	 case 59:
	    unick = "#";
	    break;
         case 60:
	    unick = "?#";
	    break;
	 case 61:
	    unick = "?#";
	    break;
	 case 62:
	    unick = "?#";
	    break;
	 case 63:
	    unick = "?#";
	    break;
	 case 64:
	    unick = "?#";
	    break;
	 case 65:
	    unick = "?#";
	    break;
	 case 67:
	    unick = "?#";
	    break;
	 case 68:
	    unick = "?#";
	    break;
	 case 69:
	    unick = "?#";
	    break;
	 case 70:
	    unick = "@#";
	    break;
	 case 71:
	    unick = "@#";
	    break;
	 case 72:
	    unick = "@#";
	    break;
	 case 73:
	    unick = "@#";
	    break;
         case 74:
	    unick = "@#";
	    break;
	 case 75:
	    unick = "@#";
	    break;
	 case 76:
	    unick = "@#";
	    break;
	 case 77:
	    unick = "@#";
	    break;
	 case 78:
	    unick = "@#";
	    break;
	 case 79:
	    unick = "@#";
	    break;
	 case 80:
	    unick = "?@#";
	    break;
	 case 81:
	    unick = "?@#";
	    break;
         case 82:
	    unick = "?@#";
	    break;
	 case 83:
	    unick = "?@#";
	    break;
	 case 84:
	    unick = "?@#";
	    break;
	 case 85:
	    unick = "?@#";
	    break;
	 case 86:
	    unick = "?@#";
	    break;
	 case 87:
	    unick = "?@#";
	    break;
	 case 88:
	    unick = "?@#";
	    break;
	 case 89:
	    unick = "?@#";
	    break;
	 case 90:
	    unick = "?#?";
	    break;
	 case 91:
	    unick = "?#?";
	    break;
	 case 92:
	    unick = "?#?";
	    break;
	 case 93:
	    unick = "?#?";
	    break;
	 case 94:
	    unick = "?#?";
	    break;
         case 95:
	    unick = "?#?";
	    break;
	 case 96:
	    unick = "?#?";
	    break;
	 case 97:
	    unick = "?#?";
	    break;
	 case 98:
	    unick = "?#?";
	    break;
	 case 99:
	    unick = "?#?";
	    break;
	 case 100:
	    unick = "##";
	    break;
	 case 101:
	    unick = "?##";
	    break;
	 case 150:
	    unick = "?##";
	    break;
	   default:
	    unick = "";
	    break;
}
sprintf(ret, "<%s%s>", unick, nick);
return ret;
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
u->id = *row[0];
u->numer = *row[1];
u->nick = row[2];
u->online = *row[3];
u->ankieta = *row[4];
u->staff = *row[5];
u->ban = *row[6];
u->czasban = *row[7];
u->powod = row[8];
u->kto = who;
u->czas = *row[10];
u->zgoda = row[11];
u->wiadomosci = *row[12];
u->znaki = *row[13];
u->wyrazy = *row[14];
u->wejscia = *row[15];
u->opis = row[16];
u->echo = row[17];
u->poke = *row[18];
u->tarcza = *row[19];
u->tarcza2 = *row[20];
u->poke2 = *row[21];
u->poke3 = *row[22];
u->kostka = *row[23];
u->kosci = *row[24];
u->kieszonkowiec = *row[25];
u->kolo = *row[26];
u->moneta = *row[27];
u->lvl = *row[28];
u->xp = *row[29];
u->exp = *row[30];
u->zl = *row[31];
u->wejscie = *row[32];
u->wyjscie = *row[33];
u->sprej = *row[34];
u->spy = *row[35];
u->karta = *row[36];
u->karta2 = *row[37];
u->kartamx = *row[38];
u->mpoke = *row[39];
u->okradanie = *row[40];
u->mtarcza = *row[41];
u->sejf = *row[42];
u->zabawy = row[43];
u->rabat = *row[44];
u->zw = *row[45];
u->bufor = row[46];
u->pass = row[47];
u->method = row[48];
u->czasonline = *row[49];
u->kicki = *row[50];
u->changenick = *row[51];
u->mssv = *row[52];
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
int cmp(char* msg1, char* msg2)
{
return strcmp(msg1, msg2);
}
