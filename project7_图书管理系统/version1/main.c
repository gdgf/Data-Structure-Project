/*
	���������������Ϊ�洢�ṹ
*/
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<time.h>
#define MAXNUM 10

typedef struct book
{
	long int starting;    //��������
	long int ending;      //Ӧ������
	char bookinform[120]; //������洢�鼮��������Ϣ
	long int callnum;     //�����
	char bookname[30];
	char writer[20];
	int totalstorage, nowstorage;//�鱾�Ĺݲ�����������
}book;
/*���ṹ�����ڴ�������Ķ�����*/
typedef struct volume
{
	book books;
	struct volume *lchild;
	struct volume *rchild;
}volume,*Btvolume;

typedef struct libcard
{
	char userID[12];
	char password[12];//����
	char clientname[20];//�û�������
	char usermessage[150];//�û���Ϣ
	book borrow[10];//ÿ������֤�޽���ʮ��
	struct libcard *next;
}libcard;              //�û���Ϣ

typedef struct administer
{
	char adminID[12];
	char password[12];
	char adminname[20];     //����Ա����...
	char adminmessage[150];
	struct administer *next;
}administer;               //����Ա��Ϣ

administer *admins,*current_admin=NULL;
libcard *clients,*current_client=NULL;
/*
	��������
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
void write_book_file(FILE *filepoint,volume *root);//д�ļ�
administer *read_admin_file(FILE *filepoint);
libcard *read_client_file(FILE *filepoint);//���ͻ���Ϣ
int write_admin_file(FILE *filepoint,administer *head);
void GetPassword(char *str,int n);


int registerer();
int login();//��¼
void logout(int c);//ע��
void admin(volume **Btroot);//����Ա
void clientsev(volume **Btroot);//�ͻ�(ѧ��)
int check_admin(administer *admin);
int check_client(libcard *client);
void in_stor(volume **root);//���
int out_stor(Btvolume *root,long int key);//����
void backbook(Btvolume *root,long int callnum);//����
int lend(Btvolume *root,long int callnum);//���飬��ѧ����������
void search(Btvolume *root);
void quesheng(Btvolume root,int a,char *key);//ȱʡ����
void preorder(Btvolume root);//�������������ȫ�����鼮
void display_clients(libcard *head);
void display_admins(administer *head);



/*
	�����������Ĳ���ģ�飬���õݹ��㷨ʵ��
*/
void insertBST(Btvolume *bst,book *key)
{
	Btvolume s;
	if(*bst==NULL)//�ݹ��������
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
	��ģ��ʵ�ֶ����������Ľ���
	˵����1������ Btvolume *bst Ϊ���������ĸ��ڵ�
		  2��ֻ�п����Ϊ�յ�ʱ����ܵ��ñ�ģ��
		  3��ֻ�й���Ա���ܵ��ñ�ģ��
		  4������ manner ����ָ�����ļ��������ǴӼ��̴���
				manner=1�����̡�manner=2�����ļ�
		  5��ֻ����ϵͳ��ʼ���ǲ�����Ӽ��̴���
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
				/*�����鱾��Ϣ*/
			key->starting=0;
			key->ending=0;
			printf("��������ţ�");
			scanf("%ld",&(key->callnum));
			if(key->callnum == 0){
				free(key);
				break;
			}
			printf("�����������");
			scanf("%d",&(key->totalstorage));
			key->nowstorage=key->totalstorage;
			printf("�����鱾����");
			scanf("%s",&(key->bookname));
			printf("���������ߣ�");
			scanf("%s",&(key->writer));
			printf("������������");
			scanf("%s",&(key->bookinform));
		}
		else
		{
			if(!feof(f_book_store))//�ж��ļ��Ƿ����
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
		insertBST(bst,key);//���ò������ʵ���������
	}
	fclose(f_book_store);

///////////////////////////////////////////////////////////////////////
	f_book_store = fopen("book_store.txt","w");
	write_book_file(f_book_store,*bst);
	fclose(f_book_store);
///////////////////////////////////////////////////////////////////////
}

