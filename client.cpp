#include <httplib.h>
#include <iostream>
using namespace std;
using namespace httplib;
char* space2slash(string);
char* command(string);
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
	while (true)
	{
		string action;
		cout << "What do you wanna do?\n";
		getline(cin, action);
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
