#include <stdio.h>
#include <malloc.h>

typedef struct TreeNode
{
	char data;
	TreeNode* left;
	TreeNode* right;
}TreeNode;

// ��ʼ��������
TreeNode* InitBinaryTree()
{
	char c;
	scanf_s("%c", &c);	// ��ʽ��������Ʒ�����'\n'��\n �ո���Ʊ�����ǿհ׷����հ��ַ���ʹscanf()�����ڶ���������ȥ�����е�һ�������հ��ַ���ֻ������һ���ǿհ׷���ʱ�������ֹscanf�����롣
	getchar();			// ѭ����������������ַ�,��ʱ������¼��һ�������ַ�,����ֹͣ����

	if (c == '?')
	{
		return NULL;
	}

	TreeNode* root = (TreeNode*)malloc(1 * sizeof(TreeNode));
	root->data = c;
	root->left = InitBinaryTree();	// �ݹ鹹��������
	root->right = InitBinaryTree();	// �ݹ鹹��������

	return root;
}

// �ݹ�ǰ��
void  PreorderTraversal(TreeNode* root)
{
	if (root != NULL)
	{
		printf("%c\t", root->data);
		PreorderTraversal(root->left);		//	�ݹ����������
		PreorderTraversal(root->right);		//	�ݹ����������
	}
}

// �ݹ�����
void  InorderTraversal(TreeNode* root)
{
	if (root != NULL)
	{
		InorderTraversal(root->left);
		printf("%c\t", root->data);
		InorderTraversal(root->right);
	}
}
/**************************����ջ*****************************/
typedef struct StackNode
{
	TreeNode* treeNode;
	StackNode* next;
}StackNode;

typedef struct Stack
{
	StackNode* top;		// ջ��ָ��
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

TreeNode* GetStackTopValue(Stack* s)	// ��ȡջ���ڵ��ڵ����ڵ�treeNode
{
	if (!IsStackEmpty(s))
	{
		return s->top->treeNode;
	}
}

StackNode* GetStackTopNode(Stack* s)	// ��ȡջ���ڵ�stackNode
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

// �ǵݹ�ǰ��
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
			root = root->right;		// ����Ҫ��ָ���Һ��ӣ����ͷ�!!!�������ڴ汨��ָ���Ѿ����ͷŽڵ���Һ��ӣ�����
			PopStack(&s);
			//printf("%c\t", root->data);
		}
	}
	printf("\n");
}

// �ǵݹ�����
void NoRecursionInorderTraversal(TreeNode* root)
{
	Stack s;
	InitStack(&s);	// ������©
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
			PopStack(&s);	// ����ָ���PopStackû���Ⱥ�˳��Ҫ��
		}
	}
	printf("\n");
}

int main()
{

	TreeNode* root = InitBinaryTree();
	printf("�ݹ�ǰ��");
	PreorderTraversal(root);
	printf("\n");
	/*printf("�ݹ�����");
	InorderTraversal(root);
	printf("\n");*/

	printf("�ǵݹ�ǰ��");
	NoRecursionPreorderTraversal(root);
	/*printf("�ǵݹ�����");
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

�����������ݣ�
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
