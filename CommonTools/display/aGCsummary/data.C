enum {
FM2_WGG_ele, FM2_WGG_muo, FM2_WGG_lep,
FM2_WGG_lep_8TeV,
FM3_WGG_ele, FM3_WGG_muo, FM3_WGG_lep,
FM3_WGG_lep_8TeV,
FT0_WGG_ele, FT0_WGG_muo, FT0_WGG_lep,
FT0_ZGG_ele, FT0_ZGG_muo, FT0_ZGG_lep,
FT0_WGG_lep_8TeV,
FT1_WGG_ele, FT1_WGG_muo, FT1_WGG_lep,
FT1_ZGG_ele, FT1_ZGG_muo, FT1_ZGG_lep,
FT1_WGG_lep_8TeV,
FT2_WGG_ele, FT2_WGG_muo, FT2_WGG_lep,
FT2_ZGG_ele, FT2_ZGG_muo, FT2_ZGG_lep,
FT2_WGG_lep_8TeV,
FT5_WGG_ele, FT5_WGG_muo, FT5_WGG_lep,
FT5_ZGG_ele, FT5_ZGG_muo, FT5_ZGG_lep,
FT6_WGG_ele, FT6_WGG_muo, FT6_WGG_lep,
FT6_ZGG_ele, FT6_ZGG_muo, FT6_ZGG_lep,
FT7_WGG_ele, FT7_WGG_muo, FT7_WGG_lep,
FT7_ZGG_ele, FT7_ZGG_muo, FT7_ZGG_lep,
FT8_ZGG_ele, FT8_ZGG_muo, FT8_ZGG_lep,
FT9_ZGG_ele, FT9_ZGG_muo, FT9_ZGG_lep,
k_nChan };

string runopt = "all"; //valid options are: all, lep, elemuo
bool excludeFM = true;
bool excludeFT012 = false;
bool excludeFT5p = true;
bool exclude8TeV = false;

bool catgcg = false;
bool catgcz = true;
bool natgcg = false;
bool natgcz = false;
bool catgceft  = true;
bool atgc = catgcg||catgcz||natgcg||natgcz|catgceft;
bool aqgc_a = false;
bool aqgc_ft = false;
bool aqgc_fm = false;
bool aqgc_fs = false;
bool aqgc = aqgc_a||aqgc_fs||aqgc_fm||aqgc_ft;
bool lineStyles = false;

int nPlotChan = 0;
vector<bool> plotChan( k_nChan, false );
vector<string> 
chanName(        k_nChan ),
  chanMeasurement( k_nChan ),
  chanResult (     k_nChan ),
  chanLumi   (     k_nChan ),
  chanSqrtS  (     k_nChan ),
  chanExp    (     k_nChan );
vector<int>
chanColor( k_nChan),
  chanLine(k_nChan);
vector<float> 
  chanaCC( k_nChan,0 ), 
  chanaCP( k_nChan,0 ),
  chanaCM( k_nChan,0 );

  int chan;

