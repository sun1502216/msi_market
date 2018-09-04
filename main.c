#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <mysql/mysql.h>
#include "insert.h"
#include "select.h"
#include "update.h"
#include "sell.h"
#include "add_user.h"

void mis_option(MYSQL* b);


int main()
{
	MYSQL mysql;
	MYSQL_RES* res;
	MYSQL_ROW row;

	char user[21],sel[200];
	char* passwd;
	int i,no,admin = 0;

	mysql_init(&mysql);

	if(!mysql_real_connect(&mysql,"localhost","sm_admin","123456","supermarket",0,NULL,0))
		fprintf(stderr,"%s\n",mysql_error(&mysql));

	mysql_query(&mysql,"set names utf8");

	printf("----------登陆----------\n");
dl:
	printf("输入用户名：");
	scanf("%s",user);
	passwd = getpass("输入密码：");

	sprintf(sel,"select * from user_info where uname = '%s' and passwd = md5('%s')",user,passwd);

	if(mysql_query(&mysql,sel))
	{
		fprintf(stderr,"%s\n",mysql_error(&mysql));
		exit(1);
	}
	else
	{
		res = mysql_use_result(&mysql);
		row = mysql_fetch_row(res);
		if(!mysql_num_rows(res)) 
		{
			printf("用户名或密码错误！请重新输入\n");
			mysql_free_result(res);
			goto dl;
		}
		else
		{
			admin = atoi(row[3]);
			mysql_free_result(res);
		}
	}

	while(1)
	{
		printf("请输入操作：\n");
		printf("1、出售商品\n");
		printf("2、查看商品价格\n");
		printf("3、修改用户密码\n");
		printf("4、进入系统设置\n");
		printf("5、切换用户\n");
		printf("6、退出系统\n");
		scanf("%d",&i);

		switch(i)
		{
			case 1:
				sell(&mysql);
				break;
			case 2:
				printf("输入商品编号\n");
				scanf("%d",&no);
				printf("价格为%d",count(no,&mysql));
				break;
			case 3:
				upd_user(user,&mysql);
				break;
			case 4:
				if(admin)
					mis_option(&mysql);
				else printf("只有管理员才能进入系统设置\n");
				break;
			case 5:
				goto dl;
			case 6:
				exit(1);
			default:
				printf("输入错误\n");
		}

	}

	mysql_close(&mysql);

	return 0;
}


void mis_option(MYSQL* b)
{
	int i;
	while(1)
	{
		printf("请选择操作：\n");
		printf("1、添加进货信息\n");
		printf("2、修改商品信息\n");
		printf("3、查看商品信息\n");
		printf("4、查看买卖记录\n");
		printf("5、添加普通用户\n");
		printf("6、退出系统设置\n");

		scanf("%d",&i);
		system("clear");

		if(i == 6)break;

		switch(i)
		{
			case 1:
				Insert(b);
				break;
			case 2:
				Update(b);
				break;
			case 3:
				Select(b);
				break;	
			case 4:
				select_bs(b);
				break;
			case 5:
				add_user(b);
				break;
			default:
				printf("输入错误！\n");
		}
	}
}
