#include<iostream>
#include<fstream>
using namespace std;
void game_menu();
void new_game();
void resume_game();
void levels_of_game();
void view_highscore();
void exit_game();
int get_length(char *arr);
void row_wise(char **board, char name[], int r, bool &flag, int &score);
void back_row_wise(char **board, char name[], int r, bool &flag, int &score);
void col_wise(char **board, char name[], int r, bool &flag, int &score);
void back_col_wise(char **board, char name[], int r, bool &flag, int &score);
void dig_wise(char **board, char name[], int r, bool &flag, int &score);
void back_dig_wise(char **board, char name[], int r, bool &flag, int &score);
void revDig_wise(char**board, char name[], int r, bool &flag, int &score);
void back_revDig_wise(char**board, char name[], int r, bool &flag, int &score);
char ** read_boardFile(char *filename, char **ptr, int r, int c);
void display_board(char **board, int r, int c);
bool check_Dictionary(char word[]);
int *regrow(int *ptr, int size);
void save_high_score(int score);
void chk_ptr(char **board, int r);
int main()
{
	game_menu();
	char choose;
	cout << "=====>Enter Choose: ";
	cin >> choose;
	if (choose == 'n' || choose == 'N')
	{
		new_game();
	}
	else if (choose == 'r' || choose == 'R')
	{
		resume_game();
	}
	else if (choose == 'L' || choose == 'l')
	{
		levels_of_game();
	}
	else if (choose == 'h' || choose == 'H')
	{
		view_highscore();
	}
	else if (choose == 'e' || choose == 'E')
	{
		exit_game();
	}
	else
	{
		cout << "Invalid Entery\n";
		return 0;
	}
	return 0;
}
void game_menu()
{
	cout << "\n****************(WELCOME TO WORD SEARCH GAME)***************\n";
	cout << "___________________________________________________________\n";
	cout << endl << "\t \t\tMENU\n\t\t       -------\n";

	cout << "\t_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n\n";
	cout << "\t|Press (n or N) for New Game :\n";
	cout << "\t|Press (r or R) for Resume Game :\n";
	cout << "\t|Press (l or L) for Level Selection :\n";
	cout << "\t|Press (h or H) for High Score :\n";
	cout << "\t|Press (e or E) for Exit\n";
	cout << "\t----------------------------------\n";
	cout << endl;
}
void new_game()
{

	system("CLS");
	char player_name[25] = { '\0' };
	cout << "Enter Your Name :";
	cin.ignore();
	cin.getline(player_name, 25, '\n');
	char **board = nullptr;
	int r = 15, c = 15, score = 0, lives = 3, num = 1;
	board = new char*[r];
	for (int i = 0; i < r; i++)
	{
		board[i] = new char[c];
	}
	char *file = { "board.txt" };
	board = read_boardFile(file, board, r, c);
	cout << "\t Level ==> Easy\n";
	display_board(board, r, c);
	while (lives>0)
	{
		cout << "Your score is : " << score << endl;
		cout << "Your lives is :" << lives << endl;
		cout << "Enter Word to search :";
		char name[20] = { '\0' };
		cin >> name;
		int l = get_length(name);
		if ((name[0] == 'p' || name[0] == 'P') && l == 1)
		{
			char *filen = { "pausegame.txt" };
			ofstream fout(filen);
			if (!fout.is_open())
			{
				cout << "pause File is not open\n";
				exit(1);
			}
			else
			{
				for (int i = 0; i < r; i++)
				{
					for (int j = 0; j < c; j++)
					{
						fout << board[i][j];
					}
					fout << endl;
				}

				fout << score << " " << lives << " " << num << endl;
				fout.close();
			}
			chk_ptr(board, r);
			char ch;
			system("CLS");
			cout << "\nPress e for Exit\n";
			cout << "\nPress r for resume\n";
			cout << "Enter choose :";
			cin >> ch;
			if (ch == 'e' || ch == 'E')
			{
				system("CLS");
				cout << "Game Exit\n";
				exit(1);
			}
			else if (ch == 'r' || ch == 'R')
			{
				system("CLS");
				char *filen = { "pausegame.txt" };
				ifstream fin(filen);
				if (!fin.is_open())
				{
					cout << "Pause File is missing\n";
					exit(1);

				}
				else
				{
					board = nullptr;
					board = new char*[r];
					for (int i = 0; i < r; i++)
					{
						board[i] = new char[c];
						for (int j = 0; j < c; j++)
						{
							fin >> board[i][j];
						}
					}
					fin >> score >> lives >> num;
					fin.close();

				}
				cout << "\t Level ==> Easy\n";
				display_board(board, r, c);
			}
		}
		else
		{

			bool flag = check_Dictionary(name);
			if (flag)
			{
				for (int i = 0; name[i] != '\0'; i++)
				{
					if (name[i] >= 'a'&&name[i] <= 'z')
					{
						name[i] -= 32;
					}
				}
				flag = false;
				if (num == 1)
				{
					row_wise(board, name, r, flag, score);
					col_wise(board, name, r, flag, score);
				}
				else if (num == 2)
				{
					row_wise(board, name, r, flag, score);
					back_row_wise(board, name, r, flag, score);
					col_wise(board, name, r, flag, score);
					back_col_wise(board, name, r, flag, score);
				}
				else if (num == 3)
				{
					row_wise(board, name, r, flag, score);
					back_row_wise(board, name, r, flag, score);
					col_wise(board, name, r, flag, score);
					back_col_wise(board, name, r, flag, score);
					dig_wise(board, name, r, flag, score);
					back_dig_wise(board, name, r, flag, score);
					revDig_wise(board, name, r, flag, score);
					back_revDig_wise(board, name, r, flag, score);
				}
				else
				{
					cout << "ERROR!!!\n";
					exit(1);

				}
				if (!flag)
				{
					lives--;
					cout << name << " not found in Board\n";
				}
			}
			else
			{
				cout << "Your Word not found in Dictionary\n";
				lives--;
			}
		}
	}
	system("CLS");
	cout << "##### Your Score is : " << score <<" #####"<< endl;
	cout << "GAMER OVER!!!\n";
	save_high_score(score);

}
void resume_game()
{
	char **board = nullptr; int r = 15, c = 15, score, lives, num;
	system("CLS");
	char *filen = { "pausegame.txt" };
	ifstream fin(filen);
	if (!fin.is_open())
	{
		cout << "Pause File is missing\n";
		exit(1);
	}
	else
	{
		board = nullptr;
		board = new char*[r];
		for (int i = 0; i < r; i++)
		{
			board[i] = new char[c];
			for (int j = 0; j < c; j++)
			{
				fin >> board[i][j];
			}
		}
		fin >> score >> lives >> num;
		fin.close();

	}
	if (num == 1)
	{
		cout << "\t Level ==> Easy\n";
	}
	else if (num == 2)
	{
		cout << "\t Level ==> Medium\n";
	}
	else
	{
		cout << "\t Level ==> Hard\n";
	}
	display_board(board, r, c);
	while (lives>0)
	{
		cout << "Your score is : " << score << endl;
		cout << "Your lives is :" << lives << endl;
		cout << "Enter Word to search :";
		char name[20] = { '\0' };
		cin >> name;

		int l = get_length(name);

		if ((name[0] == 'p' || name[0] == 'P') && l == 1)
		{
			char *filen = { "pausegame.txt" };
			ofstream fout(filen);
			if (!fout.is_open())
			{
				cout << "pause File is not open\n";
				exit(1);
			}
			else
			{
				for (int i = 0; i < r; i++)
				{
					for (int j = 0; j < c; j++)
					{
						fout << board[i][j];
					}
					fout << endl;
				}

				fout << score << " " << lives << num << endl;
				fout.close();
			}
			chk_ptr(board, r);
			char ch;
			system("CLS");
			cout << "\nPress e for Exit\n";
			cout << "\nPress r for resume\n";
			cout << "Enter choose :";
			cin >> ch;
			if (ch == 'e' || ch == 'E')
			{
				system("CLS");
				cout << "Game Exit\n";
				exit(1);
			}
			else if (ch == 'r' || ch == 'R')
			{
				system("CLS");
				char *filen = { "pausegame.txt" };
				ifstream fin(filen);
				if (!fin.is_open())
				{
					cout << "Pause File is missing\n";
					exit(1);
				}
				else
				{
					board = nullptr;
					board = new char*[r];
					for (int i = 0; i < r; i++)
					{
						board[i] = new char[c];
						for (int j = 0; j < c; j++)
						{
							fin >> board[i][j];
						}
					}
					fin >> score >> lives >> num;
					fin.close();

				}
				if (num == 1)
				{
					cout << "\t Level ==> Easy\n";
				}
				else if (num == 2)
				{
					cout << "\t Level ==> Medium\n";
				}
				else
				{
					cout << "\t Level ==> Hard\n";
				}
				display_board(board, r, c);
			}
		}
		else
		{

			bool flag = check_Dictionary(name);
			if (flag)
			{
				for (int i = 0; name[i] != '\0'; i++)
				{
					if (name[i] >= 'a'&&name[i] <= 'z')
					{
						name[i] -= 32;
					}
				}
				flag = false;
				if (num == 1)
				{
					row_wise(board, name, r, flag, score);
					col_wise(board, name, r, flag, score);
				}
				else if (num == 2)
				{
					row_wise(board, name, r, flag, score);
					back_row_wise(board, name, r, flag, score);
					col_wise(board, name, r, flag, score);
					back_col_wise(board, name, r, flag, score);
				}
				else if (num == 3)
				{
					row_wise(board, name, r, flag, score);
					back_row_wise(board, name, r, flag, score);
					col_wise(board, name, r, flag, score);
					back_col_wise(board, name, r, flag, score);
					dig_wise(board, name, r, flag, score);
					back_dig_wise(board, name, r, flag, score);
					revDig_wise(board, name, r, flag, score);
					back_revDig_wise(board, name, r, flag, score);
				}
				else
				{
					cout << "ERROR!!!\n";
					exit(1);
				}
				if (!flag)
				{
					lives--;
					cout << name << " not found in Board\n";
				}
			}
			else
			{

				cout << name << " not found in Dictionary\n";
				lives--;

			}
		}
	}
	system("CLS");
	cout << "##### Your Score is : " << score << " #####" << endl;
	cout << "GAMER OVER!!!\n";
	save_high_score(score);

}
void levels_of_game()
{
	system("CLS");
	cout << "Select Levels \n";

	cout << "Press 1 for Easy Level\n";
	cout << "Press 2 for Medium Level\n";
	cout << "Press 3 for Hard Level\n";
	cout << "Select LEvels :";
	int num;
	cin >> num;
	if (!(num >= 1 && num <= 3))
	{
		cout << "Invalid  Entery\n";
		exit(1);
	}
	system("CLS");

	char player_name[25] = { '\0' };
	cout << "Enter Your Name :";
	cin.ignore();
	cin.getline(player_name, 25, '\n');
	if (num == 1)
	{
		cout << "\t Level ==> Easy\n";
	}
	else if (num == 2)
	{
		cout << "\t Level ==> Medium\n";
	}
	else
	{
		cout << "\t Level ==> Hard\n";
	}
	char **board = nullptr;
	int r = 15, c = 15, score = 0, lives = 3;
	board = new char*[r];
	for (int i = 0; i < r; i++)
	{
		board[i] = new char[c];
	}
	char *file = { "board.txt" };
	board = read_boardFile(file, board, r, c);
	display_board(board, r, c);
	while (lives>0)
	{
		cout << "Your score is : " << score << endl;
		cout << "Your lives is :" << lives << endl;
		cout << "Enter Word to search :";
		char name[20] = { '\0' };
		cin >> name;

		int l = get_length(name);

		if ((name[0] == 'p' || name[0] == 'P') && l == 1)
		{
			char *filen = { "pausegame.txt" };
			ofstream fout(filen);
			if (!fout.is_open())
			{
				cout << "pause File is not open\n";
				exit(1);
			}
			else
			{
				for (int i = 0; i < r; i++)
				{
					for (int j = 0; j < c; j++)
					{
						fout << board[i][j];
					}
					fout << endl;
				}

				fout << score << " " << lives << " " << num << endl;
				fout.close();
			}
			chk_ptr(board, r);
			char ch;
			system("CLS");
			cout << "\nPress e for Exit\n";
			cout << "\nPress r for resume\n";
			cout << "Enter choose :";
			cin >> ch;
			if (ch == 'e' || ch == 'E')
			{
				system("CLS");
				cout << "Game Exit\n";
				exit(1);
			}
			else if (ch == 'r' || ch == 'R')
			{
				system("CLS");
				char *filen = { "pausegame.txt" };
				ifstream fin(filen);
				if (!fin.is_open())
				{
					cout << "Pause File is missing\n";
					exit(1);
				}
				else
				{
					board = nullptr;
					board = new char*[r];
					for (int i = 0; i < r; i++)
					{
						board[i] = new char[c];
						for (int j = 0; j < c; j++)
						{
							fin >> board[i][j];
						}
					}
					fin >> score >> lives >> num;
					fin.close();

				}
				if (num == 1)
				{
					cout << "\t Level ==> Easy\n";
				}
				else if (num == 2)
				{
					cout << "\t Level ==> Medium\n";
				}
				else
				{
					cout << "\t Level ==> Hard\n";
				}
				display_board(board, r, c);
			}
		}
		else
		{

			bool flag = check_Dictionary(name);
			if (flag)
			{
				for (int i = 0; name[i] != '\0'; i++)
				{
					if (name[i] >= 'a'&&name[i] <= 'z')
					{
						name[i] -= 32;
					}
				}
				flag = false;
				if (num == 1)
				{
					row_wise(board, name, r, flag, score);
					col_wise(board, name, r, flag, score);
				}
				else if (num == 2)
				{
					row_wise(board, name, r, flag, score);
					back_row_wise(board, name, r, flag, score);
					col_wise(board, name, r, flag, score);
					back_col_wise(board, name, r, flag, score);
				}
				else if (num == 3)
				{
					row_wise(board, name, r, flag, score);
					back_row_wise(board, name, r, flag, score);
					col_wise(board, name, r, flag, score);
					back_col_wise(board, name, r, flag, score);
					dig_wise(board, name, r, flag, score);
					back_dig_wise(board, name, r, flag, score);
					revDig_wise(board, name, r, flag, score);
					back_revDig_wise(board, name, r, flag, score);
				}
				else
				{
					cout << "ERROR!!!\n";
					exit(1);
				}
				if (!flag)
				{
					lives--;
					cout << name << " not found in Board\n";
				}
			}
			else
			{
				cout << name << " not found in Dictionary\n";
				lives--;
			}
		}
	}
	system("CLS");
	cout << "##### Your Score is : " << score << " #####" << endl;
	cout << "GAMER OVER!!!\n";
	save_high_score(score);
}
void view_highscore()
{
	ifstream fin("highrecord.txt");
	if (fin.is_open())
	{
		cout << "High Scores :";
		int num;
		while (fin >> num)
		{
			cout << num << " ";
		}
		cout << endl;
		fin.close();
	}
	else
	{
		cout << "High Score file is missing\n";
		exit(1);
	}
}
void exit_game()
{
	system("CLS");
	cout << "\n\n\n\n\n";
	cout << "\t\t\t&&&& Babye &&&&\n";
	cout << "\t\t\t*****Game Exit*****\n";
	exit(1);
}
int get_length(char *arr)
{
	int l = 0;
	while (arr[l] != '\0')
	{
		l++;
	}
	return l;
}
void row_wise(char **board, char name[], int r, bool &flag, int &score)
{

	int l = get_length(name), count = 0, z = 0;
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < r; j++)
		{
			if (board[i][j] == name[z])
			{

				z++;
				count++;

				if (count == l)
				{
					flag = true;
					score += 10;
					cout << "Forward Row Wise : \n";
					cout << name << endl;
					cout << "Start at(row " << i << ",col " << j - l + 1 << ")" << endl;
					cout << "End at(row " << i << ",col " << j << ")" << endl << endl;

				}

			}
			else
			{
				z = 0; count = 0;
			}
		}
		z = 0; count = 0;
	}

}
void back_row_wise(char **board, char name[], int r, bool &flag, int &score)
{

	int l = get_length(name), count = 0, z = l - 1;
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < r; j++)
		{
			if (board[i][j] == name[z])
			{
				z--;
				count++;
				if (count == l)
				{
					flag = true;
					score += 10;
					cout << "Backward Row Wise : \n";
					cout << name << endl;
					cout << "Start at(row " << i << ",col " << j << ")" << endl;
					cout << "End at(row " << i << ",col " << j - l + 1 << ")" << endl << endl;

				}
			}
			else
			{
				z = l - 1; count = 0;
			}
		}
		z = l - 1; count = 0;
	}

}
void col_wise(char **board, char name[], int r, bool &flag, int &score)
{
	int l = get_length(name), count = 0, z = 0;

	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < r; j++)
		{
			if (board[j][i] == name[z])
			{
				z++;
				count++;
				if (count == l)
				{
					flag = true;
					score += 10;
					cout << name << endl;
					cout << "Forward col wise :\n";
					cout << "Start at(row " << j - l + 1 << ",col " << i << ")" << endl;
					cout << "End at(row " << j << ",col " << i << ")" << endl << endl;

				}
			}
			else
			{
				z = 0; count = 0;
			}
		}
		z = 0; count = 0;
	}

}
void back_col_wise(char **board, char name[], int r, bool &flag, int &score)
{
	int l = get_length(name), count = 0, z = l - 1;

	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < r; j++)
		{
			if (board[j][i] == name[z])
			{
				z--;
				count++;
				if (count == l)
				{
					flag = true;
					score += 10;
					cout << name << endl;
					cout << "Backward col wise :\n";
					cout << "Start at(row " << j << ",col " << i << ")" << endl;
					cout << "End at(row " << j - l + 1 << ",col " << i << ")" << endl << endl;

				}
			}
			else
			{
				z = l - 1; count = 0;
			}
		}
		z = l - 1; count = 0;
	}

}
void dig_wise(char **board, char name[], int r, bool &flag, int &score)
{
	int l = get_length(name), count = 0, z = 0;
	int x = 0;

	int t = 1;
	int r1 = r - 1;
	while (x<r - 1)
	{
		int v = r1;
		for (int i = 0; i < t; i++)
		{
			if (board[v][i] == name[z])
			{
				z++;
				count++;
				if (count == l)
				{
					flag = true;
					score += 10;
					cout << "Forward diagonal wise :\n";
					cout << name << endl;

					cout << "Start at(row " << v - l + 1 << ",col " << i - l + 1 << ")" << endl;
					cout << "End at(row " << v << ",col " << i << ")" << endl << endl;
				}
			}
			else
			{
				z = 0; count = 0;
			}
			v++;
		}
		x++;
		r1--;
		t++;
		z = 0; count = 0;
	}

	x = 0;
	r1 = r;
	while (x<r)
	{
		int v = x;
		for (int i = 0; i < r1; i++)
		{
			if (board[i][v] == name[z])
			{
				z++;
				count++;
				if (count == l)
				{
					flag = true;
					score += 10;
					cout << name << endl;
					cout << "Forward diagonal wise \n";
					cout << "Start at(row " << i - l + 1 << ",col " << v - l + 1 << ")" << endl;
					cout << "End at(row " << i << ",col " << v << ")" << endl << endl;
				}
			}
			else
			{
				z = 0; count = 0;
			}
			v++;
		}
		x++;
		r1--;
		z = 0; count = 0;
	}



}
void back_dig_wise(char **board, char name[], int r, bool &flag, int &score)
{
	int l = get_length(name), count = 0, z = l - 1;
	int x = 0;

	int t = 1;
	int r1 = r - 1;
	while (x<r - 1)
	{
		int v = r1;
		for (int i = 0; i < t; i++)
		{
			if (board[v][i] == name[z])
			{
				z--;
				count++;
				if (count == l)
				{
					flag = true;
					score += 10;
					cout << "Backward diagonal wise :\n";
					cout << name << endl;

					cout << "Start at(row " << v << ",col " << i << ")" << endl;
					cout << "End at(row " << v - l + 1 << ",col " << i - l + 1 << ")" << endl << endl;
				}
			}
			else
			{
				z = l - 1; count = 0;
			}
			v++;
		}
		x++;
		r1--;
		t++;
		z = l - 1; count = 0;
	}

	x = 0;
	r1 = r;
	z = l - 1;
	while (x<r)
	{
		int v = x;
		for (int i = 0; i < r1; i++)
		{
			if (board[i][v] == name[z])
			{
				z--;
				count++;
				if (count == l)
				{
					flag = true;
					score += 10;
					cout << name << endl;
					cout << "Backward diagonal wise \n";
					cout << "Start at(row " << i << ",col " << v << ")" << endl;
					cout << "End at(row " << i - l + 1 << ",col " << v - l + 1 << ")" << endl<<endl;

				}
			}
			else
			{
				z = l - 1; count = 0;
			}
			v++;
		}
		x++;
		r1--;
		z = l - 1; count = 0;
	}



}
void revDig_wise(char**board, char name[], int r, bool &flag, int &score)
{
	int l = get_length(name), count = 0, z = 0;
	int x = 0, t = 1, v;
	while (x<r - 1)
	{
		v = x;
		for (int i = 0; i < t; i++)
		{
			if (board[i][v] == name[z])
			{
				z++;
				count++;
				if (count == l)
				{
					flag = true;
					score += 10;

					cout << "Reverse diagonal wise :\n";
					cout << name << endl;

					cout << "Start at(row " << i - l + 1 << ",col " << v + l - 1 << ")" << endl;
					cout << "End at(row " << i << ",col " << v << ")" << endl << endl;
				}
			}
			else
			{
				z = 0; count = 0;
			}
			v--;
		}
		z = 0, count = 0;
		t++;
		x++;
	}
	int r1 = r - 1;
	x = 0;
	while (x<r)
	{
		v = r1;
		for (int i = x; i <= r1; i++)
		{
			if (board[i][v] == name[z])
			{
				z++;
				count++;
				if (count == l)
				{
					flag = true;
					score += 10;

					cout << "Reverse diagonal wise :\n";
					cout << name << endl;

					cout << "Start at(row " << i - l + 1 << ",col " << v + l - 1 << ")" << endl;
					cout << "End at(row " << i << ",col " << v << ")" << endl << endl;
				}
			}
			else
			{
				z = 0; count = 0;
			}
			v--;
		}
		z = 0, count = 0;
		t++;
		x++;

	}
}
void back_revDig_wise(char**board, char name[], int r, bool &flag, int &score)
{
	int l = get_length(name), count = 0, z = l - 1;
	int x = 0, t = 1, v;
	while (x<r - 1)
	{
		v = x;
		for (int i = 0; i < t; i++)
		{
			if (board[i][v] == name[z])
			{
				z--;
				count++;
				if (count == l)
				{
					flag = true;
					score += 10;
					cout << "Backward Reverse diagonal wise :\n";
					cout << name << endl;

					cout << "Start at(row " << i << ",col " << v << ")" << endl;
					cout << "End at(row " << i - l + 1 << ",col " << v + l - 1 << ")" << endl << endl;
				}
			}
			else
			{
				z = l - 1; count = 0;
			}
			v--;
		}
		z = l - 1, count = 0;
		t++;
		x++;
	}
	int r1 = r - 1;
	x = 0;
	z = l - 1;
	while (x<r)
	{
		v = r1;
		for (int i = x; i <= r1; i++)
		{
			if (board[i][v] == name[z])
			{
				z--;
				count++;
				if (count == l)
				{
					flag = true;
					score += 10;
					cout << "Backward Reverse diagonal wise :\n";
					cout << name << endl;

					cout << "Start at(row " << i << ",col " << v << ")" << endl;
					cout << "End at(row " << i - l + 1 << ",col " << v + l - 1 << ")" << endl << endl;
				}
			}
			else
			{
				z = l - 1; count = 0;
			}
			v--;
		}
		z = l - 1, count = 0;
		t++;
		x++;

	}
}
char ** read_boardFile(char *filename, char **ptr, int r, int c)
{
	fstream fin(filename, ios::in);
	if (!fin.is_open())
	{
		cout << "Board file is not found\n";
		exit(1);
	}
	else
	{
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				fin >> ptr[i][j];
			}
		}

	}
	return ptr;
}
void display_board(char **board, int r, int c)
{
	cout << "\t-----------------\n";
	cout << " C|00 01 02 03 04 05 06 07 08 09 10 11 12 13 14\n";
	cout << "R ---------------------------------------------\n";
	for (int i = 0; i < r; i++)
	{

		if (i < 10)
		{
			cout << 0;
		}
		cout << i << "|";
		for (int j = 0; j < c; j++)
		{
			cout << board[i][j] << "| ";

		}
		cout << endl;


	}
	cout << "-----------------------------------------------\n";
}
bool check_Dictionary(char word[])
{

	int found = 0;
	int size = 0;
	for (int k = 0; word[k] != '\0'; k++)
	{
		if (word[k] >= 'A'&&word[k] <= 'Z')
		{
			word[k] += 32;
		}
		size++;
	}

	char dictionary[50] = { '\0' };
	ifstream dic;
	dic.open("dictionary.txt");
	if (dic.is_open())
	{
		while (!dic.eof())
		{
			dic >> dictionary;

			for (int i = 0; dictionary[i] != '\0'; i++)
			{
				if (word[i] == dictionary[i])
				{
					found++;
				}
				else
				{
					found = 0;
				}
			}
			if (found == size)
			{

				return true;

			}
		}
		dic.close();

	}
	else
	{

		cout << "Dictionary File is Missing\n";
		exit(1);
	}
	return false;
}
int *regrow(int *ptr, int size)
{
	int *fake = nullptr;
	fake = new int[size + 1];
	for (int i = 0; i < size; i++)
	{
		fake[i] = ptr[i];
	}

	if (ptr != nullptr)
	{
		delete[]ptr;
		ptr = nullptr;
	}
	return fake;
}
void save_high_score(int score)
{

	char *file = { "highrecord.txt" };

	ifstream fin(file);
	if (fin.is_open())
	{
		int f = 0;
		int n[6], count = 0;
		while (fin >> n[count])
		{
			count++;

			if (count == 5)
			{
				fin.close();
				f++;
				n[count] = score;
				int min = 0;
				for (int i = 0; i < 6; i++)
				{
					for (int j = 0; j < 6; j++)
					{
						if (n[i]>n[j])
						{
							int temp = n[i];
							n[i] = n[j];
							n[j] = temp;
						}
					}
				}

				ofstream fout(file);
				if (fout.is_open())
				{
					for (int i = 0; i < 5; i++)
					{
						fout << n[i] << endl;
					}
					fout.close();
				}
				else
				{
					cout << "file is missing\n";
					exit(1);
				}

			}

		}

		if (!f)
		{
			int *highscore = nullptr, s = 0;
			ifstream opn(file);
			if (opn.is_open())
			{
				int n;
				while (opn >> n)
				{
					highscore = regrow(highscore, s);
					highscore[s++] = n;
				}
				highscore = regrow(highscore, s);
				highscore[s++] = score;
				opn.close();
			}
			else
			{
				cout << "file is missing\n";
				exit(1);
			}

			for (int i = 0; i < s; i++)
			{
				for (int j = 0; j < s; j++)
				{
					if (highscore[i]>highscore[j])
					{
						int temp = highscore[i];
						highscore[i] = highscore[j];
						highscore[j] = temp;
					}
				}
			}
			ofstream fout(file);
			if (fout.is_open())
			{
				for (int i = 0; i < s; i++)
				{
					fout << highscore[i] << " ";
				}

				fout.close();
			}
			else
			{
				cout << "file is missing\n";
				exit(1);
			}
			if (highscore == nullptr)
			{
				delete[]highscore;
				highscore = nullptr;
			}
		}

	}
	else
	{
		ofstream fout(file);
		if (fout.is_open())
		{
			fout << score << endl;
			fout.close();
		}
		else
		{
			cout << "file is missing\n";
			exit(1);
		}
	}

}
void chk_ptr(char **board, int r)
{

	if (board != nullptr)
	{
		for (int i = 0; i < r; i++)
		{
			if (board[i] != nullptr)
			{
				delete[]board[i];
				board[i] = nullptr;
			}
		}
		delete[] board;
		board = nullptr;
	}
}
