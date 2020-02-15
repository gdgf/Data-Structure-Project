/*
	采用排序二叉树作为存储结构
*/
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<time.h>
#define MAXNUM 10

typedef struct book
{
	long int starting;    //借书日期
	long int ending;      //应还日期
	char bookinform[120]; //这里面存储书籍的描述信息
	long int callnum;     //索书号
	char bookname[30];
	char writer[20];
	int totalstorage, nowstorage;//书本的馆藏量，现有量
}book;
/*本结构体用于创建链表的二叉树*/
typedef struct volume
{
	book books;
	struct volume *lchild;
	struct volume *rchild;
}volume,*Btvolume;

typedef struct libcard
{
	char userID[12];
	char password[12];//密码
	char clientname[20];//用户的名字
	char usermessage[150];//用户信息
	book borrow[10];//每本借书证限借书十本
	struct libcard *next;
}libcard;              //用户信息

typedef struct administer
{
	char adminID[12];
	char password[12];
	char adminname[20];     //管理员名字...
	char adminmessage[150];
	struct administer *next;
}administer;               //管理员信息

administer *admins,*current_admin=NULL;
libcard *clients,*current_client=NULL;
/*
	函数声明
*/
void view_01();
void view_02();
void view_03();
void createBST(Btvolume *bst,int manner);
void insertBST(Btvolume *bst,book *key);
int strindex(char* si,char* di);
void display(volume *key);
Btvolume searchBST(Btvolume bst,int key);
int delBST(Btvolume bst,int key);
book *read_book_file(FILE *filepoint);
void write_book_file(FILE *filepoint,volume *root);//写文件
administer *read_admin_file(FILE *filepoint);
libcard *read_client_file(FILE *filepoint);//读客户信息
int write_admin_file(FILE *filepoint,administer *head);
void GetPassword(char *str,int n);


int registerer();
int login();//登录
void logout(int c);//注销
void admin(volume **Btroot);//管理员
void clientsev(volume **Btroot);//客户(学生)
int check_admin(administer *admin);
int check_client(libcard *client);
void in_stor(volume **root);//入库
int out_stor(Btvolume *root,long int key);//销毁
void backbook(Btvolume *root,long int callnum);//还书
int lend(Btvolume *root,long int callnum);//借书，有学生发出请求
void search(Btvolume *root);
void quesheng(Btvolume root,int a,char *key);//缺省查找
void preorder(Btvolume root);//遍历，用于浏览全部的书籍
void display_clients(libcard *head);
void display_admins(administer *head);



/*
	二叉排序树的插入模块，采用递归算法实现
*/
void insertBST(Btvolume *bst,book *key)
{
	Btvolume s;
	if(*bst==NULL)//递归结束条件
	{
		s=(Btvolume)malloc(sizeof(volume));
		s->books.callnum=key->callnum;
		s->books.nowstorage=key->nowstorage;
		s->books.totalstorage= key->totalstorage;
		s->books.starting = key->starting;
		s->books.ending = key->ending;
		strcpy(&(s->books.bookinform),&(key->bookinform));
		strcpy(&(s->books.bookname),&(key->bookname));
		strcpy(&(s->books.writer),&(key->writer));
		s->lchild=NULL;
		s->rchild=NULL;
		*bst=s;
	}
	else if(key->callnum < (*bst)->books.callnum)
	{
		insertBST(&((*bst)->lchild),key);
	}
	else if(key->callnum > (*bst)->books.callnum)
	{
		insertBST(&((*bst)->rchild),key);
	}
	else
	{
		(*bst)->books.nowstorage+=key->nowstorage;
		(*bst)->books.totalstorage+=key->totalstorage;
	}
}

