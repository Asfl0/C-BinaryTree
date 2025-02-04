#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;
typedef struct TreeNode
{
	struct TreeNode * lchild;
	struct TreeNode * rchild;
	ElemType data;
	unsigned int ltag;
	unsigned int rtag;
}TreeNode;
typedef TreeNode * ThreadTree;
//实现创建节点 
TreeNode * createNode(TreeNode * lchild,TreeNode * rchild , ElemType data)
{
	TreeNode * NewNode = (TreeNode *)malloc(sizeof(TreeNode));
	NewNode->lchild = lchild;
	NewNode->rchild = rchild;
	NewNode->data = data;
	return NewNode;
}
//中序线索化及遍历 
TreeNode * pre;
//线索化 
void  threadIn(TreeNode * root)
{
	if(!root)return;
	threadIn(root->lchild);//遍历左节点 
	if(root->lchild == NULL)//对当前节点的左孩子进行线索化 
	{
		root->ltag = 1;
		root->lchild = pre;
	}
	if(pre->rchild==NULL)//对当前节点的前驱节点的右孩子进行线索化 
	{
		pre->rtag = 1;
		pre->rchild = root;
	}
	pre = root;//将当前节点的前驱节点移动为当前节点 
	threadIn(pre->rchild);//遍历当前节点的右孩子 
}
void threadTree(ThreadTree * head,ThreadTree T)
{
	//目的:让头节点左指向根节点,右指向遍历的最后一个节点; 
	//遍历的第一个的节点左指向头,最后一个节点的右指向头. 
	*head = (ThreadTree)malloc(sizeof(TreeNode));
	(*head)->ltag = 0;
	(*head)->rtag = 1;
	(*head)->rchild = (*head);//先让头的右孩子指向自己本身 
	
	if(T==NULL)(*head)->lchild = *head;//如果树为空,让头的左孩子也指向自己本身 
	else//树不为空 
	{
		//头的左孩子指向树的根 
		(*head)->lchild = T;
		pre = (*head);//pre指向头节点 
		
		threadIn(T);
		//threadIn执行完后pre为最后一个节点 
		//最后一个节点线索化
		pre->rchild = *head;
		pre->rtag = 1;
		//头节点右孩子指向最后一个节点
		(*head)->rchild = pre; 
	}
}
//基于线索遍历 
void threadTraver(ThreadTree head)
{
	TreeNode * curr;
	curr = head->lchild;//curr指向头 
	
	while(curr!=head)//最后一个遍历的点的后继节点为头节点 
	{//往左边挖到底 
		while(curr->ltag!=1)//根据标志判断是否到最左 //==0不行!=1行 
		{
			curr = curr->lchild;//curr往左跑 
		}
		printf("%d ",curr->data);
		//通过线索找 
		while(curr->rtag==1 && curr->rchild != head)//根据线索遍历
		{
			curr = curr->rchild;
			printf("%d ",curr->data);
		}
		curr = curr->rchild;//不是线索时往后走 
	}
	putchar(10);
} 
void test(TreeNode * root)
{
	if(root == NULL)return;
	test(root->lchild);
	printf("%d ",root->data);
	test(root->rchild);
}
int main()
{
	TreeNode * n7 = createNode(NULL,NULL,7);
	TreeNode * n6 = createNode(NULL,n7,6);
	TreeNode * n5 = createNode(NULL,NULL,5);
	TreeNode * n4 = createNode(NULL,NULL,4);
	TreeNode * n3 = createNode(n6,NULL,3);
	TreeNode * n2 = createNode(n4,n5,2);
	TreeNode * n1 = createNode(n2,n3,1);
	test(n1);putchar(10);
	
	TreeNode * head;//构建头节点 
	threadTree(&head,n1);//线索化 
	threadTraver(head);//基于线索化遍历 

	return 0;
}
