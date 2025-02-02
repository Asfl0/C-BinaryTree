#include <stdio.h>
#include <stdlib.h>
//树结构 
#define TREEFORMAT "%d "
typedef int Elemtype;//树内容 
typedef struct TreeNode
{
	struct TreeNode * lchild;
	struct TreeNode * rchild;
	Elemtype data;
}TreeNode;
//栈结构 
#define STACKFORMAT "%p "
typedef TreeNode * Stacktype;//栈内容 
typedef struct Stack
{
	Stacktype * data;
	int top;
	int capacity;	
}Stack;

//栈实现
//创建栈 
Stack * createStack(int capacity)
{
	Stack * NewStack = (Stack*)malloc(sizeof(Stack));
	NewStack->data   = (Stacktype *)malloc(sizeof(Stacktype)*capacity);
	if(NewStack->data==NULL||NewStack==NULL)
	{
		printf("栈创建失败\n");
		return NULL;
	}
	NewStack->top = -1;
	NewStack->capacity = capacity;
	return NewStack;
}
//删除栈
void deleteStack(Stack * MyStack)
{
	free(MyStack->data);
	free(MyStack);
} 
//入栈 
Stacktype push(Stack * MyStack , Stacktype newdata)
{
	if(MyStack->top == MyStack->capacity-1)//内存不足时自动扩容 
	{
		MyStack->capacity*=2;
		MyStack->data = realloc(MyStack->data,sizeof(Stacktype)*MyStack->capacity);
	}
	MyStack->data[++MyStack->top] = newdata;
	return newdata;
}
//出栈 
Stacktype pop(Stack * MyStack)
{
	if(MyStack->top == -1)
	{
		printf("栈已空,出栈失败\n");
		return NULL;
	}
	return MyStack->data[MyStack->top--];
}
//判断栈是否为空
int isStackEmpty(Stack * MyStack) 
{
	return MyStack->top==-1;
}
//查看栈顶元素
Stacktype peekStack(Stack * MyStack)
{
	return (MyStack->data)[MyStack->top];
} 
//遍历栈 
Stacktype * traversalStack(Stack * MyStack)
{
	Stacktype * ans = (Stacktype *)malloc(sizeof(Stacktype)*MyStack->capacity);
	if(ans == NULL)
	{
		printf("遍历失败:ans内存创建失败或者栈为空\n");
	}
	for(int i = 0 ; i<MyStack->capacity ; ++i)
	{
		ans[i]=MyStack->data[i];
	}
	return ans;
}
//树实现
//新建节点 
TreeNode * createTreeNode(TreeNode * lchild , TreeNode * rchild , Elemtype data)
{
	TreeNode * NewTreeNode = (TreeNode *)malloc(sizeof(TreeNode));
	NewTreeNode -> lchild  = lchild;
	NewTreeNode -> rchild  = rchild;
	NewTreeNode ->  data   =  data;
	return NewTreeNode;
} 
//前序遍历(递归)(打印)
void preDir(TreeNode * boot)
{
	if(boot==NULL)return;
	printf(TREEFORMAT,boot->data);
	if(boot->lchild!=NULL)	preDir(boot->lchild);
	if(boot->rchild!=NULL)	preDir(boot->rchild);
}
//前序遍历(非递归)(给出数据)
Elemtype * preTraverTree(TreeNode * root,int * oi)
{
	if(root==NULL)
	{
		*oi = 0;
		return NULL;
	}
	//创建栈和存放内容的空间 
	Stack * TreeStack = createStack(20);
	unsigned int SIZEOFans = 20;
	int INDEXans = 0;
	Elemtype * ans = malloc(sizeof(Elemtype)*SIZEOFans);
	//根入栈 
	push( TreeStack , root );
	//思路:将根入栈->将根出栈并处理->处理根的左右子树,先将右子树入栈,再将左子树入栈->出栈并处理->... 
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
//中序遍历(递归)(打印)
void midDir(TreeNode * root)
{
	if(root==NULL)return;
	midDir(root->lchild);
	printf(TREEFORMAT,root->data);
	midDir(root->rchild);
} 
//中序遍历(非递归)(给出数据)
Elemtype * midTraverTree(TreeNode * root,int * oi)
{
	if(root==NULL)
	{
		*oi = 0;
		return NULL;
	}
	//创建栈和存放内容的空间 
	Stack * TreeStack = createStack(20);
	unsigned int SIZEOFans = 20;
	int INDEXans = 0;
	Elemtype * ans = (Elemtype *)malloc(sizeof(Elemtype)*SIZEOFans);
	
	TreeNode * current = root; 
	//思路:先跑到最左下角->出栈并处理->A出栈并处理,更新current为这次处理的节点的右子树->处理该右子树->A出栈并处理->... 
	//      1		 1		 1		 @		 1		 1		 1
	//	   / \		/ \		/ \		/ \		/ \		/ \		/ \
	//    2   3    @   3   2   3   2   3   2   @   2   3   2   3
	//   / \	  / \	  / \	  / \	  / \	  / \	  / \
	//  @   5	 4   5	 4   @	 4   5	 4   5	 4   5	 4   5	
	while(!isStackEmpty(TreeStack) || current!=NULL)
	{
		while(current!=NULL)//左子树入栈到最底 
		{
			push(TreeStack,current);
			current = current->lchild;//lchild为NULL时,NULL未入栈 
		}
		current = pop(TreeStack);//左边最底下出栈 
		ans[INDEXans++] = current->data;//current为最左下 
		//如果current->rchild为 NULL,内层循环不会执行,继续出栈 
		//不是NULL则会将current变为该树的最左下 
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
//以下是错误的,未更新 current 
//	TreeNode * current = root;
//	while(!isStackEmpty(TreeStack))
//	{
//		ans[INDEXans++] = pop(TreeStack)->data;
//		if(current->rchild!=NULL)push(TreeStack,current->rchild);
//		if(current->lchild!=NULL)push(TreeStack,current->lchild);
//	}

//后序遍历(递归)(打印)
void latDir(TreeNode * root)
{
	if(root==NULL)return;
	latDir(root->lchild);
	latDir(root->rchild);
	printf(TREEFORMAT,root->data);	
}
//后序遍历(非递归)(给出数据)
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
	//思路:跑到最左下角->查看栈顶,栈顶的右子树是否处理过(->处理右子树)->处理栈顶并出栈,记录->查看栈顶... 
	//      1		 1		 1		 1		 #		 #		 @
	//	   / \		/ \		/ \		/ \		/ \		/ \		/ \
	//    2   3    &   3   &   3   @   3   @   3   2   @   2   3
	//   / \	  / \	  / \	  / \	  / \	  / \	  / \
	//  @   5	 4   5	 4   @	 4   5	 4   5	 4   5	 4   5
	while(!isStackEmpty(TreeStack)||current!=NULL)
	{
		while(current!=NULL)//左子树入栈到最底 
		{
			push(TreeStack,current);
			current = current->lchild;
		}
		//查看栈顶节点 
		TreeNode * topStack = peekStack(TreeStack);
		if(topStack->rchild!=NULL&&topStack->rchild!=lastuse)//执行条件:栈顶节点的右子树存在且未被处理
		{
			current = topStack->rchild;	//current跟着栈顶更新,用于处理右子树	
		}else//执行条件:栈顶节点无右子树或者右子树已被处理 .作用:处理当前节点(根节点/左节点)
		{
			ans[INDEXans++] = topStack->data;
			lastuse = pop(TreeStack);
		}
	}
	*oi = INDEXans;
	deleteStack(TreeStack);
	return ans;
}
//打印递归遍历
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
//打印非递归遍历的数据
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
	//构建二叉树 
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
	//前序遍历 
	Elemtype * ans1 = preTraverTree(root,&oi);	
	printTraver(ans1 , oi);
	printpreDir(root);
	//中序遍历 
	Elemtype * ans2 = midTraverTree(root,&oi);
	printTraver(ans2 , oi);
	printmidDir(root);
	//后序遍历 
	Elemtype * ans3 = latTraverTree(root,&oi);
	printTraver(ans3 , oi);
	printlatDir(root);
	return 0;
}

