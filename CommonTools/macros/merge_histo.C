#include "lastbinner.C"

void merge_histo(string path, string boson, string channel, string flag, int nLastBins)
{
  // get histos
  TFile *file_in = new TFile((path+"/h_" + boson + "_"+channel+"_pho0_pho1_pt_"+flag+".root").c_str(),"OPEN");
  TH1D *data_obs = (TH1D*)file_in->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_data").c_str());
  TH1D *dibosonSM = (TH1D*)file_in->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_sig").c_str());
  TH1D *bkg_jetpho_misid = (TH1D*)file_in->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_misid").c_str());
  TH1D *bkg_irred = (TH1D*)file_in->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_irred").c_str());
  TH1D *bkg_egmisid = 0;
  if (boson == "WGG") {
    bkg_egmisid = (TH1D*)file_in->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_egmisid").c_str());
  }

  if (nLastBins != -1) {
    data_obs = lastbinner(data_obs, nLastBins);
    dibosonSM = lastbinner(dibosonSM, nLastBins);
    bkg_jetpho_misid = lastbinner(bkg_jetpho_misid, nLastBins);
    bkg_irred = lastbinner(bkg_irred, nLastBins);
    if (boson == "WGG") {
      bkg_egmisid = lastbinner(bkg_egmisid, nLastBins);
    }
  }

  // dump histos into output file
  TFile *file_out = new TFile((path+"/ch_"+channel+"_unequalBinning.root").c_str(),"UPDATE");
  if (flag == "reference") {
    data_obs->Write("data_obs");
    dibosonSM->Write("diboson");
    bkg_jetpho_misid->Write("bkg_jetpho_misid");
    bkg_irred->Write("bkg_irred");
    if (boson == "WGG") {
      bkg_egmisid->Write("bkg_egmisid");
    }
  } else {
    if (flag.find("_up") != string::npos) flag.replace(flag.find("_up"), 3, "Up");
    if (flag.find("_down") != string::npos) flag.replace(flag.find("_down"), 5, "Down");
    dibosonSM->Write(("diboson_"+flag).c_str());
    bkg_jetpho_misid->Write(("bkg_jetpho_misid_"+flag).c_str());
    bkg_irred->Write(("bkg_irred_"+flag).c_str());
    if (boson == "WGG") {
      bkg_egmisid->Write(("bkg_egmisid_"+flag).c_str());
    }
  }

  file_in->Close();
  delete file_in;
  file_out->Close();
  delete file_out;
}
