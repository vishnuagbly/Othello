#include"graphics.h"
#include<time.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
char board[8][8];
char player = 'w', comp = 'b';
int main_number = 6;
bool dual_player = false, flip_record[23][8][8];
int deep[23][8][8], deep1[23][2], best_move[2];
inline void console_print()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			cout << board[i][j] << " ";
		cout << endl;
	}
	cout << "\n\n";
}
inline void deep_print(int gahrai)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			cout << deep[gahrai][i][j] << " ";
		cout << endl;
	}
	cout << "\n\n";
}
int winner_check(bool player_check = true)
{
	int sum = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] == player && player_check == true)sum += 1;
			else if (board[i][j] == comp && player_check == false)sum += 1;
		}
	}
	return sum;
}
void print(int i = -1, int j = -1, char to_change = player)
{
	bool early_return = false;
	if (i != -1 && j != -1)
	{
		early_return = true;
		goto direct_spot;
	}
	for ( i = 0; i < 8; i++)
	{
		for ( j = 0; j < 8; j++)
		{
		direct_spot:
			if (board[i][j] == 'w')
			{
				circle(48 + j * 76, 88 + i* 76, 32);
				setfillstyle(SOLID_FILL, WHITE);
				floodfill(48 + j * 76, 88 + i * 76, 0);
			}
			if (board[i][j] == 'b')
			{
				circle(48 + j * 76, 88 + i* 76, 32);
				setfillstyle(SOLID_FILL, BLACK);
				floodfill(48 + j * 76, 88 + i * 76, 0);
			}
			if (board[i][j] == 'c')
			{
				setfillstyle(SOLID_FILL, GREEN);
				bar(15 + j * 76, 55 + i * 76, 81 + j * 76, 121 + i * 76);
				circle(48 + j * 76, 88 + i* 76, 32);
				setfillstyle(SOLID_FILL, YELLOW);
				floodfill(48 + j * 76, 88 + i * 76, 0);
				board[i][j] = to_change;
			}
			if (board[i][j] == 'x')
			{
				setfillstyle(SOLID_FILL, GREEN);
				bar(15 + j * 76, 55 + i * 76, 81 + j * 76, 121 + i * 76);
				circle(48 + j * 76, 88 + i * 76, 32);
				setfillstyle(SOLID_FILL, BLUE);
				floodfill(48 + j * 76, 88 + i * 76, 0);
				board[i][j] = to_change;
			}
			if (board[i][j] == '_')
			{
				setfillstyle(SOLID_FILL, GREEN);
				floodfill(48 + j * 76, 88 + i * 76, 0);
			}
			if (early_return == true)return;
		}
	}
}
bool check(int i, int j, char to_check, bool temp_check = false, bool save = false, int gahrai = 0)
{
	bool to_return = false;
	char opp_to_check;
	if (to_check == 'w')opp_to_check = 'b';
	else opp_to_check = 'w';
	int temp_i = i, temp_j = j;
	for (int c = -1; c < 2; c++)
	{
		for (int r = -1; r < 2; r++)
		{
			if (i + c != -1 && i + c != 8 && j + r != 8 && j + r != -1)
			{
				if (board[i + c][j + r] == opp_to_check)
				{
					for (;;)
					{
						i += c; j += r;
						if (i == -1 || i == 8 || j == -1 || j == 8 || board[i][j] == '_')
						{
							i = temp_i; j = temp_j;
							break;
						}
						if (board[i][j] == to_check)
						{
							for (;;)
							{
								i -= c; j -= r;
								if (i == temp_i && j == temp_j)break;
								else if (temp_check == false)
								{
									board[i][j] = 'c';
									if (save == true)
									{
										flip_record[gahrai][i][j] = true;
										board[i][j] = to_check;
									}
								}
								to_return = true;
							}
							break;
						}
					}
				}
			}
		}
	}
	//if (save)
	{
		//for (int i = 0; i < 8; i++)
		{
			//for (int j = 0; j < 8; j++)
				//if (flip_record[gahrai][i][j])
					//cout << "c ";
				//else cout << "_ ";
			//cout << "\n";
		}
		//cout << "\n\n";
	}
	//if (temp_check == false)
	{
		//[console_print();
		//cout << "going from check()\n";
	}
	return to_return;
}
inline void reflip(int gahrai, char to_check = player)
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (flip_record[gahrai][i][j] == true)
				board[i][j] = to_check;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			flip_record[gahrai][i][j] = false;
	//console_print();
	//system("pause");
}
bool full_check(char to_check, bool ai = false, int gahrai = 0)
{
	for(int i = 0; i < 8; i ++)
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] == '_')
			{
				board[i][j] = to_check;
				if (check(i, j, to_check, true) == true)
				{
					board[i][j] = '_';
					if(!ai) return true;
					deep[gahrai][i][j] = -101;
				}
				else if (ai) deep[gahrai][i][j] = -100;
				board[i][j] = '_';
			}
		}
	return false;
}
int cal_diff()
{
	int c_sum = 0;
	for(int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] == comp)c_sum++;
			if (board[i][j] == player)c_sum--;
		}
	return c_sum;
}
void AI()
{
	bool check_possible_moves = true;
	char copy_board[8][8];
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			copy_board[i][j] = board[i][j];
	int gahrai = 0;
	for (int k = 0; k < 23; k++)
	{
		for(int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
			{
				deep[k][i][j] = -100;
				flip_record[k][i][j] = false;
			}
		deep1[k][0] = deep1[k][1] = -1;
	}
	cout << "came to AI()\n";
computer_turn:
	{
		int diff = 0;
		best_move[0] = best_move[1] = -1;
		if (check_possible_moves == true)
			full_check(comp, true, gahrai);
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (deep[gahrai][i][j] == -101)
				{
					board[i][j] = comp;
					check(i, j, comp, false, true, gahrai);
					//cout << "\n" << gahrai << "\n";
					//deep_print(gahrai);
					//console_print();
					//system("pause");
					if (full_check(player) && gahrai < main_number)
					{
						check_possible_moves = true;
						deep1[gahrai][0] = i;
						deep1[gahrai][1] = j;
						gahrai++;
						goto player_turn;
					}
					if (gahrai <= main_number|| !full_check(comp))
					{
						board[i][j] = '_';
						//console_print();
						reflip(gahrai);
						deep[gahrai][i][j] = cal_diff();
						check_possible_moves = false;
						goto computer_turn;
					}
				}
			}
		}
		int max_diff = -99;
		for(int i = 0; i <8; i++)
			for (int j = 0; j < 8; j++)
				if (deep[gahrai][i][j] > max_diff)
				{
					max_diff = deep[gahrai][i][j];
					best_move[0] = i; 
					best_move[1] = j;
				}
		if (gahrai == 0)return;
		else
		{
			gahrai--;
			board[deep1[gahrai][0]][deep1[gahrai][1]] = '_';
			reflip(gahrai, comp);
			deep[gahrai][deep1[gahrai][0]][deep1[gahrai][1]] = max_diff;
			check_possible_moves = false;
			goto player_turn;
		}
	}
