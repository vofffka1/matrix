#include "MyFrame.h"



MyFrame::MyFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title,wxDefaultPosition,wxSize(580,290),
	wxDEFAULT_FRAME_STYLE & ~ (wxRESIZE_BORDER | wxMAXIMIZE_BOX)),
	Data(Helper())
	{

	wxBoxSizer* m_MainSizer;
	m_MainSizer = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* m_ControlSizer;
	m_ControlSizer = new wxBoxSizer( wxVERTICAL );
	
	m_label1 = new wxStaticText( this, wxID_ANY, wxT("Имя файла"), wxDefaultPosition, wxDefaultSize, 0 );
	m_label1->Wrap( -1 );
	m_ControlSizer->Add( m_label1, 0, wxALIGN_CENTER|wxALL, 10 );
	
	m_FilenameInput = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_ControlSizer->Add( m_FilenameInput, 0, wxALIGN_CENTER|wxALL|wxEXPAND, 5 );
	
	m_label2 = new wxStaticText( this, wxID_ANY, wxT("Точность"), wxDefaultPosition, wxDefaultSize, 0 );
	m_label2->Wrap( -1 );
	m_ControlSizer->Add( m_label2, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_TolInput = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_ControlSizer->Add( m_TolInput, 0, wxALIGN_CENTER|wxALL|wxEXPAND, 5 );
	
	m_ComputeButton = new wxButton( this, wxID_ANY, wxT("Расчет"), wxDefaultPosition, wxDefaultSize, 0 );
	m_ControlSizer->Add( m_ComputeButton, 0, wxALIGN_CENTER|wxALL|wxEXPAND, 15 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	m_ControlSizer->Add( m_staticline1, 0, wxEXPAND | wxALL, 10 );
	
	m_ShowChartButton = new wxButton( this, wxID_ANY, wxT("Показать график"), wxDefaultPosition, wxDefaultSize, 0 );
	m_ControlSizer->Add( m_ShowChartButton, 0, wxALIGN_CENTER|wxALL|wxEXPAND, 10 );
	
	m_MainSizer->Add( m_ControlSizer, 0, wxSHAPED, 5 );
	
	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer( wxVERTICAL );
	
	auto m_staticText7 = new wxStaticText( this, wxID_ANY, wxT("Матрица"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	bSizer41->Add( m_staticText7, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 10 );
	
	m_MatOutput = new wxTextCtrl( this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxHSCROLL|wxVSCROLL );
	bSizer41->Add( m_MatOutput, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	
	m_MainSizer->Add( bSizer41, 1, wxEXPAND, 5 );

	wxBoxSizer* m_OutputSizer;
	m_OutputSizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, wxT("Собственное значение"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	bSizer4->Add( m_staticText5, 0, wxALIGN_CENTER|wxALL, 10 );
	
	m_textCtrl5 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrl5->Enable(false);
	bSizer4->Add( m_textCtrl5, 0, wxALIGN_CENTER|wxALL, 5 );
	
	
	m_OutputSizer->Add( bSizer4, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText6 = new wxStaticText( this, wxID_ANY, wxT("Собственный вектор"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	bSizer5->Add( m_staticText6, 0, wxALIGN_CENTER|wxALL, 10 );
	

	m_TEigenVec = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,wxTE_MULTILINE | wxTE_READONLY);

	bSizer5->Add( m_TEigenVec, 1, wxALIGN_CENTER|wxALL, 5 );
	m_OutputSizer->Add( bSizer5, 1,wxALIGN_CENTER_HORIZONTAL, 5 );
	m_MainSizer->Add( m_OutputSizer, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( m_MainSizer );
	this->Layout();
	this->Centre( wxBOTH );
	Binds();
	}


MyFrame::~MyFrame(void)
	{
	}

void MyFrame::Binds()
	{
	m_ComputeButton->Bind(wxEVT_BUTTON, [&](wxCommandEvent&)
		{
		auto filename = m_FilenameInput->GetValue().ToStdString();
		std::ifstream in(filename);
		if(!in)
			{
			wxMessageBox("Не могу открыть файл!");
			return;
			}

		double value;
		if(!m_TolInput->GetValue().ToDouble(&value))
			{
			wxMessageBox("Точность задана некорректно!");
			return;
			}
		m_MatOutput->Clear();
		auto Matrix = Helper::get_matrix(in);	
		for(const auto &row : Matrix)
			{
			for(const auto &el : row)
				m_MatOutput->AppendText(std::to_string(el)+"   ");
			m_MatOutput->AppendText("\n");
			}
		Data = Helper(Matrix,value);
	
		m_textCtrl5->SetValue(std::to_string(Data.EigenValue));
		std::string text = "";
		for(const auto &el : Data.EigenVec)
			text += std::to_string(el)+"\n";
		m_TEigenVec->SetValue(text);

		});
	m_ShowChartButton->Bind(wxEVT_BUTTON, [&](wxCommandEvent&)
		{
		if(Data.is_compute)
			PlotDialog("График сходимости",Data).Show();
		else
			wxMessageBox("Сначала нужно провести расчет!");
		});

	}
