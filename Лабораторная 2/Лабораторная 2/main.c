#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<Windows.h>
#include<malloc.h>

#include"Error.h"
#include"Sorting.h"


void main()
{
	system("cls");
	setlocale(0, "ru");

	//�������� � ��������� ������ �������� �����
	FILE* book;
	errno_t err;
	err = fopen_s(&book, "book.txt", "r");
	ErrorOpen(err);
	ErrorFile(book);
	rewind(book);

	Sort(book);//������� ��� ������ ���������� ����� �� �����

	err = fclose(book);//��������� ����
	ErrorOpen(err);
}