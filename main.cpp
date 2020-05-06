
#include <vector>
#include<queue>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#define PUZSIZE 3 //puzzle size is 3
using namespace std;
class Puzzle{
	public:
		unsigned int size;
		unsigned int spacex;
		unsigned int spacey;
		unsigned int steps = 0;
		vector<vector<int>*>* puz;
		int dist = -1;
		Puzzle(unsigned int s){
			size = s;
			int num = 1;
			puz = new vector<vector<int>*>();//create the vector vector (:
			for (unsigned int i = 0; i < size; i++){
				vector<int>* row = new vector<int>();//create vector for the vector vector (((:
				puz->push_back(row);
			}
			for (unsigned int y = 0; y < size; y++){
				for (unsigned int x = 0; x < size; x++){
					puz->at(x)->push_back(num);
					if (y == x && y == size - 1){
						puz->at(x)->at(y) = 0;
					}
					num++;
				}
			}
			spacex = 2;
			spacey = 2;
		}
		Puzzle(unsigned int s, unsigned int sx, unsigned int sy, vector<vector<int>*>* p){
			size = s;
			spacex = sx;
			spacey = sy;
			puz = p;
			dist = -1;
		}
		Puzzle(unsigned int s, vector<vector<int>*>* p){
			size = s;
			puz = p;
			dist = -1;
			for (unsigned int y = 0; y < size; y++){
				for (unsigned int x = 0; x < size; x++){
					if (puz->at(x)->at(y) == 0){
						spacex = x;
						spacey = y;
						break;
					}
				}
			}
		}
		void Print(){
			for (unsigned int y = 0; y < size; y++){
				for (unsigned int x = 0; x < size; x++){
					cout << puz->at(x)->at(y) << " ";
				}
				cout << endl;
			}
		}
		bool CheckIfSolved(){
			unsigned int num = 1;
			bool solved = true;
			for (unsigned int y = 0; y < size; y++){
				for (unsigned int x = 0; x < size; x++){
					if (y == x && y == size - 1){
						solved = puz->at(x)->at(y) == 0;
					}
					else{
						solved = puz->at(x)->at(y) == num;
					}
					if (!solved){break;}
					num++;
				}
				if (!solved){break;}
			}
			return solved;
		}
		vector<vector<int>*>* Clone(){
			vector<vector<int>*>* newPuz = new vector<vector<int>*>();//create the vector vector (:
			for (unsigned int i = 0; i < size; i++){
				vector<int>* row = new vector<int>();//create vector for the vector vector (((:
				newPuz->push_back(row);
			}
			for (unsigned int y = 0; y < size; y++){
				for (unsigned int x = 0; x < size; x++){
					newPuz->at(x)->push_back(puz->at(x)->at(y));
				}
			}
			return newPuz;
		}
		Puzzle* MoveDown(){
			if (spacey == 0){
				return 0; //nothing above us so this move is impossible
			}
			vector<vector<int>*>* newPuz = Clone();
			newPuz->at(spacex)->at(spacey) = puz->at(spacex)->at(spacey-1);
			newPuz->at(spacex)->at(spacey-1) = 0;
			Puzzle* p = new Puzzle(PUZSIZE,spacex,spacey-1, newPuz);
			p->steps = steps + 1;
			return p;
		}
		Puzzle* MoveUp(){
			if (spacey == size-1){
				return 0; //nothing below us so this move is impossible
			}
			vector<vector<int>*>* newPuz = Clone();
			newPuz->at(spacex)->at(spacey) = puz->at(spacex)->at(spacey+1);
			newPuz->at(spacex)->at(spacey+1) = 0;
			Puzzle* p = new Puzzle(PUZSIZE,spacex,spacey+1, newPuz);
			p->steps = steps + 1;
			return p;
		}
		Puzzle* MoveLeft(){
			if (spacex == size-1){
				return 0; //nothing left of us so this move is impossible
			}
			vector<vector<int>*>* newPuz = Clone();
			newPuz->at(spacex)->at(spacey) = puz->at(spacex+1)->at(spacey);
			newPuz->at(spacex+1)->at(spacey) = 0;
			Puzzle* p = new Puzzle(PUZSIZE,spacex+1,spacey, newPuz);
			p->steps = steps + 1;
			return p;
		}
		Puzzle* MoveRight(){
			if (spacex == 0){
				return 0; //nothing left of us so this move is impossible
			}
			vector<vector<int>*>* newPuz = Clone();
			newPuz->at(spacex)->at(spacey) = puz->at(spacex-1)->at(spacey);
			newPuz->at(spacex-1)->at(spacey) = 0;
			Puzzle* p = new Puzzle(PUZSIZE,spacex-1,spacey, newPuz);
			p->steps = steps + 1;
			return p;
		}
		~Puzzle(){
			while (puz->size()){
				while (puz->at(puz->size()-1)->size()){
					puz->at(puz->size()-1)->pop_back();
				}
				delete puz->at(puz->size()-1);
				puz->pop_back();
			}
			delete puz;
		}
		bool CheckIfEqual(Puzzle* p2){
			for (unsigned int y = 0; y < size; y++){
				for (unsigned int x = 0; x < size; x++){
					if (puz->at(x)->at(y) != p2->puz->at(x)->at(y)){
						return false;
					}
				}
			}
			return true;
		}
		int GetEuclidian(){
			if (dist > -1){
				return dist;
			}
			dist = 0;
			unsigned int currnum = 1;
			for (int y = 0; y < size; y++){
				for (int x = 0; x < size; x++){
					bool breaking = false;
					if (x == y && x == size-1){
						break;
					}
					for ( int y2 = 0; y2 < size; y2++){
						for (int x2 = 0; x2 < size; x2++){
							if (currnum == puz->at(x2)->at(y2)){
								int xdiff = x2 - x;
								int ydiff = y2 - y;
								dist += sqrt(xdiff*xdiff + ydiff*ydiff);
								breaking = true;
							}
							if (breaking){break;}
						}
						if (breaking){break;}
					}
					currnum++;
				}
			}
			return dist;
		}

};

