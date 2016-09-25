#pragma once



namespace Mdrive {

	using namespace System;
	using namespace System::IO;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;



	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			CheckForIllegalCrossThreadCalls = false; 
			this->Manipulator = (gcnew manip::manipulator());
			this->C_Vision = (gcnew c_vis::c_vision());
			this->prog_pohyb->RowCount=15;
			this->prog_pohyb->RowHeadersWidth= 10;
			for(int i=0;i<15;i++){
				this->prog_pohyb->Rows[i]->Cells[0]->Value="-";
				this->prog_pohyb->Rows[i]->Cells[1]->Value="-";
				this->prog_pohyb->Rows[i]->Cells[2]->Value="-";
			}
			this->Tab_bodu->RowCount=40;
			for(int i=0;i<30;i++){
				this->Tab_bodu->Rows[i]->Cells[0]->Value="-";
				this->Tab_bodu->Rows[i]->Cells[1]->Value="-";
			}
			
			this->cil_bod_X->Text="3";
			this->cil_bod_Y->Text="10";
			this->cil_bod_Z->Text="20";
				
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			this->serialPort1->Close();
			if (components)
			{
				delete components;
			}
		}
	
	private: System::Windows::Forms::HScrollBar^  pr_servo0;
	private: System::Windows::Forms::HScrollBar^  pr_servo3;
	private: System::Windows::Forms::HScrollBar^  pr_servo2;
	private: System::Windows::Forms::HScrollBar^  pr_servo1;

	private: System::Windows::Forms::Label^  txt_pr_srv_0;
	private: System::Windows::Forms::Label^  txt_pr_srv_3;
	private: System::Windows::Forms::Label^  txt_pr_srv_2;
	private: System::Windows::Forms::Label^  txt_pr_srv_1;
	private: System::IO::Ports::SerialPort^  serialPort1;
	private: System::ComponentModel::IContainer^  components;

	private: System::Windows::Forms::Timer^  timer1;

	private: manip::manipulator^ Manipulator;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage1;

	private: System::Windows::Forms::TabPage^  tabPage3;

	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Button^  cam_button;
	private: System::Windows::Forms::Button^  Start_sesbirat;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Button^  Button_Najet_na_bod;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  NastB_Z;
	private: System::Windows::Forms::TextBox^  NastB_Y;
	private: System::Windows::Forms::TextBox^  NastB_X;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Button^  Prog_start_button;
	private: System::Windows::Forms::DataGridView^  prog_pohyb;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  X;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Y;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Z;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::Timer^  timer2;
	private: System::Windows::Forms::Button^  button_com_open;
	private: System::Windows::Forms::Label^  indikator_com;

	private: System::Windows::Forms::Label^  label_info_automat;
	private: System::Windows::Forms::Button^  button_start_zamerovani;






	private: System::Windows::Forms::DataGridView^  Tab_bodu;
	private: System::Windows::Forms::TextBox^  cil_bod_Z;





	private: System::Windows::Forms::TextBox^  cil_bod_X;

	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  X_2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Z_2;
