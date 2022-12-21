#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <regex>
#include <random>
#include <fcntl.h>
#include <io.h>
#include <stringapiset.h>

std::wstring utf8_decode(const std::wstring& instr);

std::string unicode2ansi(const std::wstring& wstr);

//bool operator<(const varsS& a, const varsS& b);

//bool operator==(const varsS& a, const varsS& b);

//bool operator!=(const varsS& a, const varsS& b);

//void operator-=(std::vector<varsS>& a, const std::vector<varsS>& b);

class ticket {
    std::vector <std::vector <std::wstring>> vars; //Список задач
    int variant_quantity;
    int tasks_quantity;
    char output_mode[1]{ 't' }; //Режим вывода
public:
    ~ticket() = default;

    void vars_clear();

    void tasks(const int& tasks);

    void variants(const int& variants);

    void fprint_mode(const char& mode);

    void fprint(const std::vector <std::vector <std::wstring>>& vec);

    short int scan(const std::string input_path);

    int module(const std::wstring& str);

    int size();

    void random_fprint();

    //varsS vars_substr_vec(std::vector<varsS>& used, const int& seed);
};
extern ticket processing_class;