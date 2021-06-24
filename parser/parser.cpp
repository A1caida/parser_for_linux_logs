#include <iostream>
#include <fstream>
#include <istream>
#include <string>


using namespace std;

int main()
{
    ifstream logfile;
	string packet;
	string fail;
	int temp=0;
	int temp1 = 0;
	ofstream Errorfile("C:/Users/A1caida/Desktop/bashtest/Errors.txt");
	Errorfile.close();

    logfile.open("C:\\Users\\A1caida\\Desktop\\bashtest\\logs\\30.05.2021T01_54_11_log.log", ios::binary);

	if (logfile)
	{	
		string a;
		string name;
		int t;
		while (getline(logfile, a, '\n'))
		{
			if (a.find("Packet:") != -1)
			{
				temp1 = 0;
				name = "";
				packet += '\n'+ a +'\n';
				name.insert(0, a, a.find('[')+1);
				name.erase(name.size() - 1);
				temp1++;
			}	
			
			if ((a.find(name + " (") != -1) && (temp1 == 1) &&(a.find(name) != -1))
			{
				t = 0;
				t = packet.find("[" + name + "]");
				t += name.length() + 2;
				string temps;
				temps.insert(0, a, a.find('('), a.find(')'));
				packet.insert(t, " " + temps);
				temp1--;
			}

			if (temp == 1)
			{
				packet += a + '\n';
				temp = 0;
			}

			if (a.find(": ") != -1)
			{
				if ((a.find("dpkg:") != -1)|| (a.find("usermod:") != -1))
				{
					packet += a + '\n';
					temp++;
				}
				else if ((a.find(": [") != -1) || (a.find(": /") != -1) || (a.find(": ") > 10)) {}
				else
				{
					packet += a + '\n';
				}							
			}		
		}
		logfile.close();
	}

	Errorfile.open("C:/Users/A1caida/Desktop/bashtest/Errors.txt");

	if (Errorfile.is_open())
	{
		Errorfile << packet;
		cout << "okok";
	}
}

