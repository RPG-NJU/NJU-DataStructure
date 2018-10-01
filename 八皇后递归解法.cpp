#include <iostream>
#include <cmath>

using namespace std;

#define N 8//作为N皇后问题的通解的话会比较有意义

bool JudgeQueen(int row, int*& board);
void Queen(int row, int col, int*& board);

int main()
{
	int first_row(0);
	while (cin >> first_row)
	{
		//输入成功第一行皇后的位置
		int board[N] = { 0 };
		int *p = board;
		board[0] = first_row;//将第一行的位置设置为输入值
		Queen(1, 1, p);
	}
	return 0;
}

bool JudgeQueen(int row, int*& board)
{
	for (int i = row - 1; i >= 0; --i)
	{
		if (board[i] == board[row] || abs(board[i] - board[row]) == abs(i - row))
			return false;
	}
	//cout << "true" << endl;
	return true;
}

void Queen(int row, int col, int*& board)
{
	//cout << "调用" << endl;
	if (row == N)//此时已经触底
	{
		for (int i = 0; i < N; ++i)
			cout << board[i];
		cout << endl;
		return;
	}
	else
	{
		board[row] = col;
		if (JudgeQueen(row, board))
			Queen(row + 1, 1, board);
		if (col < 8)
			Queen(row, col + 1, board);
	}
	return;
}

