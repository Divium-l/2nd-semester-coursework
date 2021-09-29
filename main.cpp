#include <iostream>
#include <string>
#include <sstream>
#include <conio.h>
#include "Matrix.cpp"

using namespace std;

//-ввод матрицы;                                                                                          | +
//                                                                                                        | 
//-подсчет суммы элементов, стоящих выше главной диагонали матрицы;                                       | +
//                                                                                                        |
//-создание на основе матрицы одномерного массива с последующей сортировкой его методом выбора;           | +
//                                                                                                        |
//-нахождение массива, каждый элемент которого представляет собой минимум соответствующей строки матрицы; | +
//                                                                                                        | 
//-вывод матрицы.                                                                                         | +

/*
* \brief Отчищает экран консоли
*/
void clrscr();

/*
* \brief Создаёт и преобразует меню в строку
* \param options Опции меню
* \param selected Положение курсора
* \return Меню в виде строки
*/
string renderUpperPart(vector<string>& options, const size_t selected);

/*
* \brief Выполняет действия, которые пользователь выбрал в меню
* \param selected Положение курсора
* \param matrix Матрица
* \param options Опции меню
* \return Результат действий в виде строки (чтобы удобно было выводить на экран)
*/
string getResult(const size_t selected, Matrix& matrix, vector<string>& options);

/*
* \brief Цикл отображения меню
* \param options Опции меню
* \param matrix Матрица
*/
void displayMenu(vector<string>& options, Matrix& matrix);

/*
* \brief Преобразует массив в строку
* \param arr Массив
* \param size Размер массива
* \return Строка массива
*/
string arrayToString(int* arr, const size_t size);

/*
* \brief Спрашивает пользователя, как вводить матрицу
* \param matrix Матрица
*/
void fillMatrix(Matrix& matrix);

/*
* \brief Ввод элементов матрицы с клавиатуры
* \param matrix Матрица
*/
void manualInput(Matrix& matrix);

/*
* \brief Подсчёт суммы элементов стоящих выше главное диагонали
* \param matrix Матрица
* \return Сумма элементов (0 если нет главной диагонали)
*/
int getUpperSum(Matrix& matrix);

/*
* \brief Преобразует матрицу в массив
* \param matrix Матрица
* \param size Размер будущего массива
* \return Массив
*/
int* matrixToArray(Matrix& matrix, const size_t size);

/*
* \brief Преобразует матрицу в массив
* \param matrix Матрица
* \param arr Массив
*/
int* getMinArray(Matrix& matrix);

/*
* \brief Сортировка массива методом выбора
* \param arr Массив
* \param size Размер массива
*/
void sortBySelection(int* arr, const size_t size);

/*
* \brief Класс чтобы усложнить себе жизнь
*/
enum class FillType
{
    randomize = 1,
    manual = 2
};

/*
* \brief Точка входа в программу. Создание меню, и инициализация матрицы.
* \param arr Массив
* \param size Размер массива
* \return Строка массива
*/
int main()
{
    //main -> dispalyMenu() <-> getResult() -> end

    vector<string> options;
    options.push_back("The Sum of the elements above the main diagonal");   //0
    options.push_back("Create array and sort it");                          //1
    options.push_back("Create array of minimal elements of each row");      //2
    options.push_back("Show matrix");                                       //3

    cout << "Please input matrix dimensions first." << "\n";
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

string renderUpperPart(vector<string>& options, const size_t selected)
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

void displayMenu(vector<string>& options, Matrix& matrix)
{
    bool exit = false;
    size_t selected = 0;
    string result = matrix.toString();

    clrscr();
    cout << renderUpperPart(options, selected);
    cout << result << "\n\n";

    while (!exit)
    {
        bool update = false;

        if (_kbhit())
        {
            update = true;

            switch (_getch())
            {
            case 72: //up
                if (selected == 0)
                    break;

                selected--;
                break;

            case 80: //down
                if (selected == 3)
                    break;

                selected++;
                break;
            case 13: //Enter
                result = getResult(selected, matrix, options);
                break;

            case 27: //ESC
                exit = true;
                break;

            default:
                break;
            }
            
        }

        if (update)
        {
            clrscr();
            cout << renderUpperPart(options, selected);
            cout << result << "\n\n";
        }
            

    }
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
        size_t size = matrix.getRowSize() * matrix.getColSize();
        int* arr = matrixToArray(matrix, size);       
        sortBySelection(arr, size);
        buffer << options.at(selected) << " : " << arrayToString(arr, size);
        delete[] arr;
        break;
    }

    case 2:
    {
        int* arr = getMinArray(matrix);
        size_t size = matrix.getRowSize();
        buffer << options.at(selected) << " : " << arrayToString(arr, size);
        delete[] arr;
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
    if (matrix.getRowSize() != matrix.getColSize())
        return 0;

    int sum = 0;

    for (size_t i = 0; i < matrix.getRowSize(); i++)
        for (size_t j = 0; j < matrix.getColSize(); j++)
            if (j > i)
                sum += matrix.at(i, j);

    return sum;
}

int* matrixToArray(Matrix& matrix, const size_t size)
{
    size_t k = 0;

    int* arr = new int[size];

    for (size_t i = 0; i < matrix.getRowSize(); i++)
        for (size_t j = 0; j < matrix.getColSize(); j++)
        {
            arr[k] = matrix.at(i, j);
            k++;
        }
   
    return arr;
}

void sortBySelection(int* arr, const size_t size)
{  
    for (size_t i = 0; i < size; i++)
    {
        int minIndex = i;

        for (size_t j = i; j < size; j++)
            if (arr[j] < arr[minIndex])
                minIndex = j;
  
        swap(arr[minIndex], arr[i]);
        
    }
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