//PARAMETERS
float FM2_WGG_ele_DOWN = -87.7;
float FM2_WGG_ele_UP = 87.5;
float FM2_WGG_muo_DOWN = -66.5;
float FM2_WGG_muo_UP = 66.5;
float FM2_WGG_lep_DOWN = -61.9;
float FM2_WGG_lep_UP = 61.9;
float FM3_WGG_ele_DOWN = -139;
float FM3_WGG_ele_UP = 142;
float FM3_WGG_muo_DOWN = -107;
float FM3_WGG_muo_UP = 108;
float FM3_WGG_lep_DOWN = -99;
float FM3_WGG_lep_UP = 101;
float FT0_WGG_ele_DOWN = -2.94;
float FT0_WGG_ele_UP = 2.94;
float FT0_WGG_muo_DOWN = -2.22;
float FT0_WGG_muo_UP = 2.22;
float FT0_WGG_lep_DOWN = -2.06;
float FT0_WGG_lep_UP = 2.06;
float FT0_ZGG_ele_DOWN = -7.02;
float FT0_ZGG_ele_UP = 6.78;
float FT0_ZGG_muo_DOWN = -5.58;
float FT0_ZGG_muo_UP = 5.34;
float FT0_ZGG_lep_DOWN = -4.98;
float FT0_ZGG_lep_UP = 4.74;
float FT1_WGG_ele_DOWN = -3.66;
float FT1_WGG_ele_UP = 3.62;
float FT1_WGG_muo_DOWN = -2.78;
float FT1_WGG_muo_UP = 2.74;
float FT1_WGG_lep_DOWN = -2.58;
float FT1_WGG_lep_UP = 2.54;
float FT1_ZGG_ele_DOWN = -7.02;
float FT1_ZGG_ele_UP = 6.78;
float FT1_ZGG_muo_DOWN = -5.58;
float FT1_ZGG_muo_UP = 5.34;
float FT1_ZGG_lep_DOWN = -4.98;
float FT1_ZGG_lep_UP = 4.74;
float FT2_WGG_ele_DOWN = -8.12;
float FT2_WGG_ele_UP = 8.12;
float FT2_WGG_muo_DOWN = -6.12;
float FT2_WGG_muo_UP = 6.2;
float FT2_WGG_lep_DOWN = -5.72;
float FT2_WGG_lep_UP = 5.72;
float FT2_ZGG_ele_DOWN = -14;
float FT2_ZGG_ele_UP = 13.6;
float FT2_ZGG_muo_DOWN = -11.2;
float FT2_ZGG_muo_UP = 10.7;
float FT2_ZGG_lep_DOWN = -9.96;
float FT2_ZGG_lep_UP = 9.48;
float FT5_WGG_ele_DOWN = -0.84;
float FT5_WGG_ele_UP = 0.92;
float FT5_WGG_muo_DOWN = -0.68;
float FT5_WGG_muo_UP = 0.68;
float FT5_WGG_lep_DOWN = -0.6;
float FT5_WGG_lep_UP = 0.68;
float FT5_ZGG_ele_DOWN = -3.48;
float FT5_ZGG_ele_UP = 3.56;
float FT5_ZGG_muo_DOWN = -2.76;
float FT5_ZGG_muo_UP = 2.76;
float FT5_ZGG_lep_DOWN = -2.44;
float FT5_ZGG_lep_UP = 2.52;
float FT6_WGG_ele_DOWN = -1.08;
float FT6_WGG_ele_UP = 1.16;
float FT6_WGG_muo_DOWN = -0.84;
float FT6_WGG_muo_UP = 0.84;
float FT6_WGG_lep_DOWN = -0.76;
float FT6_WGG_lep_UP = 0.84;
float FT6_ZGG_ele_DOWN = -5.56;
float FT6_ZGG_ele_UP = 5.56;
float FT6_ZGG_muo_DOWN = -4.36;
float FT6_ZGG_muo_UP = 4.44;
float FT6_ZGG_lep_DOWN = -3.88;
float FT6_ZGG_lep_UP = 3.96;
float FT7_WGG_ele_DOWN = -2.44;
float FT7_WGG_ele_UP = 2.44;
float FT7_WGG_muo_DOWN = -1.88;
float FT7_WGG_muo_UP = 1.88;
float FT7_WGG_lep_DOWN = -1.72;
float FT7_WGG_lep_UP = 1.72;
float FT7_ZGG_ele_DOWN = -12.8;
float FT7_ZGG_ele_UP = 12.6;
float FT7_ZGG_muo_DOWN = -10.1;
float FT7_ZGG_muo_UP = 10;
float FT7_ZGG_lep_DOWN = -9;
float FT7_ZGG_lep_UP = 8.92;
float FT8_ZGG_ele_DOWN = -1.3;
float FT8_ZGG_ele_UP = 1.34;
float FT8_ZGG_muo_DOWN = -1.02;
float FT8_ZGG_muo_UP = 1.06;
float FT8_ZGG_lep_DOWN = -0.9;
float FT8_ZGG_lep_UP = 0.94;
float FT9_ZGG_ele_DOWN = -2.66;
float FT9_ZGG_ele_UP = 2.66;
float FT9_ZGG_muo_DOWN = -2.1;
float FT9_ZGG_muo_UP = 2.1;
float FT9_ZGG_lep_DOWN = -1.86;
float FT9_ZGG_lep_UP = 1.86;
//END PARAMETERS

