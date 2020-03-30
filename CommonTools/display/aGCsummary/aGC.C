#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>



#include "TStyle.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TLatex.h"
#include "TFrame.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TMarker.h"
#include "TLine.h"
#include "TBox.h"

using namespace std;

// titles and axis, marker size, etc.
float markerSize = 1.0;
float titleOffsetX = 0.9;
float titleOffsetY = 1.1;
float titleSizeX = 0.045;
float titleSizeY = 0.05;
float labelSizeX = 0.04;
float labelOffsetX = 0.004;
float labelOffsetY = 0.004;
float labelSizeY = 0.045;
int ndivx = 506;
int ndivy = 506;
float aspR = 1.4; 

// plot type
bool _natgcz;
bool _natgcg;


// texts
size_t ntxt = 1;
string currentName;
vector<string> txt(250);
vector<float>  txtSize(250);
vector<float>  txtX(250);
vector<float>  txtY(250);
vector<int>    txtNDC(250);
vector<int>    txtAlign(250);
vector<int>    txtFont(250);
vector<int>    txtColor(250);
void text_init();
void text_reset();
void text_write();

// drawings
void draw_bin_grid( float xmin, float xmax, float ymin, float ymax, 
		    int iCol=kGray+2, int iStyle=kDotted );
// constants
const float W_br_lnu    = 10.800e-02;
const float Z0_br_ll    =  3.366e-02;

int version = 0;
bool plotVJets = false;
// version 0 standard log plot
// version 1 depreciated - should delete
// version 2 ratio


class DataPoint
{
public: 

  DataPoint( float atgcc, float atgcm, float atgcp,
	     float ypos, float dy, int color, int line) 
    : _atgcc(atgcc), _atgcm(atgcm), _atgcp(atgcp),
      _ypos(ypos), _dy(dy), _color(color), _line(line)
  {
  }

  virtual ~DataPoint() 
  {
  }

  void draw()
  {
  

    cout << "Chan color " << _color << endl;
    if( _atgcc>-999.0 )
      {
    
 
	TGraphAsymmErrors _dataExpPoint(1);
	_dataExpPoint.SetPoint(1, _atgcc, _ypos );
	_dataExpPoint.SetPointError( 1, (_atgcc-_atgcm),(_atgcp-_atgcc), 0, 0 );
	_dataExpPoint.SetLineWidth(2);
	_dataExpPoint.SetLineColor(_color);
	_dataExpPoint.SetLineStyle(_line);
	_dataExpPoint.SetMarkerSize(0);
	_dataExpPoint.DrawClone("e");	
	_dataExpPoint.SetLineStyle(1);
	_dataExpPoint.DrawClone("||");	

	if (_atgcc !=0)
	  {
 	TMarker _dataPoint( _atgcc, _ypos, kFullCircle );
 	_dataPoint.SetMarkerSize(markerSize);
	_dataPoint.SetMarkerColor(_color);
	_dataPoint.DrawClone();
	_dataPoint.SetMarkerStyle(kOpenCircle);
 	_dataPoint.SetMarkerColor(_color);
	_dataPoint.DrawClone();
	  }	

      }


  }

private:
  float _atgcc;
  float _atgcm;
  float _atgcp;
  float _ypos;
  float _dy;
  int _theoColor;
  int _expLineColor;
  int _expFillColor;
  int _expCircleColor;
  int _color;
  int _line;
};

