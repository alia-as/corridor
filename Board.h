#include <iostream>
using namespace std;
string int2str(int);
class board
{
public:
	char **theboard = new char*[11];
	string positions = "";
	void build_board();
	string print_board();
};
string board::print_board()
{
	string ans = "";
	for(int a=0; a<11; a++)
	{
		for(int b=0; b<11; b++)
		{
			ans = ans + theboard[a][b] + " ";
		}
		ans += "\n";
	}
	return ans;
}
void board::build_board()
{
	for (int a=0; a<11; a++)
	{
		theboard[a] = new char[11];
	}
	for(int a=0; a<11; a++)
	{
		for(int b=0; b<11; b++)
		{
			theboard[a][b] = *"O";
			positions = positions + int2str(11*a + b) + " ";
		}
		positions = positions + "\n";
	}
}
string int2str(int num)
{
	string ans;
	while( num>0)
	{
		int a = num%10;
		ans = (char)(a+48) + ans;
		num /= 10;
	}
	if (ans.size() == 0){ans = "0";}
	while(ans.size() < 3)
	{
		ans += " ";
	}
	return ans;
}
