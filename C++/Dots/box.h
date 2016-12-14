#ifndef BOXES_H
#define BOXES_H

#include <vector>	
#include <string>

using namespace std;

class Box
{
public:
		Box(int rowCount);
		
		bool update(string input, char player);
		
		// I don't have JUnit test cases and I adore
		// JUnit test cases. These three methods are my substitute.
		void printer();
		void AIMove();
		void getter();
		int getPlayerScore();
		int getAIScore();
			void printScore();
		
private:
	int fixString (string input);
	void AIPrint(int place);

	void rule1(vector<int> &hold, bool &three);
	void rule1p2(vector<int> &hold);
	void rule2(vector<int> &hold);
	void rule3(vector<int> &hold);
	void rule4(vector<int> &hold);
	void checkBoxes(int inputX, int inputY, char & player);
	void printChar();
	void incrementPlayer(char & player);
	void setupDOF();
	bool setter(int x, int y, char & player);
	void lowerDOF(int x, int y);
	struct Line {
		int degreesOfFreedom;
		bool value;
		int x;
		int y;
	};
	int abs(int x);
	int AIScore;
	int PlayerScore;
	bool getline(int i);
	char *boxes;
	Line *grid;
	int arraySize;
	int boxRow;
};

#endif