/*
	本模块实现二叉排序树的建立
	说明：1、参数 Btvolume *bst 为待创建树的根节点
		  2、只有库存量为空的时候才能调用本模块
		  3、只有管理员才能调用本模块
		  4、参数 manner 用于指定从文件创建还是从键盘创建
				manner=1：键盘、manner=2：从文件
		  5、只有在系统初始化是才允许从键盘创建
*/
void createBST(Btvolume *bst,int manner)
{
	book *key;
	FILE *f_book_store=NULL;
	f_book_store = fopen("book_store.txt","r");
	*bst=NULL;
	while(1){
		key=(book *)malloc(sizeof(book));//

		if(manner==1)
		{
				/*输入书本信息*/
			key->starting=0;
			key->ending=0;
			printf("输入索书号：");
			scanf("%ld",&(key->callnum));
			if(key->callnum == 0){
				free(key);
				break;
			}
			printf("输入入库量：");
			scanf("%d",&(key->totalstorage));
			key->nowstorage=key->totalstorage;
			printf("输入书本名：");
			scanf("%s",&(key->bookname));
			printf("输入著作者：");
			scanf("%s",&(key->writer));
			printf("输入书描述：");
			scanf("%s",&(key->bookinform));
		}
		else
		{
			if(!feof(f_book_store))//判断文件是否结束
			{
				key=read_book_file(f_book_store);
				if(key->callnum < -1)
				{
					free(key);
					key = NULL;
				}
			}
			else
			{
				free(key);
				break;
			}
		}
		if(key!=NULL)
		insertBST(bst,key);//调用插入操作实现新书入库
	}
	fclose(f_book_store);

///////////////////////////////////////////////////////////////////////
	f_book_store = fopen("book_store.txt","w");
	write_book_file(f_book_store,*bst);
	fclose(f_book_store);
///////////////////////////////////////////////////////////////////////
}

/*
	二叉排序树的查找算法
	按索书号为关键字进行二分查找
*/
Btvolume searchBST(Btvolume bst,long int key)
{
	if(bst==NULL)
		return NULL;
	if(bst->books.callnum == key)
		return bst;
	if(bst->books.callnum < key)
		return searchBST(bst->rchild,key);
	return searchBST(bst->lchild,key);
}

/*
	二叉排序树的删除算法
	实现对馆藏的书籍进行销毁
	返回是否成功
*/
int delBST(Btvolume bst,int key)
{
	int success=0;
	Btvolume p,f,s,q;
	p=bst;
	f=NULL;
	while(p)
	{
		if(p->books.callnum == key)
			break;
		f=p;
		if(p->books.callnum > key)
			p=p->lchild;
		else
			p=p->rchild;
	}

	if(p==NULL)
	{
		success=1;
		return success;
	}
	if(p->lchild==NULL)
	{
		if(f==NULL)
			bst=p->rchild;
		else if(f->lchild==p)
			f->lchild=p->rchild;
		else
			f->rchild=p->rchild;
		free(p);
		success=1;
	}
	else
	{
		q=p;
		s=p->lchild;
		while(s->rchild)
		{
			q=s;
			s=s->rchild;
		}
		if(q==p)
			q->lchild=s->lchild;
		else
			q->rchild=s->lchild;
		p->books.callnum=s->books.callnum;
		free(s);
		success=1;
	}
	return success;
}

/*
	串定位的模式匹配算法
*/
int strindex(char* si,char* di)
{
	int i=0,j=0;
	while(i<=strlen(si)&&j<=strlen(di))
	{
		if(si[i]==di[j])
		{
			i++;j++;
		}
		else
		{
			i=i-j+1;
			j=0;
		}
		if(j>=strlen(di))
			return 1;
		else if(i>=strlen(si))
			return 0;
		else;
	}
}

/*
	入库函数，用于增加书本库存
	函数无返回值
	实现：1、排序二叉树的建立
		  2、排序二叉树的查找
		  3、排序二叉树的插入
		  4、排序二叉树的删除
	说明：在这里并没有对物理层进行操作
*/
void in_stor(volume **root)
{
	FILE *file_book_store;
	Btvolume p,q;
	book *key;

	/*输入数据*/
	key=(book*)malloc(sizeof(book));
	printf("输入索书号：");
	scanf("%ld",&(key->callnum));
	printf("输入入库量：");
	scanf("%d",&(key->totalstorage));
	key->nowstorage=key->totalstorage;
	printf("输入书本名：");
	scanf("%s",&(key->bookname));
	printf("输入著作者：");
	scanf("%s",&(key->writer));
	printf("输入书描述：");
	scanf("%s",&(key->bookinform));
	key->starting = 0;
	key->ending = 0;

	insertBST(root,key);
}