if (!excludeFM) {
//FM2
  chan = FM2_WGG_ele;
  chanName[chan]            = "f_{M,2}";
  chanMeasurement[chan]     = "W(e#nu)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "W(e#nu)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FM2_WGG_ele_DOWN + FM2_WGG_ele_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FM2_WGG_ele_DOWN;// expected value! 
  chanaCP[chan]  = FM2_WGG_ele_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "elemuo") plotChan[chan] = true;

  chan = FM2_WGG_muo;
  chanName[chan]            = "f_{M,2}";
  chanMeasurement[chan]     = "W(#mu#nu)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "W(#mu#nu)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FM2_WGG_muo_DOWN + FM2_WGG_muo_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FM2_WGG_muo_DOWN;// expected value! 
  chanaCP[chan]  = FM2_WGG_muo_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "elemuo") plotChan[chan] = true;

  chan = FM2_WGG_lep;
  chanName[chan]            = "f_{M,2}";
  chanMeasurement[chan]     = "W(l#nu)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "W(l#nu)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FM2_WGG_lep_DOWN + FM2_WGG_lep_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FM2_WGG_lep_DOWN;// expected value! 
  chanaCP[chan]  = FM2_WGG_lep_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "lep") plotChan[chan] = true;

  chan = FM2_WGG_lep_8TeV;
  chanName[chan]            = "f_{M,2}";
  chanMeasurement[chan]     = "W(l#nu)#gamma#gamma";
  chanLumi[chan]            = "19.7 fb^{-1}";
  chanExp[chan]            = "W(l#nu)#gamma#gamma@8TeV";
  chanSqrtS[chan]          = "8 TeV";
  chanaCC[chan]  = (-549 + 531)/2;
  chanaCM[chan]  = -549;// expected value! 
  chanaCP[chan]  = 531;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "lep" || runopt == "elemuo") plotChan[chan] = true;
  if (exclude8TeV) plotChan[chan] = false;

//FM3
  chan = FM3_WGG_ele;
  chanName[chan]            = "f_{M,3}";
  chanMeasurement[chan]     = "W(e#nu)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "W(e#nu)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FM3_WGG_ele_DOWN + FM3_WGG_ele_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FM3_WGG_ele_DOWN;// expected value! 
  chanaCP[chan]  = FM3_WGG_ele_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "elemuo") plotChan[chan] = true;

  chan = FM3_WGG_muo;
  chanName[chan]            = "f_{M,3}";
  chanMeasurement[chan]     = "W(#mu#nu)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "W(#mu#nu)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FM3_WGG_muo_DOWN + FM3_WGG_muo_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FM3_WGG_muo_DOWN;// expected value! 
  chanaCP[chan]  = FM3_WGG_muo_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "elemuo") plotChan[chan] = true;

  chan = FM3_WGG_lep;
  chanName[chan]            = "f_{M,3}";
  chanMeasurement[chan]     = "W(l#nu)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "W(l#nu)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FM3_WGG_lep_DOWN + FM3_WGG_lep_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FM3_WGG_lep_DOWN;// expected value! 
  chanaCP[chan]  = FM3_WGG_lep_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "lep") plotChan[chan] = true;

  chan = FM3_WGG_lep_8TeV;
  chanName[chan]            = "f_{M,3}";
  chanMeasurement[chan]     = "W(l#nu)#gamma#gamma";
  chanLumi[chan]            = "19.7 fb^{-1}";
  chanExp[chan]            = "W(l#nu)#gamma#gamma@8TeV";
  chanSqrtS[chan]          = "8 TeV";
  chanaCC[chan]  = (-916 + 950)/2;
  chanaCM[chan]  = -916;// expected value! 
  chanaCP[chan]  = 950;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "lep" || runopt == "elemuo") plotChan[chan] = true;
  if (exclude8TeV) plotChan[chan] = false;
}

