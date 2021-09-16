#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <conio.h>
#include "Matrix.cpp"

using namespace std;


enum class FillType
{
    randomize = 1,
    manual = 2
};

void clrscr();

string renderUpperPart(vector<string>& options, int selected);

string getResult(const size_t selected, Matrix& matrix, vector<string>& options);

void displayMenu(vector<string>& options, Matrix& matrix);

string arrayToString(int* arr, const size_t size);

void fillMatrix(Matrix& matrix);

void manualInput(Matrix& matrix);

int getUpperSum(Matrix& matrix);

int* getMinArray(Matrix& matrix);

int main()
{
    vector<string> options;
    options.push_back("The Sum of the elements above the main diagonal");   //0
    options.push_back("Create array and sort it");                          //1
    options.push_back("Create array of minimal elements of each row");      //2
    options.push_back("Show matrix");                                       //3

    cout << "Please input matrix first." << "\n";
    size_t row, col;
    cout << "Rows count: ";
    cin >> row;
    cout << "Col count: ";
    cin >> col;
    Matrix matrix(row, col);

    fillMatrix(matrix);

    displayMenu(options, matrix);

    

	return 0;
}

void clrscr()
{
    system("CLS");
}

string renderUpperPart(vector<string>& options, int selected)
{
    stringstream buffer;

    for (size_t i = 0; i < options.size(); i++)
    {
        if (selected == i)
            buffer << "> " << options.at(i) << "\n";
        else
            buffer << "  " << options.at(i) << "\n";
    }

    buffer << "Navigation - ARROWS | Exit - ESC | Select - ENTER\n\n";

    return buffer.str();
}

string getResult(const size_t selected, Matrix& matrix, vector<string>& options)
{
    stringstream buffer;

    switch (selected)
    {
    case 0:
    {
        int sum = getUpperSum(matrix);
        buffer << options.at(selected) << " : " << to_string(sum);
        break;
    }

    case 1:
    {
        //Не работает убрать метод toArray. Вместо него написать обычные функции
        int* arr = new int;
        size_t size;
        matrix.toArray(arr, size);
        buffer << options.at(selected) << " : " << arrayToString(arr, size);
        delete arr;
        break;
    }

    case 2:
    {
        int* arr = getMinArray(matrix);
        size_t size = matrix.getRowSize();
        buffer << options.at(selected) << " : " << arrayToString(arr, size);
        break;
    }

    case 3:
    {
        buffer << matrix.toString();
        break;
    }

    default:
        break;
    }

    return buffer.str();
}

void displayMenu(vector<string>& options, Matrix& matrix)
{
    bool exit = false;
    size_t selected = 0;

    clrscr();
    cout << renderUpperPart(options, selected);
    cout << matrix.toString() << "\n\n";

    while (!exit)
    {
        //stringstream result;
        bool switched = false;

        if (_kbhit())
        {
            switch (_getch())
            {
            case 72: //up
                if (selected == 0)
                    break;

                selected--;
                switched = true;
                break;

            case 80: //down
                if (selected == 3)
                    break;

                selected++;
                switched = true;
                break;
            case 13: //Enter
                cout << getResult(selected, matrix, options);
                break;

            case 27: //ESC
                exit = true;
                break;

            default:
                break;
            }
            
        }

        if (switched)
        {
            clrscr();
            cout << renderUpperPart(options, selected);
            cout << matrix.toString() << "\n\n";
        }
            

    }
}

string arrayToString(int* arr, const size_t size)
{
    stringstream buffer;
    buffer << "{";

    for (size_t i = 0; i < size; i++)
    {
        buffer << arr[i];
        if (i != size - 1)
            buffer << ", ";
    }

    buffer << "}";
    buffer << "END";
    return buffer.str();
}

void fillMatrix(Matrix& matrix)
{
    size_t choice;
    cout << "Chose an option:\n1. Randomize\n2. Fill by hand\n";
    cin >> choice;

    const auto fillType = static_cast<FillType>(choice);

    switch (fillType)
    {
    case FillType::randomize:
    {
        matrix.randomize(-10, 10);
        break;
    }
    case FillType::manual:
    {
        manualInput(matrix);
        break;
    }
    default:
        break;
    }
}

void manualInput(Matrix& matrix)
{
    for (size_t i = 0; i < matrix.getRowSize(); i++)
        for (size_t j = 0; j < matrix.getColSize(); j++)
        {
            cout << "matrix[" << i << ", " << j << "] = ";
            cin >> matrix.at(i, j);
        }
}

int getUpperSum(Matrix& matrix)
{
    int sum = 0;

    for (size_t i = 0; i < matrix.getRowSize(); i++)
        for (size_t j = 0; j < matrix.getColSize(); j++)
            if (j > i)
                sum += matrix.at(i, j);

    return sum;
}

int* getMinArray(Matrix& matrix)
{
    int* minArray = new int[matrix.getRowSize()];
    size_t index = 0;

    for (size_t i = 0; i < matrix.getRowSize(); i++)
    {
        int min = matrix.at(i, 0);

        for (size_t j = 1; j < matrix.getColSize(); j++)
        {
            if (matrix.at(i, j) < min)
                min = matrix.at(i, j);
        }

        minArray[index] = min;
        index++;
    }

    return minArray;
}