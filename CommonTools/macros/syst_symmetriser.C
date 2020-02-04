#include "lastbinner.C"

void syst_symmetriser(string path, string boson, string channel, string flag, int nLastBins)
{
  // Get histos
  TFile *file_in_reference = new TFile((path+"/h_" + boson + "_"+channel+"_pho0_pho1_pt_reference.root").c_str(),"OPEN");
  TH1D *dibosonSM_reference = (TH1D*)file_in_reference->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_sig").c_str());
  TH1D *bkg_jetpho_misid_reference = (TH1D*)file_in_reference->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_misid").c_str());
  TH1D *bkg_ttgg_reference  = (TH1D*)file_in_reference->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_ttgg").c_str());
  TH1D *bkg_zg_reference = 0;
  TH1D *bkg_zgg_reference = 0;
  if (boson == "WGG") {
    bkg_zg_reference = (TH1D*)file_in_reference->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_zg").c_str());
    bkg_zgg_reference = (TH1D*)file_in_reference->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_zgg").c_str());
  }

  TFile *file_in_jetmisid = new TFile((path+"/h_" + boson + "_"+channel+"_pho0_pho1_pt_"+flag+".root").c_str(),"OPEN");
  TH1D *dibosonSM_up = (TH1D*)file_in_jetmisid->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_sig").c_str());
  TH1D *bkg_jetpho_misid_up = (TH1D*)file_in_jetmisid->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_misid").c_str());
  TH1D *bkg_ttgg_up  = (TH1D*)file_in_jetmisid->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_ttgg").c_str());
  TH1D *bkg_zg_up = 0;
  TH1D *bkg_zgg_up = 0;
  if (boson == "WGG") {
    bkg_zg_up = (TH1D*)file_in_jetmisid->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_zg").c_str());
    bkg_zgg_up = (TH1D*)file_in_jetmisid->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_zgg").c_str());
  }

  TH1D *dibosonSM_down = (TH1D*)dibosonSM_up->Clone("dibosonSM_down");
  dibosonSM_down->Reset();

  TH1D *bkg_jetpho_misid_down = (TH1D*)bkg_jetpho_misid_up->Clone("bkg_jetpho_misid_down");
  bkg_jetpho_misid_down->Reset();

  TH1D *bkg_ttgg_down = (TH1D*)bkg_ttgg_up->Clone("bkg_ttgg_down");
  bkg_ttgg_down->Reset();

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
    bkg_ttgg_down->SetBinContent(bin, bkg_ttgg_reference->GetBinContent(bin) - (bkg_ttgg_up->GetBinContent(bin) - bkg_ttgg_reference->GetBinContent(bin)));
    bkg_ttgg_down->SetBinError(bin, bkg_ttgg_up->GetBinError(bin));
    if (boson == "WGG") {
      bkg_zg_down->SetBinContent(bin , bkg_zg_reference->GetBinContent(bin) - (bkg_zg_up->GetBinContent(bin) - bkg_zg_reference->GetBinContent(bin)));
      bkg_zg_down->SetBinError(bin   , bkg_zg_up->GetBinError(bin));
      bkg_zgg_down->SetBinContent(bin, bkg_zgg_reference->GetBinContent(bin) - (bkg_zgg_up->GetBinContent(bin) - bkg_zgg_reference->GetBinContent(bin)));
      bkg_zgg_down->SetBinError(bin  , bkg_zgg_up->GetBinError(bin));
    }
  }

  if (nLastBins != -1) {
    dibosonSM_up = lastbinner(dibosonSM_up, nLastBins);
    dibosonSM_down = lastbinner(dibosonSM_down, nLastBins);
    bkg_jetpho_misid_up = lastbinner(bkg_jetpho_misid_up, nLastBins);
    bkg_jetpho_misid_down = lastbinner(bkg_jetpho_misid_down, nLastBins);
    bkg_ttgg_up = lastbinner(bkg_ttgg_up, nLastBins);
    bkg_ttgg_down = lastbinner(bkg_ttgg_down, nLastBins);
    if (boson == "WGG") {
      bkg_zg_up = lastbinner(bkg_zg_up, nLastBins);
      bkg_zg_down = lastbinner(bkg_zg_down, nLastBins);
      bkg_zgg_up = lastbinner(bkg_zgg_up, nLastBins);
      bkg_zgg_down = lastbinner(bkg_zgg_down, nLastBins);
    }
  }

  // dump histos into output file
  TFile *file_out = new TFile((path+"/ch_"+channel+"_unequalBinning.root").c_str(),"UPDATE");
  dibosonSM_up->Write("diboson_jet_misidUp");
  bkg_jetpho_misid_up->Write("bkg_jetpho_misid_jet_misidUp");
  bkg_ttgg_up->Write("bkg_ttgg_jet_misidUp");
  if (boson == "WGG") {
    bkg_zg_up->Write("bkg_zg_jet_misidUp");
    bkg_zgg_up->Write("bkg_zgg_jet_misidUp");
  }
  dibosonSM_down->Write("diboson_jet_misidDown");
  bkg_jetpho_misid_down->Write("bkg_jetpho_misid_jet_misidDown");
  bkg_ttgg_down->Write("bkg_ttgg_jet_misidDown");
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