if (!excludeFT012) {
//FT0
  chan = FT0_WGG_ele;
  chanName[chan]            = "f_{T,0}";
  chanMeasurement[chan]     = "W(e#nu)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "W(e#nu)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT0_WGG_ele_DOWN + FT0_WGG_ele_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT0_WGG_ele_DOWN;// expected value! 
  chanaCP[chan]  = FT0_WGG_ele_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "elemuo") plotChan[chan] = true;

  chan = FT0_WGG_muo;
  chanName[chan]            = "f_{T,0}";
  chanMeasurement[chan]     = "W(#mu#nu)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "W(#mu#nu)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT0_WGG_muo_DOWN + FT0_WGG_muo_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT0_WGG_muo_DOWN;// expected value! 
  chanaCP[chan]  = FT0_WGG_muo_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "elemuo") plotChan[chan] = true;

  chan = FT0_WGG_lep;
  chanName[chan]            = "f_{T,0}";
  chanMeasurement[chan]     = "W(l#nu)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "W(l#nu)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT0_WGG_lep_DOWN + FT0_WGG_lep_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT0_WGG_lep_DOWN;// expected value! 
  chanaCP[chan]  = FT0_WGG_lep_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "lep") plotChan[chan] = true;

  chan = FT0_ZGG_ele;
  chanName[chan]            = "f_{T,0}";
  chanMeasurement[chan]     = "Z(ee)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "Z(ee)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT0_ZGG_ele_DOWN + FT0_ZGG_ele_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT0_ZGG_ele_DOWN;// expected value! 
  chanaCP[chan]  = FT0_ZGG_ele_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "elemuo") plotChan[chan] = true;

  chan = FT0_ZGG_muo;
  chanName[chan]            = "f_{T,0}";
  chanMeasurement[chan]     = "Z(#mu#mu)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "Z(#mu#mu)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT0_ZGG_muo_DOWN + FT0_ZGG_muo_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT0_ZGG_muo_DOWN;// expected value! 
  chanaCP[chan]  = FT0_ZGG_muo_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "elemuo") plotChan[chan] = true;

  chan = FT0_ZGG_lep;
  chanName[chan]            = "f_{T,0}";
  chanMeasurement[chan]     = "Z(ll)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "Z(ll)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT0_ZGG_lep_DOWN + FT0_ZGG_lep_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT0_ZGG_lep_DOWN;// expected value! 
  chanaCP[chan]  = FT0_ZGG_lep_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "lep") plotChan[chan] = true;

  chan = FT0_WGG_lep_8TeV;
  chanName[chan]            = "f_{T,0}";
  chanMeasurement[chan]     = "W(l#nu)#gamma#gamma";
  chanLumi[chan]            = "19.7 fb^{-1}";
  chanExp[chan]            = "W(l#nu)#gamma#gamma@8TeV";
  chanSqrtS[chan]          = "8 TeV";
  chanaCC[chan]  = (-26.5 + 27)/2;
  chanaCM[chan]  = -26.5;// expected value! 
  chanaCP[chan]  = 27;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "lep" || runopt == "elemuo") plotChan[chan] = true;
  if (exclude8TeV) plotChan[chan] = false;

//FT1
  chan = FT1_WGG_ele;
  chanName[chan]            = "f_{T,1}";
  chanMeasurement[chan]     = "W(e#nu)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "W(e#nu)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT1_WGG_ele_DOWN + FT1_WGG_ele_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT1_WGG_ele_DOWN;// expected value! 
  chanaCP[chan]  = FT1_WGG_ele_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "elemuo") plotChan[chan] = true;

  chan = FT1_WGG_muo;
  chanName[chan]            = "f_{T,1}";
  chanMeasurement[chan]     = "W(#mu#nu)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "W(#mu#nu)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT1_WGG_muo_DOWN + FT1_WGG_muo_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT1_WGG_muo_DOWN;// expected value! 
  chanaCP[chan]  = FT1_WGG_muo_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "elemuo") plotChan[chan] = true;

  chan = FT1_WGG_lep;
  chanName[chan]            = "f_{T,1}";
  chanMeasurement[chan]     = "W(l#nu)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "W(l#nu)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT1_WGG_lep_DOWN + FT1_WGG_lep_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT1_WGG_lep_DOWN;// expected value! 
  chanaCP[chan]  = FT1_WGG_lep_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "lep") plotChan[chan] = true;

  chan = FT1_ZGG_ele;
  chanName[chan]            = "f_{T,1}";
  chanMeasurement[chan]     = "Z(ee)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "Z(ee)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT1_ZGG_ele_DOWN + FT1_ZGG_ele_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT1_ZGG_ele_DOWN;// expected value! 
  chanaCP[chan]  = FT1_ZGG_ele_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "elemuo") plotChan[chan] = true;

  chan = FT1_ZGG_muo;
  chanName[chan]            = "f_{T,1}";
  chanMeasurement[chan]     = "Z(#mu#mu)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "Z(#mu#mu)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT1_ZGG_muo_DOWN + FT1_ZGG_muo_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT1_ZGG_muo_DOWN;// expected value! 
  chanaCP[chan]  = FT1_ZGG_muo_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "elemuo") plotChan[chan] = true;

  chan = FT1_ZGG_lep;
  chanName[chan]            = "f_{T,1}";
  chanMeasurement[chan]     = "Z(ll)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "Z(ll)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT1_ZGG_lep_DOWN + FT1_ZGG_lep_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT1_ZGG_lep_DOWN;// expected value! 
  chanaCP[chan]  = FT1_ZGG_lep_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "lep") plotChan[chan] = true;
  
  chan = FT1_WGG_lep_8TeV;
  chanName[chan]            = "f_{T,1}";
  chanMeasurement[chan]     = "W(l#nu)#gamma#gamma";
  chanLumi[chan]            = "19.7 fb^{-1}";
  chanExp[chan]            = "W(l#nu)#gamma#gamma@8TeV";
  chanSqrtS[chan]          = "8 TeV";
  chanaCC[chan]  = (-34.5 + 34.8)/2;
  chanaCM[chan]  = -34.5;// expected value! 
  chanaCP[chan]  = 34.8;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "lep" || runopt == "elemuo") plotChan[chan] = true;
  if (exclude8TeV) plotChan[chan] = false;

