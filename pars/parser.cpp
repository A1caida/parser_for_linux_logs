#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <vector>

using namespace std;

int check(string a, vector<string> terms)
{
	for (size_t i = 0; i < terms.size(); i++)
	{
		if (a.find(terms[i])!=-1)
		{
			return 0;
		}	
	}
	return 1;
}

int main(int argc, char *argv[])
{
    ifstream logfile;
	string packet;
	int temp = 0;
	int temp1 = 0;
	int errorcount = 0;
	string link = argv[1];
	string name = argv[2];
	string term = argv[3];
	vector<string> terms;
	logfile.open(term);

	if (logfile)
	{
		string a;
		
		while (getline(logfile, a, '\n'))
		{
			terms.push_back(a);
		}
	}
	logfile.close();

    logfile.open(link);

	if (logfile)
	{	
		string a;
		string name;

		while (getline(logfile, a, '\n'))
		{
			if (a.find("Packet:") != -1)
			{
				temp1 = 0;
				name = "";
				packet += '\n'+ a +'\n';
				name.insert(0, a, a.find('[')+1,a.find(']')+1);

				name.erase(name.size() - 1);				
			}	
						
			if ((a.find(" (") != -1) && (temp1 == 0) && (a.find(name) != -1))
			{				
				string temps;
				temps.insert(0, a, a.find('('), a.find(')'));
				packet.insert(packet.find_last_of("[" + name + "]") + 1, " " + temps);
				temp1--;
			}

			if (temp == 1)
			{
				packet += a + '\n';
				temp = 0;
			}

			if (a.find(": ") != -1)
			{
				if (((a.find("dpkg:") != -1)|| (a.find("usermod:") != -1))&&(check(a,terms) != 1))
				{
					packet += a + '\n';
					temp++;
					errorcount++;					
				}
				else if ((a.find(": [") != -1) || (a.find(": /") != -1) || (a.find(": ") > 10)) {}
				else if(check(a,terms) != 1)
				{
					packet += a + '\n';
					errorcount++;	
				}							
			}		
		}
		logfile.close();
	}
	if (name == "-console")
	{
		cout << "Success "<< errorcount<<endl;
		cout <<packet<<endl;
		return 0;
	}
	
	name += "/"; name.insert(name.length() - 1, link, link.find_last_of("/"),link.length());
	name.erase(name.length() - 1); name += "_errors" + to_string(errorcount) + ".txt";
	ofstream Errorfile(name);

	if (Errorfile.is_open())
	{
		Errorfile << packet;
		cout << "Success "<< errorcount<<endl;
	}else
	{
		cout << "oops, try again "<<endl;
	}
	return 0;
}

