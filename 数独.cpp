/*原题:华为2016年研发工程师试题、Leetcode37题解数独
参考文章 https://blog.csdn.net/huang826336127/article/details/68958379
关于数独简单的描述：
数独是一个9*9的表格 整个表格又按每三行每三列分成九个3*3的子表格 简称宫
格中填有数字 范围1～9 共有81格 
现在表格中有些格填有数字 有些则为空白（记为0） 将这些空白的格填满
使得表格满足三条规则:
1.每一行不存在相同的数
2.每一列不存在相同的数
3.每一宫不存在相同的数

为了完成数独的算法，我们需要以下几个步骤:
1.生成一个数独
2.向数独表格中填入数字
3.检查填入的数字是否满足三条规则，如果满足，继续往下填；
如果不满足，往前回溯，还不满足则再往前回溯
4.如此循环迭代 直到填满整个数组表格为止

为此我们需要以下几个函数:
1.生成数独函数
2.检查规则函数，为每个空格检查填的数字是否符合三条规则
3.主体填数函数，对每个空格进行填数，并调用检查规则函数看是否满足；
若满足则继续运行，若不满足回溯至上一层填数函数
4.主函数，整体控制并在数组填写完毕后输出。

几个变量：
flag：一个二维数组，代表数独在初始状态中空白的区域
rule：一个三维数组，代表三个规则：用于存储每行、每列及每宫的数字占用情况。当值为0表示未占用，1表示已占用
sudoku：一个二维数组，用于存储数独的数字分布状态*/
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
	solve(0, 0);//从(0,0)位置开始填数
	return 0;
}