bool FindPuzzle(vector<Puzzle*>* eset, Puzzle* p){
	for (unsigned int i = 0; i < eset->size(); i++){
		if (eset->at(i)->CheckIfEqual(p)){
			if (eset->at(i)->steps > p->steps){
				delete eset->at(i);
				eset->at(i) = p;
			}
			return true;
		}
	}
	return false;
}

class PuzzleCompareStepsOnly
{
public:
    bool operator() (Puzzle* p1, Puzzle* p2)
    {
        return p1->steps > p2->steps;
    }
};

class PuzzleCompareGreedy
{
public:
    bool operator() (Puzzle* p1, Puzzle* p2)
    {
        return p1->GetEuclidian() > p2->GetEuclidian();
    }
};

class PuzzleCompareAStar
{
public:
    bool operator() (Puzzle* p1, Puzzle* p2)
    {
        return (p1->GetEuclidian()+p1->steps) > (p2->GetEuclidian()+p2->steps);
    }
};

void BreadthFirstSearch(Puzzle* initialPuzzle){
	vector<Puzzle*> exploredSet;
	priority_queue<Puzzle*,vector<Puzzle*>,PuzzleCompareStepsOnly> frontier;
	unsigned int numNodes = 1;
	unsigned int maxNodes = 1;
	frontier.push(initialPuzzle);
	bool found = false;
	Puzzle* sol = 0;
	while (frontier.size()){
		Puzzle* curr = frontier.top();
		frontier.pop();
		if (curr->CheckIfSolved()){
			found = true;
			sol = curr;
			break;
		}
		exploredSet.push_back(curr);
		Puzzle* left = curr->MoveLeft();
		if (left){
			if (!FindPuzzle(&exploredSet,left)){
				frontier.push(left);
				numNodes++;
			}
		}
		Puzzle* right = curr->MoveRight();
		if (right){
			if (!FindPuzzle(&exploredSet,right)){
				frontier.push(right);
				numNodes++;
			}
		}
		Puzzle* up = curr->MoveUp();
		if (up){
			if (!FindPuzzle(&exploredSet,up)){
				frontier.push(up);
				numNodes++;
			}
		}
		Puzzle* down = curr->MoveDown();
		if (down){
			if (!FindPuzzle(&exploredSet,down)){
				frontier.push(down);
				numNodes++;
			}
		}
		if (frontier.size() > maxNodes){maxNodes  = frontier.size();}
	}
	if (found){
		cout << "Solution found after creating " << numNodes << " nodes and a max of " << maxNodes << " in the queue at a time. Printing puzzle:" << endl;
		sol->Print();
		cout << "Number of steps taken: " << sol->steps << endl;
	}
	else{
		
		cout << "No solution found after creating " << numNodes << " and a max of " << maxNodes << " in the queue at a time." << endl;
	}
}