/**/
int out_stor(Btvolume *root,long int key)
{
	int success=0;//作为返回值，用于标记销毁是否成功
	delBST(*root,key);
	return success;
}

/*
	还书模块，有学生发出请求
	每次只能还一本书
	即便是两本同样的书也需还两次!
	无返回值
	还书后相应库存量增加，同时学生的当前借阅量减少
	如果超期，则罚款：没超过一天罚款0.2元，不足一天按一天算
*/
void backbook(Btvolume *root,long int callnum)
{
	Btvolume temp;
	time_t t;
	int i=0;
	double overtime,fine;

	if(current_admin==NULL)//若当前无管理员这不能借书
	{
		printf("对不起、目前管理员未登录您不可还书!\n");
		return ;
	}

	while(i<=10)
	{
		if(current_client->borrow[i].callnum==callnum)
			break;
		i++;
	}
	if(i>=10)
	{
		printf("对不起，您并未借过此书!\n");
		return;
	}
	temp=searchBST(*(root),callnum);
	if(temp==NULL)
	{
		printf("您好，本馆并未藏有此书,因此不必还!\n");
		return;
	}
	if(temp->books.nowstorage >= temp->books.totalstorage)
	{
		printf("对不起，您并未借过此书!\n");
		return;
	}
	time(&t);
	if( t > current_client->borrow[i].ending)
	{
		overtime=((t- current_client->borrow[i].ending)/43200)+1;
		fine = overtime * 0.2;
		printf("对不起，您所借的书已经超期 %0.0f 天\n",overtime);
		printf("按图书馆相关规定将对您罚款 %0.2lf 元\n",fine);
	}
	/*还书后所做的处理*/
	temp->books.nowstorage++;

	current_client->borrow[i].bookinform[0]='\0';
	current_client->borrow[i].bookname[0]='\0';
	current_client->borrow[i].callnum=0;
	current_client->borrow[i].ending= 2004967296;//
	current_client->borrow[i].starting=0;
	current_client->borrow[i].nowstorage=0;
	current_client->borrow[i].totalstorage=0;
	current_client->borrow[i].writer[0]='\0';

	printf("书已成功还回,欢迎下次光临!\n");
}

/*
	借书模块，由学生发出请求,需要至少有个管理员
	返回借书是否成功
	如果当前的可借阅量大于0且学生当前借书量未超过限制
	则借书成功 否则失败
*/
int lend(Btvolume *root,long int callnum)
{
	int success=0;//作为返回值，用于标记借阅是否成功
	int i=0;
	time_t t;
	Btvolume temp;
	if(current_admin==NULL)//若当前无管理员这不能借书
	{
		printf("对不起、目前管理员未登录您不可借书!\n");
		return success;
	}

	while(current_client->borrow[i].callnum>0)
		i++;
	if(i>=10)
		printf("对不起，您借的书过多，请先还书!\n");
	else
	{
		temp=searchBST(*root,callnum);
		if(temp==NULL)
			printf("对不起，本馆没有收藏此书!\n");
		else if(temp->books.nowstorage > 0)
		{
			time(&t);
			temp->books.nowstorage -= 1;
			current_client->borrow[i].callnum = callnum;
			current_client->borrow[i].starting = t;//获取当前系统时间
			current_client->borrow[i].ending = current_client->borrow[i].starting+2592000;
			current_client->borrow[i].totalstorage = temp->books.totalstorage;
			current_client->borrow[i].nowstorage = temp->books.nowstorage;
			strcpy(current_client->borrow[i].bookinform , temp->books.bookinform);
			strcpy(current_client->borrow[i].bookname , temp->books.bookname);
			strcpy(current_client->borrow[i].writer , temp->books.writer);
			success=1;

			printf("您已经成功借书，欢迎下次光临!\n");
		}
		else
			printf("对不起，该书已被借完!\n");
	}
	return success;
}

