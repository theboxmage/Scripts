#include <iostream>
#include <string>
#include <vector>

#include "box.h"
using namespace std;

/**
* Row count needs to be changed to rowCount+1 for lines.
*/
Box::Box(int rowCount)
{
	boxRow = rowCount;
	//Refer to as array[x*SizeY+y]
	arraySize = ((2*rowCount)+1)*(rowCount+1);
	grid = new Line[arraySize];
	for(int i = 0; i < arraySize; i++)
	{
		grid[i].value = false;
		grid[i].degreesOfFreedom = 6;
		grid[i].x = i/(rowCount*2+1);
		grid[i].y = i%(rowCount*2+1);
	}
	boxes = new char[rowCount*rowCount];
	for(int i = 0; i < rowCount*rowCount; i++)
	{
		boxes[i] = ' ';
	}
	setupDOF();
	AIScore = 0;
	PlayerScore = 0;
	grid[boxRow*boxRow*2].degreesOfFreedom = 5;
}

int Box::abs(int x)
{
	if(x < 0)
	{
		return -1*x;
	}
	return x;
}

/**
*TO FIND A VERITCAL LINE. (2X-1), MIN(Y).
*TO FIND A HORIZONTAL LINE. (2MIN(X), Y)
*/
bool Box::update(string input, char player)
{
	int dot1;
	int dot2;
	int hold = fixString(input);
	dot1 = hold/100;
	dot2 = hold%100;

	if(abs(dot1/10 - dot2/10) > 1)
	{
		return false;
	}
	
	if(dot1/10 == dot2/10)//HORIZONTAL
	{
		int inputX = 2 * min(dot1%10, dot2%10) + 1;
		int inputY = dot1/10;
		return setter(inputY, inputX, player);//THE X AND Y HERE ARE BACKWARDS. 
		//Sadly, that is intentional because I am bad at planning ahead.
		//Due to how I implemented setter() and the array, this is how it turned out.
		//If it works, don't fix it.
	}
	else if(dot1%10 == dot2%10)
	{
		int inputX;
		int inputY;
		
		if(dot1%10 == 0)
		{
			inputX = 0;
		}
		else
		{
			inputX = 2*(dot1%10);
		}
		inputY = min(dot1/10, dot2/10);
		return setter(inputY, inputX, player);
	}
	else{
		return false;
	}
}

/**
*This will be called on every update to check if a box has been completed. 
*/
void Box::checkBoxes(int inputY, int inputX, char & player)
{
	bool complete = false;
	int hold = (inputY)*(boxRow*2+1)+inputX;
	if(inputX%2 == 0)
	{
	//VERTICAL 
		if(inputX != 0 && grid[hold-1].value && grid[hold-2].value && grid[hold+boxRow*2].value)
		{
			incrementPlayer(player);
			boxes[inputY*boxRow+inputX/2-1] = player;
			complete = true;
		}
		if(inputX != boxRow*2 && grid[hold+1].value && grid[hold+2].value && grid[hold+2+boxRow*2].value)
		{
			incrementPlayer(player);
			boxes[inputY*boxRow+inputX/2] = player;
			complete = true;
		}
	}
	else
	{
		if(inputY!=0)//ABOVE
		{
			if(grid[hold-boxRow*2].value && grid[hold-boxRow*2-1].value && grid[hold-boxRow*2-2].value)
			{
				incrementPlayer(player);
				boxes[inputY*boxRow+inputX/2-boxRow] = player;
				complete = true;
			}
		}
		if(inputY!=boxRow)//BELOW
		{
			if(grid[hold+1].value && grid[hold-1].value && grid[boxRow*2+hold+1].value)
			{
				incrementPlayer(player);
				boxes[inputY*boxRow+inputX/2] = player;complete = true;
			}
		}
	}
}

void Box::incrementPlayer(char & player)
{
	if(player == 'H')
	{
		PlayerScore++;
	}
	else
	{
		AIScore++;
	}
}

bool Box::setter(int x, int y, char & player)
{
	if(grid[(x)*(boxRow*2+1)+y].value)
	{
		return false;
	}

	grid[(x)*(boxRow*2+1)+y].value = true;
	checkBoxes(x, y, player);
	lowerDOF(x, y);
	return true;
}

