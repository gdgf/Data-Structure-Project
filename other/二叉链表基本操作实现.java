typedef struct Node              /*二叉链表的结点结构*/
	      {
	              DataType data;            /*数据域*/
	              struct Node *lchild;      /*指向左孩子结点*/
	              struct Node *rchild;      /*指向右孩子结点*/
	       }*BiTree,BitNode;

//初始化
void InitBitTree(BiTree *T)
{
	*T=NULL;
}
（2）销毁二叉树。
void DestroyBitTree(BiTree *T)
{
	if(*T) 				/*如果是非空二叉树*/
	{
		   if((*T)->lchild)
				DestroyBitTree(&((*T)->lchild));
		   if((*T)->rchild)
				DestroyBitTree(&((*T)->rchild));
		   free(*T);
		   *T=NULL;
	  }
}
（3）创建二叉树。根据二叉树的递归定义，先生成二叉树的根结点，将元素值赋给结点的数据域，然后递归创建左子树和右子树。其中’#’表示空。
    void CreateBitTree(BiTree *T)
   { 
       DataType ch;
       scanf(“%c”,&ch);
       if(ch==’#’) 
           *T=NULL;
       else{
            *T=(BiTree)malloc(sizeof(BitNode)); /*生成根结点*/
             if(!(*T))
                   exit(-1);
             (*T)->data=ch;
             CreateBitTree(&((*T)->lchild)); 	/*构造左子树*/
             CreateBitTree(&((*T)->rchild)); 	/*构造右子树*/
       }
   }
   （4）二叉树的插入操作。如果p指向的是非空二叉树，则判断LR的值，如果LR为0，则将子树c插入到T中，使c成为*p的左子树，结点*p原来的左子树成为c的右子树；如果LR为1，则将子树插入到T中，使c成为*p的右子树，结点*p原来的右子树成为c的右子树。这里的c与T不想交且右子树为空。
     int InsertChild(BiTree p,int LR,BiTree c) 
    {
		  if(p){ 			                /*如果p指向的二叉树非空*/
			   if(LR==0){
					c->rchild=p->lchild; 	/*p的原来的左子树成为c的右子树*/
					p->lchild=c; 			/*子树c作为p的左子树*/
				}else{
					c->rchild=p->rchild; 		/*p的原来的右子树作为c的右子树*/
					p->rchild=c; 			/*子树c作为p的右子树*/
				}
			  return 1;
		 }
		return 0;
      }
	  （5）返回二叉树e的左孩子结点元素值。
    DataType LeftChild(BiTree T,DataType e)
   {
        BiTree p;
        if(T){           		           /*如果二叉树不空*/
             p=Point(T,e); 	               /*p是元素值e的结点的指针*/
             if(p&&p->lchild)	           /*p不为空且p的左孩子结点存在*/
                  return p->lchild->data;  /*返回p的左孩子结点的元素值*/
        }
        return; 
    }
      （6）返回e的右孩子结点元素值。如果元素值为e的结点存在，并且该结点的右孩子结点存在，则返回e的右孩子结点的元素值。
     DataType RightChild(BiTree T,DataType e)
    {
             BiTree p;
             if(T){		        /*如果二叉树不空*/
                 p=Point(T,e); 	/*p是元素值e的结点的指针*/
                 if(p&&p->rchild)/*如果p不为空且p的右孩子结点存在*/
                     return p->rchild->data; /*返回p的右孩子结点的元素值*/
            }
            return;
    }
	  (7) 返回二叉树指定结点的指针的算法实现如下。
	BiTree Point(BiTree T,DataType e)
	{
		BiTree Q[MaxSize]; 			
		int front=0,rear=0; 	/*初始化队列*/
		BitNode *p;
		if(T){ 			        /*如果二叉树非空*/
			Q[rear]=T;
			rear++;
			while(front!=rear){ 		/*如果队列非空*/
			  p=Q[front]; 		/*取出队头指针*/
			  front++;			/*将队头指针出队*/
			  if(p->data==e)
					  return p;
              if(p->lchild){ 		/*如果左孩子结点存在，将左孩子指针入队*/
           
                Q[rear]=p->lchild;	/*左孩子结点的指针入队*/
                rear++;
              }
             if(p->rchild){		/*如果右孩子结点存在，将右孩子指针入队*/
                Q[rear]=p->rchild; /*右孩子结点的指针入队*/
                rear++;
            }
          }
        }
      return NULL;
    }
   （8）删除子树操作。先判断p指向的子树是否为空，如果不为空，则判断LR的值。如果LR为0，
       则删除p指向结点的左子树；如果LR为1，则删除p指向结点的右子树。如果删除成功，返回1，否则返回0。
     int DeleteLeftChild(BiTree p,int LR) 
    {
           if(p){ 	        /*如果p不空*/
              if(LR==0)
                  DestroyBitTree(&(p->lchild)); 	/*删除左子树*/
              else
                   DestroyBitTree(&(p->rchild)); 	/*删除右子树*/
              return 1;
           }
           return 0;
     }
	 