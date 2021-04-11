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

	//открытие и обработка ошибок открытия файла
	FILE* book;
	errno_t err;
	err = fopen_s(&book, "book.txt", "r");
	ErrorOpen(err);
	ErrorFile(book);
	rewind(book);

	//Запись в массив из файла
	char* str = NULL;//Строка которую потом будем записывать в массив
	char** mass_str = NULL;//массив строк
	char symbol;//считывать будем по символам
	int len = 0, n = 0;//len - счетчик для строки, n - количество строк
	int* mass_len = NULL;//Массив длинн строк
	symbol = fgetc(book);
	while (symbol != '/')
	{
		if (symbol != '\n')//пока не встретился перенос записываем символы в строку
		{
			str = (char*)realloc(str, (len + 1) * sizeof(char));
			str[len] = symbol;
			len++;
		}
		else
		{
			mass_len = (int*)realloc(mass_len, (n + 1) * sizeof(int));//записываем длинну строки
			mass_len[n] = len;

			mass_str = (char**)realloc(mass_str, (n + 1) * sizeof(char*));//выделяем память под строку в массиве
			mass_str[n] = (char*)malloc(mass_str, len * sizeof(char));
			for (int i = 0; i <= len; i++)//записываем строку в массив
			{
				mass_str[n][i] = str[i];
			}

			n++;
			len = 0;
			str = NULL;
		}

		symbol = fgetc(book);//читаем следующий символ из файла

		if (symbol == '/')//если конец файла то записываем последнюю строку
		{

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


	//начинаем сортировку
	int max = 0;//гаходим максимальную длину
	for (int i = 0; i <= n; i++)
	{
		if (mass_len[i] > max)
			max = mass_len[i];
	}

	char** mass_str2 = (char**)malloc(n * sizeof(char*));//создаем новый массив с одинаковой длинной строк для удобства записи
	for (int i = 0; i <= n; i++)
	{
		mass_str2[i] = (char*)malloc(max * sizeof(char));
	}

	for (int i = 0; i <= n; i++)//записываем в новый массив значения исходного
	{
		for (int j = 0; j < mass_len[i]; j++)
		{
			mass_str2[i][j] = mass_str[i][j];
		}
	}

	//сортировка
	str = (char*)malloc(max * sizeof(char));
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			if (mass_len[i] > mass_len[j])
			{
				//x=a[i]
				for (int k = 0; k < max; k++)
				{
					str[k] = mass_str2[i][k];
				}

				//a[i]=a[j]
				for (int k = 0; k < max; k++)
				{
					mass_str2[i][k] = mass_str2[j][k];
				}

				//a[j]=x
				for (int k = 0; k < max; k++)
				{
					mass_str2[j][k] = str[k];
				}

				//так же меняем местами длины строк
				int x = mass_len[i];
				mass_len[i] = mass_len[j];
				mass_len[j] = x;
			}
		}
	}

	//выводим массив
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j < mass_len[i]; j++)
		{
			printf("%c", mass_str2[i][j]);
		}
		printf("\n");
	}

	err = fclose(book);//закрываем файл
	ErrorOpen(err);

	free(str);//очищаем все массивы
	for (int i = 0; i < n; i++)
	{
		free(mass_str[i]);
	}
	free(mass_str);
	for (int i = 0; i <= n; i++)
	{
		free(mass_str2[i]);
	}
	free(mass_str2);
	free(mass_len);

}