#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdlib.h>
#include<string.h>
#define MAX 1000000
using namespace std;

typedef struct node {
	char word[100];
	int n;
}Node;

int lines = 0;//文件有效行数
int characters = 0;//文件字符数

int isLetter(char c) {
	if (c <= 'Z' && c >= 'A' || c <= 'z' && c >= 'a') {
		return 1;
	}
	return 0;
}//判断是不是字母

int isDigit(char c) {
	if (c <= '9' && c >= '0') {
		return 1;
	}
	return 0;
}//判断是不是数字

int isletterOrDigit(char c) {
	return (isLetter(c) || isDigit(c));
}//判断是数字还是字母

char tolower(char c) {
	if (c <= 'Z' && c >= 'A') {
		return (char)(c - 'A' + 'a');
	}
	return c;
}//将大写字母转化为小写字母

char* readFile() {
	FILE* fp;
	char* text = NULL;
	int length = 0;
	int i, size = 0;
	char temp[1024] = { 0 };
	char* getk = 0;
	fp = fopen("input.txt", "r");
	if (fp == NULL) {
		printf("打开文件失败！\n");
		exit(-1);
	}
	text = (char*)malloc(sizeof(char) * (MAX));
	while (!feof(fp)) {
		getk = fgets(temp, 1024, fp);
		if (feof(fp) && !getk) {
			break;
		}
		length = strlen(temp);
		characters += length;
		if (length > 1) {
			lines++;
		}
		for (i = 0; i < length; i++) {
			if (isletterOrDigit(temp[i])) {
				text[size++] = tolower(temp[i]);
			}
			else {
				text[size++] = ' ';
			}
		}
	}
	text[size] = '\0';
	fclose(fp);
	return text;
}//读取input文件

int notIn(char* words[], int count) {
	int i;
	for (i = 0; i < count; i++) {
		if (strcmp(words[i], words[count]) == 0) {
			return 0;
		}
	}
	return 1;
}//终止条件

char** split(char* text, int* size) {
	int i;
	int count = 0, L = 0;
	char** words;
	words = (char**)malloc(sizeof(char*) * (MAX / 2));
	for (i = 0; i < MAX / 2; i++) {
		words[i] = (char*)malloc(sizeof(char) * 100);
	}
	int len = strlen(text);

	for (i = 0; i < len; i++) {
		if (text[i] == ' ' || text[i] == '\0') {
			words[count][L++] = '\0';
			if (L > 1 && !isDigit(words[count][0])) {
				count++;
				(*size)++;
			}
			L = 0;
		}
		else {
			words[count][L++] = text[i];
		}
	}
	words[count][L++] = '\0';
	if (L > 1 && !isDigit(words[count][0])) {
		count++;
		(*size)++;
	}
	return words;
}//把一个字符串变为字符串数组

int remove_repeat(char** words, int osize, Node* nodes) {
	int i, j;
	char** ws;
	int wi = 0;
	int exist = 0;
	int size = 0;
	ws = (char**)malloc(sizeof(char*) * (osize));
	for (i = 0; i < osize; i++) {
		ws[i] = (char*)malloc(sizeof(char) * 100);
	}
	for (i = 0; i < osize; i++) {
		exist = 0;
		for (j = 0; j < size; j++) {
			if (strcmp(words[i], ws[j]) == 0) {
				exist = 1;
			}
		}
		if (!exist) {
			size++;
			strcpy(ws[wi], words[i]);
			strcpy(nodes[wi].word, words[i]);
			nodes[wi].n = 0;
			wi++;
		}
	}
	return size;
}//统计重复单词

void count(char* text) {
	char** words;
	Node* n_count;
	int i, j, size = 0;
	int nsize = 0;
	words = split(text, &nsize);
	Node t;
	n_count = (Node*)malloc(sizeof(Node) * nsize);
	size = remove_repeat(words, nsize, n_count);

	for (i = 0; i < nsize; i++) {
		for (j = 0; j < size; j++) {
			if (strcmp(n_count[j].word, words[i]) == 0) {
				n_count[j].n++;
			}
		}
	}
	for (i = 0; i < size; i++) {
		for (j = 0; j < size - i - 1; j++) {
			if (n_count[j].n < n_count[j + 1].n) {
				t = n_count[j];
				n_count[j] = n_count[j + 1];
				n_count[j + 1] = t;
			}
		}
	}
	cout << "characters:" << characters << endl;
	cout<<"words："<< nsize << endl;
	cout<<"lines："<< lines << endl;

	size = size > 10 ? 10 : size;

	for (i = 0; i < size; i++) {
		cout << n_count[i].word <<":"<< n_count[i].n << endl;
	}


}//统计数据并输出

int main() {
	char* text;
	text = readFile();
	count(text);
	system("pause");
	return 0;
}