private: System::Windows::Forms::GroupBox^  groupBox5;
private: System::Windows::Forms::TextBox^  cil_bod_Y;












	private: c_vis::c_vision^ C_Vision;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			this->txt_pr_srv_3 = (gcnew System::Windows::Forms::Label());
			this->txt_pr_srv_2 = (gcnew System::Windows::Forms::Label());
			this->txt_pr_srv_1 = (gcnew System::Windows::Forms::Label());
			this->txt_pr_srv_0 = (gcnew System::Windows::Forms::Label());
			this->pr_servo3 = (gcnew System::Windows::Forms::HScrollBar());
			this->pr_servo2 = (gcnew System::Windows::Forms::HScrollBar());
			this->pr_servo1 = (gcnew System::Windows::Forms::HScrollBar());
			this->pr_servo0 = (gcnew System::Windows::Forms::HScrollBar());
			this->serialPort1 = (gcnew System::IO::Ports::SerialPort(this->components));
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->indikator_com = (gcnew System::Windows::Forms::Label());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->Prog_start_button = (gcnew System::Windows::Forms::Button());
			this->prog_pohyb = (gcnew System::Windows::Forms::DataGridView());
			this->X = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Y = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Z = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->button_com_open = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->Button_Najet_na_bod = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->NastB_Z = (gcnew System::Windows::Forms::TextBox());
			this->NastB_Y = (gcnew System::Windows::Forms::TextBox());
			this->NastB_X = (gcnew System::Windows::Forms::TextBox());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->Tab_bodu = (gcnew System::Windows::Forms::DataGridView());
			this->X_2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Z_2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->cil_bod_Y = (gcnew System::Windows::Forms::TextBox());
			this->cil_bod_Z = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->cil_bod_X = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->button_start_zamerovani = (gcnew System::Windows::Forms::Button());
			this->label_info_automat = (gcnew System::Windows::Forms::Label());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->Start_sesbirat = (gcnew System::Windows::Forms::Button());
			this->cam_button = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->prog_pohyb))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->groupBox5->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->Tab_bodu))->BeginInit();
			this->groupBox4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// txt_pr_srv_3
			// 
			this->txt_pr_srv_3->AutoSize = true;
			this->txt_pr_srv_3->Location = System::Drawing::Point(257, 228);
			this->txt_pr_srv_3->Name = L"txt_pr_srv_3";
			this->txt_pr_srv_3->Size = System::Drawing::Size(50, 13);
			this->txt_pr_srv_3->TabIndex = 7;
			this->txt_pr_srv_3->Text = L"Servo 3: ";
			// 
			// txt_pr_srv_2
			// 
			this->txt_pr_srv_2->AutoSize = true;
			this->txt_pr_srv_2->Location = System::Drawing::Point(34, 154);
			this->txt_pr_srv_2->Name = L"txt_pr_srv_2";
			this->txt_pr_srv_2->Size = System::Drawing::Size(50, 13);
			this->txt_pr_srv_2->TabIndex = 6;
			this->txt_pr_srv_2->Text = L"Servo 2: ";
			// 
			// txt_pr_srv_1
			// 
			this->txt_pr_srv_1->AutoSize = true;
			this->txt_pr_srv_1->Location = System::Drawing::Point(34, 94);
			this->txt_pr_srv_1->Name = L"txt_pr_srv_1";
			this->txt_pr_srv_1->Size = System::Drawing::Size(50, 13);
			this->txt_pr_srv_1->TabIndex = 5;
			this->txt_pr_srv_1->Text = L"Servo 1: ";
			// 
			// txt_pr_srv_0
			// 
			this->txt_pr_srv_0->AutoSize = true;
			this->txt_pr_srv_0->Location = System::Drawing::Point(34, 34);
			this->txt_pr_srv_0->Name = L"txt_pr_srv_0";
			this->txt_pr_srv_0->Size = System::Drawing::Size(50, 13);
			this->txt_pr_srv_0->TabIndex = 4;
			this->txt_pr_srv_0->Text = L"Servo 0: ";
			// 
			// pr_servo3
			// 
			this->pr_servo3->LargeChange = 1;
			this->pr_servo3->Location = System::Drawing::Point(260, 241);
			this->pr_servo3->Maximum = 254;
			this->pr_servo3->Minimum = 40;
			this->pr_servo3->Name = L"pr_servo3";
			this->pr_servo3->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->pr_servo3->Size = System::Drawing::Size(173, 20);
			this->pr_servo3->TabIndex = 3;
			this->pr_servo3->Value = 125;
			this->pr_servo3->ValueChanged += gcnew System::EventHandler(this, &Form1::pr_rizeni);
			// 
			// pr_servo2
			// 
			this->pr_servo2->LargeChange = 1;
			this->pr_servo2->Location = System::Drawing::Point(37, 167);
			this->pr_servo2->Maximum = 250;
			this->pr_servo2->Minimum = 16;
			this->pr_servo2->Name = L"pr_servo2";
			this->pr_servo2->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->pr_servo2->Size = System::Drawing::Size(650, 20);
			this->pr_servo2->TabIndex = 2;
			this->pr_servo2->Value = 125;
			this->pr_servo2->ValueChanged += gcnew System::EventHandler(this, &Form1::pr_rizeni);
			// 
			// pr_servo1
			// 
			this->pr_servo1->LargeChange = 1;
			this->pr_servo1->Location = System::Drawing::Point(37, 107);
			this->pr_servo1->Maximum = 255;
			this->pr_servo1->Minimum = 16;
			this->pr_servo1->Name = L"pr_servo1";
			this->pr_servo1->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->pr_servo1->Size = System::Drawing::Size(650, 20);
			this->pr_servo1->TabIndex = 1;
			this->pr_servo1->Value = 125;
			this->pr_servo1->ValueChanged += gcnew System::EventHandler(this, &Form1::pr_rizeni);
			// 
			// pr_servo0
			// 
			this->pr_servo0->LargeChange = 1;
			this->pr_servo0->Location = System::Drawing::Point(37, 47);
			this->pr_servo0->Maximum = 250;
			this->pr_servo0->Minimum = 16;
			this->pr_servo0->Name = L"pr_servo0";
			this->pr_servo0->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->pr_servo0->Size = System::Drawing::Size(650, 20);
			this->pr_servo0->TabIndex = 0;
			this->pr_servo0->Value = 125;
			this->pr_servo0->ValueChanged += gcnew System::EventHandler(this, &Form1::pr_rizeni);
			// 
			// serialPort1
			// 
			this->serialPort1->BaudRate = 2400;
			this->serialPort1->PortName = L"COM2";
			this->serialPort1->DataReceived += gcnew System::IO::Ports::SerialDataReceivedEventHandler(this, &Form1::serialPort1_DataReceived);
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Location = System::Drawing::Point(12, 12);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(1072, 534);
			this->tabControl1->TabIndex = 6;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->indikator_com);
			this->tabPage1->Controls->Add(this->groupBox3);
			this->tabPage1->Controls->Add(this->groupBox2);
			this->tabPage1->Controls->Add(this->button_com_open);
			this->tabPage1->Controls->Add(this->groupBox1);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(1064, 508);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Pøímé øízení";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// indikator_com
			// 
			this->indikator_com->AutoSize = true;
			this->indikator_com->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->indikator_com->Location = System::Drawing::Point(291, 81);
			this->indikator_com->Name = L"indikator_com";
			this->indikator_com->Size = System::Drawing::Size(105, 20);
			this->indikator_com->TabIndex = 12;
			this->indikator_com->Text = L"Nepøipojeno";
			this->indikator_com->Click += gcnew System::EventHandler(this, &Form1::indikator_com_Click);
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->pr_servo0);
			this->groupBox3->Controls->Add(this->pr_servo1);
			this->groupBox3->Controls->Add(this->pr_servo2);
			this->groupBox3->Controls->Add(this->txt_pr_srv_3);
			this->groupBox3->Controls->Add(this->pr_servo3);
			this->groupBox3->Controls->Add(this->txt_pr_srv_2);
			this->groupBox3->Controls->Add(this->txt_pr_srv_0);
			this->groupBox3->Controls->Add(this->txt_pr_srv_1);
			this->groupBox3->Location = System::Drawing::Point(295, 158);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(726, 304);
			this->groupBox3->TabIndex = 10;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Manuální øízení";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->Prog_start_button);
			this->groupBox2->Controls->Add(this->prog_pohyb);
			this->groupBox2->Location = System::Drawing::Point(37, 29);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(208, 433);
			this->groupBox2->TabIndex = 9;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Programování pohybu v prostoru";
			// 
			// Prog_start_button
			// 
			this->Prog_start_button->Location = System::Drawing::Point(62, 377);
			this->Prog_start_button->Name = L"Prog_start_button";
			this->Prog_start_button->Size = System::Drawing::Size(75, 23);
			this->Prog_start_button->TabIndex = 1;
			this->Prog_start_button->Text = L"Start";
			this->Prog_start_button->UseVisualStyleBackColor = true;
			this->Prog_start_button->Click += gcnew System::EventHandler(this, &Form1::Prog_start_button_Click);
			// 
			// prog_pohyb
			// 
			this->prog_pohyb->AllowUserToResizeColumns = false;
			this->prog_pohyb->AllowUserToResizeRows = false;
			this->prog_pohyb->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
			this->prog_pohyb->BackgroundColor = System::Drawing::SystemColors::Control;
			this->prog_pohyb->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->prog_pohyb->ColumnHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::Single;
			dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle1->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(238)));
			dataGridViewCellStyle1->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle1->NullValue = L"-";
			dataGridViewCellStyle1->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle1->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->prog_pohyb->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
			this->prog_pohyb->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->prog_pohyb->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {this->X, this->Y, 
				this->Z});
			this->prog_pohyb->Cursor = System::Windows::Forms::Cursors::IBeam;
			this->prog_pohyb->Location = System::Drawing::Point(19, 24);
			this->prog_pohyb->MaximumSize = System::Drawing::Size(192, 380);
			this->prog_pohyb->MinimumSize = System::Drawing::Size(10, 10);
			this->prog_pohyb->MultiSelect = false;
			this->prog_pohyb->Name = L"prog_pohyb";
			this->prog_pohyb->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::CellSelect;
			this->prog_pohyb->Size = System::Drawing::Size(162, 332);
			this->prog_pohyb->TabIndex = 0;
			// 
			// X
			// 
			this->X->HeaderText = L"X";
			this->X->Name = L"X";
			this->X->Width = 50;
			// 
			// Y
			// 
			this->Y->HeaderText = L"Y";
			this->Y->Name = L"Y";
			this->Y->Width = 50;
			// 
			// Z
			// 
			this->Z->HeaderText = L"Z";
			this->Z->Name = L"Z";
			this->Z->Width = 50;
			// 
			// button_com_open
			// 
			this->button_com_open->Location = System::Drawing::Point(295, 55);
			this->button_com_open->Name = L"button_com_open";
			this->button_com_open->Size = System::Drawing::Size(153, 23);
			this->button_com_open->TabIndex = 11;
			this->button_com_open->Text = L"Pøipojit k øídící jednotce";
			this->button_com_open->UseVisualStyleBackColor = true;
			this->button_com_open->Click += gcnew System::EventHandler(this, &Form1::button_com_open_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->Button_Najet_na_bod);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->NastB_Z);
			this->groupBox1->Controls->Add(this->NastB_Y);
			this->groupBox1->Controls->Add(this->NastB_X);
			this->groupBox1->Location = System::Drawing::Point(509, 39);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(306, 113);
			this->groupBox1->TabIndex = 8;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Nastavení bodu v prostoru";
			// 
			// Button_Najet_na_bod
			// 
			this->Button_Najet_na_bod->Location = System::Drawing::Point(105, 78);
			this->Button_Najet_na_bod->Name = L"Button_Najet_na_bod";
			this->Button_Najet_na_bod->Size = System::Drawing::Size(101, 23);
			this->Button_Najet_na_bod->TabIndex = 6;
			this->Button_Najet_na_bod->Text = L"Najet na bod";
			this->Button_Najet_na_bod->UseVisualStyleBackColor = true;
			this->Button_Najet_na_bod->Click += gcnew System::EventHandler(this, &Form1::Button_Najet_na_bod_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(243, 26);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(14, 13);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Z";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(150, 26);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(14, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Y";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(55, 26);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(14, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"X";
			// 
			// NastB_Z
			// 
			this->NastB_Z->Location = System::Drawing::Point(218, 42);
			this->NastB_Z->Name = L"NastB_Z";
			this->NastB_Z->Size = System::Drawing::Size(69, 20);
			this->NastB_Z->TabIndex = 2;
			// 
			// NastB_Y
			// 
			this->NastB_Y->Location = System::Drawing::Point(123, 42);
			this->NastB_Y->Name = L"NastB_Y";
			this->NastB_Y->Size = System::Drawing::Size(69, 20);
			this->NastB_Y->TabIndex = 1;
			// 
			// NastB_X
			// 
			this->NastB_X->Location = System::Drawing::Point(28, 42);
			this->NastB_X->Name = L"NastB_X";
			this->NastB_X->Size = System::Drawing::Size(69, 20);
			this->NastB_X->TabIndex = 0;
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->groupBox5);
			this->tabPage3->Controls->Add(this->groupBox4);
			this->tabPage3->Controls->Add(this->button_start_zamerovani);
			this->tabPage3->Controls->Add(this->label_info_automat);
			this->tabPage3->Controls->Add(this->pictureBox2);
			this->tabPage3->Controls->Add(this->Start_sesbirat);
			this->tabPage3->Controls->Add(this->cam_button);
			this->tabPage3->Controls->Add(this->pictureBox1);
			this->tabPage3->Location = System::Drawing::Point(4, 22);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Size = System::Drawing::Size(1064, 508);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"Poèítaèové vidìní";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->Tab_bodu);
			this->groupBox5->Location = System::Drawing::Point(557, 9);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(238, 177);
			this->groupBox5->TabIndex = 18;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"Souøadnice pøedmìtù";
			// 
			// Tab_bodu
			// 
			this->Tab_bodu->AllowUserToAddRows = false;
			this->Tab_bodu->AllowUserToDeleteRows = false;
			this->Tab_bodu->AllowUserToResizeColumns = false;
			this->Tab_bodu->AllowUserToResizeRows = false;
			this->Tab_bodu->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->Tab_bodu->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {this->X_2, this->Z_2});
			this->Tab_bodu->Location = System::Drawing::Point(27, 25);
			this->Tab_bodu->Name = L"Tab_bodu";
			this->Tab_bodu->ReadOnly = true;
			this->Tab_bodu->Size = System::Drawing::Size(182, 137);
			this->Tab_bodu->TabIndex = 0;
			// 
			// X_2
			// 
			this->X_2->HeaderText = L"X";
			this->X_2->Name = L"X_2";
			this->X_2->ReadOnly = true;
			this->X_2->Width = 60;
			// 
			// Z_2
			// 
			this->Z_2->HeaderText = L"Z";
			this->Z_2->Name = L"Z_2";
			this->Z_2->ReadOnly = true;
			this->Z_2->Width = 60;
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->cil_bod_Y);
			this->groupBox4->Controls->Add(this->cil_bod_Z);
			this->groupBox4->Controls->Add(this->label4);
			this->groupBox4->Controls->Add(this->label5);
			this->groupBox4->Controls->Add(this->cil_bod_X);
			this->groupBox4->Controls->Add(this->label6);
			this->groupBox4->Location = System::Drawing::Point(236, 34);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(290, 81);
			this->groupBox4->TabIndex = 17;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Souøadnice cílového bodu:";
			// 
			// cil_bod_Y
			// 
			this->cil_bod_Y->Location = System::Drawing::Point(108, 43);
			this->cil_bod_Y->Name = L"cil_bod_Y";
			this->cil_bod_Y->Size = System::Drawing::Size(77, 20);
			this->cil_bod_Y->TabIndex = 17;
			// 
			// cil_bod_Z
			// 
			this->cil_bod_Z->Location = System::Drawing::Point(191, 43);
			this->cil_bod_Z->Name = L"cil_bod_Z";
			this->cil_bod_Z->Size = System::Drawing::Size(82, 20);
			this->cil_bod_Z->TabIndex = 13;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(46, 27);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(14, 13);
			this->label4->TabIndex = 14;
			this->label4->Text = L"X";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(139, 27);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(14, 13);
			this->label5->TabIndex = 15;
			this->label5->Text = L"Y";
			// 
			// cil_bod_X
			// 
			this->cil_bod_X->Location = System::Drawing::Point(15, 43);
			this->cil_bod_X->Name = L"cil_bod_X";
			this->cil_bod_X->Size = System::Drawing::Size(82, 20);
			this->cil_bod_X->TabIndex = 11;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(224, 27);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(14, 13);
			this->label6->TabIndex = 16;
			this->label6->Text = L"Z";
			// 
			// button_start_zamerovani
			// 
			this->button_start_zamerovani->Location = System::Drawing::Point(44, 34);
			this->button_start_zamerovani->Name = L"button_start_zamerovani";
			this->button_start_zamerovani->Size = System::Drawing::Size(167, 23);
			this->button_start_zamerovani->TabIndex = 8;
			this->button_start_zamerovani->Text = L"Zapnout zamìøování objektù";
			this->button_start_zamerovani->UseVisualStyleBackColor = true;
			this->button_start_zamerovani->Click += gcnew System::EventHandler(this, &Form1::button_start_zamerovani_Click);
			// 
			// label_info_automat
			// 
			this->label_info_automat->AutoSize = true;
			this->label_info_automat->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Bold, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(238)));
			this->label_info_automat->ForeColor = System::Drawing::SystemColors::WindowText;
			this->label_info_automat->Location = System::Drawing::Point(49, 140);
			this->label_info_automat->Name = L"label_info_automat";
			this->label_info_automat->Size = System::Drawing::Size(182, 31);
			this->label_info_automat->TabIndex = 7;
			this->label_info_automat->Text = L"Zvolte pøíkaz";
			// 
			// pictureBox2
			// 
			this->pictureBox2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->pictureBox2->Location = System::Drawing::Point(533, 192);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(512, 288);
			this->pictureBox2->TabIndex = 6;
			this->pictureBox2->TabStop = false;
			// 
			// Start_sesbirat
			// 
			this->Start_sesbirat->Enabled = false;
			this->Start_sesbirat->Location = System::Drawing::Point(44, 63);
			this->Start_sesbirat->Name = L"Start_sesbirat";
			this->Start_sesbirat->Size = System::Drawing::Size(167, 23);
			this->Start_sesbirat->TabIndex = 5;
			this->Start_sesbirat->Text = L"Zahájit manipulaci";
			this->Start_sesbirat->UseVisualStyleBackColor = true;
			this->Start_sesbirat->Click += gcnew System::EventHandler(this, &Form1::Start_sesbirat_Click);
			// 
			// cam_button
			// 
			this->cam_button->Location = System::Drawing::Point(44, 92);
			this->cam_button->Name = L"cam_button";
			this->cam_button->Size = System::Drawing::Size(167, 23);
			this->cam_button->TabIndex = 3;
			this->cam_button->Text = L"Kalibrace obrazu";
			this->cam_button->UseVisualStyleBackColor = true;
			this->cam_button->Click += gcnew System::EventHandler(this, &Form1::cam_button_Click_1);
			// 
			// pictureBox1
			// 
			this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->pictureBox1->Location = System::Drawing::Point(14, 192);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(512, 288);
			this->pictureBox1->TabIndex = 4;
			this->pictureBox1->TabStop = false;
			// 
			// timer2
			// 
			this->timer2->Interval = 3000;
			this->timer2->Tick += gcnew System::EventHandler(this, &Form1::Timer2_Tick);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1096, 547);
			this->Controls->Add(this->tabControl1);
			this->Name = L"Form1";
			this->Text = L"Mdrive";
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->prog_pohyb))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->tabPage3->ResumeLayout(false);
			this->tabPage3->PerformLayout();
			this->groupBox5->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->Tab_bodu))->EndInit();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	
