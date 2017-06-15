#pragma once
#include <vector>
#include <cmath>
#include <algorithm>
#include <chrono>

namespace MonteCarloGrainGrowth {

	using namespace System;
	using namespace System::Threading;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	enum NeighborhoodType {
		VonNeumann,
		Moore,
		HexagonalLeft,
		HexagonalRight,
		HexagonalRandom,
		PentagonalRandom
	};

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
		delegate void FormDelegate();

		static Random^ rnd = gcnew Random();
		NeighborhoodType neighType = Moore;

		Bitmap^ pBmp;
		Graphics^ g;
		Pen^ penBk;
		int numberOfColors;
		int delayCoefficient;
		int height, width;
		bool wrapEdges;
		bool breakLoop = false;
		array<array<unsigned int>^>^ matrix;
		array<unsigned int>^ colorPool;
		
		unsigned int time = 0;
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			penBk = gcnew Pen(Color::FromArgb(122, 0, 0, 0), 1);
			pBmp = gcnew Bitmap(603, 603);
			g = Graphics::FromImage(pBmp);

			numberOfColors = Convert::ToInt32(textBox6->Text);
			delayCoefficient = trackBar2->Value;
			wrapEdges = checkBox1->Checked;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::Button^  button9;
	private: System::Windows::Forms::Button^  button8;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TrackBar^  trackBar2;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::RadioButton^  radioButton5;
	private: System::Windows::Forms::RadioButton^  radioButton4;
	private: System::Windows::Forms::RadioButton^  radioButton3;
	private: System::Windows::Forms::RadioButton^  radioButton2;
	private: System::Windows::Forms::RadioButton^  radioButton1;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::RadioButton^  radioButton11;
	private: System::Windows::Forms::RadioButton^  radioButton10;
	private: System::Windows::Forms::RadioButton^  radioButton9;
	private: System::Windows::Forms::RadioButton^  radioButton8;
	private: System::Windows::Forms::RadioButton^  radioButton7;
	private: System::Windows::Forms::RadioButton^  radioButton6;
	private: System::Windows::Forms::GroupBox^  groupBox7;
	private: System::Windows::Forms::Button^  button16;
	private: System::Windows::Forms::Button^  button17;
	private: System::Windows::Forms::TextBox^  textBox6;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::GroupBox^  groupBox5;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	private: System::Windows::Forms::Button^  button7;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->trackBar2 = (gcnew System::Windows::Forms::TrackBar());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->radioButton5 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton4 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->radioButton11 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton10 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton9 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton8 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton7 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton6 = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox7 = (gcnew System::Windows::Forms::GroupBox());
			this->button16 = (gcnew System::Windows::Forms::Button());
			this->button17 = (gcnew System::Windows::Forms::Button());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->button7 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->BeginInit();
			this->groupBox3->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->groupBox7->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::White;
			this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox1->Enabled = false;
			this->pictureBox1->Location = System::Drawing::Point(12, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(603, 603);
			this->pictureBox1->TabIndex = 14;
			this->pictureBox1->TabStop = false;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->checkBox1);
			this->groupBox1->Controls->Add(this->button9);
			this->groupBox1->Controls->Add(this->button8);
			this->groupBox1->Controls->Add(this->textBox1);
			this->groupBox1->Location = System::Drawing::Point(621, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(200, 77);
			this->groupBox1->TabIndex = 15;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"GridSize";
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(26, 47);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(84, 17);
			this->checkBox1->TabIndex = 13;
			this->checkBox1->Text = L"Wrap edges";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox1_CheckedChanged);
			// 
			// button9
			// 
			this->button9->Location = System::Drawing::Point(26, 19);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(30, 22);
			this->button9->TabIndex = 5;
			this->button9->Text = L"<";
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Click += gcnew System::EventHandler(this, &MyForm::button9_Click);
			// 
			// button8
			// 
			this->button8->Location = System::Drawing::Point(148, 19);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(30, 22);
			this->button8->TabIndex = 4;
			this->button8->Text = L">";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Click += gcnew System::EventHandler(this, &MyForm::button8_Click);
			// 
			// textBox1
			// 
			this->textBox1->Enabled = false;
			this->textBox1->Location = System::Drawing::Point(55, 20);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(94, 20);
			this->textBox1->TabIndex = 3;
			this->textBox1->Text = L"100";
			this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Controls->Add(this->label2);
			this->groupBox2->Controls->Add(this->trackBar2);
			this->groupBox2->Location = System::Drawing::Point(827, 12);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(105, 155);
			this->groupBox2->TabIndex = 17;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Speed";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(60, 19);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(28, 13);
			this->label3->TabIndex = 7;
			this->label3->Text = L"slow";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(60, 130);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(24, 13);
			this->label2->TabIndex = 6;
			this->label2->Text = L"fast";
			// 
			// trackBar2
			// 
			this->trackBar2->Location = System::Drawing::Point(11, 15);
			this->trackBar2->Maximum = 70;
			this->trackBar2->Name = L"trackBar2";
			this->trackBar2->Orientation = System::Windows::Forms::Orientation::Vertical;
			this->trackBar2->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->trackBar2->Size = System::Drawing::Size(45, 128);
			this->trackBar2->SmallChange = 5;
			this->trackBar2->TabIndex = 5;
			this->trackBar2->TickFrequency = 5;
			this->trackBar2->Scroll += gcnew System::EventHandler(this, &MyForm::trackBar2_Scroll);
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->radioButton5);
			this->groupBox3->Controls->Add(this->radioButton4);
			this->groupBox3->Controls->Add(this->radioButton3);
			this->groupBox3->Controls->Add(this->radioButton2);
			this->groupBox3->Controls->Add(this->radioButton1);
			this->groupBox3->Controls->Add(this->button3);
			this->groupBox3->Controls->Add(this->button2);
			this->groupBox3->Controls->Add(this->textBox2);
			this->groupBox3->Location = System::Drawing::Point(621, 95);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(200, 72);
			this->groupBox3->TabIndex = 18;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Number Of Iterations";
			// 
			// radioButton5
			// 
			this->radioButton5->AutoSize = true;
			this->radioButton5->Location = System::Drawing::Point(102, 19);
			this->radioButton5->Name = L"radioButton5";
			this->radioButton5->Size = System::Drawing::Size(83, 17);
			this->radioButton5->TabIndex = 8;
			this->radioButton5->TabStop = true;
			this->radioButton5->Text = L"Infinite Loop";
			this->radioButton5->UseVisualStyleBackColor = true;
			this->radioButton5->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButton5_CheckedChanged);
			// 
			// radioButton4
			// 
			this->radioButton4->AutoSize = true;
			this->radioButton4->Location = System::Drawing::Point(151, 47);
			this->radioButton4->Name = L"radioButton4";
			this->radioButton4->Size = System::Drawing::Size(43, 17);
			this->radioButton4->TabIndex = 7;
			this->radioButton4->TabStop = true;
			this->radioButton4->Text = L"100";
			this->radioButton4->UseVisualStyleBackColor = true;
			this->radioButton4->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButton4_CheckedChanged);
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Location = System::Drawing::Point(92, 47);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(37, 17);
			this->radioButton3->TabIndex = 6;
			this->radioButton3->TabStop = true;
			this->radioButton3->Text = L"10";
			this->radioButton3->UseVisualStyleBackColor = true;
			this->radioButton3->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButton3_CheckedChanged);
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Location = System::Drawing::Point(43, 47);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(31, 17);
			this->radioButton2->TabIndex = 5;
			this->radioButton2->TabStop = true;
			this->radioButton2->Text = L"2";
			this->radioButton2->UseVisualStyleBackColor = true;
			this->radioButton2->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButton2_CheckedChanged);
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Location = System::Drawing::Point(6, 47);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(31, 17);
			this->radioButton1->TabIndex = 4;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"1";
			this->radioButton1->UseVisualStyleBackColor = true;
			this->radioButton1->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButton1_CheckedChanged);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(65, 19);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(20, 22);
			this->button3->TabIndex = 2;
			this->button3->Text = L">";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(6, 19);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(20, 22);
			this->button2->TabIndex = 1;
			this->button2->Text = L"<";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(26, 20);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(39, 20);
			this->textBox2->TabIndex = 0;
			this->textBox2->Text = L"50";
			this->textBox2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->radioButton11);
			this->groupBox4->Controls->Add(this->radioButton10);
			this->groupBox4->Controls->Add(this->radioButton9);
			this->groupBox4->Controls->Add(this->radioButton8);
			this->groupBox4->Controls->Add(this->radioButton7);
			this->groupBox4->Controls->Add(this->radioButton6);
			this->groupBox4->Location = System::Drawing::Point(621, 173);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(311, 87);
			this->groupBox4->TabIndex = 22;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Neighborhood type";
			// 
			// radioButton11
			// 
			this->radioButton11->AutoSize = true;
			this->radioButton11->Location = System::Drawing::Point(137, 64);
			this->radioButton11->Name = L"radioButton11";
			this->radioButton11->Size = System::Drawing::Size(122, 17);
			this->radioButton11->TabIndex = 11;
			this->radioButton11->Text = L"Pentagonal Random";
			this->radioButton11->UseVisualStyleBackColor = true;
			this->radioButton11->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButton11_CheckedChanged);
			// 
			// radioButton10
			// 
			this->radioButton10->AutoSize = true;
			this->radioButton10->Location = System::Drawing::Point(137, 41);
			this->radioButton10->Name = L"radioButton10";
			this->radioButton10->Size = System::Drawing::Size(97, 17);
			this->radioButton10->TabIndex = 10;
			this->radioButton10->Text = L"Hexagonal Left";
			this->radioButton10->UseVisualStyleBackColor = true;
			this->radioButton10->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButton10_CheckedChanged);
			// 
			// radioButton9
			// 
			this->radioButton9->AutoSize = true;
			this->radioButton9->Location = System::Drawing::Point(137, 17);
			this->radioButton9->Name = L"radioButton9";
			this->radioButton9->Size = System::Drawing::Size(104, 17);
			this->radioButton9->TabIndex = 9;
			this->radioButton9->Text = L"Hexagonal Right";
			this->radioButton9->UseVisualStyleBackColor = true;
			this->radioButton9->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButton9_CheckedChanged);
			// 
			// radioButton8
			// 
			this->radioButton8->AutoSize = true;
			this->radioButton8->Location = System::Drawing::Point(6, 64);
			this->radioButton8->Name = L"radioButton8";
			this->radioButton8->Size = System::Drawing::Size(119, 17);
			this->radioButton8->TabIndex = 8;
			this->radioButton8->Text = L"Hexagonal Random\r\n";
			this->radioButton8->UseVisualStyleBackColor = true;
			this->radioButton8->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButton8_CheckedChanged);
			// 
			// radioButton7
			// 
			this->radioButton7->AutoSize = true;
			this->radioButton7->Checked = true;
			this->radioButton7->Location = System::Drawing::Point(6, 41);
			this->radioButton7->Name = L"radioButton7";
			this->radioButton7->Size = System::Drawing::Size(55, 17);
			this->radioButton7->TabIndex = 7;
			this->radioButton7->TabStop = true;
			this->radioButton7->Text = L"Moore";
			this->radioButton7->UseVisualStyleBackColor = true;
			this->radioButton7->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButton7_CheckedChanged);
			// 
			// radioButton6
			// 
			this->radioButton6->AutoSize = true;
			this->radioButton6->Location = System::Drawing::Point(6, 17);
			this->radioButton6->Name = L"radioButton6";
			this->radioButton6->Size = System::Drawing::Size(87, 17);
			this->radioButton6->TabIndex = 6;
			this->radioButton6->Text = L"Von Neuman";
			this->radioButton6->UseVisualStyleBackColor = true;
			this->radioButton6->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButton6_CheckedChanged);
			// 
			// groupBox7
			// 
			this->groupBox7->Controls->Add(this->button16);
			this->groupBox7->Controls->Add(this->button17);
			this->groupBox7->Controls->Add(this->textBox6);
			this->groupBox7->Location = System::Drawing::Point(621, 266);
			this->groupBox7->Name = L"groupBox7";
			this->groupBox7->Size = System::Drawing::Size(93, 66);
			this->groupBox7->TabIndex = 23;
			this->groupBox7->TabStop = false;
			this->groupBox7->Text = L"Iloœæ kolorów";
			// 
			// button16
			// 
			this->button16->Location = System::Drawing::Point(66, 32);
			this->button16->Name = L"button16";
			this->button16->Size = System::Drawing::Size(20, 22);
			this->button16->TabIndex = 5;
			this->button16->Text = L">";
			this->button16->UseVisualStyleBackColor = true;
			this->button16->Click += gcnew System::EventHandler(this, &MyForm::button16_Click);
			// 
			// button17
			// 
			this->button17->Location = System::Drawing::Point(7, 32);
			this->button17->Name = L"button17";
			this->button17->Size = System::Drawing::Size(20, 22);
			this->button17->TabIndex = 4;
			this->button17->Text = L"<";
			this->button17->UseVisualStyleBackColor = true;
			this->button17->Click += gcnew System::EventHandler(this, &MyForm::button17_Click);
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(27, 33);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(39, 20);
			this->textBox6->TabIndex = 3;
			this->textBox6->Text = L"5";
			this->textBox6->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// button5
			// 
			this->button5->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(80)),
				static_cast<System::Int32>(static_cast<System::Byte>(80)));
			this->button5->Location = System::Drawing::Point(782, 338);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(150, 51);
			this->button5->TabIndex = 26;
			this->button5->Text = L"Stop";
			this->button5->UseVisualStyleBackColor = false;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// button4
			// 
			this->button4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(119)), static_cast<System::Int32>(static_cast<System::Byte>(221)),
				static_cast<System::Int32>(static_cast<System::Byte>(119)));
			this->button4->Location = System::Drawing::Point(621, 338);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(150, 51);
			this->button4->TabIndex = 25;
			this->button4->Text = L"Start";
			this->button4->UseVisualStyleBackColor = false;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->button1);
			this->groupBox5->Controls->Add(this->button6);
			this->groupBox5->Controls->Add(this->textBox3);
			this->groupBox5->Location = System::Drawing::Point(-104, -84);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(87, 66);
			this->groupBox5->TabIndex = 24;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"k coefficent";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(66, 32);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(20, 22);
			this->button1->TabIndex = 5;
			this->button1->Text = L">";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(7, 32);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(20, 22);
			this->button6->TabIndex = 4;
			this->button6->Text = L"<";
			this->button6->UseVisualStyleBackColor = true;
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(27, 33);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(39, 20);
			this->textBox3->TabIndex = 3;
			this->textBox3->Text = L"100";
			this->textBox3->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->WorkerSupportsCancellation = true;
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MyForm::backgroundWorker1_DoWork);
			// 
			// button7
			// 
			this->button7->Location = System::Drawing::Point(720, 266);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(212, 66);
			this->button7->TabIndex = 27;
			this->button7->Text = L"Generate";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &MyForm::button7_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(939, 620);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->groupBox5);
			this->Controls->Add(this->groupBox7);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->EndInit();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->groupBox7->ResumeLayout(false);
			this->groupBox7->PerformLayout();
			this->groupBox5->ResumeLayout(false);
			this->groupBox5->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button9_Click(System::Object^  sender, System::EventArgs^  e) {
		int value = Convert::ToInt32(textBox1->Text);
		do {
			if (value > 3)
				value--;
		} while (600 % value != 0);
		textBox1->Text = value.ToString();
	}
