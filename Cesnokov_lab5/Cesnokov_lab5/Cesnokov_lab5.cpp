#include <fstream>
#include <array>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

enum class Gender
{
    Male,
    Female
};

//Структура "Person" с типами данных:
struct Person
{
    std::array<char, 20> name;
    int age;
    Gender gender;
};
//Функция для сериализации строки:
void serializeString(std::ostream& os, const std::array<char, 20>& str)
{
    //Тело функции (запись данных в поток вывода):
    os.write(str.data(), str.size());
}

//Функция для сериализации целого числа:
void serializeInteger(std::ostream& os, int intValue)
{
    //Тело функции (запись целочисленного значения в поток):
    os << intValue;
}

//Функция для сериализации поля "enum class Gender":
void serializeGender(std::ostream& os, Gender gender)
{
    //Тело функции (оператор "switch" проверяет значение "gender" и записывает символ в поток):
    switch (gender)
    {
    case Gender::Male:
        os << "M";
        break;
    case Gender::Female:
        os << "F";
        break;
    }
}

//Функция для сериализации объекта "Person" в "CSV" формат:
void serializeObject(std::ostream& os, const Person& person)
{
    //Тело функции (сериализация каждого поля обьекта "Person"):
    serializeString(os, person.name); //Сериализация имени.
    os << ","; //Разделитель (запятая).
    serializeInteger(os, person.age); //Сериализация возраста.
    os << ","; //Разделитель (запятая).
    serializeGender(os, person.gender); //Сериализация пола.
}

//Функция для десериализации строки:
void deserializeString(std::istream& is, std::array<char, 20>& str)
{
    is.read(str.data(), str.size()); //Считывание данных из потока в массив "str".
    str[str.size() - 1] = '\0'; //Установим нулевой байт в последний элемент массива.
}

//Функция для десериализации целого числа:
int deserializeInteger(std::istream& is)
{
    std::string token; //Хранение считанной строки (токена).
    std::getline(is, token, ','); //Метод считывает данные из потока "is" до символа "," и сохраняет их в строку "token".
    try
    {
        return std::stoi(token); //Преобразование строки в целочисленное значение.
    }
    catch (const std::invalid_argument&)
    {
        // Обработка ошибки (можно заменить на другое значение, например, -1)
        return 0;
    }
}

//Функция для десериализации поля "enum class Gender":
Gender deserializeGender(std::istream& is)
{
    std::string token;
    std::getline(is, token, ',');
    //Сравнение строки token с возможными значениями "M" и "F":
    if (token == "M")
        return Gender::Male;
    else if (token == "F")
        return Gender::Female;
    //Можно добавить обработку ошибки, например, бросить исключение.
    return Gender::Male; //По умолчанию.
}

//Функция для десериализации объекта "Person" из строки "CSV":
Person deserializeObject(std::istream& is)
{
    Person result;
    deserializeString(is, result.name);
    result.age = deserializeInteger(is);
    result.gender = deserializeGender(is);
    return result; //Объект "result", который теперь содержит десериализованные данные.
}

//Функция для сериализации "std::vector" из объектов "Person" в "std::ostream":
void serializeVector(std::ostream& os, const std::vector<Person>& persons)
{
    for (const auto& person : persons) //Проход по всем элементам вектора.
    {
        serializeObject(os, person); //Сериализация каждого объекта Person.
        os << "\n"; //Разделитель объектов.
    }
}

//Функция для десериализации "std::vector" из строк "CSV" в "std::istream":
std::vector<Person> deserializeVector(std::istream& is)
{
    std::vector<Person> persons; //Вектор для хранения десериализованных объектов типа "Person".
    std::string line; //Строка для считывания данных из потока построчно.
    while (std::getline(is, line))
    {
        std::istringstream iss(line); //Объект "std::istringstream", представляющий поток ввода из строки "line".
        persons.push_back(deserializeObject(iss));
    }
    return persons; //Вектор, который содержит десериализованные объекты "Person".
}

int main()
{
    std::ofstream outFile("persons.csv"); //Открывает файл "persons.csv" для записи и создает объект "std::ofstream" с именем "outFile".
    std::vector<Person> persons{
        {{"John", 25, Gender::Male}, {"Alice", 30, Gender::Female}} };
    serializeVector(outFile, persons); //Функция сериализует вектор объектов "Person" в файл "persons.csv".
    outFile.close();

    std::ifstream inFile("persons.csv");
    std::vector<Person> loadedPersons = deserializeVector(inFile); //Функция десериализует данные из файла и возвращает вектор объектов "Person":
    inFile.close();

    //Вывод информации о каждом объекте "Person":
    for (const auto& person : loadedPersons)
    {
        std::cout << "Name: " << person.name.data() << ", Age: " << person.age
            << ", Gender: " << static_cast<int>(person.gender) << std::endl;
    }
    return 0;
}