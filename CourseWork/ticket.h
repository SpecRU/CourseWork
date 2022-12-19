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
    std::vector <std::vector <String>> vars; //Список задач
    int vQ; //vQ - количество вариантов 
    int qQ; // qQ - количество вопросов
    char outmode[1]{ 't' }; //Режим вывода
public:
    void inputq(const int& qin);

    void inputv(const int& vin);

    void output(const char& outm);

    int output();

    void output(const std::vector <std::vector <String>>& vec);

    void input(const std::string inpath);

    void input();

    int module(const std::wstring& in);

    void randsortfout();

    //varsS vars_substr_vec(std::vector<varsS>& used, const int& seed);
};
extern ticket construct;