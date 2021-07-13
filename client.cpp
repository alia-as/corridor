#include <httplib.h>
#include <iostream>
using namespace std;
using namespace httplib;
char* space2slash(string);
char* command(string);
long long str2int(string );
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
	int it=0;
	while (true)
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
		if (auto res = cil.Get(command(action)))
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
	}
}
char* command(string text)
{
	text = " "+text;
	int n = text.size() ;
	char* ans = new char[n];
	for (int a=0; a< n; a++)
	{
		ans[a] = *"";
	}
	for (int a=0; a< n; a++)
	{
		if(text[a] == *" ")
		{
			ans[a] = *"/";
		}
		else
		{
			ans[a] = text[a];
		}
	}
	ans[n] = *"";
	return ans;
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
