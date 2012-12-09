#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
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
	int sum;
	//блок считывани€ файла от пользовател€
	char* file_name;
	file_name = (char *) calloc(256, sizeof(char));//выделим пам€ть под им€
	cin>>file_name;
	FILE *stream = fopen(file_name, "r+");
	free(file_name);//очистим пам€ть вз€тую под им€
	
	//проверка типа файла
	fread(&picture, sizeof(BMP), 1, stream);

	long line = (picture.biWidth * 3) + (picture.biWidth % 4);//длина строки с учетов выравнивани€

	char * buffer = (char *) calloc((picture.biHeight * line), sizeof(char));//выделим пам€ть под буффер
	//блок считывани€ растрового массива
	fseek (stream, picture.bfOffBits, 0);
	fread (buffer,(sizeof(char)), (line * picture.biHeight), stream);
	fclose (stream);
	int bitemp = picture.biWidth * 3;
	int temp = picture.biHeight * picture.biWidth;
	int alltemp = line * picture.biHeight;
	char * b = (char *) calloc(temp, sizeof(char));
	char * g = (char *) calloc(temp, sizeof(char));
	char * r = (char *) calloc(temp, sizeof(char));
	for (int i=0; i<alltemp; i++){
		if ((i <= bitemp) || ((i % line) <= bitemp)){
		/*	char blue = buffer[i];
			i++;
			char green = buffer[i];
			i++;
			char red = buffer[i];
			char sum = (green+blue+red)/3;
			buffer[i] = sum; i--;
			buffer[i] = sum; i--;
			buffer[i] = sum; i++;i++;*/
		if (i%3==0)
		b[i/3] = buffer[i];
		if (i%3==1)
		g[i/3] = buffer[i];
		if (i%3==2)
		r[i/3] = buffer[i];
		}
	}
	for (int i=0; i<temp; i++){
	char bw=(b[i]+g[i]+r[i])/3;
	b[i]=bw;
	g[i]=bw;
	r[i]=bw;}
	for (int i=0; i<alltemp; i++){
		if ((i <= bitemp)||((i % line) <= bitemp)){
		if (i%3==0)
		buffer[i] = b[i/3];
		if (i%3==1)
		buffer[i] = g[i/3];
		if (i%3==2)
		buffer[i] = r[i/3];
		}
	}	free(b);
	free(r);
	free(g);
	FILE *outfile = fopen("D:\outfile.bmp", "w+");
	fwrite(&picture, sizeof(BMP), 1, outfile);
	fseek (outfile, picture.bfOffBits, 0);
	fwrite(buffer, sizeof(char) , (line * picture.biHeight), outfile);
	fclose (outfile);

	//очистим пам€ть вз€тую под буффер
//	cout<<"Type: "<<picture.B<<picture.M<<endl<<"Width: "<<picture.biWidth<<endl<<"Height: "<<picture.biHeight<<endl<<bbyte<<sizeof(buffer)<<b;//вывод дл€ проверки
	free(buffer);

}


