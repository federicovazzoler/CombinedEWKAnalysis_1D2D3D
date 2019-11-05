void merge_histo(string path, string channel, string flag)
{
  // Get histos 
  TFile *file_in = new TFile((path+"/h_WGG_"+channel+"_pho0_pho1_pt_"+flag+".root").c_str(),"OPEN");
  TH1D *data_obs = (TH1D*)file_in->Get(("h_WGG_"+channel+"_pho0_pho1_pt_data").c_str());
  TH1D *dibosonSM = (TH1D*)file_in->Get(("h_WGG_"+channel+"_pho0_pho1_pt_sig").c_str());
  TH1D *bkg_jetpho_misid = (TH1D*)file_in->Get(("h_WGG_"+channel+"_pho0_pho1_pt_misid").c_str());
  TH1D *bkg_zg = (TH1D*)file_in->Get(("h_WGG_"+channel+"_pho0_pho1_pt_zg").c_str());
  TH1D *bkg_zgg = (TH1D*)file_in->Get(("h_WGG_"+channel+"_pho0_pho1_pt_zgg").c_str());

  // dump histos into output file
  TFile *file_out = new TFile((path+"/ch_"+channel+"_unequalBinning.root").c_str(),"UPDATE");
  if (flag == "reference") {
    data_obs->Write("data_obs");
    dibosonSM->Write("diboson");
    bkg_jetpho_misid->Write("bkg_jetpho_misid");
    bkg_zg->Write("bkg_zg");
    bkg_zgg->Write("bkg_zgg");
  } else {
    if (flag.find("_up") != string::npos) flag.replace(flag.find("_up"), 3, "Up");
    if (flag.find("_down") != string::npos) flag.replace(flag.find("_down"), 5, "Down");
    dibosonSM->Write(("diboson_"+flag).c_str());
    bkg_jetpho_misid->Write(("bkg_jetpho_misid_"+flag).c_str());
    bkg_zg->Write(("bkg_zg_"+flag).c_str());
    bkg_zgg->Write(("bkg_zgg_"+flag).c_str());
  }

  file_in->Close();
  delete file_in;
  file_out->Close();
  delete file_out;
}
