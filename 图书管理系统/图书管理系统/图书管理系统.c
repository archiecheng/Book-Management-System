#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//struct data {
//	int A;
//	float B;
//	char name[10];
//};
//3.���ݵ����
	//3.1������ʲô��������		-->���顢����������
	//3.2���ݵĽṹ	-->ͼ�����Ϣ
struct bookInfo {

	char name[20];//����
	float price;//��ļ۸�
	int num;//�������
};
struct Node {
	struct bookInfo data;
	struct Node* next;
};
struct Node* list = NULL;
//������ͷ����ͷ����һ���ṹ�����
//��һ�����֣��û���Ϣ




struct Node* createHead() {
	//��̬�ڴ�����
	struct Node* headNode = (struct Node*)malloc(sizeof(struct Node));
	//�����Ļ�������->ʹ��ǰ�����ʼ��
	headNode->next = NULL;
	return headNode;
}

//�����ڵ㣺Ϊ������׼��
//���û������ݱ�Ϊ�ṹ�����
struct Node* createNode(struct bookInfo data) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}


//���룺ֻ��Ҫһ�ֲ��뷽ʽ
void insertNodeByHead(struct Node* headNode,struct bookInfo data) {
	struct Node* newNode = createNode(data);
	newNode->next = headNode->next;
	headNode->next = newNode;
}

//void insertNodeByTail(struct Node* headNode, int data) {
//	struct Node* pMove = headNode;
//	while (pMove->next != NULL)
//	{
//		pMove = pMove->next;
//	}
//	struct Node* newNode = createNode(data);
//	pMove->next = newNode;
//}

//ָ��λ��ɾ��
void deleteNodeByName(struct Node* headNode, char* bookName) {
	struct Node* posLeftNode = headNode;
	struct Node* posNode = headNode->next;
	//����������ַ������ַ����ȽϺ���ȥ����
	while (posNode != NULL && strcmp(posNode->data.name,bookName)) {
		posLeftNode = posNode;
		posNode = posLeftNode->next;
	
	}

	if (posNode == NULL) {
		return;
	}
	else {
		printf("ɾ���ɹ�\n");
		posLeftNode->next = posNode->next;
		free(posNode);
		posNode = NULL;
	}
}

struct Node* searchByName(struct Node*headNode,char* bookName) {
	struct Node* posNode = headNode->next;
	while (posNode != NULL && strcmp(posNode->data.name, bookName)) {
		posNode = posNode->next;
	}

	return posNode;
}



void printList(struct Node* headNode) {

	struct Node* pMove = headNode->next;
	printf("����\t�۸�\t����\n");
	while (pMove!=NULL)
	{
		//�����
		printf("%s\t%.1f\t%d\n", pMove->data.name,pMove->data.price,pMove->data.num);
		pMove = pMove->next;
	}
}




//1.д����--->�˵�--->ģ��
void makeMenu() {
	printf("--------------------------\n");
	printf("\tͼ�����ϵͳ\n");
	printf("\t0.�˳�ϵͳ\n");
	printf("\t1.�Ǽ��鼮\n");
	printf("\t2.����鼮\n");
	printf("\t3.�����鼮\n");
	printf("\t4.�黹�鼮\n");
	printf("\t5.�鼮����\n");
	printf("\t6.ɾ���鼮\n");
	printf("\t7.�����鼮\n");
	printf("--------------------------\n");
	printf("������(0-7):");
}

//3.�ļ�����
//�����
void saveInfoToFile(const char* fileName, struct Node* headNode) {
	//���ļ�
	FILE* fp = fopen(fileName, "w");

	struct Node* pMove = headNode->next;
	while (pMove != NULL) {

		fprintf(fp, "%s\t%.1f\t%d\n",pMove->data.name, pMove->data.price,pMove->data.num);
		pMove = pMove->next;
	}

	//�ر��ļ�
	fclose(fp);


	
}
//�ļ�������

void readInfoFromFile(const char* fileName, struct Node* headNode) {
	FILE* fp = fopen(fileName, "r");//��һ�δ��ļ��϶�������

	if (fp == NULL) {
		//�����ڣ�������������ļ�
		fp = fopen(fileName, "w+");
	}

	struct bookInfo tempData;
	while (fscanf(fp, "%s\t%.1f\t%d\n", tempData.name, &tempData.price, &tempData.num)!=EOF) {
		insertNodeByHead(list,tempData);
	};

	fclose(fp);
}

//�㷨��һ��˼��
void bubbleSortList(struct Node* headNode) {
	for (struct Node* p = headNode->next; p != NULL; p = p->next) {
		for (struct Node* q = headNode->next; q->next != NULL; q = q->next) {
			if (q->data.price > q->next->data.price) {

				struct bookInfo tempData = q->data;
				q->data = q->next->data;
				q->next->data = tempData;


			}
		}
	}

	printList(list);
}




//2.������
void keyDown() {
	int userKey;
	struct bookInfo tempBook;//����һ����ʱ�ı����洢�鼮��Ϣ
	struct Node* result = NULL;
	scanf_s("%d", &userKey);
	switch (userKey)
	{
	case 0:
		printf("���˳���\n");
		printf("�˳��ɹ�\n");
		system("pause");
		exit(0);			//�رյ���������
		break;
	case 1:
		printf("���Ǽǡ�\n");
		printf("�����鼮����Ϣ(name,price,num):");
		scanf("%s%f%d", tempBook.name, &tempBook.price, &tempBook.num);
		insertNodeByHead(list, tempBook);
		saveInfoToFile("bookinfo.txt", list);
		break;
	case 2:
		printf("�������\n");
		printList(list);
		break;
	case 3:
		printf("�����ġ�\n");	//�鼮���ڿ��Խ��ģ��鼮��������-1�������������ʧ��
		printf("��������ĵ�����:");
		scanf_s("%s", tempBook.name);
		result = searchByName(list, tempBook.name);
		if (result == NULL) {
			printf("û������鼮���޷�����!\n");
		}
		else {
			if (result->data.num >= 1) {
				result->data.num--;
				printf("���ĳɹ���\n");
			}
			else {
				printf("��ǰ�鼮�޿�棬����ʧ�ܣ�\n");
			}
			
		}
		break;
	case 4:
		printf("���黹��\n");	//��ǰ�鼮������+1
		printf("������黹������:");
		scanf_s("%s", tempBook.name);
		result = searchByName(list, tempBook.name);
		if (result == NULL) {
			printf("������Դ�Ƿ�!\n");
		}
		else {
			result->data.num++;
			printf("�鼮�黹�ɹ���");

		}
		break;
	case 5:
		printf("������\n");
		bubbleSortList(list);
		break;
	case 6:
		printf("��ɾ����\n");
		printf("������ɾ���鼮������:");
		scanf_s("%s", tempBook.name);
		deleteNodeByName(list, tempBook.name);
		saveInfoToFile("bookinfo.txt", list);
		break;
	case 7:
		printf("�����ҡ�\n");
		printf("������Ҫ���ҵ�����:");
		scanf_s("%s", tempBook.name);
		result = searchByName(list, tempBook.name);
		if (result == NULL) {
			printf("δ�ҵ������Ϣ��\n");
		}
		else {
			printf("����\t�۸�\t����\n");
			printf("%s\t%.1f\t%d\n", result->data.name, result->data.price, result->data.num);

		}
		break;
	default:
		printf("��error��\n");
		break;

	}
}
int main() {


	/*printf("hello world");*/
	//ָ����α�ɱ���
	//int* p = NULL;
	//int a = 1;
	////1.1ʹ�ñ����ĵ�ַ
	//p = &a;
	//*p = 1001;
	//printf("%d\n", *p);

	////1.2��̬�ڴ�����
	//p = (int*)malloc(sizeof(int));
	//*p = 10033;
	//printf("%d\n", *p);


	//struct data C;//����.��Ա
	//C.A = 1001;
	//struct data* pD = &C;//ָ��ָ��->
	//pD->A = 1002;
	list = createHead();
	readInfoFromFile("bookinfo.txt",list);

	while (1)
	{
		makeMenu();
		keyDown();
		system("pause");
		system("cls");
	}

	return 0;
}