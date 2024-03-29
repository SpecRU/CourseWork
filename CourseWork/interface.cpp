﻿#include <windows.h>
#include "interface.h"
#include "ticket.h"
#include <msclr/marshal_cppstd.h>
#using <System.dll>

using namespace System;
using namespace System::Windows::Forms;
using namespace msclr::interop;
using namespace System::IO;
using namespace System::Diagnostics;
using namespace System::ComponentModel;

std::wstring utf8_decode(const std::wstring& instr) noexcept {
	const std::string str(instr.begin(), instr.end());
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}

std::string unicode2ansi(const std::wstring& wstr) noexcept {
	int size_needed = WideCharToMultiByte(CP_ACP, 0, &wstr[0], -1, NULL, 0, NULL, NULL);
	std::string strTo(size_needed, 0);
	WideCharToMultiByte(CP_ACP, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
	strTo.pop_back();
	return strTo;
}

std::random_device rd;
std::mt19937 gen(rd());
int random(int min, int max) {
	std::uniform_int_distribution<> dist(min, max);
	return dist(gen);
}

bool operator==(std::vector<std::wstring> a, std::vector<std::wstring> b) noexcept {
	short int counter = 0;
	if (a.size() == b.size()) {
		for (int i = 0; i < a.size(); ++i) {
			if (std::find(b.begin(), b.end(), a[i]) != b.end()) counter++;
		}
		if (counter == a.size()) return true;
		return false;
	}
	else return false;
}

void ticket::variants(const int& variants) noexcept {
	variants_quantity = variants;
}

void ticket::clear() noexcept {
	vars.clear();
	tasks_per_module_quantity.clear();
	output_mode[1] = { 't' };
}

void ticket::calcualte_max_variants_quantity() noexcept {
	int max = 0, nfact, nkfact, kfact;
	std::vector <int> factorials = {1, 2};

	for (const std::vector <std::wstring> i : vars) if (i.size() > max) max = i.size();
	for (int i = 3; i <= max; ++i) factorials.push_back(factorials[i - 2] * i);

	nfact = factorials[vars[0].size() - 1];
	if (vars[0].size() - tasks_per_module_quantity[0] - 1 < 0) nkfact = 0;
	else nkfact = factorials[vars[0].size() - tasks_per_module_quantity[0] - 1];
	kfact = factorials[tasks_per_module_quantity[0] - 1];

	for (int i = 1; i < vars.size(); i++) {
		if (nfact < 2) nfact = factorials[vars[i].size() - 1];
		else nfact *= factorials[vars[i].size() - 1];

		if (vars[i].size() - tasks_per_module_quantity[i] <= 0);
		else if (nkfact < 2) nkfact = factorials[vars[i].size() - tasks_per_module_quantity[i] - 1];
		else nkfact *= factorials[vars[i].size() - tasks_per_module_quantity[i] - 1];

		if (kfact < 2) kfact = factorials[tasks_per_module_quantity[i] - 1];
		else kfact *= factorials[tasks_per_module_quantity[i] - 1];
	}

	max_variants_quantity = nfact / (nkfact * kfact);
}

int ticket::max_variants() noexcept
{
	return max_variants_quantity;
}


short int ticket::scan(const std::string input_path) {
	std::wifstream input_stream(input_path);
	std::wstring input_Tmp;


	int moduleVal = 0, i = -1, scanned_tasks_quantity = 0;
	if (input_stream.is_open()) {
		while (getline(input_stream, input_Tmp)) {
			if (input_Tmp == L"") continue;
			moduleVal = module(input_Tmp);
			if (!moduleVal && i == -1) {
				return 3;
			}
			if (moduleVal) {
				tasks_per_module_quantity.push_back(moduleVal);
				scanned_tasks_quantity = 0;
				moduleVal = 0;
				++i;
				vars.resize(i+1);
				continue;
			}
			++scanned_tasks_quantity;
			vars[i].push_back(input_Tmp);
		};
		if (tasks_per_module_quantity[i] > scanned_tasks_quantity) return 2;
		input_stream.close();
		return 0;
	}
	else {
		return 1;
	}
}

int ticket::module(const std::wstring& str) {
	std::wstring b = L"", a = L"Module";

	if (str.length() > 6) {
		if (str[6] == L' ') {
			for (int i = 0; i < 6; ++i) {
				if (str[i] != a[i]) {
					break;
				}
				if (i == 5) {
					for (int k = 7; k < str.length(); ++k) {
						b += str[k];
					}
				}
			}
		}
	}

	try {
		return std::stoi(b);
	}
	catch (const std::invalid_argument&) {
		return 0;
	}
}

void ticket::fprint_mode(const char& mode) noexcept {
	output_mode[0] = mode;
}

int ticket::size() noexcept {
	return vars.size();
}

void ticket::fprint(const std::vector <std::vector <std::wstring>>& vec) {
	int current_variant = 1, current_task = 1;

	if (output_mode[0] == 'r') {
		std::ofstream fout("Sorted.rtf");
		if (fout.is_open()) {
			for (int i = 0; i < vec.size(); ++i) {
				current_task = 1;
				fout << std::endl << "Вариант " << current_variant << ":" << std::endl;
				for (int k = 0; k < vec[i].size(); ++k) {
					fout << current_task << (". ") << unicode2ansi(utf8_decode(vec[i][k])) << std::endl;
					++current_task;
				}
				++current_variant;
			}
			fout.close();
		}
		else MessageBox::Show(L"Ошибка открытия файла вывода", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
	else {
		std::wofstream fout("Sorted.txt");
		if (fout.is_open()) {
			for (int i = 0; i < vec.size(); ++i) {
				current_task = 1;
				fout << std::endl << L"ÐÐ°ÑÐ¸Ð°Ð½Ñ " << current_variant << L":" << std::endl;
				for (int k = 0; k < vec[i].size(); ++k) {
					fout << current_task << (L". ") << vec[i][k] << std::endl;
					++current_task;
				}
				++current_variant;
			}
			fout.close();
		}
		else MessageBox::Show(L"Ошибка открытия файла вывода", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}

void ticket::random_fprint() noexcept {
	std::vector <std::vector <std::wstring>> sorted(variants_quantity);
	long int iter_quantity = 0;
	
	for (int i = 0; i < variants_quantity; ++i) {
		for (int k = 0; k < vars.size(); ++k) {
			for (int j = 0; j < tasks_per_module_quantity[k]; ++j) {
				std::wstring new_task;
				while (true) {
					new_task = vars[k][random(0, vars[k].size() - 1)];
					if (std::find(sorted[i].begin(), sorted[i].end(), new_task) != sorted[i].end()) new_task = vars[k][random(0, vars[k].size() - 1)];
					else break;
				}
				sorted[i].push_back(new_task);
			}
		}

		if (i > 0) {
			for (int k = 0; k < i; ++k) {
				if (sorted[k] == sorted[i]) {
					sorted[i].clear();
					--i;
				}
			}
		}
	}

	fprint(sorted);
}

std::string FilePath;
ticket processing_class;
[STAThreadAttribute]
int main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	CourseWork::MyForm form;
	Application::Run(% form);
}
//Все что связано с [Menu_File] сверху
System::Void CourseWork::MyForm::MyForm_Load(System::Object^ sender, System::EventArgs^ e)
{
	return System::Void();
}

System::Void CourseWork::MyForm::файлToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	return System::Void();
}

System::Void CourseWork::MyForm::выходToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	Application::Exit();
}

System::Void CourseWork::MyForm::открытьToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	processing_class.clear();
	radioButtonRandom->Enabled = false;
	checkBoxTXT->Enabled = false;
	checkBoxRTF->Enabled = false;
	buttonOutput->Enabled = false;
	buttonEDIT->Enabled = false;
	buttonDELETE_CONFIRM->Enabled = false;
	buttonDELETE->Enabled = false;
	textBox1->Enabled = true;
	textBox1->Text = "0";
	textBoxOutput->Text = "";
	buttonEDIT_SAVE->Enabled = true;
	String^ FilenameOpen = "";
	OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;

	openFileDialog1->InitialDirectory = L"c:\\";
	openFileDialog1->Filter = L"txt files (*.txt)|*.txt|All files (*.*)|*.*";
	openFileDialog1->FilterIndex = 2;
	openFileDialog1->RestoreDirectory = true;

	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		FilenameOpen = openFileDialog1->FileName;//Путь

	}
	try {
		StreamReader^ file = File::OpenText(FilenameOpen);
		textBoxOutput->Text = file->ReadToEnd();
		file->Close();
		processing_class.clear();
		FilePath = marshal_as<std::string>(FilenameOpen);
		//MessageBox::Show(this, FilenameOpen, L"Инфо", MessageBoxButtons::OK, MessageBoxIcon::Error);
		short int err = processing_class.scan(FilePath);
		if (err > 0) {
			throw err;
		}
	}
	catch (short int err) {
		if (err == 1) MessageBox::Show(L"Ошибка открытия файла ввода (1)", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		if (err == 2) MessageBox::Show(L"Количество выводимых вопросов превышает их число (2)", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		if (err == 3) MessageBox::Show(L"Обнаружен ввод без модуля (3)", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		CourseWork::MyForm::Clear();
	}
	catch (Exception^ e) {
		MessageBox::Show(this, L"Ошибка чтения файла (e)", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		CourseWork::MyForm::Clear();
	}
	//return System::Void();
}

//Все что связано с [buttonEDIT]
System::Void CourseWork::MyForm::buttonEDIT_Click(System::Object^ sender, System::EventArgs^ e)
{
	buttonDELETE_CONFIRM->Enabled = false;
	buttonEDIT_SAVE->Enabled = true;
	buttonEDIT->Enabled = false;
	textBox1->Enabled = true;
	textBoxOutput->Enabled = true;
	radioButtonRandom->Enabled = false;
	radioButtonRandom->Checked = false;
	checkBoxTXT->Enabled = false;
	checkBoxRTF->Enabled = false;
	buttonOutput->Enabled = false;
	//return System::Void();
}
System::Void CourseWork::MyForm::buttonEDIT_SAVE_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (textBox1->Text == "0") {
		MessageBox::Show(this, L"Введите число больше 0", L"Внимание", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return System::Void();
	}
	else {
		if (stoi(marshal_as<std::string>(textBox1->Text)) > processing_class.max_variants()) {
			MessageBox::Show(this, L"Невозможно сгенерировать столько вариантов, вывод максимального количества", L"Внимание", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			processing_class.variants(processing_class.max_variants());
		}
		buttonDELETE_CONFIRM->Enabled = false;
		buttonEDIT_SAVE->Enabled = false;
		textBox1->Enabled = false;
		textBoxOutput->Enabled = false;
		buttonEDIT_SAVE->Enabled = false;
		buttonEDIT->Enabled = true;
		StreamWriter^ strwr = gcnew StreamWriter(marshal_as<String^>(FilePath));
		strwr->Write(textBoxOutput->Text);
		strwr->Close();
		processing_class.clear();
		processing_class.scan(FilePath);
		radioButtonRandom->Enabled = true;
	}
}
//Все что связано с [buttonDELETE]
System::Void CourseWork::MyForm::buttonDELETE_Click(System::Object^ sender, System::EventArgs^ e)
{
	buttonDELETE_CONFIRM->Enabled = true;
	//return System::Void();
}
System::Void CourseWork::MyForm::buttonDELETE_CONFIRM_Click(System::Object^ sender, System::EventArgs^ e)
{
	CourseWork::MyForm::Clear();
}

System::Void CourseWork::MyForm::Clear()
{
	textBox1->Text = "0";
	textBoxOutput->Text = "";
	processing_class.clear();
	textBox1->Enabled = false;
	textBoxOutput->Enabled = false;
	buttonEDIT->Enabled = false;
	buttonEDIT_SAVE->Enabled = false;
	radioButtonRandom->Enabled = false;
	radioButtonRandom->Checked = false;
	buttonOutput->Enabled = false;
	buttonDELETE_CONFIRM->Enabled = false;
	buttonDELETE->Enabled = false;
	checkBoxTXT->Enabled = false;
	checkBoxRTF->Enabled = false;
	//return System::Void();
}

//Все что связано с [radioButton(Type)]
System::Void CourseWork::MyForm::radioButtonRandom_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
	buttonDELETE_CONFIRM->Enabled = false;
	checkBoxTXT->Checked = false;
	checkBoxRTF->Checked = false;
	checkBoxTXT->Enabled = true;
	checkBoxRTF->Enabled = true;
	//return System::Void();
}
System::Void CourseWork::MyForm::radioButtonBalance_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
	buttonDELETE_CONFIRM->Enabled = false;
	checkBoxTXT->Checked = false;
	checkBoxRTF->Checked = false;
	checkBoxTXT->Enabled = true;
	checkBoxRTF->Enabled = true;
	//return System::Void();
}
System::Void CourseWork::MyForm::radioButtonDiff_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
	buttonDELETE_CONFIRM->Enabled = false;
	checkBoxTXT->Checked = false;
	checkBoxRTF->Checked = false;
	checkBoxTXT->Enabled = true;
	checkBoxRTF->Enabled = true;
	//return System::Void();
}
//Все что связано с [FileDialog(num)]
System::Void CourseWork::MyForm::openFileDialog1_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e)
{
	return System::Void();
}
System::Void CourseWork::MyForm::saveFileDialog1_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e)
{
	return System::Void();
}
System::Void CourseWork::MyForm::textBoxOutput_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
	buttonDELETE_CONFIRM->Enabled = false;
	return System::Void();
}
//Все что связано с [buttonOutput]
System::Void CourseWork::MyForm::buttonOutput_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	buttonDELETE_CONFIRM->Enabled = false;
	if (radioButtonRandom->Checked) {
		if (checkBoxTXT->Checked) {
			processing_class.random_fprint();
			Process::Start(L"Sorted.txt");
			//return System::Void();
		}
		else {
			processing_class.random_fprint();
			Process::Start(L"Sorted.rtf");
			//return System::Void();
		}
	}
	else {
		if (checkBoxTXT->Checked) {
			//construct.dumbsortfout();
			Process::Start(L"Sorted.txt");
			//return System::Void();
		}
		else {
			//construct.dumbsortfout();
			Process::Start(L"Sorted.rtf");
			//return System::Void();
		}
	}
}
//Все что связано с [Подсказками]
System::Void CourseWork::MyForm::textBox11_MouseHover(System::Object^ sender, System::EventArgs^ e)
{
	toolTip1->Show(L"Модули задаются вводом в формате Module *число* в отдельной строке, число - количество выводимых задач в каждом варианте", textBox11);
	//return System::Void();
}