void Box::lowerDOF(int x, int y) 
{
	int generic = boxRow*2+1;
	if(y%2 == 0)
	{
		if(x > 0)//-11
		{
			grid[(x)*(generic)+y-boxRow*2-1].degreesOfFreedom--;
		}
		if(y > 0)//-1 + 11
		{
			grid[(x)*(generic)+y-1].degreesOfFreedom--;
			grid[(x)*(generic)+y+boxRow*2].degreesOfFreedom--;
		}
		if(x < boxRow-1)
		{
			grid[(x)*(generic)+y+boxRow*2+1].degreesOfFreedom--;
		}
		if(y < boxRow*2)
		{
			grid[(x)*(generic)+y+boxRow*2+2].degreesOfFreedom--;
			grid[(x)*(generic)+y+1].degreesOfFreedom--;
		}
	}
	else
	{
		if(y > 1)
		{
			grid[(x)*(boxRow*2+1)+y-2].degreesOfFreedom--;
		}
		if(y < boxRow*2-1)
		{
			grid[(x)*(boxRow*2+1)+y+2].degreesOfFreedom--;
		}
		if(x < boxRow)
		{
			grid[(x)*(boxRow*2+1)+y+1].degreesOfFreedom--;
			grid[(x)*(boxRow*2+1)+y-1].degreesOfFreedom--;
		}
		if(x > 0)
		{
			grid[(x)*(boxRow*2+1)+y-boxRow*2].degreesOfFreedom--;
			grid[(x)*(boxRow*2+1)+y-boxRow*2-2].degreesOfFreedom--;
		}
	}
}

int Box::fixString(string input)
{
	string output;
	if(input.at(0) < 'a')
	{
		output = input.substr(1, 1) + input.substr(0, 1);
	}
	else
	{
		output = input.substr(0, 2);
	}
	if(input.at(input.length()-2) < 'a')
	{
		output += input.substr(input.length()-1, 1) + input.substr(input.length()-2, 1);
	}
	else
	{
		output += input.substr(input.length()-2);
	}
	int i = 1000*(output.at(0)-'a') + 100*(output.at(1)-'0'-1) + 10*(output.at(2)-'a') + (output.at(3)-'0'-1);
	return i;
}
void Box::setupDOF()
{
	grid[0].degreesOfFreedom = 3; // All of this mess is the outside corners
	grid[1].degreesOfFreedom = 3;
	grid[boxRow*2].degreesOfFreedom = 3;
	grid[boxRow*2-1].degreesOfFreedom = 3;
	grid[(boxRow*2+1)*(boxRow-1)].degreesOfFreedom = 3;
	grid[(boxRow*2+1)*(boxRow-1)+(boxRow*2)].degreesOfFreedom = 3;
	grid[(boxRow*2+1)*(boxRow-1)+(boxRow*2)+2].degreesOfFreedom = 3;
	grid[(boxRow*2+1)*(boxRow-1)+(boxRow*2)+boxRow*2].degreesOfFreedom = 3;
	for(int i = 1; i < boxRow-1; i++)//Outside Non-Corners
	{
		grid[i*2+1].degreesOfFreedom = 4;
		grid[boxRow*(boxRow*2+1)+2*i+1].degreesOfFreedom = 4;
	}
	for(int i = 1; i < boxRow-1; i++) // Outside Non-corners 
	{
		grid[boxRow*2+(boxRow*2+1)*i].degreesOfFreedom = 4;
		grid[(boxRow*2+1)*i].degreesOfFreedom = 4;
	}
	for(int i = 0; i < boxRow-1; i++)//Inside edge Horizontal
	{
		grid[i*2+2].degreesOfFreedom = 5;
		grid[(boxRow*2+1)*(boxRow-1)+i*2+2].degreesOfFreedom = 5;
	}
	for(int i = 1; i < boxRow; i++)
	{
		grid[i*(boxRow*2+1)+1].degreesOfFreedom = 5;
		grid[i*(boxRow*2+1)+2+boxRow+2].degreesOfFreedom = 5;
	}
	
}


void Box::printer()
{
	char row = ' ';
	for(int j = 0; j < boxRow; j++)
	{
		row = 'a' + j;
		cout << row << " ";
		int hold = j*(boxRow*2+1);
		for(int i = 0; i < boxRow; i++)
		{
			cout << '+';
			if(grid[hold+(i*2)+1].value)
			{
				cout << "-";
			}
			else
			{
				cout << " ";
				//cout << grid[hold+(i*2)+1].y;
			}
		}
		cout << '+' << endl << "  ";
		for(int i = 0; i <= boxRow; i++)
		{
			if(grid[hold+2*i].value)
			{
				cout << '|';
			}
			else
			{
				cout << ' ';
				//cout << grid[hold+2*i].y;
				
			}
			//cout << boxes[i*j];
			if((i*boxRow)+(j) < boxRow*boxRow)
			{
				cout << boxes[(j*boxRow)+(i)];
			}
		}
	cout << endl;
	}
	row++;
	cout << row++ << ' ';
	for(int i = 0; i < boxRow; i++)
	{
		cout << '+';
		if(grid[boxRow*(boxRow*2+1)+2*i+1].value)
		{
			cout << '-';
		}
		else
		{
			cout << ' ';
			//cout << grid[boxRow*(boxRow*2+1)+2*i+1].degreesOfFreedom;
		}
	}
	cout << '+' << endl << "  ";
	for(int i = 1; i < boxRow+2; i++)
	{
		cout << i << ' ';
	}

}

