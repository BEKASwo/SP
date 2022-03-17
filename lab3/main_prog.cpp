#include <iostream>
using namespace std;

extern "C" int sum(int* arr, int n);

int main()
{
    srand(time(0));

    const int N = 10;
    int array[N];

    // Генерация массива
    cout << "Array: ";
    for (int i = 0; i < N; i++)
    {
        array[i] = rand() % 200 - 100;
        cout << array [i] << "  ";
    }
    cout << endl;

    // Сумма через C++
    int result_cpp = 0;
    for (int i = 0; i < N; i++)
    {
        result_cpp += array[i] * array[i];
    }
    cout << "C++ result = " << result_cpp << endl;


    // Сумма через ASM
    int result_asm;
    result_asm = sum(array, N);

    cout << "ASM result = " << result_asm << endl;

    return 0;
}