/*
	数目缺省查找的实现模块
	主要算法为字符串匹配的模式匹配算法
	对图书进行中序遍历，对每个节点都进行比较
	进行中序遍历的目的是让结果安索书号的大小顺序显示
*/
void quesheng(Btvolume root,int a,char *key)
{
	int b=0;
	struct tm *p;
	if(root!=NULL)
	{
		b=0;
		quesheng(root->lchild,a,key);
		b=0;
		switch(a)
		{
		case 1:
			b=strindex(root->books.bookname,key);//书名
			break;
		case 2:
			b=strindex(root->books.writer,key);//作者
			break;
		case 3:
			b=strindex(root->books.bookinform,key);//信息
			break;
		case 4:
			break;
		}
		if(b)
		{
			printf("索书号：%d\n",root->books.callnum);
			printf("书名  ：%s\n",root->books.bookname);
			printf("作者  ：%s\n",root->books.writer);
			printf("描述  ：%s\n",root->books.bookinform);
			printf("馆藏量：%d\n",root->books.totalstorage);
			printf("可借量：%d\n",root->books.nowstorage);
			if(root->books.starting!=0)
			{
				p=localtime(&(root->books.starting));
				printf("借书日：%d/%d/%d\n",p->tm_year+1900,p->tm_mon+1,p->tm_mday);
				p=localtime(&(root->books.ending));
				printf("还书日：%d/%d/%d\n",p->tm_year+1900,p->tm_mon+1,p->tm_mday);
			}
			printf("----------------------------------------------\n");
		}
		b=0;
		quesheng(root->rchild,a,key);
		b=0;
	}
}

/*
	数目检索模块，可实现精确查找和缺省查找功能
	通过索书号进行精确查找
	通过数目相关信息进行精确查找
*/
void search(Btvolume *root)
{
	volume *temp;
	char keyword[30];//关键字最多允许29个字符
	long int b;
	int a;
	while(1)
	{
		view_06();
		scanf("%d",&a);
		switch(a)
		{
		case 1:
			printf("输入索书号：\n");
			scanf("%d",&b);
			temp=searchBST(root,b);
			display(temp);
			break;
		case 2:
			view_07();
			scanf("%d",&a);
			scanf("%s",&keyword);
			quesheng(root,a,keyword);
			break;
		case 3:
			return ;
		default:
			break;
		}
		system("pause");
		system("cls");
	}
}
/*
	实现中序遍历二叉排序树
*/
void preorder(Btvolume root)
{
	struct tm *p;
	if(root!=NULL)
	{
		preorder(root->lchild);

		printf("索书号：%d\n",root->books.callnum);
		printf("书名  ：%s\n",root->books.bookname);
		printf("作者  ：%s\n",root->books.writer);
		printf("描述  ：%s\n",root->books.bookinform);
		printf("馆藏量：%d\n",root->books.totalstorage);
		printf("可借量：%d\n",root->books.nowstorage);
		if(root->books.starting!=0)
		{
			p=localtime(&(root->books.starting));
			printf("借书日：%d/%d/%d\n",p->tm_year+1900,p->tm_mon+1,p->tm_mday);
			p=localtime(&(root->books.ending));
			printf("还书日：%d/%d/%d\n",p->tm_year+1900,p->tm_mon+1,p->tm_mday);
		}
		printf("----------------------------------------------\n");

		preorder(root->rchild);
	}
}

/*
	显示客户信息
*/
void display_clients(libcard *head)
{
	struct tm *p;
	int i=0;
	libcard *temp=head;
	if(head == NULL)
	{
		printf("您好，当前无客户!\n");
		return;
	}
	while(temp!=NULL)
	{
		printf("---------------------------------------------\n");
		printf("客 户 ID：%s\n",temp->userID);
		printf("客户名字：%s\n",temp->clientname);
		i=0;
		while(i<10)
		{
			if(temp->borrow[i].starting>0)
			{
				printf("  -----------------------------------------\n");
				printf("\t|客户当前借书\n");
				printf("\t|索书号：%ld\n",temp->borrow[i].callnum);
				printf("\t|书籍名：%s\n",temp->borrow[i].bookname);
				printf("\t|著作者：%s\n",temp->borrow[i].writer);
				printf("\t|简  介：%s\n",temp->borrow[i].bookinform);
				if(temp->borrow[i].starting!=0)
				{
					p=localtime(&(temp->borrow[i].starting));
					printf("\t|借书日：%d/%d/%d\n",p->tm_year+1900,p->tm_mon+1,p->tm_mday);
					p=localtime(&(temp->borrow[i].ending));
					printf("\t|还书日：%d/%d/%d\n",p->tm_year+1900,p->tm_mon+1,p->tm_mday);
				}
			}
			i++;
		}
		printf("客户说明：%s\n",temp->usermessage);
		printf("---------------------------------------------\n");
		temp=temp->next;
	}
}