//pøímé øízení
private: System::Void pr_rizeni(System::Object^  sender, System::EventArgs^  e) {
			 
			 float data[4];
			 data[0]=(float)this->pr_servo0->Value;
			 data[1]=(float)this->pr_servo1->Value;
			 data[2]=(float)this->pr_servo2->Value;
			 data[3]=(float)this->pr_servo3->Value;
			 
			 this->serialPort1->Write((this->Manipulator->DataForSend("pohyb_servo", data)), 0, this->Manipulator->pocet_B);	
			 
			 this->txt_pr_srv_0->Text = L"Servo 0:    "+this->pr_servo0->Value.ToString();
			 this->txt_pr_srv_1->Text = L"Servo 1:    "+this->pr_servo1->Value.ToString();
			 this->txt_pr_srv_2->Text = L"Servo 2:    "+this->pr_servo2->Value.ToString();
			 this->txt_pr_srv_3->Text = L"Servo 3:    "+this->pr_servo3->Value.ToString();
		 }

private: System::Void Button_Najet_na_bod_Click(System::Object^  sender, System::EventArgs^  e) {
			 bool kontrola=1;
			 float data[3];
			 
			 if(this->NastB_X->Text!="")data[0]=(float)Convert::ToDouble(this->NastB_X->Text);
			 else kontrola=0; //vyskakovací okno s chybou
			 
			 if(this->NastB_Y->Text!="")data[1]=(float)Convert::ToDouble(this->NastB_Y->Text);
			 else kontrola=0; //else vyskakovací okno s chybou
			 
		     if(this->NastB_Z->Text!="")data[2]=(float)Convert::ToDouble(this->NastB_Z->Text);
			 else kontrola=0; //else vyskakovací okno s chybou

			 if(kontrola==1) this->serialPort1->Write((this->Manipulator->DataForSend("najet_na_bod", data)), 0, this->Manipulator->pocet_B);
		}

