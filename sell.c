#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "select.h"

void sell(MYSQL* b)
{
	char ins[500];
	int no,count1;
	char len;

	printf("输入商品编号：");
	scanf("%d",&no);

	printf("输入出售数量：");
	scanf("%d",&count1);

	printf("应付%d元\n",count1*count(no,b));
	printf("确认（y/n）：");
	while(getchar() != '\n');
	scanf("%c",&len);

	if(len == 'y' || len == 'Y')
	{
		sprintf(ins,"insert into sell_info values(%d,%d,now())",no,count1);

		if(mysql_query(b,ins))
		{
			fprintf(stderr,"%s\n",mysql_error(b));
			printf("请重新输入：");
			sell(b);
		}
		else
		{
			sprintf(ins,"update commodity_info set count = count - %d where cno = %d",count1,no);

			if(mysql_query(b,ins))
				fprintf(stderr,"%s\n",mysql_error(b));
		}
	}
}

void select_bs(MYSQL* b)
{
	char sel[200],name[20];
	int i;

	printf("1、查看进货记录\n");
	printf("2、查看出售记录\n");

	scanf("%d",&i);

	if(i == 1)
	{
s_sup:
		printf("输入查看的商品名：");
		scanf("%s",name);

		sprintf(sel,"select cno,count,time,sname from %s_info,supplier_info where %s_info.sno = supplier_info.sno",name,name);
		if(mysql_query(b,sel))
		{
			fprintf(stderr,"%s\n",mysql_error(b));
			printf("输入有误，请重新输入：");
			goto s_sup;
		}
		else
		{
			MYSQL_RES* res;
			MYSQL_ROW row;

			res = mysql_store_result(b);
			while(row = mysql_fetch_row(res))
			{
				printf("时间：%s,商品：%s,进货数量：%s,供应商：%s\n",row[2],name,row[1],row[3]);
			}
			mysql_free_result(res);
		}
	}
	else if(i == 2)
	{
s_sell:
		printf("输入查看的商品名：");
		scanf("%s",name);

		sprintf(sel,"select sell_info.count,time from sell_info,commodity_info where sell_info.cno = commodity_info.cno and commodity_info.cname = %s",name);
		if(mysql_query(b,sel))
		{
			fprintf(stderr,"%s\n",mysql_error(b));	
			printf("输入有误，请重新输入：");
			goto s_sell;
		}
		else
		{
			MYSQL_RES* res;
			MYSQL_ROW row;

			res = mysql_store_result(b);
			while(row = mysql_fetch_row(res))
			{
				printf("时间：%s,商品：%s,出售数量：%s\n",row[1],name,row[0]);
				i++;
			}
			mysql_free_result(res);

			if(i == 2)
				printf("未找到相应记录\n");
		}
	}
	else printf("输入错误\n");
}
