//#include "Matrix.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <random>

#include <iostream>

using namespace std;

class Matrix
{
public:

    Matrix(size_t row, size_t col)
    {
        rowSize = row;
        colSize = col;
        matrix = initialize();
    }

    ~Matrix()
    {
        destruct();
    }

    int& at(const size_t i, const size_t j)
    {
        if (i >= rowSize || j >= colSize)
            throw out_of_range("Index is out of bounds!");

        return matrix[i][j];
    }

    size_t getRowSize()
    {
        return rowSize;
    }
    
    size_t getColSize()
    {
        return colSize;
    }

    string toString(const int width = 2, const string& message = "") //{{1,2},{3,4},{5,6}}
    {
        stringstream buffer;

        buffer << message;

        for (size_t i = 0; i < rowSize; ++i)
        {
            if (i != rowSize && i != 0)
                buffer << "\n";

            buffer << "{";

            for (size_t j = 0; j < colSize; ++j)
            {
                buffer << setw(width) << matrix[i][j];
                if (j != colSize - 1)
                    buffer << ", ";
            }

            buffer << "}\n";
        }

        return buffer.str();
    }

    void randomize(const int min = INT_MIN, const int max = INT_MAX)
    {
        random_device rd;
        mt19937 gen(rd());
        const uniform_int_distribution<> uniformIntDistribution(min, max);

        for (size_t i = 0; i < rowSize; ++i)
            for (size_t j = 0; j < colSize; ++j)
                matrix[i][j] = uniformIntDistribution(gen);

    }

private:
    size_t rowSize;
    size_t colSize;
    int** matrix;

    size_t minArraySize;
    int* minArray;

    //загрязнение памяти
    int** initialize()
    {
        int** matrix = new int* [rowSize];

        for (size_t i = 0; i < rowSize; i++)
        {
            matrix[i] = new int[colSize];
        }

        return matrix;
    }

    //отчистка памяти
    void destruct()
    {
        if (matrix == nullptr)
            return;

        for (size_t i = 0; i < rowSize; i++)
            if (matrix[i] != nullptr)
            {
                delete[] matrix[i];
                matrix[i] = nullptr;
            }
                

        delete[] matrix;
        matrix = nullptr;
    }

};