private: System::Void Prog_start_button_Click(System::Object^  sender, System::EventArgs^  e) {
			 bool kontrola=1;
			 float data[6];
			 for(int i=0;i<(this->prog_pohyb->RowCount);i++){	
                 
				 if(this->prog_pohyb->Rows[i]->Cells[0]->Value!="-")data[0]=(float)Convert::ToDouble(this->prog_pohyb->Rows[i]->Cells[0]->Value);
				 else break; //vyskakovací okno s chybou
				 if(this->prog_pohyb->Rows[i]->Cells[1]->Value!="-")data[1]=(float)Convert::ToDouble(this->prog_pohyb->Rows[i]->Cells[1]->Value);
				 else break; //vyskakovací okno s chybou
				 if(this->prog_pohyb->Rows[i]->Cells[2]->Value!="-")data[2]=(float)Convert::ToDouble(this->prog_pohyb->Rows[i]->Cells[2]->Value);
				 else break; //vyskakovací okno s chybou

				 i++;
				 if(i==(this->prog_pohyb->RowCount))break;

				 if(this->prog_pohyb->Rows[i]->Cells[0]->Value!="-")data[3]=(float)Convert::ToDouble(this->prog_pohyb->Rows[i]->Cells[0]->Value);
				 else break; //vyskakovací okno s chybou
				 if(this->prog_pohyb->Rows[i]->Cells[1]->Value!="-")data[4]=(float)Convert::ToDouble(this->prog_pohyb->Rows[i]->Cells[1]->Value);
				 else break; //vyskakovací okno s chybou
				 if(this->prog_pohyb->Rows[i]->Cells[2]->Value!="-")data[5]=(float)Convert::ToDouble(this->prog_pohyb->Rows[i]->Cells[2]->Value);
				 else break; //vyskakovací okno s chybou

				 this->serialPort1->Write((this->Manipulator->DataForSend("nahrat_program", data)), 0, this->Manipulator->pocet_B);
			 }

			 this->serialPort1->Write((this->Manipulator->DataForSend("vykonat_program", data)), 0, this->Manipulator->pocet_B);

		 }

