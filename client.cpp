#include <httplib.h>
#include <iostream>
using namespace std;
using namespace httplib;
char* space2slash(string);
char* command(string);
long long str2int(string );
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
	cout << "how many players we have?\n";
	string n;
	cin >> n;
	Params pl{ { "", n}};
	cil.Post("/play", pl);
	int p_c = str2int(n);
	for (int p=1; p <=  p_c; p++)
	{
		string mode="";
		while(mode != "y")
		{
			printf("Player%d, Are you ready (type 'y' for yes)? ",p);
			cin >> mode;
		}
		auto res = cil.Get("/start");
		cout << res->body << endl;
	}
	cout << "And here is the positions of the cells:\n";
	cout << cil.Get("/pos")->body << endl;
	int it=0;
	string winner = "N";
	while (winner == "N")
	{
		it++;
		if(it==p_c+1){ it=1;};
		string action , wall_dir="", wall_pos= "";
		cout << "Player" << it << " What do you wanna do?\n";
		cin >> action;
		if (action == "wall")
		{
			cout << "What is the direction of the wall??\nwrite 'h' for horizontal and 'v' for vertical\n";
			cin >> wall_dir;
			cout << "what is the position of the wall?\n";
			cin >> wall_pos;
			Params params{ { wall_dir , wall_pos}};
			auto res = cil.Post("/wall", params);
			cout << res->body << endl;
		}
		else if (action == "move")
		{
			string mode = "fail";
			while (mode == "fail")
			{
				cout << "Where do you wanna go?\n'u' for up and 'd' for down\n'r' for right and 'l' for left\n";
				string dirc ;
				cin >> dirc;
				Params mp{ {int2str(it) , dirc}};
				auto res = cil.Post("/move", mp);
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
			it--;
		}
		winner = cil.Get("/finish")->body;
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
