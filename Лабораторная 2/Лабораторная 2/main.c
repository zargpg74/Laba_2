#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<Windows.h>
#include<malloc.h>

#include"Error.h"


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

	//������ � ������ �� �����
	char* str = NULL;//������ ������� ����� ����� ���������� � ������
	char** mass_str = NULL;//������ �����
	char symbol;//��������� ����� �� ��������
	int len = 0, n = 0;//len - ������� ��� ������, n - ���������� �����
	int* mass_len = NULL;//������ ����� �����
	symbol = fgetc(book);
	while (symbol != '/')
	{
		if (symbol != '\n')
		{
			str = (char*)realloc(str, (len + 1) * sizeof(char));
			str[len] = symbol;
			len++;
		}
		else
		{
			if (str[0] == ' ')
			{
				for (int i = 0; i <= len; i++)
				{
					str[len] = str[len + 1];
				}
				len--;
			}

			mass_len = (int*)realloc(mass_len, (n + 1) * sizeof(int));
			mass_len[n] = len;

			mass_str = (char**)realloc(mass_str, (n + 1) * sizeof(char*));
			mass_str[n] = (char*)malloc(mass_str, len * sizeof(char));
			for (int i = 0; i <= len; i++)
			{
				mass_str[n][i] = str[i];
			}

			n++;
			len = 0;
			str = NULL;
		}

		symbol = fgetc(book);

		if (symbol == '/')
		{
			if (str[0] == ' ')
			{
				for (int i = 0; i <= len; i++)
				{
					str[len] = str[len + 1];
				}
				len--;
			}

			mass_len = (int*)realloc(mass_len, (n + 1) * sizeof(int));
			mass_len[n] = len;

			mass_str = (char**)realloc(mass_str, (n + 1) * sizeof(char*));
			mass_str[n] = (char*)malloc(mass_str, len * sizeof(char));
			for (int i = 0; i <= len; i++)
			{
				mass_str[n][i] = str[i];
			}

			n++;
		}
	}

	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j < mass_len[i]; j++)
		{
			printf("%c", mass_str[i][j]);
		}
		printf("\n");
	}
}