#include "lastbinner.C"

void syst_symmetriser(string path, string boson, string channel, string flag, string year, int nLastBins)
{
  // Get histos
  TFile *file_in_reference = new TFile((path+"/h_" + boson + "_"+channel+"_pho0_pho1_pt_reference.root").c_str(),"OPEN");
  TH1D *dibosonSM_reference = (TH1D*)file_in_reference->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_sig").c_str());
  TH1D *bkg_jetpho_misid_reference = (TH1D*)file_in_reference->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_misid").c_str());
  TH1D *bkg_irred_reference  = (TH1D*)file_in_reference->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_irred").c_str());
  TH1D *bkg_egmisid_reference = 0;
  if (boson == "WGG") {
    bkg_egmisid_reference = (TH1D*)file_in_reference->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_egmisid").c_str());
  }

  TFile *file_in_jetmisid = new TFile((path+"/h_" + boson + "_"+channel+"_pho0_pho1_pt_"+flag+".root").c_str(),"OPEN");
  TH1D *dibosonSM_var = (TH1D*)file_in_jetmisid->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_sig").c_str());
  TH1D *bkg_jetpho_misid_var = (TH1D*)file_in_jetmisid->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_misid").c_str());
  TH1D *bkg_irred_var  = (TH1D*)file_in_jetmisid->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_irred").c_str());
  TH1D *bkg_egmisid_var = 0;
  if (boson == "WGG") {
    bkg_egmisid_var = (TH1D*)file_in_jetmisid->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_egmisid").c_str());
  }

  TH1D *dibosonSM_down = (TH1D*)dibosonSM_reference->Clone("dibosonSM_down");
  dibosonSM_down->Reset();
  TH1D *bkg_jetpho_misid_down = (TH1D*)bkg_jetpho_misid_reference->Clone("bkg_jetpho_misid_down");
  bkg_jetpho_misid_down->Reset();
  TH1D *bkg_irred_down = (TH1D*)bkg_irred_reference->Clone("bkg_irred_down");
  bkg_irred_down->Reset();

  TH1D *dibosonSM_up = (TH1D*)dibosonSM_reference->Clone("dibosonSM_up");
  dibosonSM_up->Reset();
  TH1D *bkg_jetpho_misid_up = (TH1D*)bkg_jetpho_misid_reference->Clone("bkg_jetpho_misid_up");
  bkg_jetpho_misid_up->Reset();
  TH1D *bkg_irred_up = (TH1D*)bkg_irred_reference->Clone("bkg_irred_up");
  bkg_irred_up->Reset();

  TH1D *bkg_egmisid_down = 0;
  TH1D *bkg_egmisid_up = 0;

  if (boson == "WGG") {
    bkg_egmisid_down = (TH1D*)bkg_egmisid_reference->Clone("bkg_egmisid_down");
    bkg_egmisid_down->Reset();

    bkg_egmisid_up = (TH1D*)bkg_egmisid_reference->Clone("bkg_egmisid_up");
    bkg_egmisid_up->Reset();
  }

  float factor = 1.;
  if (flag == "jet_misid_syst" || flag == "jet_misid_test" || flag == "jet_misid_qcd" || flag == "jet_misid_sherpa" || flag == "eg_misid") factor = 0.5;

  for (int bin = 0; bin < bkg_jetpho_misid_up->GetNbinsX() + 2; bin++) {
    dibosonSM_down->SetBinContent(bin, dibosonSM_reference->GetBinContent(bin) - (factor * (dibosonSM_var->GetBinContent(bin) - dibosonSM_reference->GetBinContent(bin))));
    dibosonSM_down->SetBinError(bin, 0.0);
    bkg_jetpho_misid_down->SetBinContent(bin, bkg_jetpho_misid_reference->GetBinContent(bin) - (factor * (bkg_jetpho_misid_var->GetBinContent(bin) - bkg_jetpho_misid_reference->GetBinContent(bin))));
    bkg_jetpho_misid_down->SetBinError(bin, 0.0);
    bkg_irred_down->SetBinContent(bin, bkg_irred_reference->GetBinContent(bin) - (factor * (bkg_irred_var->GetBinContent(bin) - bkg_irred_reference->GetBinContent(bin))));
    bkg_irred_down->SetBinError(bin, 0.0);
    if (boson == "WGG") {
      bkg_egmisid_down->SetBinContent(bin , bkg_egmisid_reference->GetBinContent(bin) - (factor * (bkg_egmisid_var->GetBinContent(bin) - bkg_egmisid_reference->GetBinContent(bin))));
      bkg_egmisid_down->SetBinError(bin, 0.0);
    }
    dibosonSM_up->SetBinContent(bin, dibosonSM_reference->GetBinContent(bin) + (factor * (dibosonSM_var->GetBinContent(bin) - dibosonSM_reference->GetBinContent(bin))));
    dibosonSM_up->SetBinError(bin, 0.0);
    bkg_jetpho_misid_up->SetBinContent(bin, bkg_jetpho_misid_reference->GetBinContent(bin) + (factor * (bkg_jetpho_misid_var->GetBinContent(bin) - bkg_jetpho_misid_reference->GetBinContent(bin))));
    bkg_jetpho_misid_up->SetBinError(bin, 0.0);
    bkg_irred_up->SetBinContent(bin, bkg_irred_reference->GetBinContent(bin) + (factor * (bkg_irred_var->GetBinContent(bin) - bkg_irred_reference->GetBinContent(bin))));
    bkg_irred_up->SetBinError(bin, 0.0);
    if (boson == "WGG") {
      bkg_egmisid_up->SetBinContent(bin , bkg_egmisid_reference->GetBinContent(bin) + (factor * (bkg_egmisid_var->GetBinContent(bin) - bkg_egmisid_reference->GetBinContent(bin))));
      bkg_egmisid_up->SetBinError(bin, 0.0);
    }

    if (dibosonSM_down->GetBinContent(bin) <= 0.) dibosonSM_down->SetBinContent(bin, 0.);
    if (dibosonSM_up->GetBinContent(bin) <= 0.) dibosonSM_up->SetBinContent(bin, 0.);
    if (bkg_jetpho_misid_down->GetBinContent(bin) <= 0.) bkg_jetpho_misid_down->SetBinContent(bin, 0.);
    if (bkg_jetpho_misid_up->GetBinContent(bin) <= 0.) bkg_jetpho_misid_up->SetBinContent(bin, 0.);
    if (bkg_irred_down->GetBinContent(bin) <= 0.) bkg_irred_down->SetBinContent(bin, 0.);
    if (bkg_irred_up->GetBinContent(bin) <= 0.) bkg_irred_up->SetBinContent(bin, 0.);
    if (boson == "WGG") {
      if (bkg_egmisid_down->GetBinContent(bin) <= 0.) bkg_egmisid_down->SetBinContent(bin, 0.);
      if (bkg_egmisid_up->GetBinContent(bin) <= 0.) bkg_egmisid_up->SetBinContent(bin, 0.);
    }
  }

  if (nLastBins != -1) {
    dibosonSM_up = lastbinner(dibosonSM_up, nLastBins);
    dibosonSM_down = lastbinner(dibosonSM_down, nLastBins);
    bkg_jetpho_misid_up = lastbinner(bkg_jetpho_misid_up, nLastBins);
    bkg_jetpho_misid_down = lastbinner(bkg_jetpho_misid_down, nLastBins);
    bkg_irred_up = lastbinner(bkg_irred_up, nLastBins);
    bkg_irred_down = lastbinner(bkg_irred_down, nLastBins);
    if (boson == "WGG") {
      bkg_egmisid_up = lastbinner(bkg_egmisid_up, nLastBins);
      bkg_egmisid_down = lastbinner(bkg_egmisid_down, nLastBins);
    }
  }

  // dump histos into output file
  TFile *file_out = new TFile((path+"/ch_"+channel+"_"+year+"_unequalBinning.root").c_str(),"UPDATE");
  dibosonSM_up->Write(("diboson_" + flag + "Up").c_str());
  bkg_jetpho_misid_up->Write(("bkg_jetpho_misid_" + flag + "Up").c_str());
  bkg_irred_up->Write(("bkg_irred_" + flag + "Up").c_str());
  if (boson == "WGG") {
    bkg_egmisid_up->Write(("bkg_egmisid_" + flag + "Up").c_str());
  }
  dibosonSM_down->Write(("diboson_" + flag + "Down").c_str());
  bkg_jetpho_misid_down->Write(("bkg_jetpho_misid_" + flag + "Down").c_str());
  bkg_irred_down->Write(("bkg_irred_" + flag + "Down").c_str());
  if (boson == "WGG") {
    bkg_egmisid_down->Write(("bkg_egmisid_" + flag + "Down").c_str());
  }

  file_in_reference->Close();
  delete file_in_reference;
  file_in_jetmisid->Close();
  delete file_in_jetmisid;
  file_out->Close();
  delete file_out;
}