player_turn:
	{
		if (check_possible_moves == true)
			full_check(player, true, gahrai);
		for(int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
			{
				if (deep[gahrai][i][j] == -101)
				{
					board[i][j] = player;
					check(i, j, player, false, true, gahrai);
					//cout << "\n" << gahrai << "\n";
					//deep_print(gahrai);
					//console_print();
					//system("pause");
					if (full_check(comp) && gahrai < main_number)
					{
						deep1[gahrai][0] = i; deep1[gahrai][1] = j;
						gahrai++;
						check_possible_moves = true;
						goto computer_turn;
					}
					if (gahrai < main_number || !full_check(player))
					{
						board[i][j] = '_';
						reflip(gahrai, comp);
						deep[gahrai][i][j] = cal_diff();
						check_possible_moves = false;
						//cout << "player's end\n";
						//console_print();
						//system("pause");
						goto player_turn;
					}
					board[i][j] = '_';
					reflip(gahrai, comp);
				}
			}
		int min_diff = 99;
		for(int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				if (deep[gahrai][i][j] < min_diff && deep[gahrai][i][j] > -100)
					min_diff = deep[gahrai][i][j];
		gahrai--;
		board[deep1[gahrai][0]][deep1[gahrai][1]] = '_';
		reflip(gahrai);
		deep[gahrai][deep1[gahrai][0]][deep1[gahrai][1]] = min_diff;
		check_possible_moves = false;
		goto computer_turn;
	}
}
void cursor()
{
	char ch = 0;
	int i = 3, j = 3, chance = 0;
	bool player_turn = true;
start:
	if (i == -1)i = 0;
	if (i == 8)i = 7;
	if (j == -1)j = 0;
	if (j == 8)j = 7;
	setfillstyle(1, YELLOW);
	bar(38 + j * 76, 78 + i * 76, 58 + j * 76, 98 + i * 76);
	ch = getch();
	if (ch == 0)ch = getch();           //for extended keys like arrow keys 2 times getch() is needed to use as getch() will return 0 follwed by extended key value
	switch (ch)
	{
	case KEY_UP: {
		print(i--, j);
		goto start;
	}
	case KEY_DOWN:{
		print(i++, j);
		goto start;
	}
	case KEY_LEFT:{
		print(i, j--);
		goto start;
	}
	case KEY_RIGHT: {
		print(i, j++);
		goto start;
	}
	case 13: {
		if (board[i][j] == '_' && player_turn == true)
		{
			board[i][j] = player;
			if (!check(i, j, player, false))
			{
				board[i][j] = '_';
				goto start;
			}
			print(-1, -1, player);
			Sleep(1000);
			print();
			cout << "early ";
			if (full_check(comp))
			{
				player_turn = false;
				if (!dual_player)
					goto somewhere;
			}
			else if (full_check(player))player_turn = true;
			else break;
			cout << "came here\n";
		}
		if (board[i][j] == '_' && player_turn != true)
		{
			if (dual_player)
			{
				board[i][j] = comp;
				if (!check(i, j, comp, false))
				{
					board[i][j] = '_';
					goto start;
				}
				print(-1, -1, comp);
				Sleep(1000);
				print();
				if (full_check(player))player_turn = true;
				else if (full_check(comp))player_turn = false;
				else break;
			}
		}
		goto start;
	}
	default:return;
	}
somewhere:
	{
		chance++;
		if (chance > 7 && chance % 2 == 0 && main_number < 15)main_number++;
		AI();
		deep_print(0);
		cout << "\n" << main_number << endl;
		board[best_move[0]][best_move[1]] = 'x';
		console_print();
		check(best_move[0], best_move[1], comp);
		print(-1,-1,comp);
		Sleep(1000);
		print();
		if (full_check(player))
		{
			player_turn = true;
			goto start;
		}
		else if (full_check(comp))
		{
			player_turn = false;
			goto somewhere;
		}
		else return;
	}
}
int main()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			board[i][j] = '_';
			for (int k = 0; k < 23; k++)
				flip_record[k][i][j] = false;
		}
	board[3][3] = board[4][4] = 'w';
	board[3][4] = board[4][3] = 'b';
	initwindow(1000, 700, "");
	setbkcolor(15);
	cleardevice();
	setcolor(0);
	rectangle(10, 50, 618, 658);
	setfillstyle(SOLID_FILL, GREEN);
	floodfill(80, 80, 0);
	for (int i = 10; i <= 610; i += 76)
	{
		line(i, 50, i, 658);
		line(10, i + 40, 618, i + 40);
	}
	print();
	cursor();
	getch();
}