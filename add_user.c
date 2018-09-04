#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>


void add_user(MYSQL* b)
{
	char add[500],name[21];
	char* passwd1;
	char passwd2[51];

	printf("输入用户名（由字母、数字和下划线构成，最多20位）：");
	scanf("%s",name);
s_m:
	passwd1 = getpass("输入密码：");

	strcpy(passwd2,passwd1);

	passwd1 = getpass("再次输入进行确认：");

	if(!strcmp(passwd1,passwd2))
	{
		sprintf(add,"insert into user_info(uname,passwd,admin) values('%s',md5('%s'),'0')",name,passwd1);

		if(mysql_query(b,add))
			fprintf(stderr,"%s\n",mysql_error(b));
	}
	else
	{
		printf("两次输入不一致\n");
		printf("请重新输入：\n");
		goto s_m;
	}
}


void upd_user(const char* a,MYSQL* b)
{
	char upd[500];
	char* passwd1;
	char passwd2[51],passwd3[51];

s_m:
	passwd1 = getpass("输入密码：");

	strcpy(passwd2,passwd1);

	passwd1 = getpass("再次输入进行确认：");

	strcpy(passwd3,passwd1);

	if(!strcmp(passwd1,passwd2))
	{
		passwd1 = getpass("输入新密码：");
		strcpy(passwd2,passwd1);
		sprintf(upd,"update user_info set passwd = md5('%s') where uname = '%s' and passwd = md5('%s')",passwd2,a,passwd3);

	if(mysql_query(b,upd))
		fprintf(stderr,"%s\n",mysql_error(b));
	}
	else
	{
		printf("两次输入不一致\n");
		printf("请重新输入：\n");
		goto s_m;
	}
}
