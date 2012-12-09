#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
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
	int sum;
	//���� ���������� ����� �� ������������
	char* file_name;
	file_name = (char *) calloc(256, sizeof(char));//������� ������ ��� ���
	cin>>file_name;
	FILE *stream = fopen(file_name, "r+");
	free(file_name);//������� ������ ������ ��� ���
	
	//�������� ���� �����
	fread(&picture, sizeof(BMP), 1, stream);

	long line = (picture.biWidth * 3) + (picture.biWidth % 4);//����� ������ � ������ ������������

	char * buffer = (char *) calloc((picture.biHeight * line), sizeof(char));//������� ������ ��� ������
	//���� ���������� ���������� �������
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

	//������� ������ ������ ��� ������
//	cout<<"Type: "<<picture.B<<picture.M<<endl<<"Width: "<<picture.biWidth<<endl<<"Height: "<<picture.biHeight<<endl<<bbyte<<sizeof(buffer)<<b;//����� ��� ��������
	free(buffer);

}