TCanvas*
aGC(float ymin=-2.0, float ymax=900000 )
{

#include "data.C"


  if (version ==2) ymax = 4;


  _natgcz = natgcz;
  _natgcg = natgcg;
  text_init();

  gStyle->SetEndErrorSize(7);
  gStyle->SetHatchesLineWidth(1);
  gStyle->SetHatchesSpacing(0.8);

  vector<string> cutName;
    
 
  float shift_ = 2.;
  if (version ==2) shift_ = 1.5;
  float size_  = 0.025;

  vector<int> channel_;
  vector<float> ypos_;
  vector<float> dy_;
  vector<float> vline_;
  vector<float> vmin_;
  vector<float> vmax_;
  vector<int>   vstyle_;

  size_t nBin_ = 1;


  size_t DY_;
  DY_=1;

  currentName = " ";
  
  for( size_t ii=0; ii<k_nChan; ii++ )
    {
      if (plotChan[ii]) {
	channel_.push_back(ii);
	ypos_.push_back(nBin_-0.5*DY_);
	dy_.push_back(DY_);

	if (chanName[ii]!=currentName)
	  {


	    vline_.push_back( nPlotChan - (nBin_) +2.0*(DY_)  );
	    vmin_.push_back( minRange );
	    vmax_.push_back( maxRange );
	    vstyle_.push_back(1);

	    txt[ntxt] = chanName[ii];
	    if (aqgc) txtSize[ntxt] = size_-0.0;
	    if (atgc) txtSize[ntxt] = size_+0.01;
	    txtX[ntxt] = 1.0*minRange;
	    if (aqgc) txtY[ntxt] = nPlotChan - (nBin_) +1.1*DY_;
	    if (atgc) txtY[ntxt] = nPlotChan - (nBin_) +0.4*DY_;
	    cout << "chan: " << txt[ntxt] << endl;
	    cout << "text location Y: " << txtY[ntxt] << endl;
            cout << "text location X: " << txtX[ntxt] << endl;
	    txtAlign[ntxt] = 12;
	    txtFont[ntxt] = 42;
	    ntxt++;


	  }


	currentName = chanName[ii];

	txt[ntxt] = chanMeasurement[ii];
	txtSize[ntxt] = size_-0.005;
	txtX[ntxt] = 0.3*maxRange;
	txtY[ntxt] = nPlotChan - (nBin_) +1.5*DY_;
	txtAlign[ntxt] = 12;
	txtFont[ntxt] = 42;
	ntxt++;

	txt[ntxt] = chanResult[ii];
	txtSize[ntxt] = size_-0.005;
	txtX[ntxt] = 0.46*maxRange;
	txtY[ntxt] = nPlotChan - (nBin_) +1.52*DY_;
	txtAlign[ntxt] = 12;
	txtFont[ntxt] = 42;
	ntxt++;

	txt[ntxt] = chanLumi[ii];
	txtSize[ntxt] = size_-0.005;
	txtX[ntxt] = 0.75*maxRange;
	txtY[ntxt] = nPlotChan - (nBin_) +1.55*DY_;
	txtAlign[ntxt] = 12;
	txtFont[ntxt] = 42;
	ntxt++;

	txt[ntxt] = chanSqrtS[ii];
	txtSize[ntxt] = size_-0.005;
	txtX[ntxt] = 0.88*maxRange;
	txtY[ntxt] = nPlotChan - (nBin_) +1.55*DY_;
	txtAlign[ntxt] = 12;
	txtFont[ntxt] = 42;
	ntxt++;

	

	nBin_+=DY_;
      }
    }


	txt[ntxt] = "Channel";
	txtSize[ntxt] = size_-0.005;
	txtX[ntxt] = 0.3*maxRange;
	txtY[ntxt] = nPlotChan +1.55*DY_;
	txtAlign[ntxt] = 12;
	txtFont[ntxt] = 42;
	ntxt++;


	txt[ntxt] = "Limits";
	txtSize[ntxt] = size_-0.005;
	txtX[ntxt] = 0.54*maxRange;
	txtY[ntxt] = nPlotChan +1.55*DY_;
	txtAlign[ntxt] = 12;
	txtFont[ntxt] = 42;
	ntxt++;

	txt[ntxt] = "#int";
	txtSize[ntxt] = size_-0.016;
	txtX[ntxt] = 0.75*maxRange;
	txtY[ntxt] = nPlotChan +1.50*DY_;
	txtAlign[ntxt] = 12;
	txtFont[ntxt] = 42;
	ntxt++;

	txt[ntxt] = "#it{L}dt";
	txtSize[ntxt] = size_-0.005;
	txtX[ntxt] = 0.76*maxRange;
	txtY[ntxt] = nPlotChan +1.55*DY_;
	txtAlign[ntxt] = 12;
	txtFont[ntxt] = 42;
	ntxt++;

	txt[ntxt] = "#sqrt{s}";
	txtSize[ntxt] = size_-0.005;
	txtX[ntxt] = 0.88*maxRange;
	txtY[ntxt] = nPlotChan +1.55*DY_;
	txtAlign[ntxt] = 12;
	txtFont[ntxt] = 42;
	ntxt++;
	
  
	vline_.push_back((0.51+nBin_*0.0025)*DY_ );
	vmin_.push_back( minRange );
	vmax_.push_back( maxRange );
	vstyle_.push_back(1);



 
  float xw_ = 1200;
  float yw_ = xw_/aspR;
 
  // the canvas
  TCanvas* c_=new TCanvas("aGC","atgc",300,300,xw_,yw_);
  c_->SetLeftMargin( 40./xw_ );
  c_->SetRightMargin( 40./xw_ );
  c_->SetTopMargin(  10./yw_ );
  c_->SetBottomMargin( 80./yw_ ); 
  c_->SetFillColor(0);
  c_->SetTickx(0);
  c_->SetTicky(1);
  c_->SetFrameFillStyle(0);
  c_->SetFrameLineWidth(2);
  c_->SetFrameLineColor(kWhite);
  c_->SetFrameBorderMode(0);

  TH1F* h_= new TH1F( "bidon", "bidon", 30, minRange, maxRange);
  TAxis* ax_ = h_->GetXaxis();
  TAxis* ay_ = h_->GetYaxis();
  
  if (aqgc_a) ax_->SetTitle("WW#gamma#gamma aQGC Limits @95% C.L. [TeV^{-2}]");
  if (aqgc_fm||aqgc_ft||aqgc_fs) ax_->SetTitle("aQGC Limits @95% C.L. [TeV^{-4}]");
  if (atgc) ax_->SetTitle("aTGC Limits @95% C.L.");
//  if (catgceft) ax_->SetTitle("aTGC Limits @95% C.L. [TeV^{-2}]");
  if (catgceft) ax_->SetTitle("aQGC Limits @95% C.L. [TeV^{-4}]");
  if (_natgcg) ax_->SetTitle("aTGC Limits @95% C.L.          ");
  ax_->SetNdivisions(ndivx);
  ax_->SetTitleOffset(titleOffsetX);
  ax_->SetTitleSize(titleSizeX);
  ax_->SetLabelOffset(labelOffsetX);
  ax_->SetLabelSize(labelSizeX);
  ax_->SetRange(minRange,maxRange);
  
  ndivy = 0;
  ay_->SetTitle("");
  ay_->SetNdivisions(ndivy);
  ay_->SetTitleOffset(titleOffsetY);
  ay_->SetTitleSize(titleSizeY);
  ay_->SetLabelOffset(labelOffsetY);
  ay_->SetLabelSize(labelSizeY);
  
  // now plotting
  c_->Draw();
  c_->cd();


  //  ***** Dynamically set y axis
  //  ***** Invert y axis
  c_->SetLogy(false);
  h_->GetYaxis()->SetRangeUser(0.5,nBin_+(1.0/1.4)*exps+0.75);
  h_->GetXaxis()->SetRangeUser(minRange,maxRange);
  h_->GetXaxis()->SetTicks("");
  h_->Draw("hist][");
  

  // Create ledgend
  float yy_ = nBin_+(1.0/1.4)*exps+0.25;
    float xx_ = 0.05*maxRange;
    float dyx_ = 0.07*maxRange;


  	float dyy_ = 1.0/1.5;
        int exp = 0;


 
  	if (centralValue){

  	  TMarker _dataPointCV( xx_- 0.26*maxRange, yy_-dyy_*0.50, kFullCircle );
  	  _dataPointCV.SetMarkerSize(markerSize);
  	  _dataPointCV.SetMarkerColor(kRed);
  	  _dataPointCV.DrawClone();
  	  _dataPointCV.SetMarkerStyle(kOpenCircle);
  	  _dataPointCV.SetMarkerColor(kRed);
  	  _dataPointCV.DrawClone();

	  
  	  txt[ntxt] = "Central";
  	  txtSize[ntxt] = 0.020;
  	  txtX[ntxt] = xx_ - 0.3*maxRange;
  	  txtY[ntxt] = yy_-dyy_*1.5;
  	  txtAlign[ntxt] = 12;
  	  txtFont[ntxt] = 42;
  	  ntxt++;

  	  txt[ntxt] = "Fit Value";
  	  txtSize[ntxt] = 0.020;
  	  txtX[ntxt] = xx_ - 0.3*maxRange;
  	  txtY[ntxt] = yy_-dyy_*2.6;
  	  txtAlign[ntxt] = 12;
  	  txtFont[ntxt] = 42;
  	  ntxt++;
  	}

	int baseTwo = 1;

	for (int ii=0; ii<numberExperiments;ii++){
	  if (types&baseTwo){

	    // Need to change to exp*1.25 for QGC plots, 0.9 for TGC plots 
	    TGraphErrors _dataTotPoint(1);
//	    _dataTotPoint.SetPoint(1, xx_, yy_-dyy_*exp*1.25 );
	    _dataTotPoint.SetPoint(1, xx_, yy_-dyy_*exp);
	    _dataTotPoint.SetPointError( 1, dyx_/2, 0 );
	    _dataTotPoint.SetLineWidth(2);
	    _dataTotPoint.SetLineColor(colors[ii]);
	    _dataTotPoint.SetMarkerSize(0);
	    _dataTotPoint.DrawClone("e");	
/*
	    if (baseTwo==8||baseTwo==16){
	    TMarker _dataPoint( xx_, yy_-dyy_*exp*1.25);
	    _dataPoint.SetMarkerSize(markerSize);
	    _dataPoint.SetMarkerColor(colors[ii]);
	    _dataPoint.DrawClone();
	    _dataPoint.SetMarkerColor(colors[ii]);
	    _dataPoint.DrawClone();
	    }
*/	    
	    txt[ntxt] = experiments[ii];
	    txtSize[ntxt] = 0.018;
	    txtX[ntxt] = xx_ - 0.20*maxRange;
//	    txtY[ntxt] = yy_-dyy_*exp*1.25;
	    txtY[ntxt] = yy_-dyy_*exp;
	    txtAlign[ntxt] = 12;
	    txtFont[ntxt] = 42;
	    ntxt++;

	    exp++;

	  }
	  baseTwo*=2;

	}



 
    int type = 0;
  for( size_t ii=0; ii<channel_.size(); ii++ )
    {
      size_t iChan = channel_[ii];
      float xx_ = nBin_-ypos_[ii];
      float dyy_ = dy_[ii];
      type = 1;
      if (chanExp[iChan]=="ATLAS") type= 2;
     if (chanExp[iChan]=="CDF") type= 3;
       if (chanExp[iChan]=="D0") type= 4;
    if (chanExp[iChan]=="LEP") type= 5;

      DataPoint p_( chanaCC[iChan], chanaCM[iChan], chanaCP[iChan],
		    xx_, dyy_ , chanColor[iChan], chanLine[iChan]) ;
      p_.draw();
    }
  
  for( size_t ii=0; ii<vline_.size(); ii++ )
    {
      draw_bin_grid( vmin_[ii], vmax_[ii], vline_[ii], vline_[ii],
		     kGray+2, vstyle_[ii] );
    }

  c_->RedrawAxis();
  c_->GetFrame()->Draw();

  text_write();    

  return c_;
}

