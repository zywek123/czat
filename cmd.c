#include "cmd.h"
extern struct gg_session *s;
extern struct gg_event *e;
extern struct gg_login_params p;
extern struct user *u;
extern MYSQL conn;
extern MYSQL_RES *sqlres;
extern MYSQL_ROW row;

int preprocess_cmd(char* cmd_name)
{
if(cmp(cmd_name,"ver"))
{
cmd_ver();
}

return 0;
}
void cmd_ver()
{
FILE *fp;
if((fp = fopen("/proc/version", "r")) == NULL)
{
pfprintf("Wystąpił problem z odczytem /proc/version:\n");
}
char info[256];
fgets(info, 256, fp);
fclose(fp);
char buf[512];
sprintf(buf, "GgCzat primary edition v 1.0 © 2017 Żywek.\nInformacje systemowe:\n%s", info);
addmsg((const char*)buf, u->numer);
}
