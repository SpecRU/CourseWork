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

struct varsS { int diff; int module; std::wstring str; };

bool operator<(const varsS& a, const varsS& b);

bool operator==(const varsS& a, const varsS& b);

bool operator!=(const varsS& a, const varsS& b);

void operator-=(std::vector<varsS>& a, const std::vector<varsS>& b);

class ticket {
    std::vector <varsS> vars; //Список задач (сложность / строка)
    int vQ; //vQ - количество вариантов 
    int qQ; // qQ - количество вопросов
    bool isHard = false; //Есть ли задачи со сложность
    char outmode[1]{ 't' }; //Режим вывода
public:
    void inputq(const int& qin);

    void inputv(const int& vin);

    void output(const char& outm);

    int output();

    void output(const std::vector<varsS>& vec);

    void input(const std::string inpath);

    void input();

    int hardness(const std::wstring& in);

    int module(const std::wstring& in);

    bool hardness();

    void dumbsortfout();

    void balancesortfout();

    void randsortfout();

    varsS vars_substr_vec(std::vector<varsS>& used, const int& seed);
};
extern ticket construct;