//FT2
  chan = FT2_WGG_ele;
  chanName[chan]            = "f_{T,2}";
  chanMeasurement[chan]     = "W(e#nu)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "W(e#nu)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT2_WGG_ele_DOWN + FT2_WGG_ele_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT2_WGG_ele_DOWN;// expected value! 
  chanaCP[chan]  = FT2_WGG_ele_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "elemuo") plotChan[chan] = true;

  chan = FT2_WGG_muo;
  chanName[chan]            = "f_{T,2}";
  chanMeasurement[chan]     = "W(#mu#nu)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "W(#mu#nu)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT2_WGG_muo_DOWN + FT2_WGG_muo_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT2_WGG_muo_DOWN;// expected value! 
  chanaCP[chan]  = FT2_WGG_muo_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "elemuo") plotChan[chan] = true;

  chan = FT2_WGG_lep;
  chanName[chan]            = "f_{T,2}";
  chanMeasurement[chan]     = "W(l#nu)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "W(l#nu)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT2_WGG_lep_DOWN + FT2_WGG_lep_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT2_WGG_lep_DOWN;// expected value! 
  chanaCP[chan]  = FT2_WGG_lep_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "lep") plotChan[chan] = true;

  chan = FT2_ZGG_ele;
  chanName[chan]            = "f_{T,2}";
  chanMeasurement[chan]     = "Z(ee)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "Z(ee)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT2_ZGG_ele_DOWN + FT2_ZGG_ele_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT2_ZGG_ele_DOWN;// expected value! 
  chanaCP[chan]  = FT2_ZGG_ele_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "elemuo") plotChan[chan] = true;

  chan = FT2_ZGG_muo;
  chanName[chan]            = "f_{T,2}";
  chanMeasurement[chan]     = "Z(#mu#mu)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "Z(#mu#mu)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT2_ZGG_muo_DOWN + FT2_ZGG_muo_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT2_ZGG_muo_DOWN;// expected value! 
  chanaCP[chan]  = FT2_ZGG_muo_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "elemuo") plotChan[chan] = true;

  chan = FT2_ZGG_lep;
  chanName[chan]            = "f_{T,2}";
  chanMeasurement[chan]     = "Z(ll)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "Z(ll)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT2_ZGG_lep_DOWN + FT2_ZGG_lep_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT2_ZGG_lep_DOWN;// expected value! 
  chanaCP[chan]  = FT2_ZGG_lep_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "lep") plotChan[chan] = true;
  
  chan = FT2_WGG_lep_8TeV;
  chanName[chan]            = "f_{T,2}";
  chanMeasurement[chan]     = "W(l#nu)#gamma#gamma";
  chanLumi[chan]            = "19.7 fb^{-1}";
  chanExp[chan]            = "W(l#nu)#gamma#gamma@8TeV";
  chanSqrtS[chan]          = "8 TeV";
  chanaCC[chan]  = (-74.6 + 73.7)/2;
  chanaCM[chan]  = -74.6;// expected value! 
  chanaCP[chan]  = 73.7;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "lep" || runopt == "elemuo") plotChan[chan] = true;
  if (exclude8TeV) plotChan[chan] = false;
}

