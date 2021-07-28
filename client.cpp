#include <httplib.h>
#include <iostream>
using namespace std;
using namespace httplib;
char* space2slash(string);
char* command(string);
long long str2int(string );
string id;
string int2str(int);
int main()
{
	Client cil("localhost", 8080);
	if (auto res = cil.Get("/help"))
	{
		if(res -> status == 200)
		{
			cout << res->body << endl;
		}
		else
		{
			auto err = res.error();
		}
	}
	string ready = "n";
	string resp1 = cil.Get("/start")->body;
	while(cil.Post("/play",ready, "text/plain")->body == "no")
	{
		cout << resp1;
		if(resp1 != "Maximum players exceed!\n")
		{
			id = resp1.substr(6,1);
			cin >> ready;
		}
		else
		{
			return 0;
		}
	}
	cout << "Waiting for other players...\n";
	while(cil.Get("/is-started")->body == "no")
	{
	}
	cout << "Here is the board\n";
	cout << cil.Get("/print")->body << endl;
	cout << "And here is the positions of the cells:\n";
	cout << cil.Get("/pos")->body << endl;
	string winner = "N";
	int p_c = str2int(cil.Get("/players")->body);
	while (winner == "N")
	{
		if( cil.Post("/isme", id, "text/plain")->body == "yes")
		{
			cout << "Player" << id << ", What do you wanna do?\n";
			string action , wall_dir="", wall_pos= "";
			cin >> action;
			if (action == "wall")
			{
				string wallmode = "You can't put a wall here\n";
				while (wallmode.substr(0,3) == "You")
				{
					while(wall_dir != "v" && wall_dir != "h")
					{
						cout << "What is the direction of the wall??\nwrite 'h' for horizontal and 'v' for vertical\n";
						cin >> wall_dir;
						if (wall_dir != "v" && wall_dir != "h")
						{
							cout << "This is not a direction :(\n";
						}
					}
					cout << "what is the position of the wall?\n";
					cin >> wall_pos;
					auto res = cil.Post("/wall", wall_dir+wall_pos, "text/plain");
					wallmode = res->body;
					cout << wallmode << endl;
				}
				cout << cil.Get("/print")->body << endl;
				
			}
			else if (action == "move")
			{
				string mode = "fail";
				while (mode == "fail")
				{
					cout << "Where do you wanna go?\n'u' for up and 'd' for down\n'r' for right and 'l' for left\n";
					string dirc ;
					cin >> dirc;
					auto res = cil.Post("/move", id+dirc, "text/plain");
					if(res->body == "fail")
					{
						cout << "You can't go there!\n";
					}
					mode = res->body;
				}
				cout << cil.Get("/print")->body << endl;
			}
			else
			{
				cout << "You just can move or put a wall!\nTry again\n";
			}
			winner = cil.Get("/finish")->body;
		}
	}
	cout << "\t\t\tHooooooraaaaaaay\n\t\t\t    Congrates\n\t\t    " << winner << " has won the game\n"; 
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
