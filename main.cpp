#include <iostream>
#include <string>
#include <cctype>


using namespace std;

char grid[9] = { ' ', ' ', ' ',
		 ' ', ' ', ' ',
		 ' ', ' ', ' ',};

typedef struct
{
	string name = "";
	char mark = ' ';
	uint16_t moves = 0b000000000;
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
	cout << '\n';
	cout << '\t' << "       |     |\n";
	cout << "\t " << "   " << grid[0] << "  |  " << grid[1] << "  |  " << grid[2] << "\n";
	cout << '\t' << "  _____|_____|_____\n";
	cout << '\t' << "       |     |\n";
	cout << "\t " << "   " << grid[3] << "  |  " << grid[4] << "  |  " << grid[5] << "\n";
	cout << '\t' << "  _____|_____|_____\n";
	cout << '\t' << "       |     |\n";
	cout << "\t " << "   " << grid[6] << "  |  " << grid[7] << "  |  " << grid[8] << "\n";
	cout << '\t' << "       |     |\n";
	cout << '\n';
}

int check_win(player *p)
{
	const uint16_t WINMASK[8] = {0b111000000, 0b000111000, 0b000000111, 0b100100100,
				     0b010010010, 0b001001001, 0b100010001, 0b001010100,};

	for(int i = 0;i < 8;i++)
	{
		if(__builtin_popcount(p->moves & WINMASK[i]) == 3)
		{
			return 0;
		}
	}
	return 1;
}

#define INDEX(i) ((i - '0') - 1)
#define SET_BIT(BF, N) BF |= (uint16_t)1 << N

void insert(player *p)
{
	string i = "";
	cout << p->name << " enter a index: "; cin >> i;
	bool v = false;
	
	while(v == false)
	{
		if(!(i[0] >= '1' && i[0] <= '9') || i.length() > 1)
		{
			cout << "Enter a valid index, [1-9]: "; cin >> i;
		}
        
		else if(grid[INDEX(i[0])] != ' ')
		{
			cout << "Index already full, enter a different index: "; cin >> i;
		}
        
		else
		{
			v = true;
		}
	}		

	SET_BIT(p->moves, INDEX(i[0]));
	grid[INDEX(i[0])] = p->mark;
}

int main()
{
	print_grid();
	player P_1, P_2;
	player p[2] = {P_1, P_2};
	make_player(p);
	for(int i = 0;i < 9;i++)
	{
		player *go = &p[i % 2];
		print_grid();
		insert(go);
		if(i >= 4)
		{
			if(check_win(go) == 0)
			{
				cout << go->name << " wins!!!\nGame Over\n";
				print_grid();
				return 0;
			}
		}
	}
	cout << "Draw!!!\nGame Over\n";
	print_grid();
	return 0;
}
