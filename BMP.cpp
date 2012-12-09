#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
using namespace std;

#pragma pack(push, 2)//зададим выравнивание по наименьшему из типов

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
	BMP picture;

	//блок считывания файла от пользователя
	char* file_name;
	file_name = (char *) calloc(256, sizeof(char));//выделим память под имя
	cin>>file_name;
	FILE *stream = fopen(file_name, "r+");
	free(file_name);//очистим память взятую под имя

	if (stream == NULL) {
		cout<<"File not found\n";
		exit(1);
	}
	
	//проверка типа файла
	fread(&picture, sizeof(BMP), 1, stream);
	if ((picture.B != 'B') || (picture.M != 'M')){
		cout<<"File isn't BitMap\n";
		exit(-1);}
	if (picture.biBitCount != 24){
		cout<<"File isn't 24bit for pixel";
		exit(-1);}

	long line = (picture.biWidth * 3) + (picture.biWidth % 4);//длина строки с учетов выравнивания

	char * buffer = (char *) calloc((picture.biHeight * line), sizeof(char));//выделим память под буффер
	
	//блок считывания растрового массива
	fseek (stream, picture.bfOffBits, 0);
	fread (buffer, sizeof(char), (line * picture.biHeight), stream);
	fclose (stream);
	
	//блок создания рисунка
	FILE *outfile = fopen("D:\outfile.bmp", "w+");
	fwrite(&picture, sizeof(BMP), 1, outfile);
	fseek (outfile, picture.bfOffBits, 0);
	fwrite(buffer, sizeof(char) , (line * picture.biHeight), outfile);
	fclose (outfile);

	free(buffer);//очистим память взятую под буффер

	cout<<"Type: "<<picture.B<<picture.M<<endl<<"Width: "<<picture.biWidth<<endl<<"Height: "<<picture.biHeight<<endl<<line;//вывод для проверки
}