if (!excludeFT5p) {
//FT5
  chan = FT5_WGG_ele;
  chanName[chan]            = "f_{T,5}";
  chanMeasurement[chan]     = "W(e#nu)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "W(e#nu)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT5_WGG_ele_DOWN + FT5_WGG_ele_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT5_WGG_ele_DOWN;// expected value! 
  chanaCP[chan]  = FT5_WGG_ele_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "elemuo") plotChan[chan] = true;

  chan = FT5_WGG_muo;
  chanName[chan]            = "f_{T,5}";
  chanMeasurement[chan]     = "W(#mu#nu)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "W(#mu#nu)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT5_WGG_muo_DOWN + FT5_WGG_muo_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT5_WGG_muo_DOWN;// expected value! 
  chanaCP[chan]  = FT5_WGG_muo_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "elemuo") plotChan[chan] = true;

  chan = FT5_WGG_lep;
  chanName[chan]            = "f_{T,5}";
  chanMeasurement[chan]     = "W(l#nu)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "W(l#nu)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT5_WGG_lep_DOWN + FT5_WGG_lep_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT5_WGG_lep_DOWN;// expected value! 
  chanaCP[chan]  = FT5_WGG_lep_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "lep") plotChan[chan] = true;

  chan = FT5_ZGG_ele;
  chanName[chan]            = "f_{T,5}";
  chanMeasurement[chan]     = "Z(ee)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "Z(ee)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT5_ZGG_ele_DOWN + FT5_ZGG_ele_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT5_ZGG_ele_DOWN;// expected value! 
  chanaCP[chan]  = FT5_ZGG_ele_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "elemuo") plotChan[chan] = true;

  chan = FT5_ZGG_muo;
  chanName[chan]            = "f_{T,5}";
  chanMeasurement[chan]     = "Z(#mu#mu)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "Z(#mu#mu)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT5_ZGG_muo_DOWN + FT5_ZGG_muo_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT5_ZGG_muo_DOWN;// expected value! 
  chanaCP[chan]  = FT5_ZGG_muo_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "elemuo") plotChan[chan] = true;

  chan = FT5_ZGG_lep;
  chanName[chan]            = "f_{T,5}";
  chanMeasurement[chan]     = "Z(ll)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "Z(ll)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT5_ZGG_lep_DOWN + FT5_ZGG_lep_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT5_ZGG_lep_DOWN;// expected value! 
  chanaCP[chan]  = FT5_ZGG_lep_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "lep") plotChan[chan] = true;

//FT6
  chan = FT6_WGG_ele;
  chanName[chan]            = "f_{T,6}";
  chanMeasurement[chan]     = "W(e#nu)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "W(e#nu)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT6_WGG_ele_DOWN + FT6_WGG_ele_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT6_WGG_ele_DOWN;// expected value! 
  chanaCP[chan]  = FT6_WGG_ele_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "elemuo") plotChan[chan] = true;

  chan = FT6_WGG_muo;
  chanName[chan]            = "f_{T,6}";
  chanMeasurement[chan]     = "W(#mu#nu)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "W(#mu#nu)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT6_WGG_muo_DOWN + FT6_WGG_muo_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT6_WGG_muo_DOWN;// expected value! 
  chanaCP[chan]  = FT6_WGG_muo_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "elemuo") plotChan[chan] = true;

  chan = FT6_WGG_lep;
  chanName[chan]            = "f_{T,6}";
  chanMeasurement[chan]     = "W(l#nu)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "W(l#nu)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT6_WGG_lep_DOWN + FT6_WGG_lep_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT6_WGG_lep_DOWN;// expected value! 
  chanaCP[chan]  = FT6_WGG_lep_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "lep") plotChan[chan] = true;

  chan = FT6_ZGG_ele;
  chanName[chan]            = "f_{T,6}";
  chanMeasurement[chan]     = "Z(ee)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "Z(ee)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT6_ZGG_ele_DOWN + FT6_ZGG_ele_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT6_ZGG_ele_DOWN;// expected value! 
  chanaCP[chan]  = FT6_ZGG_ele_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "elemuo") plotChan[chan] = true;

  chan = FT6_ZGG_muo;
  chanName[chan]            = "f_{T,6}";
  chanMeasurement[chan]     = "Z(#mu#mu)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "Z(#mu#mu)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT6_ZGG_muo_DOWN + FT6_ZGG_muo_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT6_ZGG_muo_DOWN;// expected value! 
  chanaCP[chan]  = FT6_ZGG_muo_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "elemuo") plotChan[chan] = true;

  chan = FT6_ZGG_lep;
  chanName[chan]            = "f_{T,6}";
  chanMeasurement[chan]     = "Z(ll)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "Z(ll)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT6_ZGG_lep_DOWN + FT6_ZGG_lep_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT6_ZGG_lep_DOWN;// expected value! 
  chanaCP[chan]  = FT6_ZGG_lep_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "lep") plotChan[chan] = true;