private: Drawing::Bitmap^ IplImage2Bitmap( IplImage* iplimage )
{
	if (iplimage->roi)
	{
		IplImage* out;
		out = cvCreateImage(cvGetSize(iplimage), iplimage->depth,
		iplimage->roi->coi == 0 ? iplimage->nChannels : 1);
		cvCopyImage(iplimage, out);
		iplimage = out;
	}

		System::Drawing::Imaging::PixelFormat formato =
		(iplimage->nChannels == 3) ?
		System::Drawing::Imaging::PixelFormat::Format24bppRgb :
		System::Drawing::Imaging::PixelFormat::Format8bppIndexed;

		Drawing::Bitmap^ bmp = gcnew Drawing::Bitmap(iplimage->width,
		iplimage->height,
		iplimage->widthStep,
		formato,
		System::IntPtr(iplimage->imageData));

		if (formato == System::Drawing::Imaging::PixelFormat::Format8bppIndexed)
		{
			System::Drawing::Imaging::ColorPalette^ pal = bmp->Palette;
			for (int i = 0; i < pal->Entries->Length; i++)
				pal->Entries[i] = Color::FromArgb(255, i, i, i);
				bmp->Palette = pal;
		}	

		return bmp;
}

		 
private: System::Void cam_button_Click_1(System::Object^  sender, System::EventArgs^  e) {
			
			//this->pictureBox1->Image = this->C_Vision->frame_output();
			this->C_Vision->kalibrace();

	}