private: System::Void button8_Click(System::Object^  sender, System::EventArgs^  e) {
	int value = Convert::ToInt32(textBox1->Text);
	do {
		if (value < 300)
			value++;
	} while (600 % value != 0);
	textBox1->Text = value.ToString();
}
private: System::Void trackBar2_Scroll(System::Object^  sender, System::EventArgs^  e) {
	delayCoefficient = trackBar2->Value;
}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	int value = Convert::ToInt32(textBox2->Text);
	if (value > 0)
		value--;
	textBox2->Text = value.ToString();
}
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
	int value = Convert::ToInt32(textBox2->Text);
	value++;
	textBox2->Text = value.ToString();
}
private: System::Void radioButton1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	textBox2->Text = "1";
}
private: System::Void radioButton2_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	textBox2->Text = "2";
}
private: System::Void radioButton3_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	textBox2->Text = "10";
}
private: System::Void radioButton4_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	textBox2->Text = "100";
}
private: System::Void radioButton5_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	textBox2->Text = "2147483647";
}
private: System::Void radioButton6_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	neighType = VonNeumann;
}
private: System::Void radioButton7_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	neighType = Moore;
}
private: System::Void radioButton8_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	neighType = HexagonalRandom;
}
private: System::Void radioButton9_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	neighType = HexagonalRight;
}
private: System::Void radioButton10_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	neighType = HexagonalLeft;
}
private: System::Void radioButton11_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	neighType = PentagonalRandom;
}
private: System::Void button17_Click(System::Object^  sender, System::EventArgs^  e) {
	int value = Convert::ToInt32(textBox6->Text);
	if (value > 0)
		value--;
	textBox6->Text = value.ToString();
}
private: System::Void button16_Click(System::Object^  sender, System::EventArgs^  e) {
	int value = Convert::ToInt32(textBox6->Text);
	value++;
	textBox6->Text = value.ToString();
}
private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) {
	//generate

	numberOfColors = Convert::ToInt32(textBox6->Text);
	colorPool = gcnew array<unsigned int>(numberOfColors);

	//matrix initialization
	width = height = Convert::ToInt32(textBox1->Text) + 2;
	matrix = gcnew array<array<unsigned int>^>(height);
	for (int i = 0; i < height; i++)
	{
		matrix[i] = gcnew array<unsigned int>(width);
	}
	fillColorPool(colorPool);
	fillArray(matrix, colorPool);
	drawMatrix(matrix);
}
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
	//start
	breakLoop = false;
	button4->Enabled = false;
	button6->Enabled = false;
	button5->Enabled = true;
	groupBox1->Enabled = false;
	groupBox3->Enabled = false;
	groupBox4->Enabled = false;
	groupBox5->Enabled = false;
	pictureBox1->Enabled = false;
	backgroundWorker1->RunWorkerAsync();
}
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
	//stop
	button4->Enabled = true;
	button5->Enabled = false;
	button6->Enabled = true;
	groupBox1->Enabled = true;
	groupBox3->Enabled = true;
	groupBox4->Enabled = true;
	groupBox5->Enabled = true;
	pictureBox1->Enabled = true;
	breakLoop = true;
	backgroundWorker1->CancelAsync();
}
private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	wrapEdges = checkBox1->Checked;
}
	void drawMatrix(array<array<unsigned int>^>^ % matrix) {
		g->Clear(Color::White);

		//panel is 600x600px
		int squareSideLength = 600 / (width - 2);

		SolidBrush^ brush = gcnew SolidBrush(Color::Black);
		for (int i = 1; i < (height - 1); i++) {
			for (int j = 1; j < (width - 1); j++) {
				if (matrix[i][j] != 0) {
					brush->Color = Color::FromArgb(matrix[i][j]);
					g->FillRectangle(brush, Rectangle((j - 1) * squareSideLength, (i - 1) * squareSideLength, squareSideLength, squareSideLength));
				}
			}
		}
		for (int y = 0; y < (height - 1); ++y)
		{
			g->DrawLine(penBk, 0, y * squareSideLength, (height - 2) * squareSideLength, y * squareSideLength);
		}

		for (int x = 0; x < (width - 1); ++x)
		{
			g->DrawLine(penBk, x * squareSideLength, 0, x * squareSideLength, (width - 2) * squareSideLength);
		}
		pictureBox1->Image = pBmp;
	}
	void fillColorPool(array<unsigned int>^ colorPool) {
		for (int i = 0; i < colorPool->Length; i++) {
			colorPool[i] = getRandomColorAsInt();
		}
	}
	static int myrandom(int i) {
		return rnd->Next(i);
	}
	void applyRules(array<array<unsigned int>^>^% matrix) {
		for (int i = 1; i < (height - 1)*(height - 1); i++) {
			int x = rnd->Next(1, (width - 1));
			int y = rnd->Next(1, (height - 1));
			int energyBefore = calculateEnergy(matrix, y, x, neighType);
			unsigned int newColor = colorPool[rnd->Next(0, colorPool->Length)];
			int energyAfter = calculateEnergy(matrix, y, x, neighType, newColor);
			int deltaEnergy = energyAfter - energyBefore;
			if (deltaEnergy <= 0) {
				matrix[y][x] = newColor;
			}
		}
		time++;
	}
	void fillArray(array<array<unsigned int>^>^ % matrix, array<unsigned int>^ colorPool) {

		//panel is 600x600px
		for (int i = 1; i < (height - 1); i++) {
			for (int j = 1; j < (width - 1); j++) {
				matrix[i][j] = colorPool[rnd->Next(0, colorPool->Length)];
			}
		}
	}
	void stopButton() {
		if (this->button5->InvokeRequired) {
			FormDelegate^ d = gcnew FormDelegate(this, &MyForm::stopButton);
			this->Invoke(d, gcnew array<Object^> {});
		}
		else {
			button4->Enabled = true;
			button5->Enabled = false;
			groupBox1->Enabled = true;
			groupBox3->Enabled = true;
			groupBox4->Enabled = true;
			groupBox5->Enabled = true;
			pictureBox1->Enabled = true;
			button6->Enabled = true;
		}
	}
	unsigned int getRandomColorAsInt() {
		unsigned int randomIntColor = 4278190080 + rnd->Next(16777215); //full opaque + random first 24 bytes
		return randomIntColor;
	}
	int calculateEnergy(array<array<unsigned int>^>^% matrix, int y, int x, NeighborhoodType neighborhoodType, unsigned int color) {
		int energy = 0;
		switch (neighborhoodType) {
		case Moore:
			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {
					if (j != 0 || 0 != i) {
						if (color != matrix[y + i][x + j])
							energy++;
					}
				}
			}
			break;
		case VonNeumann:
			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {
					if (!(j != 0 && 0 != i) && (j != 0 || 0 != i)) {
						if (color != matrix[y + i][x + j])
							energy++;
					}

				}
			}
			break;
		case HexagonalLeft:
			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {
					if (!(i + j) == 0) {
						if (color != matrix[y + i][x + j])
							energy++;
					}
				}
			}
			break;
		case HexagonalRight:
			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {
					if (i != j) {
						if (color != matrix[y + i][x + j])
							energy++;
					}
				}
			}
				break;
		case HexagonalRandom:
		{
			bool randomArrayHexagonal[8] = { true, true, true, true, true, false, false, false };
			std::random_shuffle(&randomArrayHexagonal[0], &randomArrayHexagonal[8], myrandom);
			int counter = 0;
			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {
					if (j != 0 || 0 != i) {
						if (randomArrayHexagonal[counter]) {
							if (color != matrix[y + i][x + j])
								energy++;
						}
						counter++;
					}
				}
			}
		}
		break;
		case PentagonalRandom:
		{
			bool randomArrayPentagonal[8] = { true, true, true, true, false, false, false, false };
			std::random_shuffle(&randomArrayPentagonal[0], &randomArrayPentagonal[8], myrandom);
			int counter = 0;
			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {
					if (j != 0 || 0 != i) {
						if (randomArrayPentagonal[counter]) {
							if (color != matrix[y + i][x + j])
								energy++;
						}
						counter++;
					}
				}
			}
		}
		break;
		}
		return energy;
	}
	int calculateEnergy(array<array<unsigned int>^>^% matrix, int y, int x, NeighborhoodType neighborhoodType) {
		int energy = 0;
		switch (neighborhoodType) {
		case Moore:
			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {
					if (j != 0 || 0 != i) {
						if (matrix[y][x] != matrix[y + i][x + j])
							energy++;
					}
				}
			}
			break;
		case VonNeumann:
			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {
					if (!(j != 0 && 0 != i) && (j != 0 || 0 != i)) {
						if (matrix[y][x] != matrix[y + i][x + j])
							energy++;
					}

				}
			}
			break;
		case HexagonalLeft:
			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {
					if (!(i + j) == 0) {
						if (matrix[y][x] != matrix[y + i][x + j])
							energy++;
					}
				}
			}
			break;
		case HexagonalRight:
			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {
					if (i != j) {
						if (matrix[y][x] != matrix[y + i][x + j])
							energy++;
					}
				}
			}
			break;
		case HexagonalRandom:
		{
			bool randomArrayHexagonal[8] = { true, true, true, true, true, false, false, false };
			std::random_shuffle(&randomArrayHexagonal[0], &randomArrayHexagonal[8], myrandom);
			int counter = 0;
			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {
					if (j != 0 || 0 != i) {
						if (randomArrayHexagonal[counter]) {
							if (matrix[y][x] != matrix[y + i][x + j])
								energy++;
						}
						counter++;
					}
				}
			}
		}
		break;
		case PentagonalRandom:
		{
			bool randomArrayPentagonal[8] = { true, true, true, true, false, false, false, false };
			std::random_shuffle(&randomArrayPentagonal[0], &randomArrayPentagonal[8], myrandom);
			int counter = 0;
			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {
					if (j != 0 || 0 != i) {
						if (randomArrayPentagonal[counter]) {
							if (matrix[y][x] != matrix[y + i][x + j])
								energy++;
						}
						counter++;
					}
				}
			}
		}
		break;
		}
		return energy;
	}
	void wrapEdgesOnMatrix(array<array<unsigned int>^>^% matrix) {
		//top
		for (int j = 1; j < (width - 1); j++) {
			matrix[0][j] = matrix[height - 2][j];
		}
		//bottom
		for (int j = 1; j < (width - 1); j++) {
			matrix[height - 1][j] = matrix[1][j];
		}
		//left
		for (int i = 1; i < (height - 1); i++) {
			matrix[i][0] = matrix[i][width - 2];
		}
		//right
		for (int i = 1; i < (height - 1); i++) {
			matrix[i][width - 1] = matrix[i][1];
		}
		//corners

		//left top
		matrix[0][0] = matrix[height - 2][width - 2];
		//left bottom
		matrix[height - 1][0] = matrix[1][width - 2];
		//right top
		matrix[0][width - 1] = matrix[height - 2][1];
		//right bottom
		matrix[height - 1][width - 1] = matrix[1][1];
	}
private: System::Void backgroundWorker1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
	int loopLimit = Convert::ToInt32(textBox2->Text);
	for (int i = 0; i < loopLimit; i++) {
		auto start = std::chrono::system_clock::now();

		if (breakLoop) {
			breakLoop = !breakLoop;
			break;
		}

		if (wrapEdges)
			wrapEdgesOnMatrix(matrix);
		applyRules(matrix);
		drawMatrix(matrix);

		auto elapsed = std::chrono::system_clock::now() - start;
		int milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
		if ((delayCoefficient) - milliseconds > 0) {
			Thread::Sleep((delayCoefficient) - milliseconds);
		}
		else {
			Thread::Sleep((delayCoefficient));
		}
	}
	stopButton();
}
};
}
