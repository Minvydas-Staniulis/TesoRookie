#include <iostream>
#include <fstream>

using namespace std;

class Game 
{
private:
	int n = 0;
	int w = 0;
	int h = 0;
	char checker;
	char playground[1000][1000];
	int xpos, ypos;
	int neighbour = 0;
	int network = 0;
	int malware = 0;
	int firewall = 0;
	int health = 0;
	int infected = 0;


public:

	void readFromFile()
	{
		ifstream input("input.txt");
		input >> n >> w >> h;

		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				input >> playground[i][j];
			}
		}
		input.close();
	}
	void print()
	{
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				cout << playground[i][j];
			}
			cout << endl;
		}
	}
	//h lines of w characters
	void moves()
	{
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				checker = playground[i][j];
				xpos = i;
				ypos = j;
				//Network cell
				neighbours();
				if (checker == '.')
				{
					if (malware >= 2 && malware < 5)
						playground[i][j] = '*';
					if (health == 2)
						playground[i][j] = 'f';
					if (infected >= 1)
						playground[i][j] = '*';
					
				}
				//Malware cell
				else if (checker == '*')
				{
					if(network == 8)
						playground[i][j] = '.';
					if(firewall >= 2)
						playground[i][j] = 'f';
					if(malware > 5)
						playground[i][j] = '.';
					if(health >= 1)
						playground[i][j] = '.';
				}
				//FireWall cell
				else if (checker == 'f')
				{
					if(malware >= 5)
						playground[i][j] = '.';
				}
				//Healthy cell
				else if (checker == 'o')
				{
					if(malware >= 1)
						playground[i][j] = 'x';
				}
				//Infected cell
				else if (checker == 'x')
				{
					if(firewall == 8)
						playground[i][j] = 'o';
				}
			}
		}
	}
	//boundaries
	void neighbours()
	{
		char temp[8];
		neighbour = 0;
		network = 0;
		malware = 0;
		firewall = 0;
	    health = 0;
		infected = 0;
		temp[0] = playground[xpos][ypos + 1];
		temp[1] = playground[xpos + 1][ypos + 1];
		temp[2] = playground[xpos + 1][ypos];
		temp[3] = playground[xpos + 1][ypos - 1];
		temp[4] = playground[xpos][ypos - 1];
		temp[5] = playground[xpos - 1][ypos - 1];
		temp[6] = playground[xpos - 1][ypos];
		temp[7] = playground[xpos - 1][ypos + 1];
		for (int i = 0; i < 8; i++)
		{
			if (temp[i] == '.')
			{
				network++;
			}
			else if (temp[i] == '*')
			{
				malware++;
			}
			else if (temp[i] == 'f')
			{
				firewall++;
			}
			else if (temp[i] == 'o')
			{
				health++;
			}
			else if (temp[i] == 'x')
			{
				infected++;
			}
		}
		
	}
	void play()
	{
		readFromFile();
		for (int i = 0; i < n; i++)
		{
			print();
			moves();
			cout << endl;
		}
		
	}
};

int main()
{
	Game newgame;
	newgame.play();


	return 0;
}