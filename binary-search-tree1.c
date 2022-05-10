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
void freeNode(Node* ptr);
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



void inorderTraversal(Node* ptr)	//중위 순회를 하는 함수
{
	if (ptr){	// 노드가 존재할 경우 실행
		inorderTraversal(ptr->left); //왼쪽 자식노드 먼저 출력
		printf(" [%d] ", ptr->key);	//부모노드 출력
		inorderTraversal(ptr->right);//오른쪽 자식노드 출력
	}
}

void preorderTraversal(Node* ptr)	//전위 순회를 하는 함수
{
	if (ptr){
		printf(" [%d] ", ptr->key);	//부모노드를 먼저 출력
		preorderTraversal(ptr->left); //왼쪽 자식노드 출력
		preorderTraversal(ptr->right); //오른쪽 자식노드 출력
	}
}

void postorderTraversal(Node* ptr)	//후위 순회를 하는 함수
{
	if (ptr){
		postorderTraversal(ptr->left);	//왼쪽 자식노드를 먼저 출력
		postorderTraversal(ptr->right);	//오른쪽 자식노드 출력
		printf(" [%d] ", ptr->key);  //부모 노드 출력
	}
}


int insert(Node* head, int key)	//노드를 추가하는 함수
{
	Node* newNode = (Node*)malloc(sizeof(Node));	//추가할 노드를 담을 구조체 선언
	newNode->key = key;	//노드의 키값 입력
	newNode->left = NULL; // 자식 노드를 연결할 포인터 초기화
	newNode->right = NULL; // 자식 노드를 연결할 포인터 초기화

	if (head->left == NULL) { // 루트 노드가 비어있을경우
		head->left = newNode; // 왼쪽 자식노드에 추가할 노드를 추가한다
		return 1;
	}


	Node* ptr = head->left;	// 노드를 추가할 위치를 찾을 노드를 추가해 트리의 헤더 왼쪽 자식노드에 연결

	Node* parentNode = NULL;	//부모노드를 가리킬 노드 초기화
	while (ptr != NULL) {	

		
		if (ptr->key == key) return 1;	//추가할 노드와 같은 값이 있으면 추가하지 않고 리턴

		
		parentNode = ptr;	// ptr이 있는 위치를 부모노드로 설정

	
		if (ptr->key < key)	//부모노드의 키값보다 입력한 키값이 더 큰경우
			ptr = ptr->right;	//오른쪽 자식 노드로 이동한다
		else  //부모노드의 키값보다 입력한 키 값이 더 작은경우
			ptr = ptr->left;	//왼쪽 자식노드로 이동한다
	}

	
	if (parentNode->key > key) //마지막으로 이동한 노드의 키값이 입력할 키값보다 크다면
		parentNode->left = newNode; //왼쪽 자식노드에 삽입할 노드를 추가
	else//마지막으로 이동한 노드의 키값이 입력할 키값보다 작다면
		parentNode->right = newNode; //오른쪽 자식노드에 삽입할 노드 추가
	return 1;
}

int deleteLeafNode(Node* head, int key) //트리의 노드를 삭제하는 함수
{
	if (head == NULL) { //트리에 아무것도 없다면 삭제할 노드가 없으므로
		printf("\n Nothing to delete!!\n");	//에러메세지 출력
		return -1;
	}

	if (head->left == NULL) { // 루트노드에 아무것도 없다면
		printf("\n Nothing to delete!!\n");	//에러메세지 출력
		return -1;
	}

	
	Node* ptr = head->left;	//삭제할 대상을 찾을 노드 선언해 루트노드에 연결


	
	Node* parentNode = head; // 부모노드를 가리킬 노드를 선언해 상위 노드 추적

	while (ptr != NULL) {

		if (ptr->key == key) { //찾는 키값이 ptr의 위치에 있는 노드의 키값일 경우
			if (ptr->left == NULL && ptr->right == NULL) { //그 노드가 자식노드가 없을경우

				/* root node case */
				if (parentNode == head) //그 노드가 루트노드일경우
					head->left = NULL; //루트 노드 삭제

				/* left node case or right case*/
				if (parentNode->left == ptr) // 그 노드가 상위 노드의 왼쪽 자식노드일경우
					parentNode->left = NULL; //부모노드의 왼쪽 자식노드를 삭제한다
				else //그 노드가 상위 노드의 오른쪽 자식노드일경우
					parentNode->right = NULL;// 부모노드의 오른쪽 자식노드를 삭제한다

				free(ptr); //삭제된 ptr을 동적할당 해제한다
			}
			else {
				printf("the node [%d] is not a leaf \n", ptr->key); //범위 안에 없다면 에러메세지 출력
			}
			return 1;
		}

		/* keep the parent node */
		parentNode = ptr; //부모노드를 가리켰던 포인터 자식노드로 이동

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if (ptr->key < key) //ptr이 가리키는 노드의 키값이 삭제할 키값보다 작을경우
			ptr = ptr->right; //오른쪽 자식노드로 ptr 이동
		else //ptr이 가리키는 노드의 키값이 삭제할 키값보다 클경우
			ptr = ptr->left; //왼쪽 자식노드로 ptr 이동


	}

	printf("Cannot find the node for key [%d]\n ", key); //반복문에서 찾지 못했을경우 에러메세지 출력

	return 1;
}

Node* searchRecursive(Node* ptr, int key) //재귀검색함수
{
		if (ptr == NULL) //만약 트리가 비어있다면
		return NULL;	//NULL을 리턴한다
	
	if (ptr->key < key) //현재위치의 노드의 키값이 찾는 키값보다 작은경우
		ptr = searchRecursive(ptr->right, key); //오른쪽자식노드로 이동하여 검색한다
	else if (ptr->key > key)	//현재위치의 노드의 키값이 찾는 키값보다 클경우
		ptr = searchRecursive(ptr->left, key); //왼쪽 자식노드로 이동하여 검색한다

	
	return ptr; //찾는 값을 찾았을경우 해당 노드 리턴

}
Node* searchIterative(Node* head, int key) //반복 검색함수
{
	/* root node */
	Node* ptr = head->left; //ptr을 루트노드 위치에 선언

	while (ptr != NULL) 
	{
		if (ptr->key == key) //ptr의 키값이 찾는 키값이라면
			return ptr; // ptr이 위치하고있는 노드 리턴

		if (ptr->key < key) ptr = ptr->right; //찾는 키값이 ptr의 키값보다 크다면 ptr을 오른쪽 자식노드로 이동
		else //찾는 키값이 ptr의 키값보다 작다면 ptr을 왼쪽 자식노드로 이동
			ptr = ptr->left;
	}

	return NULL; //찾지 못했다면 NULL 리턴
}

void freeNode(Node* ptr)
{
	if (ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head) //트리를 동적할당 해제하는 함수
{

	if (head->left == head) //트리에 노드가 없을경우
	{
		free(head); //헤드만 동적할당 해제
		return 1;
	}

	Node* p = head->left; //p를 선언하여 루트노드를 가리키게 한다

	freeNode(p); //루트 노드 동적할당 해제

	free(head); //헤드 동적할당 해제
	return 1;
}




