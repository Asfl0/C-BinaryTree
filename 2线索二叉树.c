#include <stdio.h>
#include <stdlib.h>
 
typedef int Elemtype;
typedef struct TreeNode
{
	Elemtype data;
	struct TreeNode * lchild;
	struct TreeNode * rchild;
	int ltag;//tagΪ0:->lchildΪ1:->ǰ�� 
	int rtag;//tagΪ0:->rchildΪ1:->��� 
	//0Ϊ����,1Ϊ���� 
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

TreeNode * pre;//ʼ��ָ��ǰ�ڵ������ǰ�� 

void midThreading(TreeNode * root)//���������� 
{
	if(root)
	{
		midThreading(root->lchild);
		if(root->lchild==NULL)//����ýڵ�û��������,����ָ��ָ����������е�ǰ���ڵ� 
		{			  
			root->ltag = 1;
			root->lchild = pre;
		}
		if(pre->rchild==NULL)//���ǰ���ڵ����ָ��Ϊ��,��ǰ���ڵ����ָ��ָ��ǰ�ڵ�  
		{			 //(��˼ͬ:����ýڵ�û��������,����ָ��ָ����������еĺ�̽ڵ�) 
			pre->rtag = 1;
			pre->rchild = root;
		}
		pre = root;
		midThreading(pre->rchild);
	}
}

TreeNode * ThreadTree(TreeNode * root)
{
	//ͷ���� 
	if(root==NULL)return NULL;
	TreeNode * head = createNode(root,NULL,0);
	
	head->ltag = 0;
	head->rtag = 1;
	pre = head;
	//������ ��β��ͷ 
	midThreading(root); 
	pre->rchild = head;
	pre->rtag = 1;
	//ͷ��β 
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
