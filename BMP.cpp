#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
using namespace std;

#pragma pack(push, 2)//������� ������������ �� ����������� �� �����

struct BMP {//�������� ����� �������� ��������
	char B,M;//���
	unsigned long int bfSize;//������ ����� ����� � ������
	unsigned short int notUsed1;//�� ������������
	unsigned short int notUsed2;//-//-
	unsigned long int bfOffBits;//����� ���������� �������
	unsigned long int biSize;//������ ������ ��������� � ������
	unsigned long int biWidth;//������
	unsigned long int biHeight;//������
	unsigned short int biPlanes;//���������
	unsigned short int biBitCount;//�������
	unsigned long int biCompression;//������
	unsigned long int biSizeImage;//������ ����������� � ������
	unsigned long int biXPelsPerMeter;//�������������� ���������� � �������� �� ���� ��� �������� ����������.
	unsigned long int biYPelsPerMeter;//������������ ���������� � �������� �� ���� ��� �������� ����������.
	unsigned long int biClrUsed;//���������� ������������ �������� �������� � �������.
	unsigned long int biClrImportant;};//���������� ��������� �������, ����������� ��� ����������� �����������.
#pragma pack(pop)

int main () {
	BMP picture;

	//���� ���������� ����� �� ������������
	char* file_name;
	file_name = (char *) calloc(256, sizeof(char));//������� ������ ��� ���
	cin>>file_name;
	FILE *stream = fopen(file_name, "r+");
	free(file_name);//������� ������ ������ ��� ���

	if (stream == NULL) {
		cout<<"File not found\n";
		exit(1);
	}
	
	//�������� ���� �����
	fread(&picture, sizeof(BMP), 1, stream);
	if ((picture.B != 'B') || (picture.M != 'M')){
		cout<<"File isn't BitMap\n";
		exit(-1);}
	if (picture.biBitCount != 24){
		cout<<"File isn't 24bit for pixel";
		exit(-1);}

	long line = (picture.biWidth * 3) + (picture.biWidth % 4);//����� ������ � ������ ������������

	char * buffer = (char *) calloc((picture.biHeight * line), sizeof(char));//������� ������ ��� ������
	
	//���� ���������� ���������� �������
	fseek (stream, picture.bfOffBits, 0);
	fread (buffer, sizeof(char), (line * picture.biHeight), stream);
	fclose (stream);
	
	//���� �������� �������
	FILE *outfile = fopen("D:\outfile.bmp", "w+");
	fwrite(&picture, sizeof(BMP), 1, outfile);
	fseek (outfile, picture.bfOffBits, 0);
	fwrite(buffer, sizeof(char) , (line * picture.biHeight), outfile);
	fclose (outfile);

	free(buffer);//������� ������ ������ ��� ������

	cout<<"Type: "<<picture.B<<picture.M<<endl<<"Width: "<<picture.biWidth<<endl<<"Height: "<<picture.biHeight<<endl<<line;//����� ��� ��������
}


