#include <iostream>
using namespace std;
class player
{
public:
	string go(char**,char);
	void set_place(char**,int);
	void set_name(char);
	bool put_wall(char**,char , int);
	int get_place();
private:
	int place=-1;
	char name;
};
bool player::put_wall(char** theboard, char dir, int pos)
{
	if (pos < 121 && pos > -1 && theboard[pos/11][pos%11] == *"O") 
	{
		if (dir == *"v")
		{
			if (pos>10 && theboard[pos/11-1][pos%11] == *"O" 
			&& pos<110 && theboard[pos/11+1][pos%11] == *"O") 
			{
				theboard[pos/11][pos%11] = *"W";
				theboard[pos/11-1][pos%11] = *"W";
				theboard[pos/11+1][pos%11] = *"W";
			}
			else {return false;}
		}
		else
		{
			if (pos%11>0 && theboard[pos/11][pos%11-1] == *"O" 
			&& pos%11<10 && theboard[pos/11][pos%11+1] == *"O")
			{
				theboard[pos/11][pos%11] = *"W";
				theboard[pos/11][pos%11-1] = *"W";
				theboard[pos/11][pos%11+1] = *"W";
			}
			else {return false;}
		}
		return true;
	}
	else
	{
		return false;
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