/*
	显示管理员信息
*/
void display_admins(administer *head)
{
	int i=0;
	administer *temp=head;
	if(head == NULL)
	{
		printf("您好，当前无管理员!\n");
		return;
	}
	while(temp!=NULL)
	{
		printf("---------------------------------------------\n");
		printf("管理员  ID：%s\n",temp->adminID);
		printf("管理员姓名：%s\n",temp->adminname);
		printf("管理员信息：%s\n",temp->adminmessage);
		printf("---------------------------------------------\n");
		temp=temp->next;
	}
}

void display(volume *key)
{
	time_t t;
	if(key==NULL)
	{
		printf("对不起，本馆目前无此藏书!\n");
		return;
	}
	printf("---------------------------------------------\n");
	printf("索书号：%d\n",key->books.callnum);
	printf("书名  ：%s\n",key->books.bookname);
	printf("作者  ：%s\n",key->books.writer);
	printf("描述  ：%s\n",key->books.bookinform);
	printf("馆藏量：%d\n",key->books.totalstorage);
	printf("可借量：%d\n",key->books.nowstorage);
	printf("----------------------------------------------\n");
}



/*
	注册模块
	返回注册是否成功
	用户需注册
*/
int registerer()
{
	FILE *fad=NULL,*fcl=NULL;
	administer *admin,*admin_temp=NULL;
	libcard *client,*client_temp=NULL;
	char temp[13];
	int type,success=0;
	int admin_total=0,client_total=0;//用于记录管理员和客户人数///待完成……
	int i;
	while(1){
		printf("请选择注册的类型(1、管理员)(2、客户):");
		scanf("%d",&type);
		switch(type)
		{
		case 1:

			admin=(administer*)malloc(sizeof(administer));//这里很重要
			admin->next=NULL;/////这里很重要
			printf("管理员ID：");
			scanf("%s",&admin->adminID);
			/*
				检测是否为重复注册
			*/
			admin_temp=admins;
			while(admin_temp!=NULL)
			{
				if(!strcmp(admin->adminID , admin_temp->adminID))
					break;
				admin_temp=admin_temp->next;
			}
			if(admin_temp == NULL)//没有相同的ID
			{
				admin->next=admins;
				admins=admin;
			}
			else
			{
				printf("对不起，该ID已被占用,注册失败!\n");
				free(admin);
				admin=NULL;
				break;
			}
			while(1)
			{
				printf("密码：");
				GetPassword(&admin->password,12);//输入密码，回显*
				//scanf("%s",&admin->password);
				printf("确认密码：");
				GetPassword(&temp,12);//输入密码，回显*
				//scanf("%s",&temp);
				if(!strcmp(admin->password,temp))
					break;
				printf("您的密码输入有误，请从新输入\n");
			}
			printf("请输入用户名字:");
			scanf("%s",&admin->adminname);
			printf("请输入用户描述:");
			scanf("%s",&admin->adminmessage);

			break;

		case 2:

			client=(libcard*)malloc(sizeof(libcard));//这里很重要
			client->next=NULL;
			printf("用户ID：");
			scanf("%s",&client->userID);

			/*
				检测是否为重复注册
			*/
			client_temp=clients;
			while(client_temp!=NULL)
			{
				if(!strcmp(client->userID , client_temp->userID))//不允许相同ID但允许相同密码
					break;
				client_temp=client_temp->next;
			}
			if(client_temp == NULL)//没有相同的ID
			{
				/*
					注册成功后应对信息进行初始化
				*/
				for(i=0;i<10;i++)
				{
					client->borrow[i].bookinform[0] = '\0';
					client->borrow[i].bookname[0] = '\0';
					client->borrow[i].writer[0] = '\0';
					client->borrow[i].callnum = 0;
					client->borrow[i].starting = 0;
					client->borrow[i].ending = 315360000;//将归还日期初始为无穷大
					client->borrow[i].nowstorage = 0;
					client->borrow[i].totalstorage = 0;
				}

				client->next=clients;
				clients=client;
			}
			else
			{
				printf("对不起，该ID已被占用,注册失败!\n");
				break;
			}
			while(1)
			{
				printf("密码：");
				GetPassword(&client->password,12);
				//scanf("%s",&client->password);
				printf("确认密码：");
				GetPassword(&temp,12);
				//scanf("%s",&temp);
				if(!strcmp(client->password,temp))//检测密码是否有误
					break;
				printf("您的密码输入有误，请从新输入\n");
			}
			printf("请输入用户名字：");
			scanf("%s",&client->clientname);
			printf("请输入用户描述：");
			scanf("%s",&client->usermessage);

			break;
		default:
			break;
		}
		printf("是否继续注册?(1、继续)(0、退出)");
		scanf("%d",&type);
		if(!type)
			break;
	}
	return success;
}

