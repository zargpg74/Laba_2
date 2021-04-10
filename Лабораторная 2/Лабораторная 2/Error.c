#include<stdio.h>
#include<stdlib.h>

#include "Error.h"

void ErrorOpen(errno_t err) {//ф-я обработки ошибок открытия
	if (err != 0) {
		char error_str[100];
		strerror_s(error_str, sizeof(error_str), err);
		printf("%s\n", error_str);
		exit(err);
	}
}


void ErrorFile(FILE* input) {//ф-я обработки ошибок файла
	char pr;
	pr = getc(input);
	if (pr == EOF) {
		printf("Файл пуст");
		exit(4);
	}
}