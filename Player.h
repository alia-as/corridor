#include <iostream>
using namespace std;
class player
{
public:
	string go(char**,char);
	void set_place(char**,int);
	void set_name(char);
	string put_wall(char**,char , int);
	int get_place();
private:
	int place=-1;
	char name;
};
string player::put_wall(char** theboard, char dir, int pos)
{
	if (pos < 121 && pos > -1 && theboard[pos/11][pos%11] == *"O") 
	{
		if (dir == *"v")
		{
			if( pos==60 || pos-11 == 60 || pos+11 == 60)
			{
				return "You can't put a wall here\nThe center of board must be empty cause it is the winning place!!";
			}
			if (pos>10 && theboard[pos/11-1][pos%11] == *"O" 
			&& pos<110 && theboard[pos/11+1][pos%11] == *"O") 
			{
				theboard[pos/11][pos%11] = *"W";
				theboard[pos/11-1][pos%11] = *"W";
				theboard[pos/11+1][pos%11] = *"W";
			}
			else
			{
				if( pos<=10 || pos >= 110)
				{
					return "You can't put a wall here\nWalls must be completely in the board!";
				}
				else
				{
					return "You can't put a wall here\nYou just can put walls in empty cells!";
				}
			}
		}
		else
		{
			if( pos==60 || pos-1 == 60 || pos+1 == 60)
			{
				return "You can't put a wall here\nThe center of board must be empty cause it is the winning place!!";
			}
			if (pos%11>0 && theboard[pos/11][pos%11-1] == *"O" 
			&& pos%11<10 && theboard[pos/11][pos%11+1] == *"O")
			{
				theboard[pos/11][pos%11] = *"W";
				theboard[pos/11][pos%11-1] = *"W";
				theboard[pos/11][pos%11+1] = *"W";
			}
			else
			{
				if(pos%11==0 || pos%11 ==10)
				{
					return "You can't put a wall here\nWalls must be completely in the board!";
				}
				else
				{
					return "You can't put a wall here\nYou just can put walls in empty cells!";
				}
			}
		}
		return "OK";
	}
	else
	{
		if(pos >= 121 || pos <= -1)
		{
			return "You can't put a wall here\nThis position is out of the range!\n";
		}
		else
		{
			return "You can't put a wall here\nYou just can put walls in empty cells!";
		}
	}
	
}
void player::set_name(char n)
{
	name = n;
}
void player::set_place(char** theboard, int p)
{
	theboard[place/11][place%11] = *"O";
	place = p;
	theboard[place/11][place%11] = name;
}
string player::go(char** theboard, char dirc)
{
	theboard[place/11][place%11] = *"O";
	if(dirc == *"u")
	{
		if( place < 11 || theboard[(place-11)/11][(place-11)%11] == *"W")
		{
			return "fail";
		}
		place -= 11;
	}
	else if(dirc == *"d")
	{
		if( place > 109 || theboard[(place+11)/11][(place+11)%11] == *"W")
		{
			return "fail";
		}
		place += 11;
	}
	else if(dirc == *"r")
	{
		if( place%11 == 10 || theboard[(place+1)/11][(place+1)%11] == *"W")
		{
			return "fail";
		}
		place ++;
	}
	else if(dirc == *"l")
	{
		if( place%11 == 0 || theboard[(place-1)/11][(place-1)%11] == *"W")
		{
			return "fail";
		}
		place --;
	}
	else
	{
		return "fail";
	}
	theboard[place/11][place%11] = name;
	return "done";
}
int player::get_place()
{
	return place;
}