//FT7
  chan = FT7_WGG_ele;
  chanName[chan]            = "f_{T,7}";
  chanMeasurement[chan]     = "W(e#nu)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "W(e#nu)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT7_WGG_ele_DOWN + FT7_WGG_ele_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT7_WGG_ele_DOWN;// expected value! 
  chanaCP[chan]  = FT7_WGG_ele_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "elemuo") plotChan[chan] = true;

  chan = FT7_WGG_muo;
  chanName[chan]            = "f_{T,7}";
  chanMeasurement[chan]     = "W(#mu#nu)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "W(#mu#nu)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT7_WGG_muo_DOWN + FT7_WGG_muo_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT7_WGG_muo_DOWN;// expected value! 
  chanaCP[chan]  = FT7_WGG_muo_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "elemuo") plotChan[chan] = true;

  chan = FT7_WGG_lep;
  chanName[chan]            = "f_{T,7}";
  chanMeasurement[chan]     = "W(l#nu)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "W(l#nu)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT7_WGG_lep_DOWN + FT7_WGG_lep_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT7_WGG_lep_DOWN;// expected value! 
  chanaCP[chan]  = FT7_WGG_lep_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "lep") plotChan[chan] = true;

  chan = FT7_ZGG_ele;
  chanName[chan]            = "f_{T,7}";
  chanMeasurement[chan]     = "Z(ee)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "Z(ee)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT7_ZGG_ele_DOWN + FT7_ZGG_ele_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT7_ZGG_ele_DOWN;// expected value! 
  chanaCP[chan]  = FT7_ZGG_ele_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "elemuo") plotChan[chan] = true;

  chan = FT7_ZGG_muo;
  chanName[chan]            = "f_{T,7}";
  chanMeasurement[chan]     = "Z(#mu#mu)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "Z(#mu#mu)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT7_ZGG_muo_DOWN + FT7_ZGG_muo_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT7_ZGG_muo_DOWN;// expected value! 
  chanaCP[chan]  = FT7_ZGG_muo_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "elemuo") plotChan[chan] = true;

  chan = FT7_ZGG_lep;
  chanName[chan]            = "f_{T,7}";
  chanMeasurement[chan]     = "Z(ll)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "Z(ll)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT7_ZGG_lep_DOWN + FT7_ZGG_lep_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT7_ZGG_lep_DOWN;// expected value! 
  chanaCP[chan]  = FT7_ZGG_lep_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "lep") plotChan[chan] = true;

//FT8
  chan = FT8_ZGG_ele;
  chanName[chan]            = "f_{T,8}";
  chanMeasurement[chan]     = "Z(ee)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "Z(ee)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT8_ZGG_ele_DOWN + FT8_ZGG_ele_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT8_ZGG_ele_DOWN;// expected value! 
  chanaCP[chan]  = FT8_ZGG_ele_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "elemuo") plotChan[chan] = true;

  chan = FT8_ZGG_muo;
  chanName[chan]            = "f_{T,8}";
  chanMeasurement[chan]     = "Z(#mu#mu)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "Z(#mu#mu)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT8_ZGG_muo_DOWN + FT8_ZGG_muo_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT8_ZGG_muo_DOWN;// expected value! 
  chanaCP[chan]  = FT8_ZGG_muo_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "elemuo") plotChan[chan] = true;

  chan = FT8_ZGG_lep;
  chanName[chan]            = "f_{T,8}";
  chanMeasurement[chan]     = "Z(ll)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "Z(ll)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT8_ZGG_lep_DOWN + FT8_ZGG_lep_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT8_ZGG_lep_DOWN;// expected value! 
  chanaCP[chan]  = FT8_ZGG_lep_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "lep") plotChan[chan] = true;

