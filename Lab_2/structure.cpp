
#include <stdlib.h>
#include <iostream>

struct TwoInts
{
    int a;
    int b;
};

struct StructWithArray
{
    int arr[4];
    int* someNumber;
};

int main()
{
    //Формирование объекта структуры "TwoInts" и установка значений его полей:
    TwoInts i2 = { };
    i2.a = 5;
    i2.b = 7;

    //Вывод значений полей структуры "TwoInts":
    std::cout << i2.a << std::endl; 
    std::cout << i2.b << std::endl; 

    //Создание объекта структуры "StructWithArray" и присвоение значения его первому элементу:
    StructWithArray s = { };
    s.arr[0] = 10;

    //Создание другого экземпляра структуры "StructWithArray" и установка значения его первого элемента:
    StructWithArray s1 = { };
    s1.arr[0] = 15;

    //Создание указателя "sPointer", который ссылается на структуру "s":
    StructWithArray* sPointer = &s;
    sPointer->arr[0] = 20;

    //Отображение значения первого элемента массива "s" с использованием указателя "sPointer" (20):
    std::cout << s.arr[0] << std::endl; 

    //Прямая модификация значения первого элемента массива "s" (25):
    s.arr[0] = 25;
    std::cout << s.arr[0] << std::endl; 

    //Модификация значения первого элемента массива "s" с использованием указателя "sPointer" (30):
    sPointer->arr[0] = 30;
    std::cout << s.arr[0] << std::endl; 

    //Изменение направления указателя "sPointer" так, чтобы он указывал на структуру "s1":
    sPointer = &s1;
    sPointer->arr[0] = 35;

    //Вывод значения первого элемента массива "s" (30):
    std::cout << s.arr[0] << std::endl; 

    //Вывод значения первого элемента массива "s1" (35):
    std::cout << s1.arr[0] << std::endl; 

    //Создание массива из двух структур "StructWithArray" и инициализация элементов:
    StructWithArray structArray[2] = { };
    structArray[0].arr[3] = 77;
    structArray[1].someNumber = &structArray[0].arr[3];

    sPointer = &s;

    //Создание указателя "pointer", который указывает на четвертый элемент массива "s":
    int* pointer = &sPointer->arr[3];

    //Прямое изменение четвертого элемента массива "s" (72):
    s.arr[3] = 72;

    //Вывод значения, на которое указывает "pointer" (72):
    std::cout << *pointer; 

    //Структура "memory" и заполнение ее памяти нулями:
    StructWithArray memory;
    memset(&memory, 0, sizeof(StructWithArray));

    return 0;
}