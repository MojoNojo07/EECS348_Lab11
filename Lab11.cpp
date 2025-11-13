#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>


using namespace std;

int dotProduct(vector<int> vector1, vector<int> vector2) {
    if (vector1.size() == vector2.size()) {
        int sum = 0;
        for(int i = 0; i < vector1.size(); i++) {
            sum += vector1[i] * vector2[i];
        }
        return sum;
    } else {
        return 0;
    }
}

vector<string> splitString(string input, char delimiter) {
    vector<string> split = {""};
    for (char character : input) {
        if (character == delimiter) {
            split.push_back("");
        } else {
            split.at(split.size() - 1) += character;
        }
    }

    return split;
} 

template <typename T> class Matrix {
    public:
        Matrix(int n) {
            this->_size = n;
            for(int i = 0; i < n; i++) {
                vector<T> row;
                for(int j = 0; j < n; j++) {
                    row.push_back(0);
                }
                matrix.push_back(row);
            }
        }

        int size() {
            return this->_size;
        }

        void set(int row, int col, T entry) {
            matrix[row][col] = entry;
        }

        T get(int row, int col) {
            return matrix[row][col];
        }

        void print() {
            for(int i = 0; i < this->size(); i++) {
                for(int j = 0; j < this->size(); j++) {
                    cout << setw(2) << get(i, j) << ' ';
                }
                cout << endl;
            }
        }

        void setRow(int rowIndex, vector<T> row) {
            matrix[rowIndex] = row;
        }

        vector<T> getRow(int row) {
            return matrix[row];
        }

        vector<T> getColumn(int col) {
            vector<T> returnVector;
            for (int i = 0; i < this->size(); i++) {
                returnVector.push_back(matrix[i][col]);
            }

            return returnVector;
        }

        T primaryDiagonalSum() {
            T sum = 0;
            for (int i = 0; i < this->size(); i++) {
                sum += get(i, i);
            }
            return sum;
        }

        T secondaryDiagonalSum() {
            T sum = 0;
            for (int i = 0; i < this->size(); i++) {
                sum += get(i, this->size() - 1 - i);
            }
            return sum;
        }

        Matrix<T> swapRows(int row1, int row2) {
            Matrix<T> swappedMatrix = *this;
            swappedMatrix.setRow(row1, getRow(row2));
            swappedMatrix.setRow(row2, getRow(row1));

            return swappedMatrix;
        }

        Matrix<T> swapColumns(int col1, int col2) {
            Matrix<T> swappedMatrix = *this;
            for (int i = 0; i < this->size(); i++) {
                swappedMatrix.set(i, col1, get(i, col2));
                swappedMatrix.set(i, col2, get(i, col1));
            }

            return swappedMatrix;
        }

        Matrix<T> operator+(Matrix<T> matrix2) {
            Matrix<T> returnMatrix(this->size());
            if (this->size() == matrix2.size()) {
                for (int i = 0; i < returnMatrix.size(); i++) {
                    for (int j = 0; j < returnMatrix.size(); j++) {
                        returnMatrix.set(i, j, this->get(i, j) + matrix2.get(i, j));
                    }
                }
            } else {
                cout << "Cannot add matrices of different sizes!\n";
            }
            return returnMatrix;
        }

        Matrix<T> operator*(Matrix<T> matrix2) {
            Matrix returnMatrix(this->size());
            if (this->size() == matrix2.size()) {
                for (int i = 0; i < returnMatrix.size(); i++) {
                    for (int j = 0; j < returnMatrix.size(); j++) {
                        int entry = dotProduct(this->getRow(i), matrix2.getColumn(j));
                        returnMatrix.set(i, j, entry);
                    }
                }
            } else {
                cout << "Cannot multiply matrices of different sizes!\n";
            }
            return returnMatrix;
        }
        
    private:
        int _size;
        vector<vector<T>> matrix;
};

int main() {
    string line;
    ifstream inputFile("input.txt");

    if (inputFile.is_open()) {
        getline(inputFile, line);
        int matrix_size = stoi(line);
        Matrix<int> matrix1(matrix_size);
        int row = 0;
        while (row < matrix_size) {
            getline(inputFile, line);
            if (!line.empty()) {
                vector<string> splitLine = splitString(line, ' ');
                for (int col = 0; col < splitLine.size(); col++) {
                    matrix1.set(row, col, stoi(splitLine[col]));
                }
                row++;
            }
        }

        getline(inputFile, line);
        Matrix<int> matrix2(matrix_size);
        row = 0;
        while (row < matrix_size) {
            getline(inputFile, line);
            if (!line.empty()) {
                vector<string> splitLine = splitString(line, ' ');
                for (int col = 0; col < splitLine.size(); col++) {
                    matrix2.set(row, col, stoi(splitLine[col]));
                }
                row++;
            }
        }
        // we don't have any more input to process after this, so we can close the file here
        inputFile.close();

        int option;

        cout << "Select an option:\n";
        cout << "1) Print both input matrices\n";
        cout << "2) Add input matrices\n";
        cout << "3) Multiply input matrices\n";
        cout << "4) Get the sum of the first matrix's diagonals\n";
        cout << "5) Swap rows in matrix 1\n";
        cout << "6) Swap columns in matrix 1\n";
        cout << "7) Set an element of matrix 1\n";
        cout << "Option: ";
        cin >> option;

        cout << endl;

        if (option == 1) {
            cout << "== MATRIX 1 ==\n";
            matrix1.print();
            cout << "\n== MATRIX 2 ==\n";
            matrix2.print();
        } else if (option == 2) {
            Matrix<int> addedMatrix = matrix1 + matrix2;
            cout << "== SUM ==\n";
            addedMatrix.print();
        } else if (option == 3) {
            Matrix<int> multipliedMatrix = matrix1 * matrix2;
            cout << "== PRODUCT ==\n";
            multipliedMatrix.print();
        } else if (option == 4) {
            cout << "Sum of primary diagonal: " << matrix1.primaryDiagonalSum() << endl;
            cout << "Sum of secondary diagonal: " << matrix1.secondaryDiagonalSum() << endl;
            cout << "Sum of both diagonals: " << matrix1.primaryDiagonalSum() + matrix1.secondaryDiagonalSum() << endl;
        } else if (option == 5) {
            int row1;
            int row2;
            cout << "Enter the number of the first row: ";
            cin >> row1;
            cout << "Enter the number of the second row: ";
            cin >> row2;
            cout << "== NEW MATRIX ==\n";
            matrix1.swapRows(row1, row2).print();
        } else if (option == 6) {
            int col1;
            int col2;
            cout << "Enter the number of the first column: ";
            cin >> col1;
            cout << "Enter the number of the second column: ";
            cin >> col2;
            cout << "== NEW MATRIX ==\n";
            matrix1.swapColumns(col1, col2).print();
        } else if (option == 7) {
            int row;
            int col;
            int entry;
            cout << "Enter the row of the entry to set: ";
            cin >> row;
            cout << "Enter the column of the entry to set: ";
            cin >> col;
            cout << "Enter the new entry: ";
            cin >> entry;

            matrix1.set(row, col, entry);
            cout << "== NEW MATRIX ==\n";
            matrix1.print();
        } else {
            cout << "Invalid option!\n";
        }
    }
}

