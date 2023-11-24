#include <iostream>

int main()
{
    int i = 69;
    int number = 72;

    i += number;

    int array[3] = {};

    int* iPointer;
    iPointer = &i;

    number = *iPointer;

    *iPointer = 15;

    iPointer = &arr[0];

    iPointer = iPointer + 2;

    array[0] = 5;
    *iPointer = 6;

    for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++) {
        printf("%i\n", array[i]);
    }
}