/*
	登录模块
	返回登录的用户类型
	用户必须先登录才能对图书进行操作
*/
int login()
{
	administer *temp_admin=NULL;
	libcard *temp_client=NULL;
	int type,temp;
	view_01();
	scanf("%d",&type);
	while(1)
	{
		switch(type)
		{
		case 1:
			if(current_admin!=NULL)
			{
				printf("对不起，登录人数已满，您目前还不能登陆!\n");
				break;
			}
			temp_admin=(administer*)malloc(sizeof(administer));
			printf("请输入管理员ID:");
			scanf("%s",&temp_admin->adminID);

			printf("请输入登录密码：");
			GetPassword(&temp_admin->password,12);
			//scanf("%s",&temp_admin->password);
			if(check_admin(&temp_admin))//调用函数检查
			{
				current_admin=temp_admin;
				return type;
			}
			else
			{
				printf("对不起，密码错误!\n");
				free(temp_admin);//如果登录失败则不能进行更多的操作
				current_admin=NULL;
				break;
			}
		case 2:
			if(current_client!=NULL)
			{
				printf("对不起，登录人数已满，您目前还不能登陆!\n");
				break;
			}
			temp_client = (libcard *)malloc(sizeof(libcard));
			printf("请输入借阅证号：");
			scanf("%s",&temp_client->userID);
			printf("请输入密码：");
			GetPassword(&temp_client->password,12);
			//scanf("%s",&temp_client->password);
			if(check_client(&temp_client))//调用函数检查
			{
				current_client=temp_client;
				return type;
			}
			else
			{
				printf("对不起，密码错误!\n");
				free(temp_client);
				current_client = NULL;
				break;
			}
		}

		printf("(0、退出)\n");
		scanf("%d",&temp);
		if(!temp)return 0;
	}
}

/*
	注销
*/
void logout(int c)
{
	switch(c)
	{
	case 1:
		printf("账号：%s 成功注销\n",current_admin->adminID);
		current_admin=NULL;

		break;
	case 2:
		printf("账号：%s 成功注销\n",current_client->userID);
		current_client=NULL;
		break;
	default:break;
	}
}

int check_admin(administer **admin)
{
	int success=0;
	administer *temp=admins;
	while(temp!=NULL)
	{
		if(!strcmp((*admin)->adminID , temp->adminID)&&!strcmp((*admin)->password,temp->password))
		{
			free(*admin);
			*admin=temp;
			success=1;
			break;
		}
		temp=temp->next;
	}
	return success;
}

int check_client(libcard **client)
{
	int success=0;
	libcard *temp=clients;
	while(temp!=NULL)
	{
		if(!strcmp((*client)->userID , temp->userID)&&!strcmp((*client)->password , temp->password))
		{
			free(*client);
			*client=temp;
			success=1;
			break;
		}
		temp=temp->next;
	}
	return success;
}

/*读取文件*/
book *read_book_file(FILE *filepoint)
{
   book *wz;
   wz=(book*)malloc(sizeof(book));
   fread(wz,sizeof(book),1,filepoint);
   return(wz);
}

