#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <random>

std::wstring utf8_decode(const std::wstring& instr) noexcept; //используется для перевода из кодировки UTF-8
std::string unicode2ansi(const std::wstring& wstr) noexcept; //используется для перевода в кодировку ANSI
//2 функции, необходимые для вывода в файл .txt, учитывая использование std::wstring

bool operator==(std::vector <std::wstring> a, std::vector <std::wstring> b) noexcept; //перегрузка сравения wstring векторов, необходима для поиска одинаковых билетов

class ticket {
    std::vector <std::vector <std::wstring>> vars; //Список необработанных задач [["abc", "vrd"], ["f3f", "wefw"], [] ...], задается при считвании файла
    std::vector <int> tasks_per_module_quantity; //Список количества задач для вывода из каждого модуля, задается при считвании файла
    int variants_quantity = 0; //Количество вариантов, задается в интерфейсе
    int max_variants_quantity = 0; //Количество максимальных вариантов, высчитывается методом calcualte_max_variants_quantity()
    char output_mode[1]{ 't' }; //Режим вывода, задается в интерфейсе
public:
    ~ticket() noexcept = default; //Стандартный деконструктор

    void clear() noexcept; //Очистка данных, необходим для "сброса" программы

    void calcualte_max_variants_quantity() noexcept; //Вызывается при считывании файла задач, считает максимальное количество уникальных сочетаний, по сути программная реализация уравнения комбинаторики

    int max_variants() noexcept; //Вывод количества максимальных вариантов, необходим для работы интерфейса

    void variants(const int& variants) noexcept; //Ввод количества необходимых вариантов, передается объектом класса интерфейса

    void fprint_mode(const char& mode) noexcept; //Ввод режима вывода файла, передается объектом класса интерфейса

    void fprint(const std::vector <std::vector <std::wstring>>& vec); //Вывод в файл, вызвается методом random_fprint() в конце его работы, он передает в метод ссылку на форматированную под вывод векторную матрицу строк.

    short int scan(const std::string input_path); //Считвание файла в vars, парралельно использует метод module(const std::wstring& str) для поиска модулей. Записывает количество выводимых из этих модулей задач в tasks_per_module_quantity.

    int module(const std::wstring& str); //Поиск правильно записанных команд - Module *цифры*

    int size() noexcept; //Вывод размера vars, необходимо для работы интерфейса

    void random_fprint() noexcept; //Основной алгоритм построения билетов (вариантов), создает случайные варианты и смотрит являются ли они уникальными. Если нет, генерирует заново.

};