void Box::printScore()
{
	cout << endl << "You: " << PlayerScore << "    Me: " << AIScore << endl;
}

void Box::AIMove()
{
	if(PlayerScore+AIScore == boxRow*boxRow)
	{
		return;
	}
	char AI = 'C';
	vector<int> list;
	//list.push_back(0);
	int size = ((2*boxRow+1))*(boxRow);
	for(int i = 0; i < size ; i++)
	{
		if(!grid[i].value)
		{
			list.push_back(i);
		}
	}
	for(int i = 0; i < boxRow; i++)
	{
		if(!grid[(2*boxRow+1)*boxRow+i*2+1].value)
		{
			list.push_back((2*boxRow+1)*boxRow+i*2+1);
		}
	}
	bool three = false;
	rule1(list, three);
	if(three)
	{
		if(list.size()==1)
		{
			setter(grid[list[0]].x, grid[list[0]].y, AI);
			AIPrint(list[0]);
			AIMove();
		}
		else
		{
			rule2(list);
			if(list.size() == 1)
			{
				setter(grid[list[0]].x, grid[list[0]].y, AI);
				AIPrint(list[0]);
				AIMove();
			}
			rule3(list);
			if(list.size() == 1)
			{
				setter(grid[list[0]].x, grid[list[0]].y, AI);
				AIPrint(list[0]);
				AIMove();
			}
			else
			{
				rule4(list);
				setter(grid[list[0]].x, grid[list[0]].y, AI);
				AIPrint(list[0]);
				AIMove();
			}
		}
	}
	if(!three)
	{
		rule1p2(list);
		if(list.size() == 1)
		{
			setter(grid[list[0]].x, grid[list[0]].y, AI);
			AIPrint(list[0]);
		}
		else
		{
			rule2(list);
			if(list.size() == 1)
			{
				setter(grid[list[0]].x, grid[list[0]].y, AI);
				AIPrint(list[0]);
			}
			else
			{
				rule3(list);
				if(list.size() == 1)
				{
					setter(grid[list[0]].x, grid[list[0]].y, AI);
					AIPrint(list[0]);
				}
				else
				{
					rule4(list);
					setter(grid[list[0]].x, grid[list[0]].y, AI);
					AIPrint(list[0]);
				}
			}
		}
	}
}

void Box::rule1p2(vector<int> &hold)// I tried to use ((bool1? 1:0) but couldn't get it to work.
{
	for(int i = 0; i < hold.size(); i++)
	{
		bool test = false;
		if(grid[hold[i]].y%2 == 1)
		{
			if(grid[hold[i]].x < boxRow)
			{
				if(grid[hold[i]-1].value && grid[hold[i]+1].value)
				{
					test = true;
					hold[i]=hold.back();
					hold.pop_back();
					i =0;
				}
				else if(grid[hold[i]-1].value && grid[hold[i]+(boxRow)*2+1].value)
				{
					test = true;
					hold[i]=hold.back();
					hold.pop_back();
					i =0;
				}
				else if(grid[hold[i]+1].value && grid[hold[i]+(boxRow)*2+1].value)
				{
					test = true;
					hold[i]=hold.back();
					hold.pop_back();
					i =0;
				}
			}
			if(grid[hold[i]].x > 0 && !test)
			{
				if(grid[hold[i]-boxRow*2-1].value && grid[hold[i]-boxRow*2-2].value)
				{
					hold[i]=hold.back();
					hold.pop_back();
					i =0;
				}
				else if(grid[hold[i]-boxRow*2-1].value && grid[hold[i]-boxRow*2].value)
				{
					hold[i]=hold.back();
					hold.pop_back();
					i =0;
				}
				else if(grid[hold[i]-boxRow*2-2].value && grid[hold[i]-boxRow*2].value)
				{
					hold[i]=hold.back();
					hold.pop_back();
					i =0;
				}
			}
		}
		else
		{
			if(grid[hold[i]].y > 0)
			{
				if(grid[hold[i]-1].value && grid[hold[i]-2].value)
				{
					test = true;
					hold[i]=hold.back();
					hold.pop_back();
					i =0;
				}
				else if(grid[hold[i]-1].value && grid[hold[i]+boxRow*2-2].value)
				{
					test = true;
					hold[i]=hold.back();
					hold.pop_back();
					i =0;
				}
				else if(grid[hold[i]-2].value && grid[hold[i]+boxRow*2-2].value)
				{
					test = true;
					hold[i]=hold.back();
					hold.pop_back();
					i =0;
				}
			}
			if(grid[hold[i]].y < boxRow*2 && !test)
			{
				if(grid[hold[i]+1].value && grid[hold[i]+2].value)
				{
					test = true;
					hold[i]=hold.back();
					hold.pop_back();
					i =0;
				}
				else if(grid[hold[i]+1].value && grid[hold[i]+boxRow*2+1].value)
				{
					test = true;
					hold[i]=hold.back();
					hold.pop_back();
					i =0;
				}
				else if(grid[hold[i]+2].value && grid[hold[i]+boxRow*2+1].value)
				{
					test = true;
					hold[i]=hold.back();
					hold.pop_back();
					i =0;
				}
			}
		}
	}

}
void Box::rule4(vector<int> &hold)
{
	int maxY = hold[0];
	vector<int> temp;
	for(int i = 0; i < hold.size(); i++)
	{
		if(grid[hold[i]].x < maxY)
		{
			maxY = grid[hold[i]].x;
			temp.clear();
		}
		if(grid[hold[i]].x == maxY)
		{
			temp.push_back(hold[i]);
		}
	}
	hold = temp;
}