System::Void CourseWork::MyForm::textBoxOutput_MouseHover(System::Object^ sender, System::EventArgs^ e)
{
	toolTip1->Show(L"Текст из файла, который можно будет редактировать после нажатия на [Изменить],\nПри нажатии разблокируется редактирование текста и если нажать [Сохранить],то\nисходный файл будет перезаписан с введенными изменениями, будьте осторожны\nЧтобы задать сложность предложения в нужной части текста напишите через пробел [ !(1-5)]\nВнимание! перед вводом сложности обязательно должен быть минимум 1 символ(Образец ввода)", textBoxOutput);

	//return System::Void();
}

System::Void CourseWork::MyForm::buttonOutput_MouseHover(System::Object^ sender, System::EventArgs^ e)
{
	toolTip1->Show(L"После выбора режима сортировки, выводит обработанный этим режимом текст в отдельном окне(txt файл)", buttonOutput);
	//return System::Void();
}

System::Void CourseWork::MyForm::buttonEDIT_MouseHover(System::Object^ sender, System::EventArgs^ e)
{
	toolTip1->Show(L"При нажатии разблокирует доступ к редактированию ввода и текста из файла", buttonEDIT);
	//return System::Void();
}

System::Void CourseWork::MyForm::buttonEDIT_SAVE_MouseHover(System::Object^ sender, System::EventArgs^ e)
{
	toolTip1->Show(L"При нажатии заблокирует доступ к редактированию ввода и текста из файла\nВ целях защиты ввода и текста из файла от нежелательного(случайного) изменения данных", buttonEDIT_SAVE);
	//return System::Void();
}

