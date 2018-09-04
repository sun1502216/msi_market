#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int count(int a,MYSQL* b)
{
	char sel[50];
	int c;

	sprintf(sel,"select count from commodity_info where cno = %d",a);

	if(mysql_query(b,sel))
	{
		fprintf(stderr,"select fault:%s\n",mysql_error(b));
		return -1;
	}
	else
	{
		MYSQL_RES* res;
		MYSQL_ROW row;

		res = mysql_use_result(b);
		row = mysql_fetch_row(res);

		c = atoi(row[0]);

		mysql_free_result(res);

		return c;
	}
}


float price(int a,MYSQL* b)
{
	char sel[50];
	float p;

	sprintf(sel,"select price from commodity_info where cno = %d",a);

	if(mysql_query(b,sel))
	{
		fprintf(stderr,"select fault:%s\n",mysql_error(b));
		return -1;
	}
	else
	{
		MYSQL_RES* res;
		MYSQL_ROW row;

		res = mysql_use_result(b);
		row = mysql_fetch_row(res);

		p = atof(row[0]);

		mysql_free_result(res);

		return p;
	}
}


void sm_information(int a,MYSQL* b)
{
	char sel[50];

	sprintf(sel,"select * from commodity_info where cno = %d",a);

	if(mysql_query(b,sel))
	{
		fprintf(stderr,"select fault:%s\n",mysql_error(b));
	}
	else
	{
		MYSQL_RES* res;
		MYSQL_ROW row;

		res = mysql_use_result(b);
		row = mysql_fetch_row(res);

		printf("商品编号为%s\n商品名称为%s\n商品价格为%s\n备注为%s\n剩余数量为%s\n",row[0],row[1],row[2],row[3],row[4]);

		mysql_free_result(res);
	}
}


void sl_information(int a,MYSQL* b)
{
	char sel[50];

	sprintf(sel,"select * from supplier_info where sno = %d",a);

	if(mysql_query(b,sel))
	{
		fprintf(stderr,"select fault:%s\n",mysql_error(b));
	}
	else
	{
		MYSQL_RES* res;
		MYSQL_ROW row;

		res = mysql_use_result(b);
		row = mysql_fetch_row(res);

		printf("供应商编号为%s\n供应商名为%s\n供应商地址为%s\n供应商电话为%s\n",row[0],row[1],row[2],row[3]);

		mysql_free_result(res);
	}
}


void Select(MYSQL* b)
{
	int i,a;
	printf("1、查看商品剩余数量\n");
	printf("2、查看商品价格\n");
	printf("3、查看商品全部信息\n");
	printf("4、查看供应商全部信息\n");

	scanf("%d",&i);

	switch(i)
	{
		case 1:
			printf("输入要查询的商品的编号：");
			scanf("%d",&a);
			printf("剩余数量为%d\n",count(a,b));
			break;
		case 2:
			printf("输入要查询的商品的编号：");
			scanf("%d",&a);
			printf("价格为%.1f\n",price(a,b));
			break;
		case 3:
			printf("输入要查询的商品的编号：");
			scanf("%d",&a);
			sm_information(a,b);
			break;
		case 4:
			printf("输入要查询的商品的编号：");
			scanf("%d",&a);
			sl_information(a,b);
			break;
		default:
			printf("输入错误\n");
	}

}