/*
	�����������Ĳ����㷨
	�������Ϊ�ؼ��ֽ��ж��ֲ���
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
	������������ɾ���㷨
	ʵ�ֶԹݲص��鼮��������
	�����Ƿ�ɹ�
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
	����λ��ģʽƥ���㷨
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
	��⺯�������������鱾���
	�����޷���ֵ
	ʵ�֣�1������������Ľ���
		  2������������Ĳ���
		  3������������Ĳ���
		  4�������������ɾ��
	˵���������ﲢû�ж��������в���
*/
void in_stor(volume **root)
{
	FILE *file_book_store;
	Btvolume p,q;
	book *key;

	/*��������*/
	key=(book*)malloc(sizeof(book));
	printf("��������ţ�");
	scanf("%ld",&(key->callnum));
	printf("�����������");
	scanf("%d",&(key->totalstorage));
	key->nowstorage=key->totalstorage;
	printf("�����鱾����");
	scanf("%s",&(key->bookname));
	printf("���������ߣ�");
	scanf("%s",&(key->writer));
	printf("������������");
	scanf("%s",&(key->bookinform));
	key->starting = 0;
	key->ending = 0;

	insertBST(root,key);
}

/**/
int out_stor(Btvolume *root,long int key)
{
	int success=0;//��Ϊ����ֵ�����ڱ�������Ƿ�ɹ�
	delBST(*root,key);
	return success;
}

/*
	����ģ�飬��ѧ����������
	ÿ��ֻ�ܻ�һ����
	����������ͬ������Ҳ�軹����!
	�޷���ֵ
	�������Ӧ��������ӣ�ͬʱѧ���ĵ�ǰ����������
	������ڣ��򷣿û����һ�췣��0.2Ԫ������һ�찴һ����
*/
void backbook(Btvolume *root,long int callnum)
{
	Btvolume temp;
	time_t t;
	int i=0;
	double overtime,fine;

	if(current_admin==NULL)//����ǰ�޹���Ա�ⲻ�ܽ���
	{
		printf("�Բ���Ŀǰ����Աδ��¼�����ɻ���!\n");
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
		printf("�Բ�������δ�������!\n");
		return;
	}
	temp=searchBST(*(root),callnum);
	if(temp==NULL)
	{
		printf("���ã����ݲ�δ���д���,��˲��ػ�!\n");
		return;
	}
	if(temp->books.nowstorage >= temp->books.totalstorage)
	{
		printf("�Բ�������δ�������!\n");
		return;
	}
	time(&t);
	if( t > current_client->borrow[i].ending)
	{
		overtime=((t- current_client->borrow[i].ending)/43200)+1;
		fine = overtime * 0.2;
		printf("�Բ�������������Ѿ����� %0.0f ��\n",overtime);
		printf("��ͼ�����ع涨���������� %0.2lf Ԫ\n",fine);
	}
	/*����������Ĵ���*/
	temp->books.nowstorage++;

	current_client->borrow[i].bookinform[0]='\0';
	current_client->borrow[i].bookname[0]='\0';
	current_client->borrow[i].callnum=0;
	current_client->borrow[i].ending= 2004967296;//
	current_client->borrow[i].starting=0;
	current_client->borrow[i].nowstorage=0;
	current_client->borrow[i].totalstorage=0;
	current_client->borrow[i].writer[0]='\0';

	printf("���ѳɹ�����,��ӭ�´ι���!\n");
}

/*
	����ģ�飬��ѧ����������,��Ҫ�����и�����Ա
	���ؽ����Ƿ�ɹ�
	�����ǰ�Ŀɽ���������0��ѧ����ǰ������δ��������
	�����ɹ� ����ʧ��
*/
int lend(Btvolume *root,long int callnum)
{
	int success=0;//��Ϊ����ֵ�����ڱ�ǽ����Ƿ�ɹ�
	int i=0;
	time_t t;
	Btvolume temp;
	if(current_admin==NULL)//����ǰ�޹���Ա�ⲻ�ܽ���
	{
		printf("�Բ���Ŀǰ����Աδ��¼�����ɽ���!\n");
		return success;
	}

	while(current_client->borrow[i].callnum>0)
		i++;
	if(i>=10)
		printf("�Բ������������࣬���Ȼ���!\n");
	else
	{
		temp=searchBST(*root,callnum);
		if(temp==NULL)
			printf("�Բ��𣬱���û���ղش���!\n");
		else if(temp->books.nowstorage > 0)
		{
			time(&t);
			temp->books.nowstorage -= 1;
			current_client->borrow[i].callnum = callnum;
			current_client->borrow[i].starting = t;//��ȡ��ǰϵͳʱ��
			current_client->borrow[i].ending = current_client->borrow[i].starting+2592000;
			current_client->borrow[i].totalstorage = temp->books.totalstorage;
			current_client->borrow[i].nowstorage = temp->books.nowstorage;
			strcpy(current_client->borrow[i].bookinform , temp->books.bookinform);
			strcpy(current_client->borrow[i].bookname , temp->books.bookname);
			strcpy(current_client->borrow[i].writer , temp->books.writer);
			success=1;

			printf("���Ѿ��ɹ����飬��ӭ�´ι���!\n");
		}
		else
			printf("�Բ��𣬸����ѱ�����!\n");
	}
	return success;
}