void draw_bin_grid( float xmin, float xmax, float ymin, float ymax, int iCol, int iStyle )
{
  TLine grid_;
  grid_.SetLineColor(iCol);
  grid_.SetLineStyle(iStyle);
  grid_.DrawLine(xmin,ymin,xmax,ymax);
}

void text_reset()
{
  for( size_t ii=0; ii<250; ii++ )
    {
      txt[ii]="";
      txtX[ii]=0.50;
      txtY[ii]=0.50;
      txtSize[ii]=0.050;
      txtAlign[ii]=11;
      txtFont[ii]=42;
      txtColor[ii]=kBlack;
      txtNDC[ii]=false;
    }
}

void text_init()
{
  text_reset();

  ntxt = 3;

  txt[0] = "";
  txtSize[0] = 0.055;
  txtX[0] = 0.95;
  txtY[0] = 0.95;
  txtAlign[0] = 31;
  txtNDC[0]=true;
  txtFont[0] = 42;

//  txt[1] = "July 2019";
  txt[1] = "Preliminary";
  txtSize[1] = 0.028;
  txtX[1] = 0.1;
  txtY[1] = 0.96;
  txtAlign[1] = 31;
  txtNDC[1]=true;
  txtFont[1] = 42;

  txt[2] = "";
  txtSize[2] = 0.025;
  txtX[2] = 0.035;
  //if (version ==0||version==8) txtX[2] = 0.05;
  txtY[2] = 0.024;
  txtAlign[2] = 11;
  txtNDC[2]=true;
  txtFont[2] = 42;


  
   if (_natgcg) {
  txt[ntxt] = "x10^{-2}(h_{3}),";
  txtSize[ntxt] = 0.03;
  txtX[ntxt] = 0.91;
  txtY[ntxt] = 0.06;
  txtAlign[ntxt] = 11;
  txtNDC[ntxt]=true;
  txtFont[ntxt] = 42;
  ntxt++;

  txt[ntxt] = "x10^{-4}(h_{4})";
  txtSize[ntxt] = 0.03;
  txtX[ntxt] = 0.91;
  txtY[ntxt] = 0.02;
  txtAlign[ntxt] = 11;
  txtNDC[ntxt]=true;
  txtFont[ntxt] = 42;
  ntxt++;
  }
 
}

void
text_write()
{  
  for( size_t ii=0; ii<ntxt; ii++ )
    { 
      TLatex latex;
      if( txtNDC[ii] ) latex.SetNDC();    
      latex.SetTextFont(txtFont[ii]);
      latex.SetTextSize(txtSize[ii]);    
      latex.SetTextColor(txtColor[ii]);    
      latex.SetTextAlign(txtAlign[ii]); 
      latex.DrawLatex(txtX[ii],txtY[ii],txt[ii].c_str());
    }
}

