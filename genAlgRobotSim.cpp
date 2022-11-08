//final.cpp
//Safwan Ali
//Fowler
//December 16 2021
//CISP 400

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//Generates grid
class createGrid {
public:
	int grid[10][10];
	void newGrid();
	int gridNum(int y, int z);
	int changeGridNum(int y, int z, int w);
	void printGrid();

};
void createGrid::newGrid() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			grid[i][j] = 0;
		}
	}
	for (int i = 0; i < 40; i++) {
		int legitAns = 0;
		while (legitAns == 0) {
			int clmn = rand() % 10;
			int rw = rand() % 10;
			if (grid[clmn][rw] == 0) {
				grid[clmn][rw] = 1;
				legitAns = 1;
			}
		}
	}
}

void createGrid::printGrid() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
int createGrid::gridNum(int y, int z) {
	return grid[y][z];
}
int createGrid::changeGridNum(int y, int z, int w) {
	return grid[y][z] = w;
}
//creates generation of robots
class makeRobot {
public:
	int robots[200][16][5];
	void setGenes();
	void genePrint();
	void printRobot(int i);
	int getRobotValue(int y, int z, int x);
	int editRobotValue(int y, int z, int x, int w);
};

void makeRobot::setGenes() {
	for (int i = 0; i < 200; i++) {
		for (int j = 0; j < 16; j++) {
			for (int n = 0; n < 4; n++) {
				robots[i][j][n] = rand() % 3;
			}
			robots[i][j][4] = rand() % 5;
		}
	}
}
void makeRobot::genePrint() {
	for (int i = 0; i < 200; i++) {
		cout << "Robot " << i + 1 << endl;

		for (int j = 0; j < 16; j++) {
			for (int n = 0; n < 5; n++) {
				cout << robots[i][j][n] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
}
void makeRobot::printRobot(int y) {
	cout << "Robot " << y + 1 << endl;
	for (int j = 0; j < 16; j++) {
		for (int n = 0; n < 5; n++) {
			cout << robots[y][j][n] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
int makeRobot::getRobotValue(int y, int z, int x) {
	return robots[y][z][x];
}
int makeRobot::editRobotValue(int y, int z, int x, int w) {
	return robots[y][z][x] = w;
}


int main() {
	unsigned int seed;
	seed = time_t(0);
	srand(seed);

	createGrid grid;

	makeRobot robots;
	robots.setGenes();

	const int numGenerations = 20;
	int avgFitness[numGenerations];


	for (int g = 0; g < numGenerations; g++) {
		int robotFitness[200][2];

		cout << endl;

		for (int r = 0; r < 200; r++) {
			grid.newGrid();

			int power = 5;
			int fitness = 0;
			int north = 0,
				south = 0,
				east = 0,
				west = 0;
			int move;
			int clmn = rand() % 10;
			int rw = rand() % 10;

			while (power > 0) {
				if (rw == 0) {
					north = 1;
				}
				if (rw == 9) {
					south = 1;
				}
				if (clmn == 0) {
					west = 1;
				}

				if (clmn == 9) {
					east = 1;
				}
				if (grid.gridNum(rw, clmn) == 1) {
					power = power + 5;
					fitness = fitness + 5;
				}
				grid.changeGridNum(rw, clmn, 0);

				if (grid.gridNum(rw - 1, clmn) == 1) {
					north = 2;
				}
				if (grid.gridNum(rw + 1, clmn) == 1) {
					south = 2;
				}
				if (grid.gridNum(rw, clmn + 1) == 1) {
					east = 2;
				}
				if (grid.gridNum(rw, clmn - 1) == 1) {
					west = 2;
				}
				for (int j = 0; j < 16; j++) {
					if (north == robots.getRobotValue(r, j, 0) and south == robots.getRobotValue(r, j, 1) and south == robots.getRobotValue(r, j, 2) and south == robots.getRobotValue(r, j, 3)) {
						move = robots.getRobotValue(r, j, 4);
					}
					else {
						move = robots.getRobotValue(r, 15, 4);
					}
				}
				if (move == 0) {
					move = rand() % 4 + 1;
				}
				if (move == 1 && rw != 0) {
					rw--;
				}
				else if (move == 2 && rw != 9) {
					rw++;
				}
				else if (move == 3 && clmn != 0) {
					clmn--;
				}
				else if (move == 4 && clmn != 0) {
					clmn++;
				}
				else {
					rw = rw + 0;
					clmn = clmn + 0;
				}
				power--;

			}
			robotFitness[r][0] = fitness;
			robotFitness[r][1] = r;
			cout << "Robot #" << g + 1 << "_" << r + 1 << " collected " << fitness << " power." << endl;
		}

		// sort robot fitness scores in array in descending order
		qsort(robotFitness, 200, sizeof(*robotFitness), [](const void* botFitness1, const void* botFitness2)->int {
			int const* left = static_cast<int const*> (botFitness1);
			int const* right = static_cast<int const*> (botFitness2);
			return (left[0] < right[0]) ? -1
				: ((right[0] < left[0]) ? 1
					: (left[1] < right[1] ? -1
						: ((right[1] < left[1] ? 1 : 0))));
			});
		//temporary array to hold robots for reproduction
		int tempRobots[200][16][5];

		for (int y = 0; y < 100; y = y + 2) {
			for (int x = 0; x < 8; x++) {
				for (int z = 0; z < 5; z++) {
					tempRobots[y][x][z] = robots.getRobotValue(robotFitness[y + 99][1], x, z);
					tempRobots[y + 1][x][z] = robots.getRobotValue(robotFitness[y + 100][1], x, z);
				}
			}
			for (int x = 8; x < 16; x++) {
				for (int z = 0; z < 5; z++) {
					tempRobots[y][x][z] = robots.getRobotValue(robotFitness[y + 100][1], x, z);
					tempRobots[y + 1][x][z] = robots.getRobotValue(robotFitness[y + 99][1], x, z);
				}
			}
		}
		//reproduce robots using genes of parent bots
		for (int y = 100; y < 200; y++) {
			for (int x = 0; x < 16; x++) {
				for (int z = 0; z < 5; z++) {
					tempRobots[y][x][z] = robots.getRobotValue(robotFitness[y][1], x, z);
				}
			}
		}
		for (int i = 0; i < 200; i++) {
			for (int j = 0; j < 16; j++) {
				for (int n = 0; n < 5; n++) {
					robots.editRobotValue(i, j, n, tempRobots[i][j][n]);
				}
			}
		}
		cout << endl;
		//find avg fitness for generation and save in array
		int totalPower = 0;
		for (int r = 0; r < 200; r++) {
			totalPower = totalPower + robotFitness[r][0];
		}
		avgFitness[g] = (totalPower / 200);
	}
	//display average fitness for each generation
	cout << "======================================================" << endl << endl;
	for (int y = 0; y < numGenerations; y++) {
		cout << "The average fitness for generation " << y + 1 << " was " << avgFitness[y] << endl;
		cout << endl;
	}
	cout << "This is the plot of the average fitness per generation. Generation number is on left." << endl;
	cout << "Distance from left axis is value for average fitness. " << endl << endl;
	for (int i = 0; i < numGenerations; i++) {
		cout << i + 1 << ": " << avgFitness[i];
		for (int s = 0; s < avgFitness[i]; s++) {
			cout << " ";
		}
		cout << "*" << endl;
	}
	return 0;
}