void Box::rule3(vector<int> &hold)
{
	int maxX = boxRow*2+1;
	vector<int> temp;
	for(int i = 0; i < hold.size(); i++)
	{
		if(grid[hold[i]].y < maxX)
		{
			maxX = grid[hold[i]].y;
			temp.clear();
		}
		if(grid[hold[i]].y == maxX)
		{
			temp.push_back(hold[i]);
		}
	}
	hold = temp;
}

bool Box::getline(int i)
{
	if(grid[i].value)
	{
		//cout << "TRUE";
		return true;
	}
	else{
		//cout << "FALSE";
		return false;
	}
}


void Box::AIPrint(int place)
{
	int y1=0;
	int y2=0;
	int x1= 0;
	int x2=0;
	if(grid[place].y%2 == 0)
	{
		y1 = grid[place].x;
		y2 = y1+1;
		x1 = grid[place].y/2+1;
		x2 = x1;
	}
	else
	{	
		y1 = grid[place].x;
		y2 = y1;
		x1 = grid[place].y/2+1;
		x2 = x1+1;
	}
	char yc = y1+'a';
	char y2c=y2+'a';
	cout << "I choose to connect dots " << yc << x1 << " and " << y2c << x2 << "." << endl;
	
	printer();
	printScore();
}

void Box::rule2(vector<int> &hold)
{
	int degrees = 0;
	vector<int> temp;
	for(int i = 0; i < hold.size(); i++)
	{
		if(grid[hold[i]].degreesOfFreedom > degrees)
		{
			temp.clear();
			degrees = grid[hold[i]].degreesOfFreedom;
		}
		if(grid[hold[i]].degreesOfFreedom == degrees)
		{
			temp.push_back(hold[i]);
		}
	}
	hold = temp;
}



void Box::rule1(vector<int> &hold, bool &three)
{
	char AI = 'C';
	vector<int> answer;
	for(int j = 0; j < boxRow; j++)
		{
		for(int i = 0; i < boxRow; i++)
		{
			int cLine=i*2+2;
			int jLine=j*(boxRow*2+1);
			
			if(grid[jLine+cLine-2].value && grid[jLine+cLine-1].value && grid[jLine+cLine].value && !grid[jLine+cLine+boxRow*2].value)
			{
				answer.push_back(jLine+cLine+boxRow*2);
			}
			else if(grid[jLine+cLine-2].value && grid[jLine+cLine-1].value && !grid[jLine+cLine].value && grid[jLine+cLine+boxRow*2].value)
			{
				answer.push_back(jLine+cLine);
			}
			else if(grid[jLine+cLine-2].value && !grid[jLine+cLine-1].value && grid[jLine+cLine].value && grid[jLine+cLine+boxRow*2].value)
			{
				answer.push_back(jLine+cLine-1);
			}
			else if(!grid[jLine+cLine-2].value && grid[jLine+cLine-1].value && grid[jLine+cLine].value && grid[jLine+cLine+boxRow*2].value)
			{
				answer.push_back(jLine+cLine-2);
			}
		}
	}
	if(answer.size() > 0)
	{
		hold = answer;
		three = true;
	}
}


int Box::getPlayerScore()
{
	return PlayerScore;
}

int Box::getAIScore()
{
	return AIScore;
}