private: void camera_vision( void )
{
	
	CvCapture* capture = cvCreateCameraCapture( CV_CAP_ANY );
	cvSetCaptureProperty(capture,CV_CAP_PROP_FRAME_WIDTH, 1280);
	cvSetCaptureProperty(capture,CV_CAP_PROP_FRAME_HEIGHT, 720);
	cvSetCaptureProperty(capture,CV_CAP_PROP_FPS, 1);

   if ( !capture ) {
     //fprintf( stderr, "ERROR: capture is NULL \n" );
     //getchar();
   }

    IplImage* frame;
   
     // Get one frame
     frame = cvQueryFrame( capture );
     
	 if ( !frame ) {
       //fprintf( stderr, "ERROR: frame is null...\n" );
       //getchar();
       //break;
     }
     Drawing::Bitmap^ bmp1 = IplImage2Bitmap(frame);
	 this->pictureBox1->Image = bmp1;
	 
	 //cvShowImage( "pohled_kamery", frame );
	 // Do not release the frame!
     //If ESC key pressed, Key=0x10001B under OpenCV 0.9.7(linux version),
     //remove higher bits using AND operator
    // if ( (cvWaitKey(10) & 255) == 27 ) break;
   

   // Release the capture device housekeeping
   
   //cvDestroyWindow( "pohled_kamery" );
	
   //cvReleaseCapture( &capture );
}

