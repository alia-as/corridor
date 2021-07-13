#include <httplib.h>
using namespace httplib;
using namespace std;

string menu = "\t\t   Welcome to CORRIDOR game\n\t\tHere is the help for this game:\n\t\t   'play' to start the game\n\t\t   'print' to see the board\n\t\t     'wall' to put a wall\n\t\t'pos' to see positions of cells\n";
string int2str(int );
long long str2int(string );

class board
{
public:
	board();
	string print_board();
	string positions;
	void put_wall( char, int);
private:
	char **theboard = new char*[11];
};
int main()
{
	Server svr;
	board gboard;
  	svr.Get("/play", [](const Request& req, Response& res) {
    	res.set_content("That's greaaaat!!!!!", "text/html");
  	});
  	svr.Get("/pos", [&gboard](const Request& req, Response& res) {
    	res.set_content( gboard.positions ,"text/html");
  	});
  	svr.Get("/print", [&gboard](const Request& req, Response& res) {
    	res.set_content(gboard.print_board(), "text/plain" ); 
  	});
  	svr.Get("/help", [](const Request& req, Response& res) {
    	res.set_content(menu, "text/html" ); 
  	});
  	svr.Post("/wall", [&](const Request &req, Response &res, const ContentReader &content_reader)
  	{
  	string body;
      	content_reader([&](const char *data, size_t data_length) {
        body.append(data, data_length);
        gboard.put_wall(body[0], str2int(body.substr(2)));
        cout << "put wall complete\n";
        res.set_content(gboard.print_board(), "text/plain");
        return true;
      	});});
  	svr.listen("localhost", 8080);
}
board::board()
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
void board::put_wall(char dir, int pos)
{
	printf( "dir: %c   pos: %d", dir, pos);
	printf("pos: %d\n", pos);
	if (pos < 121 && pos > -1) 
	{theboard[pos/11][pos%11] = *"W";
		if (dir == *"h")
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
	cout << "num: " << num << endl;
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
	cout << ans << endl;
	return ans;
}
