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
	unsigned long int biSizeImage;//размер изображени€ в байтах
	unsigned long int biXPelsPerMeter;//√оризонтальное разрешение в пиксел€х на метр дл€ целевого устройства.
	unsigned long int biYPelsPerMeter;//¬ертикальное разрешение в пиксел€х на метр дл€ целевого устройства.
	unsigned long int biClrUsed;// оличество используемых цветовых индексов в палитре.
	unsigned long int biClrImportant;};// оличество элементов палитры, необходимых дл€ отображени€ изображени€.
#pragma pack(pop)

int main () {
	BMP picture;

	//блок считывани€ файла от пользовател€
	char* file_name;
	file_name = (char *) calloc(256, sizeof(char));//выделим пам€ть под им€
	cin>>file_name;
	FILE *stream = fopen(file_name, "r+");
	free(file_name);//очистим пам€ть вз€тую под им€

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

	long line = (picture.biWidth * 3) + (picture.biWidth % 4);//длина строки с учетов выравнивани€

	char * buffer = (char *) calloc((picture.biHeight * line), sizeof(char));//выделим пам€ть под буффер
	
	//блок считывани€ растрового массива
	fseek (stream, picture.bfOffBits, 0);
	fread (buffer, sizeof(char), (line * picture.biHeight), stream);
	fclose (stream);
	
	//блок создани€ рисунка
	FILE *outfile = fopen("D:\outfile.bmp", "w+");
	fwrite(&picture, sizeof(BMP), 1, outfile);
	fseek (outfile, picture.bfOffBits, 0);
	fwrite(buffer, sizeof(char) , (line * picture.biHeight), outfile);
	fclose (outfile);

	free(buffer);//очистим пам€ть вз€тую под буффер

	cout<<"Type: "<<picture.B<<picture.M<<endl<<"Width: "<<picture.biWidth<<endl<<"Height: "<<picture.biHeight<<endl<<line;//вывод дл€ проверки
}