private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
	
   this->pictureBox1->Image = this->C_Vision->frame_output();

		 }

private: void zahajit_manipulaci(void){
			 
			 this->Start_sesbirat->Enabled=false;
			 if(this->indikator_com->Text=="Komunikace OK"){
				float data[6];
				data[3]= (float)Convert::ToDouble(this->cil_bod_X->Text);
				data[4]= (float)Convert::ToDouble(this->cil_bod_Y->Text);
				data[5]= (float)Convert::ToDouble(this->cil_bod_Z->Text);
				
				/*
				data[3]= 3;
				data[4]= 10;
				data[5]= 20;
				*/
				for(int i=0; i<1000; i++){
					if(this->C_Vision->souradnice[i]==9999)break;  // konec cyklu po posledním objektu
					if ( (i%2)==1 ){
						data[0]= this->C_Vision->souradnice[i];   // +1 kvùli korekci pøi sbírání pøedmìtu
						data[1]= 0;
						data[2]= this->C_Vision->souradnice[i-1];
						this->serialPort1->Write((this->Manipulator->DataForSend("nahrat_program", data)), 0, this->Manipulator->pocet_B);
					}
				}
			
				this->serialPort1->Write((this->Manipulator->DataForSend("vykonat_program", data)), 0, this->Manipulator->pocet_B);

				//array<unsigned char>^ odeslat = gcnew array<unsigned char>(1);
				//odeslat=this->Manipulator->DataForSend("dokonceno?", data);
				//this->serialPort1->Write(odeslat, 0, this->Manipulator->pocet_B);
				this->label_info_automat->Text="Manipulace probíhá";
			 }

			 else{
				this->label_info_automat->Text="Není navázána komunikace";
			 }
		 
		 }