/*
	为书
	写文件
	中序遍历的递归算法
	每次操作结束都需要将当前的操作存入文件保存
*/
void write_book_file(FILE *filepoint,volume *root)
{
	book wz;
	if(root!=NULL)
	{
		 write_book_file(filepoint,root->lchild);

		  strcpy(wz.bookinform , root->books.bookinform);
          strcpy(wz.bookname , root->books.bookname);
          strcpy(wz.writer , root->books.writer);
          wz.callnum = root->books.callnum;
		  wz.ending = root->books.ending;
		  wz.starting = root->books.starting;
		  wz.totalstorage = root->books.totalstorage;
		  wz.nowstorage = root->books.nowstorage;
          fwrite(&wz,sizeof(book),1,filepoint);

		write_book_file(filepoint,root->rchild);
	}
}

/*
	读取客户信息
*/
libcard *read_client_file(FILE *filepoint)
{
	int i=0;
	libcard wz;
	libcard *head=NULL;
	libcard *p1=NULL;
	libcard *p2=NULL;

	while(1)
	{
		i=0;
		fread (&wz,sizeof(libcard),1,filepoint);
		p1=(libcard *)malloc(sizeof(libcard));
		if(feof(filepoint))//判断文件结束
		{
			free(p1);
			break;
		}
		strcpy(p1->userID , wz.userID);
		strcpy(p1->password , wz.password);
		strcpy(p1->clientname , wz.clientname);
		strcpy(p1->usermessage , wz.usermessage);
		for(i=0;i<10;i++)
		{
			strcpy(p1->borrow[i].bookinform ,wz.borrow[i].bookinform);
			strcpy(p1->borrow[i].bookname , wz.borrow[i].bookname);
			strcpy(p1->borrow[i].writer , wz.borrow[i].writer);
			p1->borrow[i].callnum = wz.borrow[i].callnum ;
			p1->borrow[i].ending = wz.borrow[i].ending;
			p1->borrow[i].nowstorage = wz.borrow[i].nowstorage;
			p1->borrow[i].starting = wz.borrow[i].starting;
			p1->borrow[i].totalstorage = wz.borrow[i].totalstorage;
		}

		p1->next=p2;
		p2=p1;
	}
	head=p2;
    return(head);
}

/*
	读取管理员用户信息文件

*/
administer *read_admin_file(FILE *filepoint)
{
   administer wz;
   administer *head=NULL;
   administer *p1=NULL;
   administer *p2=NULL;
   while(1)
	{
		fread(&wz,sizeof(administer),1,filepoint);
		p1=(administer *)malloc(sizeof(administer));
		if(feof(filepoint))
		{
			free(p1);
			break;
		}

		strcpy(p1->adminID , wz.adminID);
		strcpy(p1->adminname , wz.adminname);
		strcpy(p1->adminmessage , wz.adminmessage);
		strcpy(p1->password , wz.password);
		p1->next=p2;
		p2=p1;
	}
	head=p2;
    return(head);
}

/*
	从键盘获取字符密码,显示为*,设定最大字符数为n
*/
void GetPassword(char *str,int n)
{
	int i=0;
	char c;
	while((c=getch())!=13&&i<n)//不回显
	{
		if(c!=8)
		{
			putch('*');//回显*
			str[i++]=c;
		}
		else
			i--;
	}
	putch('\n');
	str[i]='\0';
}


/*
	写入管理员用户的信息
*/
int write_admin_file(FILE *filepoint,administer *head)
{
  while(head!=NULL)//把链表中的数据存入文件
  {
		fwrite(head,sizeof(administer),1,filepoint);
		head=head->next;
  }
   return 0;
}

/*
	写入客户信息
*/
int write_client_file(FILE *filepoint, libcard *head)
{
	while(head!=NULL)
	{
		fwrite(head,sizeof(libcard),1,filepoint);
		head=head->next;
	}
	return 0;
}

