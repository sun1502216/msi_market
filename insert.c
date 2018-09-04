#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void insert_com(MYSQL* b)
{
	char ins[500], sel[100];
	int no, count = 0, sno;
	char name[20];
	float price;

	printf("输入商品编号：");
	scanf("%d",&no);

	sprintf(sel,"select * from commodity_info where cno = %d",no);
	if(mysql_query(b,sel))
		fprintf(stderr,"%s\n",mysql_error(b));
	else
	{
		MYSQL_RES* res;
		MYSQL_ROW row;

		res = mysql_use_result(b);

		if(!(row = mysql_fetch_row(res)))
		{
			printf("新增商品：\n");
			printf("输入商品名称：");
			scanf("%s",name);

			printf("输入商品价格：");
			scanf("%f",&price);

			sprintf(ins,"insert into commodity_info(cno,cname,price,count) values(%d,'%s',%.1f,%d)",no,name,price,count);

			if(mysql_query(b,ins))
				fprintf(stderr,"insert fault:%s\n",mysql_error(b));
			else
			{
				printf("输入进货数量：");
				scanf("%d",&count);

				printf("输入供应商编号：");
				scanf("%d",&sno);

				sprintf(ins,"create table %s_info (cno int unsigned not null,count int not null,time date not null,sno int unsigned not null,foreign key(cno) references commodity_info(cno),foreign key(sno) references supplier_info(sno))",name);

				if(mysql_query(b,ins))
				{
					fprintf(stderr,"%s\n",mysql_error(b));
					sprintf(ins,"delete from commodity_info where cno = %d",no);
					mysql_query(b,ins);
				}
				else
				{
					sprintf(ins,"insert into %s_info values(%d,%d,now(),%d)",name,no,count,sno);

					if(mysql_query(b,ins))
						fprintf(stderr,"%s\n",mysql_error(b));

					sprintf(ins,"update commodity_info set count = count + %d where cno = %d",count,no);

					if(mysql_query(b,ins))
						fprintf(stderr,"%s\n",mysql_error(b));
				}
			}
			mysql_free_result(res);
		}
		else
		{
			printf("输入进货数量：");
			scanf("%d",&count);

			printf("输入供应商编号：");
			scanf("%d",&sno);

			sprintf(ins,"insert into %s_info values(%d,%d,now(),%d)",row[1],no,count,sno);

			mysql_free_result(res);	

			if(mysql_query(b,ins))
				fprintf(stderr,"%s\n",mysql_error(b));

			sprintf(ins,"update commodity_info set count = count + %d where cno = %d",count,no);

			if(mysql_query(b,ins))
				fprintf(stderr,"%s\n",mysql_error(b));
		}
	}
}


void insert_sup(MYSQL* b)
{
	char ins[500],name[20],addr[50],phone[12];
	int no;

	printf("输入供应商编号：");
	scanf("%d",&no);

	sprintf(ins,"select * from supplier_info where sno = %d",no);
	if(mysql_query(b,ins))
		fprintf(stderr,"insert into fault:%s\n",mysql_error(b));
	else
	{
		MYSQL_RES* res;
		MYSQL_ROW row;

		res = mysql_use_result(b);

		if(!(row = mysql_fetch_row(res)))
		{
			printf("输入供应商名称：");
			scanf("%s",name);

			printf("输入供应商地址：");
			scanf("%s",addr);

			printf("输入供应商电话：");
			scanf("%s",phone);

			sprintf(ins,"insert into supplier_info values(%d,'%s','%s','%s')",no,name,addr,phone);
			if(mysql_query(b,ins))
				fprintf(stderr,"insert into fault:%s\n",mysql_error(b));
		}
		else printf("供应商已存在\n");
		mysql_free_result(res);
	}
}


void Insert(MYSQL* b)
{
	int i;

	printf("1、添加商品信息\n2、添加供应商信息\n");
	scanf("%d",&i);

	if(i == 1)
		insert_com(b);
	else if(i == 2)
		insert_sup(b);
	else printf("输入错误！\n");
}
