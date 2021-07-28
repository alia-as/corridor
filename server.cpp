#include <httplib.h>
#include "Player.h"
#include "Board.h"
using namespace httplib;
using namespace std;

string menu = "\t\t   Welcome to CORRIDOR game\n\t\t   After you start the game\n\t\twrite 'move' to move your player\n\t\t And write 'wall' to put a wall\n";
string int2str(int );
long long str2int(string );

bool is_started = false;
int players_count = 0;
int players_in_game = 0;
const int win_place = 60;
string is_finish();

player *alls;
int main()
{
	board gboard;
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
  	svr.Get("/pos", [&gboard](const Request& req, Response& res) {
    	res.set_content( gboard.positions ,"text/html");
  	});
  	svr.Get("/finish", [](const Request& req, Response& res) {
    	res.set_content( is_finish() ,"text/html");
  	});
  	svr.Get("/start", [&gboard](const Request& req, Response& res) {
    	players_in_game ++;
    	if(players_in_game == players_count)
    	{
    		gboard.build_board();
    		alls = new player[players_count];
    		res.set_content( "Great\nGame created\n", "text/plain");
    		int place[4] ={0,120,10,110};
    		char namee = 65;
    		for (int q=0; q<players_count; q++)
    		{
    			alls[q].set_name(namee+q);
    			alls[q].set_place(gboard.theboard, place[q]);
    		}
    		
    	}
  	});
  	svr.Get("/help", [](const Request& req, Response& res) {
    	res.set_content(menu, "text/html" ); 
  	});
  	svr.Get("/print", [&gboard](const Request& req, Response& res) {
    	res.set_content(gboard.print_board(), "text/plain");
  	});
  	svr.Post("/wall", [&](const Request &req, Response &res, const ContentReader &content_reader)
  	{
  	string body;
      	content_reader([&](const char *data, size_t data_length) {
        body.append(data, data_length);
        auto wallres = alls[0].put_wall(gboard.theboard, body[0], str2int(body.substr(2)));
        res.set_content(wallres, "text/plain");
        return true;
      	});});
      	svr.Post("/move", [&](const Request &req, Response &res, const ContentReader &content_reader)
  	{
  	string body;
      	content_reader([&](const char *data, size_t data_length) {
        body.append(data, data_length);
        string result = alls[str2int(body.substr(0,1))-1].go(gboard.theboard, body[4]);
        res.set_content(  result, "text/plain");
        return true;
      	});});
  	svr.listen("localhost", 8080);
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
string is_finish()
{
	string ans = "N";
	for (int q=0; q< players_count; q++)
	{
		if (alls[q].get_place() == win_place)
		{
			ans = "Player" + int2str(q+1);
		}
		break;
	}
	return ans;
}
