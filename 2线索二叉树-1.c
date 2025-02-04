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
//ʵ�ִ����ڵ� 
TreeNode * createNode(TreeNode * lchild,TreeNode * rchild , ElemType data)
{
	TreeNode * NewNode = (TreeNode *)malloc(sizeof(TreeNode));
	NewNode->lchild = lchild;
	NewNode->rchild = rchild;
	NewNode->data = data;
	return NewNode;
}
//���������������� 
TreeNode * pre;
//������ 
void  threadIn(TreeNode * root)
{
	if(!root)return;
	threadIn(root->lchild);//������ڵ� 
	if(root->lchild == NULL)//�Ե�ǰ�ڵ�����ӽ��������� 
	{
		root->ltag = 1;
		root->lchild = pre;
	}
	if(pre->rchild==NULL)//�Ե�ǰ�ڵ��ǰ���ڵ���Һ��ӽ��������� 
	{
		pre->rtag = 1;
		pre->rchild = root;
	}
	pre = root;//����ǰ�ڵ��ǰ���ڵ��ƶ�Ϊ��ǰ�ڵ� 
	threadIn(pre->rchild);//������ǰ�ڵ���Һ��� 
}
void threadTree(ThreadTree * head,ThreadTree T)
{
	//Ŀ��:��ͷ�ڵ���ָ����ڵ�,��ָ����������һ���ڵ�; 
	//�����ĵ�һ���Ľڵ���ָ��ͷ,���һ���ڵ����ָ��ͷ. 
	*head = (ThreadTree)malloc(sizeof(TreeNode));
	(*head)->ltag = 0;
	(*head)->rtag = 1;
	(*head)->rchild = (*head);//����ͷ���Һ���ָ���Լ����� 
	
	if(T==NULL)(*head)->lchild = *head;//�����Ϊ��,��ͷ������Ҳָ���Լ����� 
	else//����Ϊ�� 
	{
		//ͷ������ָ�����ĸ� 
		(*head)->lchild = T;
		pre = (*head);//preָ��ͷ�ڵ� 
		
		threadIn(T);
		//threadInִ�����preΪ���һ���ڵ� 
		//���һ���ڵ�������
		pre->rchild = *head;
		pre->rtag = 1;
		//ͷ�ڵ��Һ���ָ�����һ���ڵ�
		(*head)->rchild = pre; 
	}
}
//������������ 
void threadTraver(ThreadTree head)
{
	TreeNode * curr;
	curr = head->lchild;//currָ��ͷ 
	
	while(curr!=head)//���һ�������ĵ�ĺ�̽ڵ�Ϊͷ�ڵ� 
	{//������ڵ��� 
		while(curr->ltag!=1)//���ݱ�־�ж��Ƿ����� //==0����!=1�� 
		{
			curr = curr->lchild;//curr������ 
		}
		printf("%d ",curr->data);
		//ͨ�������� 
		while(curr->rtag==1 && curr->rchild != head)//������������
		{
			curr = curr->rchild;
			printf("%d ",curr->data);
		}
		curr = curr->rchild;//��������ʱ������ 
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
	
	TreeNode * head;//����ͷ�ڵ� 
	threadTree(&head,n1);//������ 
	threadTraver(head);//�������������� 

	return 0;
}
