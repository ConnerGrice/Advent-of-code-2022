#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//Represents a grid of trees of different heights
class Grid {
public:
	Grid(std::ifstream& inputFile) {
		std::string line;
		while (std::getline(inputFile, line)) {
			std::vector<int> row;
			for (int i = 0; i < line.length(); i++) {
				//Convert each tree in a row into an int from 0-9
				row.push_back(line.at(i) - '0');
			}
			grid.push_back(row);
		}
		sideLength = grid.size();
	}
	Grid(std::vector < std::vector<int>> inputGrid) {
		grid = inputGrid;
		sideLength = grid.size();
	}

	//Gets parameter of grid
	int outerPoints() {
		return sideLength * 4 - 4;
	}
public:
	std::vector<std::vector<int>> grid;
	size_t sideLength;

};

//Represents an elf viewing the forest from a selected side
class Viewer {
public:
	const Grid& viewingGrid;

	Viewer(Grid& forestGrid) : viewingGrid(forestGrid) {}
	
	//Represents the elf looking at a row of trees from the right side of the grid (East).
	// Returns the index of the tallest tree that can be seen
	int FindTallestRight(int rowFromTop) {
		std::vector<int> row = viewingGrid.grid[rowFromTop];

		int tempTallest = 0;
		int tempIndex = viewingGrid.sideLength;

		for (int i = viewingGrid.sideLength - 1; i > 0; i--) {
			if (row[i] > tempTallest) {
				tempTallest = row[i];
				tempIndex = i;
				std::cout << "Height: " << tempTallest << " - Index: " << tempIndex << std::endl;
			}
		}
		return tempIndex;
	}

	//Represents an else looking at a row of trees from the left side. Returns the index of the tallest tree
	int FindTallestLeft(int rowFromTop) {
		std::vector<int> row = viewingGrid.grid[rowFromTop];
		int tempTallest = 0;
		int tempIndex = 0;

		for (int i = 0; i < viewingGrid.sideLength; i++) {
			if (row[i] <= tempTallest) continue;
			tempTallest = row[i];
			tempIndex = i;
			std::cout << "Height: " << tempTallest << " - Index: " << tempIndex << std::endl;
		}
		return tempIndex;
	};

	int FindTallestTop(int columnFromLeft) {

	};

private:
	//Rotating grid by 90 degrees anti-clockwise
	Grid transpose() {
		std::vector<std::vector<int>> transposedGrid;
		std::vector<std::vector<int>> rotatedGrid;
		for (i = 0; i < viewingGrid.sideLength; i++) {
			for (j = 0; j < viewingGrid.sideLength; j++) {
				transposedGrid[j][i] = viewingGrid.grid[i][j];
			}
		}
		for (i = 0; i < viewingGrid.sideLength; i++) {
			for (j = 0; j < viewingGrid.sideLength/2; j++) {
				rotatedGrid[i][j] = transposedGrid[i][viewingGrid.sideLength-j-1];
			}
		}
		return Grid(rotatedGrid);
	}
};

int main() {
	std::ifstream forestScan("../input.txt");
	Grid forest(forestScan);
	Viewer elf(forest);
	int firstTallestRight = elf.FindTallestRight(0);
	int firstTallestLeft = elf.FindTallestLeft(0);
	std::cout << "Tallest true first row from right: " << firstTallestRight << std::endl;
	std::cout << "Tallest true first row from left : " << firstTallestLeft << std::endl;

}