//FT9
  chan = FT9_ZGG_ele;
  chanName[chan]            = "f_{T,9}";
  chanMeasurement[chan]     = "Z(ee)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "Z(ee)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT9_ZGG_ele_DOWN + FT9_ZGG_ele_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT9_ZGG_ele_DOWN;// expected value! 
  chanaCP[chan]  = FT9_ZGG_ele_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "elemuo") plotChan[chan] = true;

  chan = FT9_ZGG_muo;
  chanName[chan]            = "f_{T,9}";
  chanMeasurement[chan]     = "Z(#mu#mu)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "Z(#mu#mu)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT9_ZGG_muo_DOWN + FT9_ZGG_muo_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT9_ZGG_muo_DOWN;// expected value! 
  chanaCP[chan]  = FT9_ZGG_muo_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "elemuo") plotChan[chan] = true;

  chan = FT9_ZGG_lep;
  chanName[chan]            = "f_{T,9}";
  chanMeasurement[chan]     = "Z(ll)#gamma#gamma";
  chanLumi[chan]            = "137 fb^{-1}";
  chanExp[chan]            = "Z(ll)#gamma#gamma";
  chanSqrtS[chan]          = "13 TeV";
  chanaCC[chan]  = (FT9_ZGG_lep_DOWN + FT9_ZGG_lep_UP)/2;
  if (chanaCC[chan] == 0) chanaCC[chan]  = 1e-10;
  chanaCM[chan]  = FT9_ZGG_lep_DOWN;// expected value! 
  chanaCP[chan]  = FT9_ZGG_lep_UP;// expected value
  plotChan[chan] = false;
  if (runopt == "all" || runopt == "lep") plotChan[chan] = true;
}
// define experiments and experiment colors

const int numberExperiments = 7;
vector<string> experiments(numberExperiments);
vector<int> colors(numberExperiments);

experiments[0] = "W(e#nu)#gamma#gamma";
experiments[1] = "W(#mu#nu)#gamma#gamma";
experiments[2] = "W(l#nu)#gamma#gamma";
experiments[3] = "Z(ee)#gamma#gamma";
experiments[4] = "Z(#mu#mu)#gamma#gamma";
experiments[5] = "Z(ll)#gamma#gamma";
experiments[6] = "W(l#nu)#gamma#gamma@8TeV";

colors[0] = kAzure+1;
colors[1] = kViolet;
colors[2] = kBlue;
colors[3] = kOrange;
colors[4] = kOrange+2;
colors[5] = kRed;
colors[6] = kGreen;

// determine limit range and number of measurements and experiments

float range = 0.0;

int types = 0;
int exps = 0;
bool centralValue = false;

for( size_t ii=0; ii<k_nChan; ii++ )
  {
    if (plotChan[ii] == true) {
      // determine limit range, used for x axis

      if (-chanaCM[ii] > range) range = -chanaCM[ii];
      if ( chanaCP[ii] > range) range =  chanaCP[ii];

      // determine number of measurement, used in y axis
      nPlotChan++;
      // determine number of experiments,  used in ledgend
      if (chanExp[ii]=="W(e#nu)#gamma#gamma")   types = types|1;
      if (chanExp[ii]=="W(#mu#nu)#gamma#gamma")   types = types|2;
      if (chanExp[ii]=="W(l#nu)#gamma#gamma")   types = types|4;
      if (chanExp[ii]=="Z(ee)#gamma#gamma")   types = types|8;
      if (chanExp[ii]=="Z(#mu#mu)#gamma#gamma")   types = types|16;
      if (chanExp[ii]=="Z(ll)#gamma#gamma")   types = types|32;
      if (chanExp[ii]=="W(l#nu)#gamma#gamma@8TeV")   types = types|64;
      
// Concatonate chan results strings

      ostringstream stream1, stream2, stream3;
      stream1.precision(1);
      stream2.precision(1);
      stream3.precision(1);
      stream1 << scientific;
      stream2 << scientific;
      stream3 << scientific;

      stream1<< (chanaCC[ii]);    // for fixed point notation
      stream2<<(chanaCM[ii]);    // for fixed point notation
      stream3<<(chanaCP[ii]);    // for fixed point notation

      if (chanaCM[ii]<0.0||chanaCP[ii]>0.0) chanResult[ii] = "[" + stream2.str() + ", " + stream3.str() + "]";

      // Determine channel colors and line types;

      for (int jj = 0; jj < numberExperiments; jj++){
	if (chanExp[ii]==experiments[jj]) chanColor[ii] = colors[jj];
      }

      cout << "Set chan color " << chanColor[ii] << endl;

    }
  }
    
if (types&1) exps++;
if (types&2) exps++;
if (types&4) exps++;
if (types&8) exps++;
if (types&16) exps++;
if (types&32) exps++;
    

float minRange = -range*1.3*1.3;
float maxRange = range*1.3*3.2;
cout << "Range: " << -minRange << " - " << maxRange << endl;

cout << "Number of experiments: " << exps << ", Number of measurements: " << nPlotChan << endl;

