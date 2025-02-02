#include <stdio.h>
#include <stdlib.h>
//���ṹ 
#define TREEFORMAT "%d "
typedef int Elemtype;//������ 
typedef struct TreeNode
{
	struct TreeNode * lchild;
	struct TreeNode * rchild;
	Elemtype data;
}TreeNode;
//ջ�ṹ 
#define STACKFORMAT "%p "
typedef TreeNode * Stacktype;//ջ���� 
typedef struct Stack
{
	Stacktype * data;
	int top;
	int capacity;	
}Stack;

//ջʵ��
//����ջ 
Stack * createStack(int capacity)
{
	Stack * NewStack = (Stack*)malloc(sizeof(Stack));
	NewStack->data   = (Stacktype *)malloc(sizeof(Stacktype)*capacity);
	if(NewStack->data==NULL||NewStack==NULL)
	{
		printf("ջ����ʧ��\n");
		return NULL;
	}
	NewStack->top = -1;
	NewStack->capacity = capacity;
	return NewStack;
}
//ɾ��ջ
void deleteStack(Stack * MyStack)
{
	free(MyStack->data);
	free(MyStack);
} 
//��ջ 
Stacktype push(Stack * MyStack , Stacktype newdata)
{
	if(MyStack->top == MyStack->capacity-1)//�ڴ治��ʱ�Զ����� 
	{
		MyStack->capacity*=2;
		MyStack->data = realloc(MyStack->data,sizeof(Stacktype)*MyStack->capacity);
	}
	MyStack->data[++MyStack->top] = newdata;
	return newdata;
}
//��ջ 
Stacktype pop(Stack * MyStack)
{
	if(MyStack->top == -1)
	{
		printf("ջ�ѿ�,��ջʧ��\n");
		return NULL;
	}
	return MyStack->data[MyStack->top--];
}
//�ж�ջ�Ƿ�Ϊ��
int isStackEmpty(Stack * MyStack) 
{
	return MyStack->top==-1;
}
//�鿴ջ��Ԫ��
Stacktype peekStack(Stack * MyStack)
{
	return (MyStack->data)[MyStack->top];
} 
//����ջ 
Stacktype * traversalStack(Stack * MyStack)
{
	Stacktype * ans = (Stacktype *)malloc(sizeof(Stacktype)*MyStack->capacity);
	if(ans == NULL)
	{
		printf("����ʧ��:ans�ڴ洴��ʧ�ܻ���ջΪ��\n");
	}
	for(int i = 0 ; i<MyStack->capacity ; ++i)
	{
		ans[i]=MyStack->data[i];
	}
	return ans;
}
//��ʵ��
//�½��ڵ� 
TreeNode * createTreeNode(TreeNode * lchild , TreeNode * rchild , Elemtype data)
{
	TreeNode * NewTreeNode = (TreeNode *)malloc(sizeof(TreeNode));
	NewTreeNode -> lchild  = lchild;
	NewTreeNode -> rchild  = rchild;
	NewTreeNode ->  data   =  data;
	return NewTreeNode;
} 
//ǰ�����(�ݹ�)(��ӡ)
void preDir(TreeNode * boot)
{
	if(boot==NULL)return;
	printf(TREEFORMAT,boot->data);
	if(boot->lchild!=NULL)	preDir(boot->lchild);
	if(boot->rchild!=NULL)	preDir(boot->rchild);
}
//ǰ�����(�ǵݹ�)(��������)
Elemtype * preTraverTree(TreeNode * root,int * oi)
{
	if(root==NULL)
	{
		*oi = 0;
		return NULL;
	}
	//����ջ�ʹ�����ݵĿռ� 
	Stack * TreeStack = createStack(20);
	unsigned int SIZEOFans = 20;
	int INDEXans = 0;
	Elemtype * ans = malloc(sizeof(Elemtype)*SIZEOFans);
	//����ջ 
	push( TreeStack , root );
	//˼·:������ջ->������ջ������->���������������,�Ƚ���������ջ,�ٽ���������ջ->��ջ������->... 
	//      @		 1		 1		 1		 1
	//	   / \		/ \		/ \		/ \		/ \
	//    2   3    @   3   2   3   2   3   2   @
	//   / \	  / \	  / \	  / \	  / \
	//  4   5	 4   5	 @   5	 4   @	 4   5
	while(!isStackEmpty(TreeStack))
	{
		TreeNode * currentNode = pop(TreeStack);
		ans[INDEXans++]=currentNode->data;
		if(INDEXans == SIZEOFans)
		{
			SIZEOFans*=2;
			ans = realloc(ans,sizeof(Elemtype)*SIZEOFans);
		}
		if(currentNode->rchild!=NULL)push(TreeStack,currentNode->rchild);
		if(currentNode->lchild!=NULL)push(TreeStack,currentNode->lchild);
	}
	*oi = INDEXans;
	deleteStack(TreeStack);
	return ans;
}
//�������(�ݹ�)(��ӡ)
void midDir(TreeNode * root)
{
	if(root==NULL)return;
	midDir(root->lchild);
	printf(TREEFORMAT,root->data);
	midDir(root->rchild);
} 
//�������(�ǵݹ�)(��������)
Elemtype * midTraverTree(TreeNode * root,int * oi)
{
	if(root==NULL)
	{
		*oi = 0;
		return NULL;
	}
	//����ջ�ʹ�����ݵĿռ� 
	Stack * TreeStack = createStack(20);
	unsigned int SIZEOFans = 20;
	int INDEXans = 0;
	Elemtype * ans = (Elemtype *)malloc(sizeof(Elemtype)*SIZEOFans);
	
	TreeNode * current = root; 
	//˼·:���ܵ������½�->��ջ������->A��ջ������,����currentΪ��δ���Ľڵ��������->�����������->A��ջ������->... 
	//      1		 1		 1		 @		 1		 1		 1
	//	   / \		/ \		/ \		/ \		/ \		/ \		/ \
	//    2   3    @   3   2   3   2   3   2   @   2   3   2   3
	//   / \	  / \	  / \	  / \	  / \	  / \	  / \
	//  @   5	 4   5	 4   @	 4   5	 4   5	 4   5	 4   5	
	while(!isStackEmpty(TreeStack) || current!=NULL)
	{
		while(current!=NULL)//��������ջ����� 
		{
			push(TreeStack,current);
			current = current->lchild;//lchildΪNULLʱ,NULLδ��ջ 
		}
		current = pop(TreeStack);//�������³�ջ 
		ans[INDEXans++] = current->data;//currentΪ������ 
		//���current->rchildΪ NULL,�ڲ�ѭ������ִ��,������ջ 
		//����NULL��Ὣcurrent��Ϊ������������ 
		current = current->rchild;
		if(INDEXans == SIZEOFans)
		{
			SIZEOFans*=2;
			ans = realloc(ans,sizeof(Elemtype)*SIZEOFans);
		}
	}
	*oi = INDEXans;
	deleteStack(TreeStack);
	return ans;
} 
//�����Ǵ����,δ���� current 
//	TreeNode * current = root;
//	while(!isStackEmpty(TreeStack))
//	{
//		ans[INDEXans++] = pop(TreeStack)->data;
//		if(current->rchild!=NULL)push(TreeStack,current->rchild);
//		if(current->lchild!=NULL)push(TreeStack,current->lchild);
//	}

