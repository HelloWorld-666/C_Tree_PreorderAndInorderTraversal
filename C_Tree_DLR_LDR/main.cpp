#include <stdio.h>
#include <malloc.h>

typedef struct TreeNode
{
	char data;
	TreeNode* left;
	TreeNode* right;
}TreeNode;

// 初始化二叉树
TreeNode* InitBinaryTree()
{
	char c;
	scanf_s("%c", &c);	// 格式化输出控制符不加'\n'，\n 空格和制表符，是空白符。空白字符会使scanf()函数在读操作中略去输入中的一个或多个空白字符。只有输入一个非空白符的时候才能终止scanf的输入。
	getchar();			// 循环中连续多次输入字符,此时缓存会记录上一次输入字符,不再停止输入

	if (c == '?')
	{
		return NULL;
	}

	TreeNode* root = (TreeNode*)malloc(1 * sizeof(TreeNode));
	root->data = c;
	root->left = InitBinaryTree();	// 递归构建左子树
	root->right = InitBinaryTree();	// 递归构建右子树

	return root;
}

// 递归前序：
void  PreorderTraversal(TreeNode* root)
{
	if (root != NULL)
	{
		printf("%c\t", root->data);
		PreorderTraversal(root->left);		//	递归遍历左子树
		PreorderTraversal(root->right);		//	递归遍历右子树
	}
}

// 递归中序：
void  InorderTraversal(TreeNode* root)
{
	if (root != NULL)
	{
		InorderTraversal(root->left);
		printf("%c\t", root->data);
		InorderTraversal(root->right);
	}
}
/**************************定义栈*****************************/
typedef struct StackNode
{
	TreeNode* treeNode;
	StackNode* next;
}StackNode;

typedef struct Stack
{
	StackNode* top;		// 栈顶指针
}Stack;

void InitStack(Stack* s)
{
	s->top = NULL;
}

bool IsStackEmpty(Stack* s)
{
	if (s->top == NULL)
	{
		return true;
	}

	return  false;
}

TreeNode* GetStackTopValue(Stack* s)	// 获取栈顶节点内的树节点treeNode
{
	if (!IsStackEmpty(s))
	{
		return s->top->treeNode;
	}
}

StackNode* GetStackTopNode(Stack* s)	// 获取栈顶节点stackNode
{
	if (!IsStackEmpty(s))
	{
		return s->top;
	}
}

void PushStack(Stack* s, TreeNode* root)
{
	// new_node:
	StackNode* newStackNode = (StackNode*)malloc(1 * sizeof(StackNode));
	newStackNode->treeNode = root;
	newStackNode->next = NULL;

	// insert:
	newStackNode->next = s->top;
	s->top = newStackNode;
}

void PopStack(Stack* s)
{
	if (!IsStackEmpty(s))
	{
		StackNode* popNode = s->top;
		s->top = s->top->next;
		free(popNode);
		popNode = NULL;
	}
}

// 非递归前序：
void NoRecursionPreorderTraversal(TreeNode* root)
{
	Stack s;
	InitStack(&s);
	while (root != NULL || !IsStackEmpty(&s))
	{
		while (root != NULL)
		{
			printf("%c\t", root->data);
			PushStack(&s, root);
			root = root->left;
		}

		if (!IsStackEmpty(&s))
		{
			root = GetStackTopValue(&s);
			root = root->right;		// 必须要先指向右孩子，再释放!!!，否则内存报错：指向已经被释放节点的右孩子，出错。
			PopStack(&s);
			//printf("%c\t", root->data);
		}
	}
	printf("\n");
}

// 非递归中序：
void NoRecursionInorderTraversal(TreeNode* root)
{
	Stack s;
	InitStack(&s);	// 不能遗漏
	while (root != NULL || !IsStackEmpty(&s))
	{
		while (root != NULL)
		{
			PushStack(&s, root);
			root = root->left;
		}

		if (!IsStackEmpty(&s))
		{
			root = GetStackTopValue(&s);
			printf("%c\t", root->data);
			root = root->right;
			PopStack(&s);	// 这里指向和PopStack没有先后顺序要求
		}
	}
	printf("\n");
}

int main()
{

	TreeNode* root = InitBinaryTree();
	printf("递归前序：");
	PreorderTraversal(root);
	printf("\n");
	/*printf("递归中序：");
	InorderTraversal(root);
	printf("\n");*/

	printf("非递归前序：");
	NoRecursionPreorderTraversal(root);
	/*printf("非递归中序：");
	NoRecursionInorderTraversal(root);*/

	getchar();

	return 0;
}

/*
a
/  \
b	   c
/ \
d   e

测试输入数据：
a
b
d
?
?
e
?
?
c
?
?

*/