System::Void CourseWork::MyForm::buttonDELETE_MouseHover(System::Object^ sender, System::EventArgs^ e)
{
	toolTip1->Show(L"При нажатии очистит все введенные данные (данные ввода и текста из файла)", buttonDELETE);
	//return System::Void();
}

System::Void CourseWork::MyForm::labelSTART_MouseHover(System::Object^ sender, System::EventArgs^ e)
{
	toolTip1->Show(L"Для начала нажмите на [Файл] и нажмите [Открыть],\nВыберите файл с текстом для обработки и готово,\nНазвание файла должно быть без русских символов.\nПочти у всех элементов есть подсказки", labelSTART);
	//return System::Void();
}

System::Void CourseWork::MyForm::labelOutputInfo_MouseHover(System::Object^ sender, System::EventArgs^ e)
{
	//toolTip1->Show(L"Чтобы задать сложность предложения в нужной части текста напишите через пробел [ !(1-5)]\nВнимание! для работы [Баланс] и [по Сложности] перед вводом сложности обязательно должен быть минимум 1 символ\n(Образец ввода)\nЯблоко !5Машина\nЯблоко Машина !5\nЯбл !5око Машина\nНо не  !5Яблоко Машина!", labelOutputInfo);
	//return System::Void();
}

//Все что связано с [textBox(Num)_ValueChanged]
System::Void CourseWork::MyForm::textBox1_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{	
	try {
		if (textBox1->Text == "0") {
			return System::Void();
		}
		else {
			buttonDELETE->Enabled = true;
			buttonEDIT->Enabled = false;
			processing_class.calcualte_max_variants_quantity();
			processing_class.variants(stoi(marshal_as<std::string>(textBox1->Text)));
		}
	}
	catch (std::string a) {
		buttonDELETE->Enabled = true;
		buttonEDIT->Enabled = false;
		processing_class.calcualte_max_variants_quantity();
		processing_class.variants(processing_class.max_variants());
	}
}

//Все что связано с [checkBox(Type)_CheckedChanged]
System::Void CourseWork::MyForm::checkBoxTXT_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (checkBoxTXT->Checked) {
		processing_class.fprint_mode('t');
		checkBoxRTF->Enabled = false;
		buttonOutput->Enabled = true;
	}
	else {
		checkBoxRTF->Enabled = true;
		checkBoxTXT->Enabled = true;
		buttonOutput->Enabled = false;
	}
}

System::Void CourseWork::MyForm::checkBoxRTF_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (checkBoxRTF->Checked) {
		processing_class.fprint_mode('r');
		checkBoxTXT->Enabled = false;
		buttonOutput->Enabled = true;
	}
	else {
		checkBoxRTF->Enabled = true;
		checkBoxTXT->Enabled = true;
		buttonOutput->Enabled = false;
	}
}
