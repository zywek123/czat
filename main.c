#include "main.h"

struct gg_session *s;
struct gg_event *e;
struct gg_login_params p;
struct user *u;
gg_pubdir50_t req;
gg_pubdir50_t res;
MYSQL conn;
MYSQL_RES *sqlres;
MYSQL_ROW row;
int msgc=0;
int ticket = 1;
int blokada_opisu;
static time_t czas = 0;
int szukany,num_seq,tencoszuka;
void sig_chld(int signo)
{
	pid_t	pid;
	int		stat;

	while ( (pid = waitpid(pid, &stat, WNOHANG)) > 0) {
		 printf("child %d terminated\n", pid);
	}
	return;
}


void sig_quit(int signo)
{
    gg_change_status_descr(s, GG_STATUS_NOT_AVAIL_DESCR, "dobranoc! :)");
    gg_logoff(s);
    gg_free_session(s);
    remove("gg.pid");
    exit(0);
}


void polacz(void)
{
    while ((s = gg_login(&p)) < 0) {
        printf("Cannot connect: %s\n", strerror(errno));
		fflush(0);
    }
}


void check_cfg(void)
{
pfprintf("Odczytuje nr gg z pliku \n");
int gg;
char pass[128];
memset(&gg, 0, sizeof(gg));
memset(&pass, 0, sizeof(pass));
pfprintf("Zerowanie pamięci\n");
gg = ini_getl("gg", "NumerGg", -1, "gg.cfg");
char* mal1 = malloc(sizeof(gg));
pfprintf("Alokowano\n");
ini_gets("gg", "pass", "fail", pass, sizearray(pass), "gg.cfg");
char* mal2 = malloc(sizeof(pass));
pfprintf("Alokowano\n");
pfprintf("Logowanie...\n");
p.uin = gg;
p.password = strdup(pass);
free(mal1);
free(mal2);
}


void fevent(void)
{
pfprintf("Zerowanie %i bajtów pamięci dla struktury użytkownika\n", sizeof(&u));
memset(&u, 0, sizeof(&u));
pfprintf("Zgadza się\n");
    if (!(e = gg_watch_fd(s))) {
        perror("Descriptor Error: \n");
	    gg_logoff(s);
    	gg_free_session(s);
        polacz();
		return;
    }
pfprintf("Oczekiwanie na zdarzenie\n");
    switch (e->type) {
        case GG_EVENT_NONE:
            pfprintf("Łączenie\n");
            break;
        case GG_EVENT_PONG:
            pfprintf("Serwer odesłał pong\n");
            break;
        case GG_EVENT_CONN_SUCCESS:
            perror("Connected");
char description[100];
ini_gets("gg", "description", "fail", description, sizearray(description), "gg.cfg");
gg_change_status_descr(s, GG_STATUS_AVAIL_DESCR, description);
gg_notify(s, NULL, 0);
break;
        case GG_EVENT_CONN_FAILED:
            perror("Cannot connect\n");
	        polacz();
            break;
        case GG_EVENT_MSG:
pfprintf("Alokowanie pamięci dla struktury użytkownika... Rozmiar: %d bajtów\n", sizeof(&u));
if(!(u = malloc(sizeof(*u))))
{
printf("Błąd alokowania pamięci!\n");
exit(1);
}
pfprintf("Pobranie numeru\n");
if(get_ui(e->event.msg.sender) != 0)
{
pfprintf("Użytkownik o nr %d nie istnieje w bazie danych!", e->event.msg.sender);
if(strcmp(e->event.msg.message,"/join") != 0 || strcmp(e->event.msg.message,".join") != 0 || strcmp(e->event.msg.message,"/dodaj") != 0 || strcmp(e->event.msg.message,".dodaj") != 0)
{
addmsg("Nie jesteś zarejestrowany! wpisz /dodaj ...", e->event.msg.sender);
free(u);
break;
}
}
else
{
pfprintf("Użytkownik istnieje\n");
if(u->online == 0)
{
pfprintf("Użytkownik nie jest zalogowany\n");
if(strcmp(e->event.msg.message,"/join") != 0 || strcmp(e->event.msg.message,".join") != 0 || strcmp(e->event.msg.message,"/j") != 0 || strcmp(e->event.msg.message,".j") != 0)
{
pfprintf("Użytkownik %d nie wpisał ani .join, ani /join, ani .j ani /j\n", u->numer);
addmsg("Nie jesteś zalogowany! Wpisz /join, aby się zalogować. :)", u->numer);
free(u);
break;
}
}
}
if(u->online == 1 && u->zw == 1)
{
addmsg("Jesteś na zw. Nie możesz pisać", u->numer);
free(u);
break;
}

break;

        case GG_EVENT_PUBDIR50_SEARCH_REPLY:

     		break;

        case GG_EVENT_NOTIFY:
	pfprintf("Pobrano listę.\n");
             break;

	 case GG_EVENT_NOTIFY60:

pfprintf("GG_EVENT_NOTIFY60: Pobrano listę\n");
         break;

	 case GG_EVENT_USERLIST:

 break;

     case GG_EVENT_STATUS:
pfprintf("Ktoś %d zmienił status %d\n", e->event.status.uin, e->event.status.status);
         break;

	 case GG_EVENT_STATUS60:
pfprintf("Ktoś %d zmienił status %d\n", e->event.status60.uin, e->event.status60.status);
         break;


     case GG_EVENT_ACK:
pfprintf("Dostarczono do %d", e->event.ack.recipient);
break;

    }
    gg_event_free(e);
}