/*
	��Ŀȱʡ���ҵ�ʵ��ģ��
	��Ҫ�㷨Ϊ�ַ���ƥ���ģʽƥ���㷨
	��ͼ����������������ÿ���ڵ㶼���бȽ�
	�������������Ŀ�����ý��������ŵĴ�С˳����ʾ
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
			b=strindex(root->books.bookname,key);//����
			break;
		case 2:
			b=strindex(root->books.writer,key);//����
			break;
		case 3:
			b=strindex(root->books.bookinform,key);//��Ϣ
			break;
		case 4:
			break;
		}
		if(b)
		{
			printf("����ţ�%d\n",root->books.callnum);
			printf("����  ��%s\n",root->books.bookname);
			printf("����  ��%s\n",root->books.writer);
			printf("����  ��%s\n",root->books.bookinform);
			printf("�ݲ�����%d\n",root->books.totalstorage);
			printf("�ɽ�����%d\n",root->books.nowstorage);
			if(root->books.starting!=0)
			{
				p=localtime(&(root->books.starting));
				printf("�����գ�%d/%d/%d\n",p->tm_year+1900,p->tm_mon+1,p->tm_mday);
				p=localtime(&(root->books.ending));
				printf("�����գ�%d/%d/%d\n",p->tm_year+1900,p->tm_mon+1,p->tm_mday);
			}
			printf("----------------------------------------------\n");
		}
		b=0;
		quesheng(root->rchild,a,key);
		b=0;
	}
}

/*
	��Ŀ����ģ�飬��ʵ�־�ȷ���Һ�ȱʡ���ҹ���
	ͨ������Ž��о�ȷ����
	ͨ����Ŀ�����Ϣ���о�ȷ����
*/
void search(Btvolume *root)
{
	volume *temp;
	char keyword[30];//�ؼ����������29���ַ�
	long int b;
	int a;
	while(1)
	{
		view_06();
		scanf("%d",&a);
		switch(a)
		{
		case 1:
			printf("��������ţ�\n");
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
	ʵ�������������������
*/
void preorder(Btvolume root)
{
	struct tm *p;
	if(root!=NULL)
	{
		preorder(root->lchild);

		printf("����ţ�%d\n",root->books.callnum);
		printf("����  ��%s\n",root->books.bookname);
		printf("����  ��%s\n",root->books.writer);
		printf("����  ��%s\n",root->books.bookinform);
		printf("�ݲ�����%d\n",root->books.totalstorage);
		printf("�ɽ�����%d\n",root->books.nowstorage);
		if(root->books.starting!=0)
		{
			p=localtime(&(root->books.starting));
			printf("�����գ�%d/%d/%d\n",p->tm_year+1900,p->tm_mon+1,p->tm_mday);
			p=localtime(&(root->books.ending));
			printf("�����գ�%d/%d/%d\n",p->tm_year+1900,p->tm_mon+1,p->tm_mday);
		}
		printf("----------------------------------------------\n");

		preorder(root->rchild);
	}
}

/*
	��ʾ�ͻ���Ϣ
*/
void display_clients(libcard *head)
{
	struct tm *p;
	int i=0;
	libcard *temp=head;
	if(head == NULL)
	{
		printf("���ã���ǰ�޿ͻ�!\n");
		return;
	}
	while(temp!=NULL)
	{
		printf("---------------------------------------------\n");
		printf("�� �� ID��%s\n",temp->userID);
		printf("�ͻ����֣�%s\n",temp->clientname);
		i=0;
		while(i<10)
		{
			if(temp->borrow[i].starting>0)
			{
				printf("  -----------------------------------------\n");
				printf("\t|�ͻ���ǰ����\n");
				printf("\t|����ţ�%ld\n",temp->borrow[i].callnum);
				printf("\t|�鼮����%s\n",temp->borrow[i].bookname);
				printf("\t|�����ߣ�%s\n",temp->borrow[i].writer);
				printf("\t|��  �飺%s\n",temp->borrow[i].bookinform);
				if(temp->borrow[i].starting!=0)
				{
					p=localtime(&(temp->borrow[i].starting));
					printf("\t|�����գ�%d/%d/%d\n",p->tm_year+1900,p->tm_mon+1,p->tm_mday);
					p=localtime(&(temp->borrow[i].ending));
					printf("\t|�����գ�%d/%d/%d\n",p->tm_year+1900,p->tm_mon+1,p->tm_mday);
				}
			}
			i++;
		}
		printf("�ͻ�˵����%s\n",temp->usermessage);
		printf("---------------------------------------------\n");
		temp=temp->next;
	}
}

/*
	��ʾ����Ա��Ϣ
*/
void display_admins(administer *head)
{
	int i=0;
	administer *temp=head;
	if(head == NULL)
	{
		printf("���ã���ǰ�޹���Ա!\n");
		return;
	}
	while(temp!=NULL)
	{
		printf("---------------------------------------------\n");
		printf("����Ա  ID��%s\n",temp->adminID);
		printf("����Ա������%s\n",temp->adminname);
		printf("����Ա��Ϣ��%s\n",temp->adminmessage);
		printf("---------------------------------------------\n");
		temp=temp->next;
	}
}

void display(volume *key)
{
	time_t t;
	if(key==NULL)
	{
		printf("�Բ��𣬱���Ŀǰ�޴˲���!\n");
		return;
	}
	printf("---------------------------------------------\n");
	printf("����ţ�%d\n",key->books.callnum);
	printf("����  ��%s\n",key->books.bookname);
	printf("����  ��%s\n",key->books.writer);
	printf("����  ��%s\n",key->books.bookinform);
	printf("�ݲ�����%d\n",key->books.totalstorage);
	printf("�ɽ�����%d\n",key->books.nowstorage);
	printf("----------------------------------------------\n");
}



/*
	ע��ģ��
	����ע���Ƿ�ɹ�
	�û���ע��
*/
int registerer()
{
	FILE *fad=NULL,*fcl=NULL;
	administer *admin,*admin_temp=NULL;
	libcard *client,*client_temp=NULL;
	char temp[13];
	int type,success=0;
	int admin_total=0,client_total=0;//���ڼ�¼����Ա�Ϳͻ�����///����ɡ���
	int i;
	while(1){
		printf("��ѡ��ע�������(1������Ա)(2���ͻ�):");
		scanf("%d",&type);
		switch(type)
		{
		case 1:

			admin=(administer*)malloc(sizeof(administer));//�������Ҫ
			admin->next=NULL;/////�������Ҫ
			printf("����ԱID��");
			scanf("%s",&admin->adminID);
			/*
				����Ƿ�Ϊ�ظ�ע��
			*/
			admin_temp=admins;
			while(admin_temp!=NULL)
			{
				if(!strcmp(admin->adminID , admin_temp->adminID))
					break;
				admin_temp=admin_temp->next;
			}
			if(admin_temp == NULL)//û����ͬ��ID
			{
				admin->next=admins;
				admins=admin;
			}
			else
			{
				printf("�Բ��𣬸�ID�ѱ�ռ��,ע��ʧ��!\n");
				free(admin);
				admin=NULL;
				break;
			}
			while(1)
			{
				printf("���룺");
				GetPassword(&admin->password,12);//�������룬����*
				//scanf("%s",&admin->password);
				printf("ȷ�����룺");
				GetPassword(&temp,12);//�������룬����*
				//scanf("%s",&temp);
				if(!strcmp(admin->password,temp))
					break;
				printf("�������������������������\n");
			}
			printf("�������û�����:");
			scanf("%s",&admin->adminname);
			printf("�������û�����:");
			scanf("%s",&admin->adminmessage);

			break;

		case 2:

			client=(libcard*)malloc(sizeof(libcard));//�������Ҫ
			client->next=NULL;
			printf("�û�ID��");
			scanf("%s",&client->userID);

			/*
				����Ƿ�Ϊ�ظ�ע��
			*/
			client_temp=clients;
			while(client_temp!=NULL)
			{
				if(!strcmp(client->userID , client_temp->userID))//��������ͬID��������ͬ����
					break;
				client_temp=client_temp->next;
			}
			if(client_temp == NULL)//û����ͬ��ID
			{
				/*
					ע��ɹ���Ӧ����Ϣ���г�ʼ��
				*/
				for(i=0;i<10;i++)
				{
					client->borrow[i].bookinform[0] = '\0';
					client->borrow[i].bookname[0] = '\0';
					client->borrow[i].writer[0] = '\0';
					client->borrow[i].callnum = 0;
					client->borrow[i].starting = 0;
					client->borrow[i].ending = 315360000;//���黹���ڳ�ʼΪ�����
					client->borrow[i].nowstorage = 0;
					client->borrow[i].totalstorage = 0;
				}

				client->next=clients;
				clients=client;
			}
			else
			{
				printf("�Բ��𣬸�ID�ѱ�ռ��,ע��ʧ��!\n");
				break;
			}
			while(1)
			{
				printf("���룺");
				GetPassword(&client->password,12);
				//scanf("%s",&client->password);
				printf("ȷ�����룺");
				GetPassword(&temp,12);
				//scanf("%s",&temp);
				if(!strcmp(client->password,temp))//��������Ƿ�����
					break;
				printf("�������������������������\n");
			}
			printf("�������û����֣�");
			scanf("%s",&client->clientname);
			printf("�������û�������");
			scanf("%s",&client->usermessage);

			break;
		default:
			break;
		}
		printf("�Ƿ����ע��?(1������)(0���˳�)");
		scanf("%d",&type);
		if(!type)
			break;
	}
	return success;
}

/*
	��¼ģ��
	���ص�¼���û�����
	�û������ȵ�¼���ܶ�ͼ����в���
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
				printf("�Բ��𣬵�¼������������Ŀǰ�����ܵ�½!\n");
				break;
			}
			temp_admin=(administer*)malloc(sizeof(administer));
			printf("���������ԱID:");
			scanf("%s",&temp_admin->adminID);

			printf("�������¼���룺");
			GetPassword(&temp_admin->password,12);
			//scanf("%s",&temp_admin->password);
			if(check_admin(&temp_admin))//���ú������
			{
				current_admin=temp_admin;
				return type;
			}
			else
			{
				printf("�Բ����������!\n");
				free(temp_admin);//�����¼ʧ�����ܽ��и���Ĳ���
				current_admin=NULL;
				break;
			}
		case 2:
			if(current_client!=NULL)
			{
				printf("�Բ��𣬵�¼������������Ŀǰ�����ܵ�½!\n");
				break;
			}
			temp_client = (libcard *)malloc(sizeof(libcard));
			printf("���������֤�ţ�");
			scanf("%s",&temp_client->userID);
			printf("���������룺");
			GetPassword(&temp_client->password,12);
			//scanf("%s",&temp_client->password);
			if(check_client(&temp_client))//���ú������
			{
				current_client=temp_client;
				return type;
			}
			else
			{
				printf("�Բ����������!\n");
				free(temp_client);
				current_client = NULL;
				break;
			}
		}

		printf("(0���˳�)\n");
		scanf("%d",&temp);
		if(!temp)return 0;
	}
}

/*
	ע��
*/
void logout(int c)
{
	switch(c)
	{
	case 1:
		printf("�˺ţ�%s �ɹ�ע��\n",current_admin->adminID);
		current_admin=NULL;

		break;
	case 2:
		printf("�˺ţ�%s �ɹ�ע��\n",current_client->userID);
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

/*��ȡ�ļ�*/
book *read_book_file(FILE *filepoint)
{
   book *wz;
   wz=(book*)malloc(sizeof(book));
   fread(wz,sizeof(book),1,filepoint);
   return(wz);
}

/*
	Ϊ��
	д�ļ�
	��������ĵݹ��㷨
	ÿ�β�����������Ҫ����ǰ�Ĳ��������ļ�����
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
	��ȡ�ͻ���Ϣ
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
		if(feof(filepoint))//�ж��ļ�����
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
	��ȡ����Ա�û���Ϣ�ļ�

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
	�Ӽ��̻�ȡ�ַ�����,��ʾΪ*,�趨����ַ���Ϊn
*/
void GetPassword(char *str,int n)
{
	int i=0;
	char c;
	while((c=getch())!=13&&i<n)//������
	{
		if(c!=8)
		{
			putch('*');//����*
			str[i++]=c;
		}
		else
			i--;
	}
	putch('\n');
	str[i]='\0';
}


/*
	д�����Ա�û�����Ϣ
*/
int write_admin_file(FILE *filepoint,administer *head)
{
  while(head!=NULL)//�������е����ݴ����ļ�
  {
		fwrite(head,sizeof(administer),1,filepoint);
		head=head->next;
  }
   return 0;
}

/*
	д��ͻ���Ϣ
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
	�ͻ�
*/
void clientsev(volume **Btroot)
{
	int a,b;
	volume *temp;
	libcard *p=NULL;//������ʱָ��

	if(current_client==NULL)
	{
		printf("����δ��¼�����¼!\n");
		login();
		system("cls");////////////����
		return;//�����Ƿ�ɹ���½��������ԭ��
	}

	while(1)
	{
		system("cls");////////////����
		view_03();
		scanf("%d",&a);
		switch(a)
		{
		case 1:
			search(*Btroot);
			break;
		case 2:
			printf("��������ţ�\n");
			scanf("%d",&b);
			lend(Btroot,b);
			break;
		case 3:
			printf("��������ţ�\n");
			scanf("%d",&b);
			backbook(Btroot,b);
			break;
		case 4:
			preorder(*Btroot);
			break;

			/*�û��鿴�Լ�����Ϣ*/
		case 5:
			p=current_client->next;//������
			current_client->next=NULL;//������ǰ�ڵ�
			display_clients(current_client);
			current_client->next=p;//�ָ���
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
			if(current_admin!=NULL)//����ʱ�ͻ����е�½��ת���ͻ���
				admin(Btroot);
			return;
		default:return;
		}
		system("pause");////////////////////////////
	}
}

/*
	����Ա
	����Ա�ܽ���ͼ��Ĺ���������٣����ܶ�ͼ����в�ѯ�����Լ�����ͻ�����
	���ǹ���Ա�Լ����ܽ���
*/
void admin(volume **Btroot)
{
	int a,b,oper;
	volume *temp;
	libcard *head;
	FILE *filepoint=NULL;

	system("cls");////////////����
	if(current_admin==NULL)
	{
		printf("����δ��¼!\n");
		login();
		system("cls");////////////����
		return;//���ܵ�¼�Ƿ�ɹ������ص�ԭ��
	}

	while(1)
	{
		system("cls");////////////����
		view_02();
		scanf("%d",&oper);
		switch(oper)
		{
		case 1:
			in_stor(Btroot);
			break;
		case 2:
			printf("��������Ž������٣�");
			scanf("%d",&a);
			if(!out_stor(Btroot,a))
				printf("�Բ��𣬱��ݲ�δ���д���!\n");
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
			if(current_client!=NULL)//����ʱ����Ա�е�½��ת������Ա����
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
		��ȡ���й���Ա�Ϳͻ�
	*/
	f_admin=fopen("user_admin.txt","r");
	admins=read_admin_file(f_admin);
	fclose(f_admin);
	f_client=fopen("user_client.txt","r");
	clients=read_client_file(f_client);
	fclose(f_client);
	createBST(&Btroot,2);//��ϵͳ����ʱ������¼

	while(1)
	{
		system("cls");////////////����
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
				ѡ���¼���û�
				��ϵͳ�����ȵ�¼���ܲ���
			*/
		switch(cases)
		{
		case 1:
			admin(&Btroot);//ֻ�гɹ���½�Ĺ���Ա�ž���Ȩ��
			break;
		case 2:
			clientsev(&Btroot);
			break;
		default:break;
		}
		system("cls");////////////����
		printf("�Ƿ����(1������)(0���˳�)");
		scanf("%d",&goornot);
		if(!goornot)
			break;
	}


	/*
		�˳�������֮ǰ�����εĸĶ���¼���ļ�
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