void GreedySearch(Puzzle* initialPuzzle){
	vector<Puzzle*> exploredSet;
	priority_queue<Puzzle*,vector<Puzzle*>,PuzzleCompareGreedy> frontier;
	unsigned int numNodes = 1;
	unsigned int maxNodes = 1;
	frontier.push(initialPuzzle);
	bool found = false;
	Puzzle* sol = 0;
	while (frontier.size()){
		Puzzle* curr = frontier.top();
		frontier.pop();
		if (curr->CheckIfSolved()){
			found = true;
			sol = curr;
			break;
		}
		exploredSet.push_back(curr);
		Puzzle* left = curr->MoveLeft();
		if (left){
			if (!FindPuzzle(&exploredSet,left)){
				frontier.push(left);
				numNodes++;
			}
		}
		Puzzle* right = curr->MoveRight();
		if (right){
			if (!FindPuzzle(&exploredSet,right)){
				frontier.push(right);
				numNodes++;
			}
		}
		Puzzle* up = curr->MoveUp();
		if (up){
			if (!FindPuzzle(&exploredSet,up)){
				frontier.push(up);
				numNodes++;
			}
		}
		Puzzle* down = curr->MoveDown();
		if (down){
			if (!FindPuzzle(&exploredSet,down)){
				frontier.push(down);
				numNodes++;
			}
		}
		if (frontier.size() > maxNodes){maxNodes  = frontier.size();}
	}
	if (found){
		cout << "Solution found after creating " << numNodes << " nodes and a max of " << maxNodes << " in the queue at a time. Printing puzzle:" << endl;
		sol->Print();
		cout << "Number of steps taken: " << sol->steps << endl;
	}
	else{
		
		cout << "No solution found after creating " << numNodes << " and a max of " << maxNodes << " in the queue at a time." << endl;
	}
}

void AStarSearch(Puzzle* initialPuzzle){
	vector<Puzzle*> exploredSet;
	priority_queue<Puzzle*,vector<Puzzle*>,PuzzleCompareAStar> frontier;
	unsigned int numNodes = 1;
	unsigned int maxNodes = 1;
	frontier.push(initialPuzzle);
	bool found = false;
	Puzzle* sol = 0;
	while (frontier.size()){
		Puzzle* curr = frontier.top();
		frontier.pop();
		if (curr->CheckIfSolved()){
			found = true;
			sol = curr;
			break;
		}
		exploredSet.push_back(curr);
		Puzzle* left = curr->MoveLeft();
		if (left){
			if (!FindPuzzle(&exploredSet,left)){
				frontier.push(left);
				numNodes++;
			}
		}
		Puzzle* right = curr->MoveRight();
		if (right){
			if (!FindPuzzle(&exploredSet,right)){
				frontier.push(right);
				numNodes++;
			}
		}
		Puzzle* up = curr->MoveUp();
		if (up){
			if (!FindPuzzle(&exploredSet,up)){
				frontier.push(up);
				numNodes++;
			}
		}
		Puzzle* down = curr->MoveDown();
		if (down){
			if (!FindPuzzle(&exploredSet,down)){
				frontier.push(down);
				numNodes++;
			}
		}
		if (frontier.size() > maxNodes){maxNodes  = frontier.size();}
	}
	if (found){
		cout << "Solution found after creating " << numNodes << " nodes and a max of " << maxNodes << " in the queue at a time. Printing puzzle:" << endl;
		sol->Print();
		cout << "Number of steps taken: " << sol->steps << endl;
	}
	else{
		
		cout << "No solution found after creating " << numNodes << " and a max of " << maxNodes << " in the queue at a time." << endl;
	}
}


