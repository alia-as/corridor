#include <httplib.h>
using namespace httplib;
using namespace std;
char **board = new char*[11];
string menu = "\t\t   Welcome to CORRIDOR game\n\t\tHere is the help for this game:\n\t\t   'play' to start the game\n\t\t   'print' to see the board\n";
void build_board();
string print_board();
int main()
{
	int ab = 5;
	for (int a=0; a<11; a++)
	{
		board[a] = new char[11];
	}
	Server svr;
	svr.Get("/hi", [](const Request& req, Response& res) {
    	res.set_content("Hello World!", "text/plain");
  	});
  	svr.Get("/play", [](const Request& req, Response& res) {
    	res.set_content("That's greaaaat!!!!!", "text/html");
    	build_board();
  	});
  	svr.Get("/print", [](const Request& req, Response& res) {
    	res.set_content(print_board(), "text/html" ); 
  	});
  	svr.Get("/help", [](const Request& req, Response& res) {
    	res.set_content(menu, "text/html" ); 
  	});
  	svr.Get("/hwall", [](const Request& req, Response& res) {
    	res.set_content("hldskl;fk", "text/html" ); 
  	});
  	svr.listen("localhost", 8080);
}
void build_board()
{
	for(int a=0; a<11; a++)
	{
		for(int b=0; b<11; b++)
		{
			board[a][b] = *"O";
		}
	}
}
string print_board()
{
	string ans = "";
	for(int a=0; a<11; a++)
	{
		for(int b=0; b<11; b++)
		{
			cout << board[a][b] << " ";
			ans = ans + board[a][b] + " ";
		}
		cout << endl;
		ans += "\n";
	}
	return ans;
}
