#include <string>
#pragma once

class Matrix
{
public:

    Matrix(size_t row, size_t col);
    ~Matrix();

    std::string toString(const int width = 2, const std::string& message = "");

    void randomize(const int min, const int max);

private:
    size_t rowSize;
    size_t colSize;
    int** matrix;

    int** initialize();

};