private: System::Void Start_sesbirat_Click(System::Object^  sender, System::EventArgs^  e) {
			 
			 this->Start_sesbirat->Enabled=false;
			 zahajit_manipulaci();

}

private: void zamerit_predmety(){

			this->C_Vision->zamereni();
			this->pictureBox2->Image = this->C_Vision->obr_zamereni_output();

			int pocet_radku=0;
			for(int i=0; i<30; i++){
				
				if(this->C_Vision->souradnice[i]==9999){
					for(int radek=pocet_radku;radek<30;radek++){
						this->Tab_bodu->Rows[radek]->Cells[0]->Value = "-";
						this->Tab_bodu->Rows[radek]->Cells[1]->Value = "-";
						
					}
					break;  // konec cyklu po posledním objektu
				}
				
				if ( (i%2)==1 ){
					
					this->Tab_bodu->Rows[pocet_radku]->Cells[0]->Value = Convert::ToString((double)this->C_Vision->souradnice[i]+1);
					this->Tab_bodu->Rows[pocet_radku]->Cells[1]->Value = Convert::ToString((double)this->C_Vision->souradnice[i-1]);
					pocet_radku++;
				}
				
			}
			if(this->label_info_automat->Text!="Manipulace probíhá")this->Start_sesbirat->Enabled=true;
		 
		 }

private: System::Void Timer2_Tick(System::Object^  sender, System::EventArgs^  e) {
		    zamerit_predmety();
		 }
private: System::Void button_com_open_Click(System::Object^  sender, System::EventArgs^  e) {
			 
			 float data[1];  // pouze pro správnou funkci nemá zde žádný význam
			 array<unsigned char>^ serial_buffer = gcnew array<unsigned char>(1);
			 array<unsigned char>^ odeslat = gcnew array<unsigned char>(1);

			 if(this->button_com_open->Text=="Pøipojit k øídící jednotce")
			 {
				this->serialPort1->Open();
				this->button_com_open->Text="Odpojit øídící jednotku";
				odeslat=this->Manipulator->DataForSend("pripojit", data);
				this->serialPort1->Write(odeslat, 0, this->Manipulator->pocet_B);
				this->serialPort1->Read(serial_buffer, 0, 1);
				if(serial_buffer[0]==odeslat[0])this->indikator_com->Text="Komunikace OK";
				else this->indikator_com->Text="Chyba komunikace";
			 }
			 else{
				this->button_com_open->Text="Pøipojit k øídící jednotce";
				odeslat=this->Manipulator->DataForSend("odpojit", data);
				this->serialPort1->Write(odeslat, 0, this->Manipulator->pocet_B);
				this->serialPort1->Close();
				this->indikator_com->Text="Odpojeno";
			 }
		}

private: System::Void button_start_zamerovani_Click(System::Object^  sender, System::EventArgs^  e) {
			 
			// zapnutí/vypnutí perspektivní transformace a zamìøování objektù
			 if(this->timer2->Enabled == false){
				this->timer2->Enabled= true; 
				zamerit_predmety();
				this->button_start_zamerovani->Text="Vypnout zamìøování objektù";
			 }
			 else{
				this->timer2->Enabled=false;   
				this->button_start_zamerovani->Text="Zapnout zamìøování objektù";
				this->Start_sesbirat->Enabled=false;
			 }

		 }


private: System::Void serialPort1_DataReceived(System::Object^  sender, System::IO::Ports::SerialDataReceivedEventArgs^  e) {

			array<unsigned char>^ serial_buffer = gcnew array<unsigned char>(4096);
			this->serialPort1->Read(serial_buffer, 0, 4096);
			
			float data[1];  // data[1] pouze pro správnou funkci nemá zde žádný význam
			
			
			array<unsigned char>^ odeslano = gcnew array<unsigned char>(1);
			odeslano=this->Manipulator->DataForSend("dokonceno?", data);
			// pøi dokonèení sesbírání dojde k pøíjmu signalizaèního bytu
			for(int a=0; a<4096; a++){
				if(serial_buffer[a]==odeslano[0]){
					this->label_info_automat->Text="Manipulace dokonèena";
					this->Start_sesbirat->Enabled=true;
					break;
					/*
					this->label_info_automat->Text="Test úspìšnosti manipulace";
						
						this->timer2->Enabled=false;
						zamerit_predmety();
						this->timer2->Enabled=true;

						if(this->C_Vision->souradnice[0]==9999){
							this->label_info_automat->Text="Manipulace dokonèena";
						}
						else{
							//Oprava po chybném uchopení
							zahajit_manipulaci();
						}
						*/
					
				}
			}
         }

private: System::Void indikator_com_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}

