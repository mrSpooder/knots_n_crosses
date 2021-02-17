#include <iostream>
#include <string>
#include <cctype>

#define R(r) (r -'A')
#define C(c) (c -'1')

// NOTE: Figure out problem with check_win() 

using namespace std;

char grid[3][3] = { {' ', ' ', ' '},
		    {' ', ' ', ' '},
		    {' ', ' ', ' '},};

typedef struct
{
	string name = "";
	char mark = ' ';
}player;

void make_player(player p[2])
{
	for(int i = 0;i < 2;i++)
	{
		cout << "Player " << i + 1 << " enter a name: "; cin >> p[i].name; cout << '\n';
		string m = "";
		cout << "Choose: 'O' or 'X'\n"; cin >> m;
        
		bool v = false;
		while(v == false)
		{
			if(!(m[0] == 'O' || m[0] == 'X') || (m.length() > 1))
			{
				m = "";
				cout << "Choose: 'O' or 'X'\n";
				cin >> m;
			}
			else if(i == 1 && m[0] == p[0].mark)
			{
				cout << m << " already taken, choose the other one:\n";
				m = "";
				cin >> m;
			}
			else
			{
				v = true;
			}
		}
		p[i].mark = m[0];
	}
}

void print_grid()
{
	cout << '\t' << "    1     2     3\n";
	cout << '\t' << "       |     |\n";
	cout << "\tA" << "   " << grid[0][0] << "  |  " << grid[0][1] << "  |  " << grid[0][2] << "\n";
	cout << '\t' << "  _____|_____|_____\n";
	cout << '\t' << "       |     |\n";
	cout << "\tB" << "   " << grid[1][0] << "  |  " << grid[1][1] << "  |  " << grid[1][2] << "\n";
	cout << '\t' << "  _____|_____|_____\n";
	cout << '\t' << "       |     |\n";
	cout << "\tC" << "   " << grid[2][0] << "  |  " << grid[2][1] << "  |  " << grid[2][2] << "\n";
	cout << '\t' << "       |     |\n";
	cout << '\n';
}

int check_win()
{
	const string win[8][3] = {{"A1", "A2", "A3"}, {"B1", "B2", "B3"},
			    	  {"C1", "C2", "C3"}, {"A1", "B1", "C1"},
				  {"A2", "B2", "C2"}, {"A3", "B3", "C3"},
			    	  {"A1", "B2", "C3"}, {"A3", "B2", "C1"},};

	for(int i = 0;i < 8;i++)
	{
		int count = 0;
		for(int j = 0;j < 2;j++)
		{
			int r = R(win[i][j][0]), c = C(win[i][j][1]);
			int r_next = R(win[i][j + 1][0]), c_next = C(win[i][j + 1][1]);
			if((grid[r][c] == grid[r_next][c_next]) && (grid[r][c] == 'O' || grid[r][c] == 'X'))
			{
				count++;
			}
			else
			{
				break;
			}
		}
		if(count == 2)
		{
			return 1;
		}
		else
		{
			count = 0;
		}
	}
	return 0;
}

void insert(player *p)
{
	string s = "";
	cout << p->name << " enter a index: "; cin >> s;
	s[0] = toupper(s[0]);
	int r = R(s[0]), c = C(s[1]);
	bool v = false;
	
	while(v == false)
	{
		if(!(s[0] >= 'A' && s[0] <= 'C') || !(s[1] >= '1' && s[1] <= '3') || (s.length() > 2))
		{
			cout << "Enter a valid index, [ROW][COLUMN]: "; cin >> s;
			s[0] = toupper(s[0]);
			r = R(s[0]);
			c = C(s[1]);
		}
        
		else if(grid[r][c] != ' ')
		{
			cout << "Index already full, enter a different index: "; cin >> s;
			s[0] = toupper(s[0]);
			r = s[0] - 'A';
			c = (s[1] - '0') - 1;
		}
        
		else
		{
			v = true;
		}
	}		

	grid[r][c] = p->mark;
}

int main()
{
	print_grid();
	player P_1, P_2;
	player p[2] = {P_1, P_2};
	make_player(p);
	for(int i = 0;i < 9;i++)
	{
		player go = p[i % 2];
		print_grid();
		insert(&go);
		if(i >= 4)
		{
			if(check_win() == 1)
			{
				cout << go.name << " wins!!!\nGame Over\n";
				print_grid();
				return 0;
			}
		}
	}
	cout << "Draw!!!\nGame Over\n";
	print_grid();
	return 0;
}
