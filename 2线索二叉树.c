#include <stdio.h>
#include <stdlib.h>
 
typedef int Elemtype;
typedef struct TreeNode
{
	Elemtype data;
	struct TreeNode * lchild;
	struct TreeNode * rchild;
	int ltag;//tag为0:->lchild为1:->前驱 
	int rtag;//tag为0:->rchild为1:->后继 
	//0为子树,1为线索 
}TreeNode;
TreeNode * createNode(TreeNode * lchild,TreeNode * rchild,Elemtype data)
{
	TreeNode * NewTree = (TreeNode *)malloc(sizeof(TreeNode));
	NewTree->lchild = lchild;
	NewTree->rchild = rchild;
	NewTree-> data  =  data ;
	NewTree-> ltag  = NewTree->lchild==NULL?1:0;
	NewTree-> rtag  = NewTree->rchild==NULL?1:0;
	return NewTree;
}

TreeNode * pre;//始终指向当前节点的中序前驱 

void midThreading(TreeNode * root)//中序线索化 
{
	if(root)
	{
		midThreading(root->lchild);
		if(root->lchild==NULL)//如果该节点没有左子树,则将左指针指向遍历序列中的前驱节点 
		{			  
			root->ltag = 1;
			root->lchild = pre;
		}
		if(pre->rchild==NULL)//如果前驱节点的右指针为空,将前驱节点的右指针指向当前节点  
		{			 //(意思同:如果该节点没有右子树,则将右指针指向遍历序列中的后继节点) 
			pre->rtag = 1;
			pre->rchild = root;
		}
		pre = root;
		midThreading(pre->rchild);
	}
}

TreeNode * ThreadTree(TreeNode * root)
{
	//头连根 
	if(root==NULL)return NULL;
	TreeNode * head = createNode(root,NULL,0);
	
	head->ltag = 0;
	head->rtag = 1;
	pre = head;
	//线索化 首尾接头 
	midThreading(root); 
	pre->rchild = head;
	pre->rtag = 1;
	//头连尾 
	head->rchild = pre;
	return head;
}
void dir(TreeNode * root)
{
	TreeNode * curr = root->lchild;
	while(curr!=root)
	{
		while(curr->ltag==0)
		{
			curr = curr->lchild;
		}
		printf("%d ",curr->data);
		while(curr->rtag==1&&curr->rchild!=root)
		{
			curr = curr->rchild;
			printf("%d ",curr->data);
		}
		curr = curr->rchild;
	}
	putchar(10);
}
void midDir(TreeNode * root)
{
	if(root==NULL)return;
	midDir(root->lchild);
	printf("%d ",root->data);
	midDir(root->rchild);
}
int main()
{
	TreeNode * n10= createNode(NULL,NULL,10);
	TreeNode * n9 = createNode(NULL,NULL,9 );
	TreeNode * n8 = createNode(NULL,NULL,8 );
	TreeNode * n7 = createNode(NULL,NULL,7 );
	TreeNode * n6 = createNode(NULL,NULL,6 );
	TreeNode * n5 = createNode( n10,NULL,5 );
	TreeNode * n4 = createNode( n8 , n9 ,4 );
	TreeNode * n3 = createNode( n6 , n7 ,3 );
	TreeNode * n2 = createNode( n4 , n5 ,2 );
	TreeNode * n1 = createNode( n2 , n3 ,1 );
	midDir(n1);putchar(10);
	ThreadTree(n1);

	
	
	return 0;
}
