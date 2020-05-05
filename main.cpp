
#include <vector>
#include<queue>
#include <iostream>
#include <stdlib.h>
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
			cout << "hey" << endl;
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
				return 0; //nothing right of us so this move is impossible
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
		int GetManhattansteps(){
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
								dist += abs(xdiff) + abs(ydiff);
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

class PuzzleComparestepsOnly
{
public:
    bool operator() (Puzzle* p1, Puzzle* p2)
    {
        return p1->steps > p2->steps;
    }
};


int main(){
	vector<Puzzle*> exploredSet;
	priority_queue<Puzzle*,vector<Puzzle*>,PuzzleComparestepsOnly> pq;
	cout << "hey" << endl;
	Puzzle* p = new Puzzle(PUZSIZE);
	p->Print();
	cout << p->CheckIfSolved() << endl;
	Puzzle* p2 = p->MoveDown();
	p2->Print();
	cout << p2->CheckIfSolved() << endl;
	Puzzle* p3 = p2->MoveRight();
	p3->Print();
	cout << p3->CheckIfSolved() << endl;
	Puzzle* p4 = p3->MoveUp();
	p4->Print();
	cout << p4->CheckIfSolved() << endl;
	cout << p4->GetManhattansteps() << endl;
	pq.push(p);
	pq.push(p2);
	pq.push(p3);
	pq.push(p4);
	while (!pq.empty())
    {
        cout << pq.top()->steps << endl;
        pq.pop();
    }

}