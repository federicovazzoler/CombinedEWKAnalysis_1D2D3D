void syst_symmetriser(string path, string boson, string channel, string flag)
{
  // Get histos
  TFile *file_in_reference = new TFile((path+"/h_" + boson + "_"+channel+"_pho0_pho1_pt_reference.root").c_str(),"OPEN");
  TH1D *dibosonSM_reference = (TH1D*)file_in_reference->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_sig").c_str());
  TH1D *bkg_jetpho_misid_reference = (TH1D*)file_in_reference->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_misid").c_str());
  TH1D *bkg_ttg_reference  = (TH1D*)file_in_reference->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_ttg").c_str());
  TH1D *bkg_ttgg_reference  = (TH1D*)file_in_reference->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_ttgg").c_str());
  TH1D *bkg_vvg_reference  = (TH1D*)file_in_reference->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_vvg").c_str());
  TH1D *bkg_zg_reference = 0;
  TH1D *bkg_zgg_reference = 0;
  if (boson == "WGG") {
    bkg_zg_reference = (TH1D*)file_in_reference->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_zg").c_str());
    bkg_zgg_reference = (TH1D*)file_in_reference->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_zgg").c_str());
  }
  TH1D *bkg_multiboson_reference = (TH1D*)bkg_ttg_reference->Clone("bkg_multiboson_reference");
  bkg_multiboson_reference->Reset();
  bkg_multiboson_reference->Add(bkg_ttg_reference);
  bkg_multiboson_reference->Add(bkg_ttgg_reference);
  bkg_multiboson_reference->Add(bkg_vvg_reference);

  TFile *file_in_jetmisid = new TFile((path+"/h_" + boson + "_"+channel+"_pho0_pho1_pt_"+flag+".root").c_str(),"OPEN");
  TH1D *dibosonSM_up = (TH1D*)file_in_jetmisid->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_sig").c_str());
  TH1D *bkg_jetpho_misid_up = (TH1D*)file_in_jetmisid->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_misid").c_str());
  TH1D *bkg_ttg_up  = (TH1D*)file_in_jetmisid->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_ttg").c_str());
  TH1D *bkg_ttgg_up  = (TH1D*)file_in_jetmisid->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_ttgg").c_str());
  TH1D *bkg_vvg_up  = (TH1D*)file_in_jetmisid->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_vvg").c_str());
  TH1D *bkg_zg_up = 0;
  TH1D *bkg_zgg_up = 0;
  if (boson == "WGG") {
    bkg_zg_up = (TH1D*)file_in_jetmisid->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_zg").c_str());
    bkg_zgg_up = (TH1D*)file_in_jetmisid->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_zgg").c_str());
  }
  TH1D *bkg_multiboson_up = (TH1D*)bkg_ttg_up->Clone("bkg_multiboson_up");
  bkg_multiboson_up->Reset();
  bkg_multiboson_up->Add(bkg_ttg_up);
  bkg_multiboson_up->Add(bkg_ttgg_up);
  bkg_multiboson_up->Add(bkg_vvg_up);

  TH1D *dibosonSM_down = (TH1D*)dibosonSM_up->Clone("dibosonSM_down");
  dibosonSM_down->Reset();

  TH1D *bkg_jetpho_misid_down = (TH1D*)bkg_jetpho_misid_up->Clone("bkg_jetpho_misid_down");
  bkg_jetpho_misid_down->Reset();

  TH1D *bkg_multiboson_down = (TH1D*)bkg_ttg_up->Clone("bkg_multiboson_down");
  bkg_multiboson_down->Reset();

  TH1D *bkg_zg_down = 0;
  TH1D *bkg_zgg_down = 0;

  if (boson == "WGG") {
    bkg_zg_down = (TH1D*)bkg_zg_up->Clone("bkg_zg_down");
    bkg_zg_down->Reset();

    bkg_zgg_down = (TH1D*)bkg_zgg_up->Clone("bkg_zgg_down");
    bkg_zgg_down->Reset();
  }

  for (int bin = 0; bin < bkg_jetpho_misid_up->GetNbinsX() + 2; bin++) {
    dibosonSM_down->SetBinContent(bin, dibosonSM_reference->GetBinContent(bin) - (dibosonSM_up->GetBinContent(bin) - dibosonSM_reference->GetBinContent(bin)));
    dibosonSM_down->SetBinError(bin, dibosonSM_up->GetBinError(bin));
    bkg_jetpho_misid_down->SetBinContent(bin, bkg_jetpho_misid_reference->GetBinContent(bin) - (bkg_jetpho_misid_up->GetBinContent(bin) - bkg_jetpho_misid_reference->GetBinContent(bin)));
    bkg_jetpho_misid_down->SetBinError(bin, bkg_jetpho_misid_up->GetBinError(bin));
    bkg_multiboson_down->SetBinContent(bin, bkg_multiboson_reference->GetBinContent(bin) - (bkg_multiboson_up->GetBinContent(bin) - bkg_multiboson_reference->GetBinContent(bin)));
    bkg_multiboson_down->SetBinError(bin, bkg_multiboson_up->GetBinError(bin));
    if (boson == "WGG") {
      bkg_zg_down->SetBinContent(bin , bkg_zg_reference->GetBinContent(bin) - (bkg_zg_up->GetBinContent(bin) - bkg_zg_reference->GetBinContent(bin)));
      bkg_zg_down->SetBinError(bin   , bkg_zg_up->GetBinError(bin));
      bkg_zgg_down->SetBinContent(bin, bkg_zgg_reference->GetBinContent(bin) - (bkg_zgg_up->GetBinContent(bin) - bkg_zgg_reference->GetBinContent(bin)));
      bkg_zgg_down->SetBinError(bin  , bkg_zgg_up->GetBinError(bin));
    }
  }

  // dump histos into output file
  TFile *file_out = new TFile((path+"/ch_"+channel+"_unequalBinning.root").c_str(),"UPDATE");
  dibosonSM_up->Write("diboson_jet_misidUp");
  bkg_jetpho_misid_up->Write("bkg_jetpho_misid_jet_misidUp");
  bkg_multiboson_up->Write("bkg_multibosonUp");
  if (boson == "WGG") {
    bkg_zg_up->Write("bkg_zg_jet_misidUp");
    bkg_zgg_up->Write("bkg_zgg_jet_misidUp");
  }
  dibosonSM_down->Write("diboson_jet_misidDown");
  bkg_jetpho_misid_down->Write("bkg_jetpho_misid_jet_misidDown");
  bkg_multiboson_down->Write("bkg_multibosonDown");
  if (boson == "WGG") {
    bkg_zg_down->Write("bkg_zg_jet_misidDown");
    bkg_zgg_down->Write("bkg_zgg_jet_misidDown");
  }

  file_in_reference->Close();
  delete file_in_reference;
  file_in_jetmisid->Close();
  delete file_in_jetmisid;
  file_out->Close();
  delete file_out;
}
