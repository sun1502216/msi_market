#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>


void update_com(MYSQL* b)
{
	char upd[200],name1[20],name2[20],remark[50];
	int price;
	int i;

	printf("输入要修改的具体内容：\n");
	printf("1、商品名\n");
	printf("2、商品价格\n");
	printf("3、商品备注\n");

	scanf("%d",&i);

	switch(i)
	{
		case 1:
			printf("输入要更改的商品名：");
			scanf("%s",name1);
			printf("输入更改后的商品名：");
			scanf("%s",name2);
			sprintf(upd,"update commodity_info set cname = '%s' where cname = '%s'",name2,name1);
			if(mysql_query(b,upd))
				fprintf(stderr,"%s\n",mysql_error(b));
			break;
		case 2:
			printf("输入要更改的商品名：");
			scanf("%s",name1);
			printf("输入更改后的商品价格：");
			scanf("%d",&price);
			sprintf(upd,"update commodity_info set price = %d where cname = '%s'",price,name1);
			if(mysql_query(b,upd))
				fprintf(stderr,"%s\n",mysql_error(b));
			break;
		case 3:
			printf("输入要更改的商品名：");
			scanf("%s",name1);
			printf("输入更改后的商品备注：");
			scanf("%s",remark);
			sprintf(upd,"update commodity_info set remark = '%s' where cname = '%s'",remark,name1);
			if(mysql_query(b,upd))
				fprintf(stderr,"%s\n",mysql_error(b));
			break;
		default:
			printf("输入错误\n");
	}
}


void update_sup(MYSQL* b)
{
	char upd[200],name1[20],name2[20],addr[50],phone[12];
	int i;

	printf("输入要修改的具体内容：\n");
	printf("1、供应商名\n");
	printf("2、供应商地址\n");
	printf("3、供应商电话\n");

	scanf("%d",&i);

	switch(i)
	{
		case 1:
			printf("输入要更改的供应商名：");
			scanf("%s",name1);
			printf("输入更改后的供应商名：");
			scanf("%s",name2);
			sprintf(upd,"update supplier_info set cname = '%s' where sname = '%s'",name2,name1);
			if(mysql_query(b,upd))
				fprintf(stderr,"%s\n",mysql_error(b));
			break;
		case 2:
			printf("输入要更改的供应商名：");
			scanf("%s",name1);
			printf("输入更改后的供应商地址：");
			scanf("%s",addr);
			sprintf(upd,"update supplier_info set saddr = '%s' where sname = '%s'",addr,name1);
			if(mysql_query(b,upd))
				fprintf(stderr,"%s\n",mysql_error(b));
			break;
		case 3:
			printf("输入要更改的供应商名：");
			scanf("%s",name1);
			printf("输入更改后的供应商电话：");
			scanf("%s",phone);
			sprintf(upd,"update supplier_info set sphone = '%s' where sname = '%s'",phone,name1);
			if(mysql_query(b,upd))
				fprintf(stderr,"%s\n",mysql_error(b));
			break;
		default:
			printf("输入错误\n");
	}

}


void Update(MYSQL* b)
{
	int i;

	printf("1、修改商品信息\n2、修改供应商信息\n");
	scanf("%d",&i);

	if(i == 1)
		update_com(b);
	else if(i == 2)
		update_sup(b);
	else printf("输入错误！\n");

}
