#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <random>
#include <fcntl.h>
#include <io.h>
#include <stringapiset.h>

std::wstring utf8_decode(const std::wstring& instr) noexcept;

std::string unicode2ansi(const std::wstring& wstr) noexcept;

bool operator==(std::vector <std::wstring> a, std::vector <std::wstring> b) noexcept;

class ticket {
    std::vector <std::vector <std::wstring>> vars; //Список задач [["abc", "vrd"], ["f3f", "wefw"], [] ...]
    std::vector <int> tasks_per_module_quantity; //Список количества задач для вывода
    int variants_quantity = 0; //Количество вариантов
    int max_variants_quantity = 0;
    char output_mode[1]{ 't' }; //Режим вывода
public:
    ~ticket() noexcept = default;

    void clear() noexcept;

    void calcualte_max_variants_quantity() noexcept;

    int max_variants() noexcept;

    void variants(const int& variants) noexcept;

    void fprint_mode(const char& mode) noexcept;

    void fprint(const std::vector <std::vector <std::wstring>>& vec);

    short int scan(const std::string input_path);

    int module(const std::wstring& str);

    int size() noexcept;

    void random_fprint() noexcept;

};
extern ticket processing_class;