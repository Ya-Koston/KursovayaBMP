#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
using namespace std;

#pragma pack(push, 2)//зададим выравнивание структуры по наименьшему из типов

struct BMP {//создадим общую стуктуру картинки
	char B,M;//тип
	unsigned long int bfSize;//размер всего файла в байтах
	unsigned short int notUsed1;//не используемые
	unsigned short int notUsed2;//-//-
	unsigned long int bfOffBits;//адрес растрового массива
	unsigned long int biSize;//размер данной структуры в байтах
	unsigned long int biWidth;//ширина
	unsigned long int biHeight;//высота
	unsigned short int biPlanes;//плоскости
	unsigned short int biBitCount;//пиксель
	unsigned long int biCompression;//сжатие
	unsigned long int biSizeImage;//размер изображения в байтах
	unsigned long int biXPelsPerMeter;//Горизонтальное разрешение в пикселях на метр для целевого устройства.
	unsigned long int biYPelsPerMeter;//Вертикальное разрешение в пикселях на метр для целевого устройства.
	unsigned long int biClrUsed;//Количество используемых цветовых индексов в палитре.
	unsigned long int biClrImportant;};//Количество элементов палитры, необходимых для отображения изображения.
#pragma pack(pop)

int main () {
	cout<<"Please, enter the path of the picture to inversion: ";
	BMP picture;

	//блок считывания файла от пользователя
	char* infile_name;
	infile_name = (char *) calloc(256, sizeof(char));//выделим память под имя
	cin>>infile_name;
	FILE *stream = fopen(infile_name, "r+");
	free(infile_name);//очистим память взятую под имя
	
	//проверка типа файла
	fread(&picture, sizeof(BMP), 1, stream);
	if (picture.B!='B' || picture.M!='M')
	{ cout<<"File isn't BitMap! Please enter picture in format .bmp\n";
	exit(-1);}
	if (picture.biBitCount!=24)
	{cout<<"File isn't 24 bit per pixel!\n";
	exit(-1);}

	long line = (picture.biWidth * 3) + (picture.biWidth % 4);//длина строки с учетов выравнивания
	char * buffer = (char *) calloc((picture.biHeight * line), sizeof(char));//выделим память под буффер
	int alltemp = line * picture.biHeight;//количество бит в картинке

	//блок считывания растрового массива
	fseek (stream, picture.bfOffBits, 0);
	fread (buffer,(sizeof(char)), alltemp, stream);
	fclose (stream);
	
	//Фильтр "Инверсия"
	for (int i=0; i<alltemp; i++)
			buffer[i] = 255-buffer[i];
	
	//блок записи отформатированного изображения в файл
	cout<<"Please, enter the path to picture with inversion in format .bmp: ";
	char* outfile_name;
	outfile_name = (char *) calloc(256, sizeof(char));//выделим память под имя
	cin>>outfile_name;
	FILE *outfile = fopen(outfile_name, "w+");
	free(outfile_name);//очистим память взятую под имя
	fwrite(&picture, sizeof(BMP), 1, outfile);
	fwrite(buffer, sizeof(char), alltemp, outfile);
	fclose (outfile);

	free(buffer);//очистим память взятую под буффер
}

