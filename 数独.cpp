/*ԭ��:��Ϊ2016���з�����ʦ���⡢Leetcode37�������
�ο����� https://blog.csdn.net/huang826336127/article/details/68958379
���������򵥵�������
������һ��9*9�ı�� ��������ְ�ÿ����ÿ���зֳɾŸ�3*3���ӱ�� ��ƹ�
������������ ��Χ1��9 ����81�� 
���ڱ������Щ���������� ��Щ��Ϊ�հף���Ϊ0�� ����Щ�հ׵ĸ�����
ʹ�ñ��������������:
1.ÿһ�в�������ͬ����
2.ÿһ�в�������ͬ����
3.ÿһ����������ͬ����

Ϊ������������㷨��������Ҫ���¼�������:
1.����һ������
2.�������������������
3.�������������Ƿ�������������������㣬���������
��������㣬��ǰ���ݣ���������������ǰ����
4.���ѭ������ ֱ����������������Ϊֹ

Ϊ��������Ҫ���¼�������:
1.������������
2.����������Ϊÿ���ո�����������Ƿ������������
3.����������������ÿ���ո���������������ü����������Ƿ����㣻
��������������У����������������һ����������
4.��������������Ʋ���������д��Ϻ������

����������
flag��һ����ά���飬���������ڳ�ʼ״̬�пհ׵�����
rule��һ����ά���飬���������������ڴ洢ÿ�С�ÿ�м�ÿ��������ռ���������ֵΪ0��ʾδռ�ã�1��ʾ��ռ��
sudoku��һ����ά���飬���ڴ洢���������ֲַ�״̬*/
#include <iostream>
#include <string>
using namespace std;

int rule[3][9][9], sudoku[9][9], flag[9][9];

int findSmallIndex(int rowIndex, int colIndex) 
{
	return (3 * (rowIndex / 3) + (colIndex / 3));
}

int findNextValue(int rowIndex, int colIndex, int start) 
{
	int index = findSmallIndex(rowIndex, colIndex);
	for (int i = start; i < 9; i++) 
	{
		if (rule[0][rowIndex][i]) continue;
		if (rule[1][colIndex][i]) continue;
		if (rule[2][index][i]) continue;
		return i;
	}
	return -1;
}

void changeRule(int rowIndex, int colIndex, int style) 
{
	int index = findSmallIndex(rowIndex, colIndex);
	int value = sudoku[rowIndex][colIndex];
	rule[0][rowIndex][value] = style;
	rule[1][colIndex][value] = style;
	rule[2][index][value] = style;
}

void initSudoku() 
{
	for (int i = 0; i < 9; i++) 
	{
		for (int j = 0; j < 9; j++) 
		{
			sudoku[i][j] = getchar() - '0' - 1;
			flag[i][j] = ~sudoku[i][j] ? 0 : 1;
			if (!flag[i][j]) changeRule(i, j, 1);
		}
		getchar();
	}
}

void show() 
{
	for (int i = 0; i < 9; i++) 
	{
		string line = "";
		for (int j = 0; j < 9; j++) 
		{
			line += '0' + sudoku[i][j] + 1;
		}
		cout << line << endl;
	}
}

void solve(int rowIndex, int colIndex) 
{
	if (colIndex == 9) { rowIndex++; colIndex = 0; }
	while (rowIndex <= 8 && !flag[rowIndex][colIndex]) 
	{
		colIndex++; if (colIndex == 9) { rowIndex++; colIndex = 0; }
	}
	if (rowIndex > 8) { show(); return; }
	while (~(sudoku[rowIndex][colIndex] = findNextValue(rowIndex, colIndex, sudoku[rowIndex][colIndex] + 1))) 
	{
		changeRule(rowIndex, colIndex, 1);
		solve(rowIndex, colIndex + 1);
		changeRule(rowIndex, colIndex, 0);
	}
}

int main() 
{
	initSudoku();
	solve(0, 0);//��(0,0)λ�ÿ�ʼ����
	return 0;
}