/*
	客户
*/
void clientsev(volume **Btroot)
{
	int a,b;
	volume *temp;
	libcard *p=NULL;//用作临时指针

	if(current_client==NULL)
	{
		printf("您还未登录，请登录!\n");
		login();
		system("cls");////////////清屏
		return;//不管是否成功登陆都将返回原处
	}

	while(1)
	{
		system("cls");////////////清屏
		view_03();
		scanf("%d",&a);
		switch(a)
		{
		case 1:
			search(*Btroot);
			break;
		case 2:
			printf("输入索书号：\n");
			scanf("%d",&b);
			lend(Btroot,b);
			break;
		case 3:
			printf("输入索书号：\n");
			scanf("%d",&b);
			backbook(Btroot,b);
			break;
		case 4:
			preorder(*Btroot);
			break;

			/*用户查看自己的信息*/
		case 5:
			p=current_client->next;//保护链
			current_client->next=NULL;//孤立当前节点
			display_clients(current_client);
			current_client->next=p;//恢复链
			break;
		case 6:
			display_admins(admins);
			break;
		case 7:
			admin(Btroot);
			if(current_client==NULL)
				return;
			break;
		case 8:
			logout(2);
			if(current_admin!=NULL)//若此时客户端有登陆者转到客户端
				admin(Btroot);
			return;
		default:return;
		}
		system("pause");////////////////////////////
	}
}

/*
	管理员
	管理员能进行图书的购入或者销毁，还能对图书进行查询操作以及浏览客户资料
	但是管理员自己不能借书
*/
void admin(volume **Btroot)
{
	int a,b,oper;
	volume *temp;
	libcard *head;
	FILE *filepoint=NULL;

	system("cls");////////////清屏
	if(current_admin==NULL)
	{
		printf("您还未登录!\n");
		login();
		system("cls");////////////清屏
		return;//不管登录是否成功都将回到原处
	}

	while(1)
	{
		system("cls");////////////清屏
		view_02();
		scanf("%d",&oper);
		switch(oper)
		{
		case 1:
			in_stor(Btroot);
			break;
		case 2:
			printf("输入索书号进行销毁：");
			scanf("%d",&a);
			if(!out_stor(Btroot,a))
				printf("对不起，本馆并未藏有此书!\n");
			break;
		case 3:
			search(*Btroot);
			break;
		case 4:
			preorder(*Btroot);
			break;
		case 5:
			display_clients(clients);
			break;
		case 6:
			display_admins(admins);
			break;
		case 7:
			clientsev(Btroot);
			if(current_admin==NULL)
				return;
			break;
		case 8:
			logout(1);
			if(current_client!=NULL)//若此时管理员有登陆者转到管理员界面
				clientsev(Btroot);
			return;
		default:return ;
		}
		system("pause");
	}
}


int main()
{
	int a=0,b;
	int cases=0,goornot;
	FILE *f_book_store=NULL,*f_admin=NULL,*f_client=NULL;
	book booker;
	volume root,*Btroot;

	/*
		读取所有管理员和客户
	*/
	f_admin=fopen("user_admin.txt","r");
	admins=read_admin_file(f_admin);
	fclose(f_admin);
	f_client=fopen("user_client.txt","r");
	clients=read_client_file(f_client);
	fclose(f_client);
	createBST(&Btroot,2);//在系统启动时调出记录

	while(1)
	{
		system("cls");////////////清屏
		view_00();
		cases=0;//
		scanf("%d",&b);
		switch(b)
		{
		case 1:
			registerer();
			break;
		case 2:
			cases=login();
		default:break;
		}
			/*
				选择登录的用户
				本系统必须先登录才能操作
			*/
		switch(cases)
		{
		case 1:
			admin(&Btroot);//只有成功登陆的管理员才具有权限
			break;
		case 2:
			clientsev(&Btroot);
			break;
		default:break;
		}
		system("cls");////////////清屏
		printf("是否继续(1、继续)(0、退出)");
		scanf("%d",&goornot);
		if(!goornot)
			break;
	}


	/*
		退出本程序之前将本次的改动记录入文件
	*/
	f_admin=fopen("user_admin.txt","w");
	write_admin_file(f_admin,admins);
	fclose(f_admin);

	f_client=fopen("user_client.txt","w");
	write_client_file(f_client,clients);
	fclose(f_client);

	f_book_store = fopen("book_store.txt","w");
	write_book_file(f_book_store,Btroot);
	fclose(f_book_store);
	return 0;
}
