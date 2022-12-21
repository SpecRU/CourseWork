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

//bool operator<(const varsS& a, const varsS& b) { return a.diff < b.diff; }
//bool operator==(const varsS& a, const varsS& b) { return a.str == b.str && a.diff == b.diff && a.module == b.module; }
//bool operator!=(const varsS& a, const varsS& b) { return a.str != b.str && a.diff != b.diff && a.module != b.module; }
/*void operator-=(std::vector<varsS>& a, const std::vector<varsS>& b)
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
} */

void ticket::variants(const int& variants) {
	variant_quantity = variants;
}

void ticket::vars_clear() {
	vars.clear();
}

void ticket::tasks(const int& tasks) {
	tasks_quantity = tasks;
}

short int ticket::scan(const std::string input_path) {
	std::wifstream input_stream(input_path);
	std::wstring input_Tmp;
	std::vector <std::wstring> init;
	vars.push_back(init);

	int modulePos = 0, module_out_quantity = -1, i = 0, scanned_tasks_quantity = 0;
	if (input_stream.is_open()) {
		while (getline(input_stream, input_Tmp)) {
			modulePos = module(input_Tmp);
			if (modulePos) {
				module_out_quantity = std::stoi(&input_Tmp[modulePos + 8]) * 10 + std::stoi(&input_Tmp[modulePos + 9]);
				vars[i].push_back(std::to_wstring(module_out_quantity));
				vars.push_back(init);
				input_Tmp.erase(input_Tmp.begin() + modulePos, input_Tmp.begin() + modulePos + 10);
				scanned_tasks_quantity = 0;
				++i;
			}
			++scanned_tasks_quantity;
			if (module_out_quantity > scanned_tasks_quantity && module_out_quantity != -1) {
				return 2;
			}
			vars[i].push_back(input_Tmp);
		};
		input_stream.close();
		return 0;
	}
	else {
		return 1;
	}
}

int ticket::module(const std::wstring& str) {
	std::wregex filter(L"\n!Module [0-9][0-9]");
	std::wsregex_iterator find{ str.begin(), str.end(), filter };
	std::wsregex_iterator end{};

	for (auto i = find; i != end; ++i) {
		return i->position();
	}
	return 0;
}

void ticket::fprint_mode(const char& mode) {
	output_mode[0] = mode;
}

int ticket::size()
{
	return vars.size();
}

void ticket::fprint(const std::vector <std::vector <std::wstring>>& vec) {
	int current_variant = 0, current_task = 1;

	if (output_mode[0] == 'r') {
		std::ofstream fout("Sorted.rtf");
		if (fout.is_open()) {
			for (int i = 0; i < vec.size(); ++i) {
				current_task = 1;
				fout << std::endl << "Вариант " << current_variant << ":" << std::endl;
				for (int k = 0; k < vec[i].size(); ++k) {
					fout << current_task << (". ") << unicode2ansi(utf8_decode(vec[i][k]));
					++current_task;
				}
				fout.close();
			}
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
					fout << current_task << (L". ") << vec[i][k];
					++current_task;
				}
				fout.close();
			}
		}
		else MessageBox::Show(L"Ошибка открытия файла вывода", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}

/*void ticket::randsortfout() {
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
} */

void ticket::random_fprint() {
	std::vector <std::vector <std::wstring>> sorted;
	

	//size(sorted);
}

/*varsS ticket::vars_substr_vec(std::vector<varsS>& used, const int& seed) {
	std::vector <varsS> vec = vars;

	if (used.size())vec -= used;

	srand(unsigned(time(NULL)) + seed);
	return vec[(rand() % vec.size() + 1) - 1];
} */

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
	processing_class.vars_clear();
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
		processing_class.vars_clear();
		//MessageBox::Show(this, FilenameOpen, L"Инфо", MessageBoxButtons::OK, MessageBoxIcon::Error);
		short int err = processing_class.scan(marshal_as<std::string>(FilenameOpen));
		if (err == 1) {
			throw 1;
		}
		if (err == 2) {
			throw 2;
		}
	}
	catch (short int err) {
		if (err == 1) {
			MessageBox::Show(L"Ошибка открытия файла ввода", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			CourseWork::MyForm::Clear();
		}
		if (err == 2) {
			MessageBox::Show(L"Ошибка, количество выводимых вопросов превышает их число", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			CourseWork::MyForm::Clear();
		}
	}
	catch (Exception^ e) {
		MessageBox::Show(this, L"Ошибка чтения файла", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
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
	if (textBox1->Text == "0") {
		MessageBox::Show(this, L"Введите количество больше 0", L"Внимание", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return System::Void();
	}
	else {
		buttonDELETE_CONFIRM->Enabled = false;
		buttonEDIT_SAVE->Enabled = false;
		textBox1->Enabled = false;
		textBoxOutput->Enabled = false;
		buttonEDIT_SAVE->Enabled = false;
		buttonEDIT->Enabled = true;
		StreamWriter^ strwr = gcnew StreamWriter(marshal_as<String^>(FilePath));
		strwr->Write(textBoxOutput->Text);
		strwr->Close();
		processing_class.vars_clear();
		processing_class.scan(FilePath);
		radioButtonBalance->Enabled = false;
		radioButtonDiff->Enabled = false;
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
	processing_class.vars_clear();
	textBox1->Enabled = false;
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
	toolTip1->Show(L"Отвечает за то, на сколько вариантов будет раздроблен текст", textBox11);
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
		processing_class.variants(stoi(marshal_as<std::string>(textBox1->Text)));
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
