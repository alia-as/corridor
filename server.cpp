#include <httplib.h>
using namespace httplib;
using namespace std;

string menu = "\t\t   Welcome to CORRIDOR game\n\t\t   After you start the game\n\t\twrite 'move' to move your player\n\t\t And write 'wall' to put a wall\n";
string int2str(int );
long long str2int(string );
char **theboard = new char*[11];
bool is_started = false;
int players_count = 0;
int players_in_game = 0;
string positions = "";
void build_board();
string print_board();
class player
{
public:
	
	string go(char);
	void set_place(int);
	void set_name(char);
	bool move(char);
	void put_wall(char , int);
private:
	int place=-1;
	char name;
};
player *alls;
int main()
{
	Server svr;
  	svr.Post("/play", [&](const Request &req, Response &res, const ContentReader &content_reader)
  	{
  	string body;
      	content_reader([&](const char *data, size_t data_length) {
        body.append(data, data_length);
        players_count = str2int(body.substr(1));
        players_in_game = 0;
        return true;
      	});});
  	svr.Get("/pos", [](const Request& req, Response& res) {
    	res.set_content( positions ,"text/html");
  	});
  	svr.Get("/start", [](const Request& req, Response& res) {
    	players_in_game ++;
    	if(players_in_game == players_count)
    	{
    		build_board();
    		alls = new player[players_count];
    		res.set_content( "Great\nGame created\n", "text/plain");
    		int place[4] ={0,10,120,110};
    		char namee = 65;
    		for (int q=0; q<players_count; q++)
    		{
    			alls[q].set_name(namee+q);
    			alls[q].set_place(place[q]);
    		}
    		res.set_content("Here is the board\n" + print_board(), "text/plain");
    	}
  	});
  	svr.Get("/help", [](const Request& req, Response& res) {
    	res.set_content(menu, "text/html" ); 
  	});
  	svr.Get("/print", [](const Request& req, Response& res) {
    	res.set_content(print_board(), "text/plain");
  	});
  	svr.Post("/wall", [&](const Request &req, Response &res, const ContentReader &content_reader)
  	{
  	string body;
      	content_reader([&](const char *data, size_t data_length) {
        body.append(data, data_length);
        alls[0].put_wall(body[0], str2int(body.substr(2)));
        res.set_content(print_board(), "text/plain");
        return true;
      	});});
      	svr.Post("/move", [&](const Request &req, Response &res, const ContentReader &content_reader)
  	{
  	string body;
      	content_reader([&](const char *data, size_t data_length) {
        body.append(data, data_length);
        string result = alls[str2int(body.substr(0,1))-1].go(body[4]);
        res.set_content(  result, "text/plain");
        return true;
      	});});
  	svr.listen("localhost", 8080);
}
void build_board()
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
string print_board()
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
void player::put_wall(char dir, int pos)
{
	if (pos < 121 && pos > -1) 
	{theboard[pos/11][pos%11] = *"W";
		if (dir == *"v")
		{
			if (pos>10) {theboard[pos/11-1][pos%11] = *"W";}
			if (pos<110) {theboard[pos/11+1][pos%11] = *"W";}
		}
		else
		{
			if (pos%11>0) {theboard[pos/11][pos%11-1] = *"W";}
			if (pos%11<10) {theboard[pos/11][pos%11+1] = *"W";}
		}
	}
}
long long str2int(string num )
{
    long long k = 1;
    long long n= num.size();
    // For handling negative numbers
    if (num.substr(0,1) == "-")
    {
        k=-1;
        n--;
        num = num.substr(1);
    }
    long long ans=0;
    for (long long r=0 ; r<n ; r++)
    {
        ans = ans*10 + ((long long)num[r] - 48);
    }
    return ans*k;
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
void player::set_name(char n)
{
	name = n;
}
void player::set_place(int p)
{
	theboard[place/11][place%11] = *"O";
	place = p;
	theboard[place/11][place%11] = name;
}
string player::go(char dirc)
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

