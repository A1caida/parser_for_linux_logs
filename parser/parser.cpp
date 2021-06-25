#include <iostream>
#include <fstream>
#include <istream>
#include <string>


using namespace std;

int main()
{
    ifstream logfile;
	string packet;
	int temp = 0;
	int temp1 = 0;
	int errorcount = 0;
	string link;
	string name;

	cout << "Link to the file: ";
	cin >> link;
	
	cout << "Link to folder where to save: ";
	cin >> name;

    logfile.open(link);//28.05.2021T04_09_38_log.log   27.05.2021T19_40_17_log.log   18.03.2021T02_19_15_log.log "C:/Users/A1caida/Desktop/bashtest/logs/21.10.2020T16_12_00_log.log"

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
				name.insert(0, a, a.find('[')+1);
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
				if ((a.find("dpkg:") != -1)|| (a.find("usermod:") != -1))
				{
					packet += a + '\n';
					temp++;
					errorcount++;
				}
				else if ((a.find(": [") != -1) || (a.find(": /") != -1) || (a.find(": ") > 10)) {}
				else
				{
					packet += a + '\n';
					errorcount++;
				}							
			}		
		}
		logfile.close();
	}

	name += "/";  name.insert(name.length() - 1, link, link.find_last_of("/"));
	name.erase(name.length() - 1); name += "_errors" + to_string(errorcount) + ".txt";
	ofstream Errorfile(name);

	if (Errorfile.is_open())
	{
		Errorfile << packet;
		cout << "Success "<< errorcount;
	}
}