//�������(�ݹ�)(��ӡ)
void latDir(TreeNode * root)
{
	if(root==NULL)return;
	latDir(root->lchild);
	latDir(root->rchild);
	printf(TREEFORMAT,root->data);	
}
//�������(�ǵݹ�)(��������)
Elemtype * latTraverTree(TreeNode * root,int * oi)
{
	if(root==NULL)
	{
		*oi = 0;
		return NULL;
	}
	unsigned int SIZEOFans = 20;
	Stack * TreeStack = createStack(20);
	Elemtype * ans = (Elemtype *)malloc(sizeof(Elemtype)*SIZEOFans);
	
	int INDEXans = 0;
	TreeNode * current = root;
	TreeNode * lastuse = NULL;
	//˼·:�ܵ������½�->�鿴ջ��,ջ�����������Ƿ����(->����������)->����ջ������ջ,��¼->�鿴ջ��... 
	//      1		 1		 1		 1		 #		 #		 @
	//	   / \		/ \		/ \		/ \		/ \		/ \		/ \
	//    2   3    &   3   &   3   @   3   @   3   2   @   2   3
	//   / \	  / \	  / \	  / \	  / \	  / \	  / \
	//  @   5	 4   5	 4   @	 4   5	 4   5	 4   5	 4   5
	while(!isStackEmpty(TreeStack)||current!=NULL)
	{
		while(current!=NULL)//��������ջ����� 
		{
			push(TreeStack,current);
			current = current->lchild;
		}
		//�鿴ջ���ڵ� 
		TreeNode * topStack = peekStack(TreeStack);
		if(topStack->rchild!=NULL&&topStack->rchild!=lastuse)//ִ������:ջ���ڵ��������������δ������
		{
			current = topStack->rchild;	//current����ջ������,���ڴ���������	
		}else//ִ������:ջ���ڵ��������������������ѱ����� .����:����ǰ�ڵ�(���ڵ�/��ڵ�)
		{
			ans[INDEXans++] = topStack->data;
			lastuse = pop(TreeStack);
		}
	}
	*oi = INDEXans;
	deleteStack(TreeStack);
	return ans;
}
//��ӡ�ݹ����
void printpreDir(TreeNode * root)
{
	preDir(root);
	putchar(10);
}
void printmidDir(TreeNode * root)
{
	midDir(root);
	putchar(10);
}
void printlatDir(TreeNode * root)
{
	latDir(root);
	putchar(10);
}
//��ӡ�ǵݹ����������
void printTraver(Elemtype * ans,int index)
{
	for(int i = 0 ; i<index ; ++i)
	{
		printf(TREEFORMAT,ans[i]);
	}putchar(10);
	free(ans);
}  
int main()
{
	//���������� 
	//      1
	//     / \
	//    2   3
	//   / \
	//  4   5
	TreeNode * n5  = createTreeNode(NULL,NULL,5);
	TreeNode * n4  = createTreeNode(NULL,NULL,4);
	TreeNode * n3  = createTreeNode(NULL,NULL,3);
	TreeNode * n2  = createTreeNode( n4 , n5 ,2);
	TreeNode * root= createTreeNode( n2 , n3 ,1);
	int oi;	
	//ǰ����� 
	Elemtype * ans1 = preTraverTree(root,&oi);	
	printTraver(ans1 , oi);
	printpreDir(root);
	//������� 
	Elemtype * ans2 = midTraverTree(root,&oi);
	printTraver(ans2 , oi);
	printmidDir(root);
	//������� 
	Elemtype * ans3 = latTraverTree(root,&oi);
	printTraver(ans3 , oi);
	printlatDir(root);
	return 0;
}

