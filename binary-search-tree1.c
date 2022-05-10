#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {	

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)	//���� ��ȸ�� �ϴ� �Լ�
{
		// ��尡 ������ ��� ����
		inorderTraversal(ptr->left); //���� �ڽĳ�� ���� ���
		printf(" [%d] ", ptr->key);	//�θ��� ���
		inorderTraversal(ptr->right);//������ �ڽĳ�� ���
	
}

void preorderTraversal(Node* ptr)	//���� ��ȸ�� �ϴ� �Լ�
{
	
		printf(" [%d] ", ptr->key);	//�θ��带 ���� ���
		preorderTraversal(ptr->left); //���� �ڽĳ�� ���
		preorderTraversal(ptr->right); //������ �ڽĳ�� ���
	
}

void postorderTraversal(Node* ptr)	//���� ��ȸ�� �ϴ� �Լ�
{
		postorderTraversal(ptr->left);	//���� �ڽĳ�带 ���� ���
		postorderTraversal(ptr->right);	//������ �ڽĳ�� ���
		printf(" [%d] ", ptr->key);  //�θ� ��� ���
	
}


int insert(Node* head, int key)	//��带 �߰��ϴ� �Լ�
{
	Node* newNode = (Node*)malloc(sizeof(Node));	//�߰��� ��带 ���� ����ü ����
	newNode->key = key;	//����� Ű�� �Է�
	newNode->left = NULL; // �ڽ� ��带 ������ ������ �ʱ�ȭ
	newNode->right = NULL; // �ڽ� ��带 ������ ������ �ʱ�ȭ

	if (head->left == NULL) { // ��Ʈ ��尡 ����������
		head->left = newNode; // ���� �ڽĳ�忡 �߰��� ��带 �߰��Ѵ�
		return 1;
	}


	Node* ptr = head->left;	// ��带 �߰��� ��ġ�� ã�� ��带 �߰��� Ʈ���� ��� ���� �ڽĳ�忡 ����

	Node* parentNode = NULL;	//�θ��带 ����ų ��� �ʱ�ȭ
	while (ptr != NULL) {	

		
		if (ptr->key == key) return 1;	//�߰��� ���� ���� ���� ������ �߰����� �ʰ� ����

		
		parentNode = ptr;	// ptr�� �ִ� ��ġ�� �θ���� ����

	
		if (ptr->key < key)	//�θ����� Ű������ �Է��� Ű���� �� ū���
			ptr = ptr->right;	//������ �ڽ� ���� �̵��Ѵ�
		else  //�θ����� Ű������ �Է��� Ű ���� �� �������
			ptr = ptr->left;	//���� �ڽĳ��� �̵��Ѵ�
	}

	
	if (parentNode->key > key) //���������� �̵��� ����� Ű���� �Է��� Ű������ ũ�ٸ�
		parentNode->left = newNode; //���� �ڽĳ�忡 ������ ��带 �߰�
	else//���������� �̵��� ����� Ű���� �Է��� Ű������ �۴ٸ�
		parentNode->right = newNode; //������ �ڽĳ�忡 ������ ��� �߰�
	return 1;
}

int deleteLeafNode(Node* head, int key) //Ʈ���� ��带 �����ϴ� �Լ�
{
	if (head == NULL) { //Ʈ���� �ƹ��͵� ���ٸ� ������ ��尡 �����Ƿ�
		printf("\n Nothing to delete!!\n");	//�����޼��� ���
		return -1;
	}

	if (head->left == NULL) { // ��Ʈ��忡 �ƹ��͵� ���ٸ�
		printf("\n Nothing to delete!!\n");	//�����޼��� ���
		return -1;
	}

	
	Node* ptr = head->left;	//������ ����� ã�� ��� ������ ��Ʈ��忡 ����


	
	Node* parentNode = head; // �θ��带 ����ų ��带 ������ ���� ��� ����

	while (ptr != NULL) {

		if (ptr->key == key) { //ã�� Ű���� ptr�� ��ġ�� �ִ� ����� Ű���� ���
			if (ptr->left == NULL && ptr->right == NULL) { //�� ��尡 �ڽĳ�尡 �������

				/* root node case */
				if (parentNode == head) //�� ��尡 ��Ʈ����ϰ��
					head->left = NULL; //��Ʈ ��� ����

				/* left node case or right case*/
				if (parentNode->left == ptr) // �� ��尡 ���� ����� ���� �ڽĳ���ϰ��
					parentNode->left = NULL; //�θ����� ���� �ڽĳ�带 �����Ѵ�
				else //�� ��尡 ���� ����� ������ �ڽĳ���ϰ��
					parentNode->right = NULL;// �θ����� ������ �ڽĳ�带 �����Ѵ�

				free(ptr); //������ ptr�� �����Ҵ� �����Ѵ�
			}
			else {
				printf("the node [%d] is not a leaf \n", ptr->key); //���� �ȿ� ���ٸ� �����޼��� ���
			}
			return 1;
		}

		/* keep the parent node */
		parentNode = ptr; //�θ��带 �����״� ������ �ڽĳ��� �̵�

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if (ptr->key < key) //ptr�� ����Ű�� ����� Ű���� ������ Ű������ �������
			ptr = ptr->right; //������ �ڽĳ��� ptr �̵�
		else //ptr�� ����Ű�� ����� Ű���� ������ Ű������ Ŭ���
			ptr = ptr->left; //���� �ڽĳ��� ptr �̵�


	}

	printf("Cannot find the node for key [%d]\n ", key); //�ݺ������� ã�� ��������� �����޼��� ���

	return 1;
}

Node* searchRecursive(Node* ptr, int key) //��Ͱ˻��Լ�
{
	
	if (ptr->key < key) //������ġ�� ����� Ű���� ã�� Ű������ �������
		ptr = searchRecursive(ptr->right, key); //�������ڽĳ��� �̵��Ͽ� �˻��Ѵ�
	else if (ptr->key > key)	//������ġ�� ����� Ű���� ã�� Ű������ Ŭ���
		ptr = searchRecursive(ptr->left, key); //���� �ڽĳ��� �̵��Ͽ� �˻��Ѵ�

	
	return ptr; //ã�� ���� ã������� �ش� ��� ����

}
Node* searchIterative(Node* head, int key) //�ݺ� �˻��Լ�
{
	/* root node */
	Node* ptr = head->left; //ptr�� ��Ʈ��� ��ġ�� ����

	while (ptr != NULL) 
	{
		if (ptr->key == key) //ptr�� Ű���� ã�� Ű���̶��
			return ptr; // ptr�� ��ġ�ϰ��ִ� ��� ����

		if (ptr->key < key) ptr = ptr->right; //ã�� Ű���� ptr�� Ű������ ũ�ٸ� ptr�� ������ �ڽĳ��� �̵�
		else //ã�� Ű���� ptr�� Ű������ �۴ٸ� ptr�� ���� �ڽĳ��� �̵�
			ptr = ptr->left;
	}

	return NULL; //ã�� ���ߴٸ� NULL ����
}



int freeBST(Node* head) //Ʈ���� �����Ҵ� �����ϴ� �Լ�
{

	if (head->left == head) //Ʈ���� ��尡 �������
	{
		free(head); //��常 �����Ҵ� ����
		return 1;
	}

	Node* p = head->left; //p�� �����Ͽ� ��Ʈ��带 ����Ű�� �Ѵ�

	freeNode(p); //��Ʈ ��� �����Ҵ� ����

	free(head); //��� �����Ҵ� ����
	return 1;
}




