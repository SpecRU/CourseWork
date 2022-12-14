#include <windows.h>
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

std::wstring utf8_decode(const std::wstring& instr) {
	const std::string str(instr.begin(), instr.end());
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}

std::string unicode2ansi(const std::wstring& wstr) {
	int size_needed = WideCharToMultiByte(CP_ACP, 0, &wstr[0], -1, NULL, 0, NULL, NULL);
	std::string strTo(size_needed, 0);
	WideCharToMultiByte(CP_ACP, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
	strTo.pop_back();
	return strTo;
}

bool operator<(const varsS& a, const varsS& b) { return a.diff < b.diff; }
bool operator==(const varsS& a, const varsS& b) { return a.str == b.str && a.diff == b.diff && a.module == b.module; }
bool operator!=(const varsS& a, const varsS& b) { return a.str != b.str && a.diff != b.diff && a.module != b.module; }
void operator-=(std::vector<varsS>& a, const std::vector<varsS>& b)
{
	std::vector<varsS>::iterator it = a.begin();
	std::vector<varsS>::const_iterator it2 = b.begin();

	while (it != a.end()) {
		while (it2 != b.end() && it != a.end()) {
			if (*it == *it2) {
				it = a.erase(it);
				it2 = b.begin();
			}
			else
				++it2;
		}
		if (it != a.end()) ++it;
		it2 = b.begin();
	}
}

void ticket::inputv(const int& vin) {
	vQ = vin;
}

void ticket::inputq(const int& qin) {
	qQ = qin;
}

void ticket::input() {
	vars.clear();
	isHard = false;
}

void ticket::input(const std::string inpath) {
	std::wifstream fin(inpath);
	isHard = false;

	varsS initial;
	std::wstring inTmp;
	int hardPos, modulePos, current_module, coun = 0;
	if (fin.is_open()) {
		while (getline(fin, inTmp)) {
			vars.push_back(initial);
			hardPos = hardness(std::wstring(inTmp));
			modulePos = module(std::wstring(inTmp));
			if (modulePos) {
				vars.at(coun).module = std::stoi(&inTmp[hardPos + 8]) + std::stoi(&inTmp[hardPos + 9]);
				inTmp.erase(inTmp.begin() + hardPos, inTmp.begin() + hardPos + 9);
			}
			if (hardPos) {
				isHard = true;
				vars.at(coun).diff = std::stoi(&inTmp[hardPos + 2]);
				inTmp.erase(inTmp.begin() + hardPos, inTmp.begin() + hardPos + 3);
			}
			else {
				vars.at(coun).diff = 6;
			};

			vars.at(coun).str = inTmp;
			++coun;
		}
		fin.close();
	}
	else MessageBox::Show(L"Ошибка открытия файла ввода!", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
}

int ticket::hardness(const std::wstring& in) {
	std::wregex temp(L"\s![1-5]");
	std::wsregex_iterator find{ in.begin(), in.end(), temp };
	std::wsregex_iterator end{};

	for (auto i = find; i != end; ++i) return i->position();
	return 0;
}

int ticket::module(const std::wstring& in) {
	std::wregex temp(L"!Модуль [0-9][0-9]");
	std::wsregex_iterator find{ in.begin(), in.end(), temp };
	std::wsregex_iterator end{};

	for (auto i = find; i != end; ++i) return i->position();
	return 0;
}

void ticket::output(const char& outm) {
	outmode[0] = outm;
}

int ticket::output()
{
	return vars.size();
}

void ticket::output(const std::vector<varsS>& vec) {
	int coun = 0, counv = 0;
	if (outmode[0] == 'r') {
		std::ofstream fout("Sorted.rtf");

		if (fout.is_open()) {
			for (const varsS& i : vec) {
				if (!i.diff) {
					counv++;
					fout << std::endl << "Вариант " << counv << ":" << std::endl;
					coun = 0;
				}
				else {
					++coun;
					fout << coun << (". ") << unicode2ansi(utf8_decode(i.str));
					if (isHard) fout << " : " << i.diff;
					fout << std::endl;
				}
			}
			fout.close();
		}
		else MessageBox::Show(L"Ошибка открытия файла вывода!", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
	else {
		std::wofstream fout("Sorted.txt");

		if (fout.is_open()) {
			for (const varsS& i : vec) {
				if (!i.diff) {
					counv++;
					fout << std::endl << L"ÐÐ°ÑÐ¸Ð°Ð½Ñ " << counv << L":" << std::endl;
					coun = 0;
				}
				else {
					++coun;
					fout << coun << L". " << i.str;
					if (isHard) fout << L" : " << i.diff;
					fout << std::endl;
				}
			}
			fout.close();
		}
		else MessageBox::Show(L"Ошибка открытия файла вывода!", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}

void ticket::dumbsortfout() {
	std::vector <varsS> sorted, inp = vars;
	varsS null{ null.diff = 0 };
	std::stable_sort(inp.begin(), inp.end());

	for (int i = 0; i < vQ; ++i) {
		if (!inp.size()) break;

		sorted.push_back(null);

		if (inp.size() < qQ) {
			for (const varsS& i : inp) sorted.push_back(i);
			inp.clear();
			break;
		};

		for (int k = 0; k < qQ; ++k) {
			sorted.push_back(inp[0]);
			inp.erase(inp.begin());
		}
	}

	output(sorted);
}

void ticket::randsortfout() {
	std::vector <varsS> sorted;
	std::vector <varsS> used;
	varsS null{ null.diff = 0 };
	varsS it;

	for (int i = 0; i < vQ; ++i) {
		sorted.push_back(null);
		used.clear();
		for (int k = i * vQ; k < i * vQ + qQ; ++k) {
			it = vars_substr_vec(used, k);
			sorted.push_back(it);
			used.push_back(it);
		}
	}

	output(sorted);
}

varsS ticket::vars_substr_vec(std::vector<varsS>& used, const int& seed) {
	std::vector <varsS> vec = vars;

	if (used.size())vec -= used;

	srand(unsigned(time(NULL)) + seed);
	return vec[(rand() % vec.size() + 1) - 1];
}

void ticket::balancesortfout() {
	std::vector <varsS> sorted, used, in = vars;
	varsS used1elem;
	varsS null{ null.diff = 0 };

	for (int i = in.size(); i <= qQ * vQ; ++i) {
		in.push_back(vars_substr_vec(used, i));
	}

	stable_sort(in.rbegin(), in.rend());

	int mid = 0;
	for (const varsS& i : in) {
		mid += i.diff;
	}
	mid = ceil((mid + .0) / vQ);

	int tmp;
	for (int i = 0; i < vQ; ++i) {
		if (i) used1elem = used[0];
		tmp = 0, used.clear();

		if (!in.size()) break;

		sorted.push_back(null);

		for (int k = 0; k < in.size(); ++k) {
			if ((tmp + in.at(k).diff <= mid) && (std::find(used.begin(), used.end(), in[k]) == used.end())) {
				if (i && in[k] == used1elem) continue;
					used.push_back(in[k]);
					tmp += in.at(k).diff;
					sorted.push_back(in[k]);
					in.erase(in.begin() + k);
			}
		}
	}

	output(sorted);
} 

bool ticket::hardness() {
	return isHard;
}

std::string FilePath;
ticket construct;
[STAThreadAttribute]
void main(array<String^>^ args) {
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
	construct.input();
	radioButtonRandom->Enabled = false;
	radioButtonBalance->Enabled = false;
	radioButtonDiff->Enabled = false;
	radioButtonRandom->Checked = false;
	radioButtonBalance->Checked = false;
	radioButtonDiff->Checked = false;
	checkBoxTXT->Enabled = false;
	checkBoxRTF->Enabled = false;
	buttonOutput->Enabled = false;
	buttonEDIT->Enabled = false;
	buttonDELETE_CONFIRM->Enabled = false;
	buttonDELETE->Enabled = false;
	textBox1->Enabled = true;
	textBox2->Enabled = true;
	textBox1->Text = "0";
	textBox2->Text = "0";
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
		construct.input();
		FilePath = marshal_as<std::string>(FilenameOpen);
		//MessageBox::Show(this, FilenameOpen, L"Инфо", MessageBoxButtons::OK, MessageBoxIcon::Error);
		construct.input(FilePath);
	}
	catch (Exception^ e) {
		MessageBox::Show(this, L"Неудачно", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
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
	textBox2->Enabled = true;
	textBoxOutput->Enabled = true;
	radioButtonRandom->Enabled = false;
	radioButtonBalance->Enabled = false;
	radioButtonDiff->Enabled = false;
	radioButtonRandom->Checked = false;
	radioButtonBalance->Checked = false;
	radioButtonDiff->Checked = false;
	checkBoxTXT->Enabled = false;
	checkBoxRTF->Enabled = false;
	buttonOutput->Enabled = false;
	//return System::Void();
}
System::Void CourseWork::MyForm::buttonEDIT_SAVE_Click(System::Object^ sender, System::EventArgs^ e)
{
	if ((textBox1->Text == "0" && textBox2->Text == "0") || (textBox1->Text != "0" && textBox2->Text == "0") || (textBox1->Text == "0" && textBox2->Text != "0")) {
		MessageBox::Show(this, L"Введите количество больше 0", L"Внимание", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return System::Void();
	}
	else {
		buttonDELETE_CONFIRM->Enabled = false;
		buttonEDIT_SAVE->Enabled = false;
		textBox1->Enabled = false;
		textBox2->Enabled = false;
		textBoxOutput->Enabled = false;
		buttonEDIT_SAVE->Enabled = false;
		buttonEDIT->Enabled = true;
		StreamWriter^ strwr = gcnew StreamWriter(marshal_as<String^>(FilePath));
		strwr->Write(textBoxOutput->Text);
		strwr->Close();
		construct.input();
		construct.input(FilePath);
		if (construct.hardness() == 0) {
			radioButtonBalance->Enabled = false;
			radioButtonDiff->Enabled = false;
			radioButtonRandom->Enabled = true;
		}
		else
		{
			radioButtonBalance->Enabled = true;
			radioButtonDiff->Enabled = true;
			radioButtonRandom->Enabled = true;
		}
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
	textBox1->Text = "0";
	textBox2->Text = "0";
	textBoxOutput->Text = "";
	construct.input();
	textBox1->Enabled = false;
	textBox2->Enabled = false;
	textBoxOutput->Enabled = false;
	buttonEDIT->Enabled = false;
	buttonEDIT_SAVE->Enabled = false;
	radioButtonRandom->Enabled = false;
	radioButtonBalance->Enabled = false;
	radioButtonDiff->Enabled = false;
	radioButtonRandom->Checked = false;
	radioButtonBalance->Checked = false;
	radioButtonDiff->Checked = false;
	buttonOutput->Enabled = false;
	buttonDELETE_CONFIRM->Enabled = false;
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
			construct.randsortfout();
			Process::Start(L"Sorted.txt");
			//return System::Void();
		}
		else {
			construct.randsortfout();
			Process::Start(L"Sorted.rtf");
			//return System::Void();
		}
	}
	else if (radioButtonBalance->Checked) {
		if (checkBoxTXT->Checked) {
			construct.balancesortfout();
			Process::Start(L"Sorted.txt");
			//return System::Void();
		}
		else {
			construct.balancesortfout();
			Process::Start(L"Sorted.rtf");
			//return System::Void();
		}
	}
	else {
		if (checkBoxTXT->Checked) {
			construct.dumbsortfout();
			Process::Start(L"Sorted.txt");
			//return System::Void();
		}
		else {
			construct.dumbsortfout();
			Process::Start(L"Sorted.rtf");
			//return System::Void();
		}
	}
}
//Все что связано с [Подсказками]
System::Void CourseWork::MyForm::textBox11_MouseHover(System::Object^ sender, System::EventArgs^ e)
{
	toolTip1->Show(L"Отвечает за то, на сколько вариантов будет раздроблен текст", textBox11);
	//return System::Void();
}
System::Void CourseWork::MyForm::textBox22_MouseHover(System::Object^ sender, System::EventArgs^ e)
{
	toolTip1->Show(L"Отвечает за то, сколько вопросов будет в варианте", textBox22);
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
	toolTip1->Show(L"Чтобы задать сложность предложения в нужной части текста напишите через пробел [ !(1-5)]\nВнимание! для работы [Баланс] и [по Сложности] перед вводом сложности обязательно должен быть минимум 1 символ\n(Образец ввода)\nЯблоко !5Машина\nЯблоко Машина !5\nЯбл !5око Машина\nНо не  !5Яблоко Машина!", labelOutputInfo);
	//return System::Void();
}
//Все что связано с [textBox(Num)_ValueChanged]
System::Void CourseWork::MyForm::textBox1_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (textBox1->Text == "0") {
		return System::Void();
	}
	else {
		buttonDELETE->Enabled = true;
		buttonEDIT->Enabled = false;
		construct.inputv(stoi(marshal_as<std::string>(textBox1->Text)));
	}
}

System::Void CourseWork::MyForm::textBox2_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (construct.output() < stoi(marshal_as<std::string>(textBox2->Text))) {
		MessageBox::Show(this, L"Число вопросов должно быть больше чем строк на вводе", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return System::Void();
	}
	if (textBox2->Text == "0") {
		return System::Void();
	}
	else {
		buttonDELETE->Enabled = true;
		buttonEDIT->Enabled = false;
		construct.inputq(stoi(marshal_as<std::string>(textBox2->Text)));
	}
}
//Все что связано с [checkBox(Type)_CheckedChanged]
System::Void CourseWork::MyForm::checkBoxTXT_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (checkBoxTXT->Checked) {
		construct.output('t');
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
		construct.output('r');
		checkBoxTXT->Enabled = false;
		buttonOutput->Enabled = true;
	}
	else {
		checkBoxRTF->Enabled = true;
		checkBoxTXT->Enabled = true;
		buttonOutput->Enabled = false;
	}
}
