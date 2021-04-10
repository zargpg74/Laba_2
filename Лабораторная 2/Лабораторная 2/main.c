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

	//открытие и обработка ошибок открыти€ файла
	FILE* book;
	errno_t err;
	err = fopen_s(&book, "book.txt", "r");
	ErrorOpen(err);
	ErrorFile(book);
	rewind(book);

	//«апись в массив из файла
	char* str = NULL;//—трока которую потом будем записывать в массив
	char** mass_str = NULL;//массив строк
	char symbol;//считывать будем по символам
	int len = 0, n = 0;//len - счетчик дл€ строки, n - количество строк
	int* mass_len = NULL;//ћассив длинн строк
	symbol = fgetc(book);
	while (symbol != '/')
	{
		if (symbol != '\n')//пока не встретим перенос строки записываем символы в строку
		{
			str = (char*)realloc(str, (len + 1) * sizeof(char));
			str[len] = symbol;
			len++;
		}
		else//когда встретилс€ перенос записываем стрку в массив
		{
			if (str[0] == ' ')//если в начале строки пробел его надо удалить
			{
				for (int i = 0; i <= len; i++)
				{
					str[len] = str[len + 1];
				}
				len--;
			}

			mass_len = (int*)realloc(mass_len, (n + 1) * sizeof(int));//записываем длину строки в массив строк
			mass_len[n] = len;

			mass_str = (char**)realloc(mass_str, (n + 1) * sizeof(char*));//выдел€ем пам€ть под строку в массиве
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

		if (symbol == '/')//если встретилс€ конец файла последнюю строку все равно записываем
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

	for (int i = 0; i <= n; i++)//вывод строк
	{
		for (int j = 0; j < mass_len[i]; j++)
		{
			printf("%c", mass_str[i][j]);
		}
		printf("\n");
	}
}