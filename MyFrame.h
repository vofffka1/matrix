#pragma once
#include "wx/wx.h"
#include <wx/statline.h>
#include "Helper.h"
#include "DataChart.h"

class MyFrame : public wxFrame 
	{
	public:

		MyFrame(const wxString& title);
		~MyFrame();

	protected:
		wxStaticText* m_label1;
		wxTextCtrl* m_FilenameInput;
		wxStaticText* m_label2;
		wxTextCtrl* m_TolInput;
		wxButton* m_ComputeButton;
		wxStaticLine* m_staticline1;
		wxButton* m_ShowChartButton;
		wxTextCtrl* m_MatOutput;
		wxStaticText* m_staticText5;
		wxTextCtrl* m_textCtrl5;
		wxTextCtrl* m_TEigenVec;
		wxStaticText* m_staticText6;
		Helper Data;

	private:
		void Binds();

	};

class PlotDialog : public wxDialog
	{
	public:

		PlotDialog(const wxString &title,const Helper &d)
			: wxDialog(nullptr, -1, title)
			{
			this->SetSize(600,400);
			this->SetPosition(wxPoint(100,100));
			DataChart* my_plot = new DataChart(this,d.Results);
			ShowModal();
			Destroy();
			}
	};
