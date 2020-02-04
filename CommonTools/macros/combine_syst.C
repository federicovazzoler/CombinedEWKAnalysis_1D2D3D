#include "lastbinner.C"

void combine_syst(string path, string boson, string channel, string flag, int nLastBins)
{
  // Get histos
  TFile *file_in_2016 = new TFile((path+"/h_" + boson + "_"+channel+"_pho0_pho1_pt_"+flag+"_2016.root").c_str(),"OPEN");
  TH1D *dibosonSM_2016 = (TH1D*)file_in_2016->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_sig").c_str());
  TH1D *bkg_jetpho_misid_2016 = (TH1D*)file_in_2016->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_misid").c_str());
  TH1D *bkg_ttgg_2016  = (TH1D*)file_in_2016 ->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_ttgg").c_str());
  TH1D *bkg_zg_2016 = 0;
  TH1D *bkg_zgg_2016 = 0;
  if (boson == "WGG") {
    bkg_zg_2016 = (TH1D*)file_in_2016->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_zg").c_str());
    bkg_zgg_2016 = (TH1D*)file_in_2016->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_zgg").c_str());
  }

  TFile *file_in_2017 = new TFile((path+"/h_" + boson + "_"+channel+"_pho0_pho1_pt_"+flag+"_2017.root").c_str(),"OPEN");
  TH1D *dibosonSM_2017 = (TH1D*)file_in_2017->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_sig").c_str());
  TH1D *bkg_jetpho_misid_2017 = (TH1D*)file_in_2017->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_misid").c_str());
  TH1D *bkg_ttgg_2017  = (TH1D*)file_in_2017 ->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_ttgg").c_str());
  TH1D *bkg_zg_2017 = 0;
  TH1D *bkg_zgg_2017 = 0;
  if (boson == "WGG") {
    bkg_zg_2017 = (TH1D*)file_in_2017->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_zg").c_str());
    bkg_zgg_2017 = (TH1D*)file_in_2017->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_zgg").c_str());
  }

  TFile *file_in_2018 = new TFile((path+"/h_" + boson + "_"+channel+"_pho0_pho1_pt_"+flag+"_2018.root").c_str(),"OPEN");
  TH1D *dibosonSM_2018 = (TH1D*)file_in_2018->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_sig").c_str());
  TH1D *bkg_jetpho_misid_2018 = (TH1D*)file_in_2018->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_misid").c_str());
  TH1D *bkg_ttgg_2018  = (TH1D*)file_in_2018 ->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_ttgg").c_str());
  TH1D *bkg_zg_2018 = 0;
  TH1D *bkg_zgg_2018 = 0;
  if (boson == "WGG") {
    bkg_zg_2018 = (TH1D*)file_in_2018->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_zg").c_str());
    bkg_zgg_2018 = (TH1D*)file_in_2018->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_zgg").c_str());
  }

  // combine years
  TH1D *dibosonSM = (TH1D*)dibosonSM_2016->Clone("dibosonSM");
  dibosonSM->Reset();

  TH1D *bkg_jetpho_misid = (TH1D*)bkg_jetpho_misid_2016->Clone("bkg_jetpho_misid");
  bkg_jetpho_misid->Reset();

  TH1D *bkg_ttgg = (TH1D*)bkg_ttgg_2016->Clone("bkg_ttgg");
  bkg_ttgg->Reset();

  TH1D *bkg_zg = 0;
  TH1D *bkg_zgg = 0;

  if (boson == "WGG") {
    bkg_zg = (TH1D*)bkg_zg_2016->Clone("bkg_zg");
    bkg_zg->Reset();

    bkg_zgg = (TH1D*)bkg_zgg_2016->Clone("bkg_zgg");
    bkg_zgg->Reset();
  }

  for (int bin = 0; bin < bkg_jetpho_misid->GetNbinsX() + 2; bin++) {
    dibosonSM->SetBinContent(bin, TMath::Sqrt(TMath::Power(dibosonSM_2016->GetBinContent(bin),2) + TMath::Power(dibosonSM_2017->GetBinContent(bin),2) + TMath::Power(dibosonSM_2018->GetBinContent(bin),2)));
    dibosonSM->SetBinError(bin, TMath::Sqrt(TMath::Power(TMath::Power(dibosonSM_2016->GetBinContent(bin),2) + TMath::Power(dibosonSM_2017->GetBinContent(bin),2) + TMath::Power(dibosonSM_2018->GetBinContent(bin),2), -1) * (TMath::Power(dibosonSM_2016->GetBinContent(bin) * dibosonSM_2016->GetBinError(bin), 2) + TMath::Power(dibosonSM_2017->GetBinContent(bin) * dibosonSM_2017->GetBinError(bin), 2) + TMath::Power(dibosonSM_2018->GetBinContent(bin) * dibosonSM_2018->GetBinError(bin), 2))));

    bkg_jetpho_misid->SetBinContent(bin, TMath::Sqrt(TMath::Power(bkg_jetpho_misid_2016->GetBinContent(bin),2) + TMath::Power(bkg_jetpho_misid_2017->GetBinContent(bin),2) + TMath::Power(bkg_jetpho_misid_2018->GetBinContent(bin),2)));
    bkg_jetpho_misid->SetBinError(bin, TMath::Sqrt(TMath::Power(TMath::Power(bkg_jetpho_misid_2016->GetBinContent(bin),2) + TMath::Power(bkg_jetpho_misid_2017->GetBinContent(bin),2) + TMath::Power(bkg_jetpho_misid_2018->GetBinContent(bin),2), -1) * (TMath::Power(bkg_jetpho_misid_2016->GetBinContent(bin) * bkg_jetpho_misid_2016->GetBinError(bin), 2) + TMath::Power(bkg_jetpho_misid_2017->GetBinContent(bin) * bkg_jetpho_misid_2017->GetBinError(bin), 2) + TMath::Power(bkg_jetpho_misid_2018->GetBinContent(bin) * bkg_jetpho_misid_2018->GetBinError(bin), 2))));

    bkg_ttgg->SetBinContent(bin, TMath::Sqrt(TMath::Power(bkg_ttgg_2016->GetBinContent(bin),2) + TMath::Power(bkg_ttgg_2017->GetBinContent(bin),2) + TMath::Power(bkg_ttgg_2018->GetBinContent(bin),2)));
    bkg_ttgg->SetBinError(bin, TMath::Sqrt(TMath::Power(TMath::Power(bkg_ttgg_2016->GetBinContent(bin),2) + TMath::Power(bkg_ttgg_2017->GetBinContent(bin),2) + TMath::Power(bkg_ttgg_2018->GetBinContent(bin),2), -1) * (TMath::Power(bkg_ttgg_2016->GetBinContent(bin) * bkg_ttgg_2016->GetBinError(bin), 2) + TMath::Power(bkg_ttgg_2017->GetBinContent(bin) * bkg_ttgg_2017->GetBinError(bin), 2) + TMath::Power(bkg_ttgg_2018->GetBinContent(bin) * bkg_ttgg_2018->GetBinError(bin), 2))));

    if (boson == "WGG") {
      bkg_zg->SetBinContent(bin, TMath::Sqrt(TMath::Power(bkg_zg_2016->GetBinContent(bin),2) + TMath::Power(bkg_zg_2017->GetBinContent(bin),2) + TMath::Power(bkg_zg_2018->GetBinContent(bin),2)));
      bkg_zg->SetBinError(bin, TMath::Sqrt(TMath::Power(TMath::Power(bkg_zg_2016->GetBinContent(bin),2) + TMath::Power(bkg_zg_2017->GetBinContent(bin),2) + TMath::Power(bkg_zg_2018->GetBinContent(bin),2), -1) * (TMath::Power(bkg_zg_2016->GetBinContent(bin) * bkg_zg_2016->GetBinError(bin), 2) + TMath::Power(bkg_zg_2017->GetBinContent(bin) * bkg_zg_2017->GetBinError(bin), 2) + TMath::Power(bkg_zg_2018->GetBinContent(bin) * bkg_zg_2018->GetBinError(bin), 2))));

      bkg_zgg->SetBinContent(bin, TMath::Sqrt(TMath::Power(bkg_zgg_2016->GetBinContent(bin),2) + TMath::Power(bkg_zgg_2017->GetBinContent(bin),2) + TMath::Power(bkg_zgg_2018->GetBinContent(bin),2)));
      bkg_zgg->SetBinError(bin, TMath::Sqrt(TMath::Power(TMath::Power(bkg_zgg_2016->GetBinContent(bin),2) + TMath::Power(bkg_zgg_2017->GetBinContent(bin),2) + TMath::Power(bkg_zgg_2018->GetBinContent(bin),2), -1) * (TMath::Power(bkg_zgg_2016->GetBinContent(bin) * bkg_zgg_2016->GetBinError(bin), 2) + TMath::Power(bkg_zgg_2017->GetBinContent(bin) * bkg_zgg_2017->GetBinError(bin), 2) + TMath::Power(bkg_zgg_2018->GetBinContent(bin) * bkg_zgg_2018->GetBinError(bin), 2))));
    }
  }

  if (nLastBins != -1) {
    dibosonSM = lastbinner(dibosonSM, nLastBins);
    bkg_jetpho_misid = lastbinner(bkg_jetpho_misid, nLastBins);
    bkg_ttgg = lastbinner(bkg_ttgg, nLastBins);
    if (boson == "WGG") {
      bkg_zg = lastbinner(bkg_zg, nLastBins);
      bkg_zgg = lastbinner(bkg_zgg, nLastBins);
    }
  }

  // dump histos into output file
  TFile *file_out = new TFile((path+"/ch_"+channel+"_unequalBinning.root").c_str(),"UPDATE");
  if (flag.find("_up") != string::npos) flag.replace(flag.find("_up"), 3, "Up");
  if (flag.find("_down") != string::npos) flag.replace(flag.find("_down"), 5, "Down");
  dibosonSM->Write(("diboson_"+flag).c_str());
  bkg_jetpho_misid->Write(("bkg_jetpho_misid_"+flag).c_str());
  bkg_ttgg->Write(("bkg_ttgg_"+flag).c_str());
  if (boson == "WGG") {
    bkg_zg->Write(("bkg_zg_"+flag).c_str());
    bkg_zgg->Write(("bkg_zgg_"+flag).c_str());
  }

  file_in_2016->Close();
  delete file_in_2016;
  file_in_2017->Close();
  delete file_in_2017;
  file_in_2018->Close();
  delete file_in_2018;
  file_out->Close();
  delete file_out;
}