int main(int argc, char **argv)
{
    gg_debug_level = 0;
    struct timeval czas_selecta;
    time_t czas_kick =0 ;
//    extern int ticket;
    memset(&p, 0, sizeof(p));
    p.async = 1;
    p.status = GG_STATUS_AVAIL;
p.encoding = GG_ENCODING_UTF8;
    czas= time(NULL);
    czas_kick= time(NULL);
    FILE *plik;

    if (argc==2 && strcmp(argv[1],"-V")==0){
	printf("1.0.0\n");
	exit (1);
    }


    if ((plik = fopen("gg.PID","w")) == NULL) {
pfprintf("Saving PID");
         exit (1);
     }

fprintf(plik,"%d",getpid());
     fclose(plik);
mysql_init(&conn);
char host[128];
char login[128];
char passwd[128];
char base[128];
memset(&host, 0, sizeof(host));
memset(&login, 0, sizeof(login));
memset(&passwd, 0, sizeof(passwd));
memset(&base, 0, sizeof(base));
ini_gets("db", "host", "localhost", host, sizearray(host), "gg.cfg");
char* memhost = malloc(sizeof(host));
ini_gets("db", "user", "root", login, sizearray(login), "gg.cfg");
char* memlogin = malloc(sizeof(login));
ini_gets("db", "pass", "nopass", passwd, sizearray(passwd), "gg.cfg");
char* mempasswd = malloc(sizeof(passwd));
ini_gets("db", "name", "base", base, sizearray(base), "gg.cfg");
char* membase = malloc(sizeof(base));
pfprintf("Connecting to %s %s %s %s\n", host, login, passwd, base);
if(!mysql_real_connect(&conn, host, login, passwd, base, 0, NULL, 0))
{
pfprintf("#%i: %s", mysql_errno(&conn), mysql_error(&conn));
exit(1);
}
free(memhost);
free(memlogin);
free(mempasswd);
free(membase);
    check_cfg();
pfprintf("Connecting ...\n");
	fflush(0);

    signal(SIGCHLD, sig_chld);
    signal(SIGQUIT, sig_quit);
    signal(SIGTERM, sig_quit);
    signal(SIGINT, sig_quit);
signal(SIGABRT, sig_quit);
    polacz();

    while (1) {
        fd_set rd, wr, ex;
        FD_ZERO(&rd);
        FD_ZERO(&wr);
        FD_ZERO(&ex);



        if (s && s->state == GG_STATE_CONNECTED && time(NULL) - czas > 60) {
			msgc=0;
            pfprintf("Time to ping ...\n");
            if (czas) {
                gg_ping(s);
            }
            czas = time(NULL);
        }

        if ((s->check & GG_CHECK_READ))
            FD_SET(s->fd, &rd);
        if ((s->check & GG_CHECK_WRITE))
            FD_SET(s->fd, &wr);
        FD_SET(s->fd, &ex);

        czas_selecta.tv_sec = 1;
        czas_selecta.tv_usec = 0;
        if (select(s->fd + 1, &rd, &wr, &ex, &czas_selecta) == -1) {
             pfprintf("Error: %s", strerror(errno));
             polacz();
        }
        if (FD_ISSET(s->fd, &ex)) {
             pfprintf("Error: %s", strerror(errno));
             polacz();
        }
        if (FD_ISSET(s->fd, &rd) || FD_ISSET(s->fd, &wr))
             fevent();
    }
    gg_logoff(s);
    gg_free_session(s);
mysql_free_result(sqlres);
mysql_close(&conn);    
return 0;
}

