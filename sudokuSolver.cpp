#include<iostream>
#include<fstream>
#include<string>
#include<chrono>


#define N 9


void printBoard(int arr[N][N]) {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (arr[i][j] == 0) std::cout << " ";
			else std::cout << arr[i][j];

			if (j == (N - 1)) std::cout << std::endl;
			else std::cout << " ";
		}
	}

}


// check if it is legal to assign number to given col, row
bool isLegalMove(int arr[N][N], int row, int col, int num) {
	
	// check row
	for (int x = 0; x < N; x++) 
		if (arr[row][x] == num) return false;
	
	
	// check column
	for (int y = 0; y < N; y++) 
		if (arr[y][col] == num) return false;
	

	// check 3x3 matrix
	int startRow = row - (row % 3),
		startCol = col - (col % 3);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (arr[i + startRow][j+startCol] == num)return false;
		}
	}

	
	return true; 
}
bool solver(int arr[N][N], int row, int col) { 
	
	// check if 8th row and 9th column is reached
	// and return true to avoid further backtracking
	if (row == N - 1 && col == N) return true;

	//start next row if we reach the end of current row
	if (col == N) {
		col = 0;
		row++;
	}

	// skip current position if already filled
	if (arr[row][col] > 0) return solver(arr, row, col + 1);

	for (int num = 1; num <= N; num++) {
		if (isLegalMove(arr, row, col, num)) {
			// if it number is legal, assign it
			arr[row][col] = num;

			// begin recursive solving
			// and move to next number in the row
			if (solver(arr, row, col + 1)) return true;
		}


		// reset back to 0 if assumption is wrong
		// try again with a new number
		arr[row][col] = 0;

	}
	
	
	return false; 
}



int main() {

	int sudokuBoard[N][N];
	int solution[N][N];
	std::string reader;
	std::ifstream sudokuInput;
	sudokuInput.open("input.txt");
	
	//check if file is open
	if (sudokuInput.is_open()) {

		while (sudokuInput) {
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++) {
					sudokuInput >> sudokuBoard[i][j];
					solution[i][j] = sudokuBoard[i][j];
				}
		}

		sudokuInput.close();
	}
	else {
		std::cout << "ERR: Cannot open file." << "\n" << std::endl;
	}


	// timing the algorithm
	auto start = std::chrono::high_resolution_clock::now();
	if (solver(solution, 0, 0)) {

		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

		std::cout << "|SOLVED!|" << std::endl;
		std::cout << "---------" << std::endl;
		std::cout << "ORIGINAL" << std::endl;
		printBoard(sudokuBoard);
		std::cout << "==================" << std::endl;
		std::cout << "==================" << std::endl;
		std::cout << "SOLUTION" << std::endl;
		printBoard(solution);

		std::cout << "" << std::endl;
		std::cout << "Sudoku board solved in " << duration.count() << " microseconds" << std::endl;

	}
	else std::cout << "No solution exists :( " << std::endl;



	return 0;
}