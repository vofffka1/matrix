#pragma once
#include "wx/wx.h"
#include <wxcharts.h>

typedef std::pair<std::size_t,double> DPair;
typedef std::vector<DPair> VecDPair;

class DataChart : public wxScrolledWindow
	{
	public:
		DataChart(wxWindow* parent,const VecDPair &data) : wxScrolledWindow(parent)
			{
			wxVector<double> points;
			wxVector<wxString> labels;
			auto Size = data.size();

			for(std::size_t i=0;i<Size;i++)
				{
				points.push_back(data[i].second);
				labels.push_back(std::to_string(data[i].first));
				}
			wxLineChartData chartData(labels);

			wxLineChartDataset::ptr dataset1(new wxLineChartDataset(
				"", wxColor(0, 255, 0), wxColor(255, 255, 255), wxColor(255, 255, 255), points));  
			chartData.AddDataset(dataset1);

			auto lineChartCtrl = new wxLineChartCtrl(this, wxID_ANY, chartData,
				wxDefaultPosition, wxSize(400,300), wxBORDER_NONE);

			wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
			topSizer->Add(lineChartCtrl, 1, wxEXPAND);
			
			this->SetSizer(topSizer);
			this->FitInside(); 
			this->SetScrollRate(10, 10);
			this->Layout();
			}

	};


