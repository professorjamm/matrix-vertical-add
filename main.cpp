/*
Program Name: Vertical Additive Symmetric Matrix
Date: 2023-09-15
Author: Faizaan Siddiqui
Module Purpose:
This program takes in information from a text file, which contains 10 matrices and information regarding those matricies (# of rows/columns and values of each number in the matrix). With that information the program checks to see if each matrix has vertical additive symmetry, meaning the sum of the left columns are the same as the sumn of the right columns (if there are an odd # of columns the sum of the middle one won't matter). Not only does this program demonstrate reading in text from a file in C++, but it also shows how 2D arrays and loops work in C++. The program can take in ints up to 4 digits (both positive and negative), and also shows each row of each matrix sorted from lowest numeric value to highest.
*/

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm> 

using namespace std;

const unsigned MAX_MATRIX_SIZE = 20;
const unsigned WIDTH_DISPLAY = 12;

unsigned int YES = 0;  //i added these 2 ints into my code to keep track of the # of matrices with vertrical additive symmetry 
unsigned int NO = 0;

bool    readMatrixFromFile(int[][MAX_MATRIX_SIZE], unsigned&, unsigned&, ifstream&);
void         displayMatrix(int[][MAX_MATRIX_SIZE], unsigned, unsigned);
void displayCalcMatrixSums(int[][MAX_MATRIX_SIZE], unsigned, unsigned, int[MAX_MATRIX_SIZE]);
void   symmetryCheckMatrix(int[], unsigned, unsigned);
void        sortMatrixRows(int[][MAX_MATRIX_SIZE], unsigned, unsigned);


int main() {
    unsigned height,
        width;
    int      matrix[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE],
        colSums[MAX_MATRIX_SIZE];
    string   INPUT_FILE_NAME = "matrixes.txt";
    ifstream inputFileStreamObj(INPUT_FILE_NAME);

    if (inputFileStreamObj.fail()) {
        cout << "File " << INPUT_FILE_NAME << "could not be opened !" << endl;
        cout << endl << "Press the enter key once or twice to leave..." << endl; cin.ignore(); cin.get();
        exit(EXIT_FAILURE);
    }

    do {

        if (readMatrixFromFile(matrix, height, width, inputFileStreamObj))
            break;

        cout << "Input:" << endl;
        displayMatrix(matrix, height, width);
        displayCalcMatrixSums(matrix, height, width, colSums);
        symmetryCheckMatrix(colSums, width, height);
        sortMatrixRows(matrix, width, height);
        cout << "Sorted:" << endl;
        displayMatrix(matrix, height, width);

        cout << endl << "Press the enter key once or twice to continue..." << endl; cin.ignore(); cin.get();

    } while (true);

    cout << "Program Done" << endl << endl;
    cout << "Yes: " << YES << " No: " << NO << endl;
    exit(EXIT_SUCCESS);
}

bool readMatrixFromFile(int matrix[][MAX_MATRIX_SIZE], unsigned& height, unsigned& width, ifstream& inputFileStreamObj) 
{
    //checkin if the file is empty  
    if (!(inputFileStreamObj >> height))
        return true;
    
    //since file not empty it is reading in the width
    inputFileStreamObj >> width;

    //c = column and r = row, just did this so I could code it faster
    for(unsigned r=0;r<height;r++)
        for(unsigned c = 0; c<width; c++)
            inputFileStreamObj >> matrix[r][c];

    return(false);
}


void displayMatrix(int matrix[][MAX_MATRIX_SIZE], unsigned height, unsigned width) 
{
    for (unsigned r = 0; r < height; r++)
    {
        for (unsigned c = 0; c < width; c++)
            cout << setw(WIDTH_DISPLAY) << matrix[r][c];
        cout << endl;
    }
    cout << endl;
}


void displayCalcMatrixSums(int matrix[][MAX_MATRIX_SIZE], unsigned height, unsigned width, int colSums[MAX_MATRIX_SIZE]) 
{
    for (unsigned c = 0; c < width; c++)
        colSums[c] = 0;

    for (unsigned c = 0; c < width; c++)
        for (unsigned r = 0; r < height; r++)
            colSums[c] += matrix[r][c];

    cout << "Sums: " << endl;

    for (unsigned c = 0; c < width; c++)
        cout << setw(WIDTH_DISPLAY) << colSums[c];

    cout << endl << endl;
}


void symmetryCheckMatrix(int colSums[], unsigned width, unsigned height) 
{
    bool isSymmetric = true;

    if (width % 2 == 0) //even # of columns 
    {
        for (unsigned i = 0; i < width / 2; i++) 
            if (colSums[i] != colSums[width - 1 - i]) 
            {
                isSymmetric = false;
                break;
            }
    }
    else //odd # of columns 
    { 
        for (unsigned i = 0; i < width / 2; i++)
            if (colSums[i] != colSums[width - 1 - i]) 
            {
                isSymmetric = false;
                break;
            }
    }

    if (isSymmetric)
    {
        cout << "Vertical additive symmetry : Yes" << endl << endl; 
        YES++;
    }
    else
    {
        cout << "Vertical additive symmetry : No" << endl << endl;
        NO++;
    }
       
}

void sortMatrixRows(int matrix[][MAX_MATRIX_SIZE], unsigned width, unsigned height) 
{
    for (unsigned r = 0; r < height; ++r) //going through each row and sorting them 
        std::sort(matrix[r], matrix[r] + width);
}