int main(){
	vector<vector<int>*>* initialState = new vector<vector<int>*>();
	for (unsigned int i = 0; i < PUZSIZE; i++){
		vector<int>* row = new vector<int>();//create vector for the vector vector (((:
		initialState->push_back(row);
	}
	int typeSelector = -1;
	while (typeSelector != 1 && typeSelector != 2){
		cout << "Type 1 to use a predefined puzzle or type 2 to use a custom puzzle" << endl;
		cin >> typeSelector;
	}
	Puzzle* initialPuzzle = 0;
	if (typeSelector == 1){
		initialState->at(0)->push_back(0);
		initialState->at(1)->push_back(1);
		initialState->at(2)->push_back(2);
		initialState->at(0)->push_back(4);
		initialState->at(1)->push_back(5);
		initialState->at(2)->push_back(3);
		initialState->at(0)->push_back(7);
		initialState->at(1)->push_back(8);
		initialState->at(2)->push_back(6);
		cout<< "thank you! printing the default puzzle" << endl;
		initialPuzzle = new Puzzle(PUZSIZE,initialState);
		initialPuzzle->Print();
	}
	if (typeSelector == 2){
		int inputnum;
		cout << "Please input the puzzle's numbers from left to right, top to bottom. Meaning start from top left, then top middle, then top right, then middle left..." << endl;
		cout << "Use 0 to represent the empty slot." << endl;
		cin >> inputnum;
		initialState->at(0)->push_back(inputnum);
		cout<< endl << "next number: ";
		cin >> inputnum;
		initialState->at(1)->push_back(inputnum);
		cout<< endl << "next number: ";
		cin >> inputnum;
		initialState->at(2)->push_back(inputnum);
		cout<< endl << "next number: ";
		cin >> inputnum;
		initialState->at(0)->push_back(inputnum);
		cout<< endl << "next number: ";
		cin >> inputnum;
		initialState->at(1)->push_back(inputnum);
		cout<< endl << "next number: ";
		cin >> inputnum;
		initialState->at(2)->push_back(inputnum);
		cout<< endl << "next number: ";
		cin >> inputnum;
		initialState->at(0)->push_back(inputnum);
		cout<< endl << "next number: ";
		cin >> inputnum;
		initialState->at(1)->push_back(inputnum);
		cout<< endl << "next number: ";
		cin >> inputnum;
		initialState->at(2)->push_back(inputnum);
		cout<< endl << "thank you! printing the entered puzzle" << endl;
		initialPuzzle = new Puzzle(PUZSIZE,initialState);
		initialPuzzle->Print();
	}
	typeSelector = -1;
	while (typeSelector != 1 && typeSelector != 2 && typeSelector != 3){
		cout << "Type 1 to use breadth-first search, type 2 to use a greedy algorithm, and type 3 to use A*" << endl;
		cin >> typeSelector;
	}
	if (typeSelector == 1){
		cout<< endl << "thank you! solving the puzzle" << endl;
		BreadthFirstSearch(initialPuzzle);
	}
	if (typeSelector == 2){
		cout<< endl << "thank you! solving the puzzle" << endl;
		GreedySearch(initialPuzzle);
		
	}
	if (typeSelector == 3){
		cout<< endl << "thank you! solving the puzzle" << endl;
		AStarSearch(initialPuzzle);
		
	}
	
}