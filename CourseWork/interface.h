#pragma once

namespace CourseWork {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:

		MyForm(void)
		{
			InitializeComponent();
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ файлToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ открытьToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ выходToolStripMenuItem;
	private: System::Windows::Forms::ContextMenuStrip^ contextMenuStrip1;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
	private: System::Windows::Forms::ContextMenuStrip^ contextMenuStrip2;
	private: System::Windows::Forms::Label^ labelVars;
	private: System::Windows::Forms::Label^ labelSorting;
	private: System::Windows::Forms::TextBox^ textBoxOutput;
	private: System::Windows::Forms::RadioButton^ radioButtonRandom;
	private: System::Windows::Forms::RadioButton^ radioButtonBalance;
	private: System::Windows::Forms::RadioButton^ radioButtonDiff;
	private: System::Windows::Forms::FolderBrowserDialog^ folderBrowserDialog1;
	private: System::Windows::Forms::Button^ buttonEDIT;
	private: System::Windows::Forms::Button^ buttonDELETE;
	private: System::Windows::Forms::Button^ buttonEDIT_SAVE;
	private: System::Windows::Forms::Button^ buttonDELETE_CONFIRM;
	private: System::Windows::Forms::ToolTip^ toolTip1;
	private: System::Windows::Forms::Label^ labelSTART;
	private: System::Windows::Forms::Button^ buttonOutput;
	private: System::Windows::Forms::Label^ labelQuestions;
	private: System::ComponentModel::BackgroundWorker^ backgroundWorker1;
	private: System::Windows::Forms::CheckBox^ checkBoxTXT;
	private: System::Windows::Forms::CheckBox^ checkBoxRTF;
	private: System::Windows::Forms::NumericUpDown^ textBox1;
	private: System::Windows::Forms::NumericUpDown^ textBox2;
	private: System::Windows::Forms::Label^ textBox11;
	private: System::Windows::Forms::Label^ textBox22;
	private: System::Windows::Forms::Label^ labelOutputInfo;
	private: System::Windows::Forms::ToolStripSeparator^ toolStripMenuItem2;
	private: System::Windows::Forms::Label^ label1;
	private: System::ComponentModel::IContainer^ components;
	public:
#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->файлToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->открытьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->выходToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->contextMenuStrip2 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->labelVars = (gcnew System::Windows::Forms::Label());
			this->labelSorting = (gcnew System::Windows::Forms::Label());
			this->textBoxOutput = (gcnew System::Windows::Forms::TextBox());
			this->radioButtonRandom = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonBalance = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonDiff = (gcnew System::Windows::Forms::RadioButton());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->buttonEDIT = (gcnew System::Windows::Forms::Button());
			this->buttonDELETE = (gcnew System::Windows::Forms::Button());
			this->buttonEDIT_SAVE = (gcnew System::Windows::Forms::Button());
			this->buttonDELETE_CONFIRM = (gcnew System::Windows::Forms::Button());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->labelSTART = (gcnew System::Windows::Forms::Label());
			this->buttonOutput = (gcnew System::Windows::Forms::Button());
			this->labelQuestions = (gcnew System::Windows::Forms::Label());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->checkBoxTXT = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxRTF = (gcnew System::Windows::Forms::CheckBox());
			this->textBox1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->textBox2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->textBox11 = (gcnew System::Windows::Forms::Label());
			this->textBox22 = (gcnew System::Windows::Forms::Label());
			this->labelOutputInfo = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->textBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->textBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(28, 28);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->файлToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(688, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// файлToolStripMenuItem
			// 
			this->файлToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->открытьToolStripMenuItem,
					this->toolStripMenuItem2, this->выходToolStripMenuItem
			});
			this->файлToolStripMenuItem->Name = L"файлToolStripMenuItem";
			this->файлToolStripMenuItem->Size = System::Drawing::Size(48, 20);
			this->файлToolStripMenuItem->Text = L"Файл";
			this->файлToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::файлToolStripMenuItem_Click);
			// 
			// открытьToolStripMenuItem
			// 
			this->открытьToolStripMenuItem->Name = L"открытьToolStripMenuItem";
			this->открытьToolStripMenuItem->Size = System::Drawing::Size(130, 22);
			this->открытьToolStripMenuItem->Text = L"Открыть...";
			this->открытьToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::открытьToolStripMenuItem_Click);
			// 
			// toolStripMenuItem2
			// 
			this->toolStripMenuItem2->Name = L"toolStripMenuItem2";
			this->toolStripMenuItem2->Size = System::Drawing::Size(127, 6);
			// 
			// выходToolStripMenuItem
			// 
			this->выходToolStripMenuItem->Name = L"выходToolStripMenuItem";
			this->выходToolStripMenuItem->Size = System::Drawing::Size(130, 22);
			this->выходToolStripMenuItem->Text = L"Выход";
			this->выходToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::выходToolStripMenuItem_Click);
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->ImageScalingSize = System::Drawing::Size(28, 28);
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(61, 4);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openFileDialog1_FileOk);
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::saveFileDialog1_FileOk);
			// 
			// contextMenuStrip2
			// 
			this->contextMenuStrip2->ImageScalingSize = System::Drawing::Size(28, 28);
			this->contextMenuStrip2->Name = L"contextMenuStrip2";
			this->contextMenuStrip2->Size = System::Drawing::Size(61, 4);
			// 
			// labelVars
			// 
			this->labelVars->AutoSize = true;
			this->labelVars->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelVars->Location = System::Drawing::Point(13, 24);
			this->labelVars->Name = L"labelVars";
			this->labelVars->Size = System::Drawing::Size(183, 16);
			this->labelVars->TabIndex = 13;
			this->labelVars->Text = L"Введите кол-во вариантов";
			this->labelVars->Click += gcnew System::EventHandler(this, &MyForm::labelVars_Click);
			// 
			// labelSorting
			// 
			this->labelSorting->AutoSize = true;
			this->labelSorting->Location = System::Drawing::Point(22, 124);
			this->labelSorting->Name = L"labelSorting";
			this->labelSorting->Size = System::Drawing::Size(156, 13);
			this->labelSorting->TabIndex = 17;
			this->labelSorting->Text = L"Выберите режим сортировки";
			// 
			// textBoxOutput
			// 
			this->textBoxOutput->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBoxOutput->Enabled = false;
			this->textBoxOutput->HideSelection = false;
			this->textBoxOutput->Location = System::Drawing::Point(219, 6);
			this->textBoxOutput->MaxLength = 999999999;
			this->textBoxOutput->Multiline = true;
			this->textBoxOutput->Name = L"textBoxOutput";
			this->textBoxOutput->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->textBoxOutput->Size = System::Drawing::Size(455, 288);
			this->textBoxOutput->TabIndex = 18;
			this->textBoxOutput->WordWrap = false;
			this->textBoxOutput->TextChanged += gcnew System::EventHandler(this, &MyForm::textBoxOutput_TextChanged);
			this->textBoxOutput->MouseHover += gcnew System::EventHandler(this, &MyForm::textBoxOutput_MouseHover);
			// 
			// radioButtonRandom
			// 
			this->radioButtonRandom->AutoSize = true;
			this->radioButtonRandom->Enabled = false;
			this->radioButtonRandom->Location = System::Drawing::Point(116, 164);
			this->radioButtonRandom->Name = L"radioButtonRandom";
			this->radioButtonRandom->Size = System::Drawing::Size(72, 17);
			this->radioButtonRandom->TabIndex = 8;
			this->radioButtonRandom->TabStop = true;
			this->radioButtonRandom->Text = L"Случайно";
			this->radioButtonRandom->UseVisualStyleBackColor = true;
			this->radioButtonRandom->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButtonRandom_CheckedChanged);
			// 
			// radioButtonBalance
			// 
			this->radioButtonBalance->AutoSize = true;
			this->radioButtonBalance->Enabled = false;
			this->radioButtonBalance->Location = System::Drawing::Point(16, 141);
			this->radioButtonBalance->Name = L"radioButtonBalance";
			this->radioButtonBalance->Size = System::Drawing::Size(62, 17);
			this->radioButtonBalance->TabIndex = 9;
			this->radioButtonBalance->TabStop = true;
			this->radioButtonBalance->Text = L"Баланс";
			this->radioButtonBalance->UseVisualStyleBackColor = true;
			this->radioButtonBalance->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButtonBalance_CheckedChanged);
			// 
			// radioButtonDiff
			// 
			this->radioButtonDiff->AutoSize = true;
			this->radioButtonDiff->Enabled = false;
			this->radioButtonDiff->Location = System::Drawing::Point(16, 164);
			this->radioButtonDiff->Name = L"radioButtonDiff";
			this->radioButtonDiff->Size = System::Drawing::Size(97, 17);
			this->radioButtonDiff->TabIndex = 10;
			this->radioButtonDiff->TabStop = true;
			this->radioButtonDiff->Text = L"По сложности";
			this->radioButtonDiff->UseVisualStyleBackColor = true;
			this->radioButtonDiff->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButtonDiff_CheckedChanged);
			// 
			// buttonEDIT
			// 
			this->buttonEDIT->Enabled = false;
			this->buttonEDIT->Location = System::Drawing::Point(16, 239);
			this->buttonEDIT->Name = L"buttonEDIT";
			this->buttonEDIT->Size = System::Drawing::Size(85, 30);
			this->buttonEDIT->TabIndex = 3;
			this->buttonEDIT->Text = L"Изменить";
			this->buttonEDIT->UseVisualStyleBackColor = true;
			this->buttonEDIT->Click += gcnew System::EventHandler(this, &MyForm::buttonEDIT_Click);
			this->buttonEDIT->MouseHover += gcnew System::EventHandler(this, &MyForm::buttonEDIT_MouseHover);
			// 
			// buttonDELETE
			// 
			this->buttonDELETE->Enabled = false;
			this->buttonDELETE->Location = System::Drawing::Point(16, 275);
			this->buttonDELETE->Name = L"buttonDELETE";
			this->buttonDELETE->Size = System::Drawing::Size(85, 30);
			this->buttonDELETE->TabIndex = 4;
			this->buttonDELETE->Text = L"Удалить";
			this->buttonDELETE->UseVisualStyleBackColor = true;
			this->buttonDELETE->Click += gcnew System::EventHandler(this, &MyForm::buttonDELETE_Click);
			this->buttonDELETE->MouseHover += gcnew System::EventHandler(this, &MyForm::buttonDELETE_MouseHover);
			// 
			// buttonEDIT_SAVE
			// 
			this->buttonEDIT_SAVE->Enabled = false;
			this->buttonEDIT_SAVE->Location = System::Drawing::Point(107, 239);
			this->buttonEDIT_SAVE->Name = L"buttonEDIT_SAVE";
			this->buttonEDIT_SAVE->Size = System::Drawing::Size(85, 30);
			this->buttonEDIT_SAVE->TabIndex = 6;
			this->buttonEDIT_SAVE->Text = L"Сохранить";
			this->buttonEDIT_SAVE->UseVisualStyleBackColor = true;
			this->buttonEDIT_SAVE->Click += gcnew System::EventHandler(this, &MyForm::buttonEDIT_SAVE_Click);
			this->buttonEDIT_SAVE->MouseHover += gcnew System::EventHandler(this, &MyForm::buttonEDIT_SAVE_MouseHover);
			// 
			// buttonDELETE_CONFIRM
			// 
			this->buttonDELETE_CONFIRM->Enabled = false;
			this->buttonDELETE_CONFIRM->Location = System::Drawing::Point(111, 275);
			this->buttonDELETE_CONFIRM->Name = L"buttonDELETE_CONFIRM";
			this->buttonDELETE_CONFIRM->Size = System::Drawing::Size(85, 30);
			this->buttonDELETE_CONFIRM->TabIndex = 7;
			this->buttonDELETE_CONFIRM->Text = L"Подтвердить";
			this->buttonDELETE_CONFIRM->UseVisualStyleBackColor = true;
			this->buttonDELETE_CONFIRM->Click += gcnew System::EventHandler(this, &MyForm::buttonDELETE_CONFIRM_Click);
			// 
			// labelSTART
			// 
			this->labelSTART->AutoSize = true;
			this->labelSTART->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelSTART->Location = System::Drawing::Point(56, 6);
			this->labelSTART->Name = L"labelSTART";
			this->labelSTART->Size = System::Drawing::Size(152, 13);
			this->labelSTART->TabIndex = 25;
			this->labelSTART->Text = L"[Наведитесь для подсказки]";
			this->labelSTART->MouseHover += gcnew System::EventHandler(this, &MyForm::labelSTART_MouseHover);
			// 
			// buttonOutput
			// 
			this->buttonOutput->Enabled = false;
			this->buttonOutput->Location = System::Drawing::Point(16, 203);
			this->buttonOutput->Name = L"buttonOutput";
			this->buttonOutput->Size = System::Drawing::Size(176, 30);
			this->buttonOutput->TabIndex = 26;
			this->buttonOutput->Text = L"Вывод";
			this->buttonOutput->UseVisualStyleBackColor = true;
			this->buttonOutput->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::buttonOutput_MouseClick);
			this->buttonOutput->MouseHover += gcnew System::EventHandler(this, &MyForm::buttonOutput_MouseHover);
			// 
			// labelQuestions
			// 
			this->labelQuestions->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelQuestions->Location = System::Drawing::Point(13, 66);
			this->labelQuestions->Name = L"labelQuestions";
			this->labelQuestions->Size = System::Drawing::Size(180, 35);
			this->labelQuestions->TabIndex = 27;
			this->labelQuestions->Text = L"Введите кол-во вопросов из каждого модуля";
			this->labelQuestions->Click += gcnew System::EventHandler(this, &MyForm::labelQuestions_Click);
			// 
			// checkBoxTXT
			// 
			this->checkBoxTXT->AutoSize = true;
			this->checkBoxTXT->Enabled = false;
			this->checkBoxTXT->Location = System::Drawing::Point(148, 183);
			this->checkBoxTXT->Name = L"checkBoxTXT";
			this->checkBoxTXT->Size = System::Drawing::Size(40, 17);
			this->checkBoxTXT->TabIndex = 29;
			this->checkBoxTXT->Text = L".txt";
			this->checkBoxTXT->UseVisualStyleBackColor = true;
			this->checkBoxTXT->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBoxTXT_CheckedChanged);
			// 
			// checkBoxRTF
			// 
			this->checkBoxRTF->AutoSize = true;
			this->checkBoxRTF->Enabled = false;
			this->checkBoxRTF->Location = System::Drawing::Point(184, 183);
			this->checkBoxRTF->Name = L"checkBoxRTF";
			this->checkBoxRTF->Size = System::Drawing::Size(38, 17);
			this->checkBoxRTF->TabIndex = 31;
			this->checkBoxRTF->Text = L".rtf";
			this->checkBoxRTF->UseVisualStyleBackColor = true;
			this->checkBoxRTF->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBoxRTF_CheckedChanged);
			// 
			// textBox1
			// 
			this->textBox1->Enabled = false;
			this->textBox1->Location = System::Drawing::Point(16, 43);
			this->textBox1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(176, 20);
			this->textBox1->TabIndex = 32;
			this->textBox1->ValueChanged += gcnew System::EventHandler(this, &MyForm::textBox1_ValueChanged);
			// 
			// textBox2
			// 
			this->textBox2->Enabled = false;
			this->textBox2->Location = System::Drawing::Point(16, 101);
			this->textBox2->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(176, 20);
			this->textBox2->TabIndex = 33;
			this->textBox2->ValueChanged += gcnew System::EventHandler(this, &MyForm::textBox2_ValueChanged);
			// 
			// textBox11
			// 
			this->textBox11->AutoSize = true;
			this->textBox11->Location = System::Drawing::Point(195, 45);
			this->textBox11->Name = L"textBox11";
			this->textBox11->Size = System::Drawing::Size(13, 13);
			this->textBox11->TabIndex = 34;
			this->textBox11->Text = L"\?";
			this->textBox11->Click += gcnew System::EventHandler(this, &MyForm::textBox11_Click);
			this->textBox11->MouseHover += gcnew System::EventHandler(this, &MyForm::textBox11_MouseHover);
			// 
			// textBox22
			// 
			this->textBox22->AutoSize = true;
			this->textBox22->Location = System::Drawing::Point(195, 103);
			this->textBox22->Name = L"textBox22";
			this->textBox22->Size = System::Drawing::Size(13, 13);
			this->textBox22->TabIndex = 35;
			this->textBox22->Text = L"\?";
			this->textBox22->MouseHover += gcnew System::EventHandler(this, &MyForm::textBox22_MouseHover);
			// 
			// labelOutputInfo
			// 
			this->labelOutputInfo->AutoSize = true;
			this->labelOutputInfo->Location = System::Drawing::Point(80, 143);
			this->labelOutputInfo->Name = L"labelOutputInfo";
			this->labelOutputInfo->Size = System::Drawing::Size(30, 13);
			this->labelOutputInfo->TabIndex = 36;
			this->labelOutputInfo->Text = L"←\?↓";
			this->labelOutputInfo->MouseHover += gcnew System::EventHandler(this, &MyForm::labelOutputInfo_MouseHover);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(7, 183);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(135, 13);
			this->label1->TabIndex = 37;
			this->label1->Text = L"Выберите режим вывода";
			this->label1->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
			// 
			// MyForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->ClientSize = System::Drawing::Size(688, 308);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->labelOutputInfo);
			this->Controls->Add(this->textBox22);
			this->Controls->Add(this->textBox11);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->checkBoxRTF);
			this->Controls->Add(this->checkBoxTXT);
			this->Controls->Add(this->labelQuestions);
			this->Controls->Add(this->buttonOutput);
			this->Controls->Add(this->labelSTART);
			this->Controls->Add(this->textBoxOutput);
			this->Controls->Add(this->labelSorting);
			this->Controls->Add(this->labelVars);
			this->Controls->Add(this->radioButtonDiff);
			this->Controls->Add(this->radioButtonBalance);
			this->Controls->Add(this->radioButtonRandom);
			this->Controls->Add(this->buttonDELETE_CONFIRM);
			this->Controls->Add(this->buttonEDIT_SAVE);
			this->Controls->Add(this->buttonDELETE);
			this->Controls->Add(this->buttonEDIT);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Show;
			this->Text = L"Конструктор Экзаменационных Билетов";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->textBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->textBox2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e);
	private: System::Void файлToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void выходToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void открытьToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void buttonEDIT_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void buttonDELETE_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void buttonEDIT_SAVE_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void buttonDELETE_CONFIRM_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void radioButtonRandom_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void radioButtonBalance_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void radioButtonDiff_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void openFileDialog1_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e);
	private: System::Void saveFileDialog1_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e);
	private: System::Void textBoxOutput_TextChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void buttonOutput_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void textBox11_MouseHover(System::Object^ sender, System::EventArgs^ e);
	private: System::Void textBox22_MouseHover(System::Object^ sender, System::EventArgs^ e);
	private: System::Void textBoxOutput_MouseHover(System::Object^ sender, System::EventArgs^ e);
	private: System::Void buttonOutput_MouseHover(System::Object^ sender, System::EventArgs^ e);
	private: System::Void buttonEDIT_MouseHover(System::Object^ sender, System::EventArgs^ e);
	private: System::Void buttonEDIT_SAVE_MouseHover(System::Object^ sender, System::EventArgs^ e);
	private: System::Void buttonDELETE_MouseHover(System::Object^ sender, System::EventArgs^ e);
	private: System::Void labelSTART_MouseHover(System::Object^ sender, System::EventArgs^ e);
	private: System::Void checkBoxTXT_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void checkBoxRTF_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void textBox1_ValueChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void textBox2_ValueChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void labelOutputInfo_MouseHover(System::Object^ sender, System::EventArgs^ e);
private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void labelQuestions_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void textBox11_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void labelVars_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}