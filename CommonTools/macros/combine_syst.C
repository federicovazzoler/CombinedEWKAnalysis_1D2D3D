#include "lastbinner.C"

void combine_syst(string path, string boson, string channel, string flag, int nLastBins)
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

  TFile *file_in_reference_2016 = new TFile((path+"/h_" + boson + "_"+channel+"_pho0_pho1_pt_reference_2016.root").c_str(),"OPEN");
  TH1D *dibosonSM_reference_2016 = (TH1D*)file_in_reference_2016->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_sig").c_str());
  TH1D *bkg_jetpho_misid_reference_2016 = (TH1D*)file_in_reference_2016->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_misid").c_str());
  TH1D *bkg_irred_reference_2016 = (TH1D*)file_in_reference_2016->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_irred").c_str());;
  TH1D *bkg_egmisid_reference_2016 = 0;
  if (boson == "WGG") {
    bkg_egmisid_reference_2016 = (TH1D*)file_in_reference_2016->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_egmisid").c_str());
  }

  TFile *file_in_reference_2017 = new TFile((path+"/h_" + boson + "_"+channel+"_pho0_pho1_pt_reference_2017.root").c_str(),"OPEN");
  TH1D *dibosonSM_reference_2017 = (TH1D*)file_in_reference_2017->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_sig").c_str());
  TH1D *bkg_jetpho_misid_reference_2017 = (TH1D*)file_in_reference_2017->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_misid").c_str());
  TH1D *bkg_irred_reference_2017 = (TH1D*)file_in_reference_2017->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_irred").c_str());;
  TH1D *bkg_egmisid_reference_2017 = 0;
  if (boson == "WGG") {
    bkg_egmisid_reference_2017 = (TH1D*)file_in_reference_2017->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_egmisid").c_str());
  }

  TFile *file_in_reference_2018 = new TFile((path+"/h_" + boson + "_"+channel+"_pho0_pho1_pt_reference_2018.root").c_str(),"OPEN");
  TH1D *dibosonSM_reference_2018 = (TH1D*)file_in_reference_2018->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_sig").c_str());
  TH1D *bkg_jetpho_misid_reference_2018 = (TH1D*)file_in_reference_2018->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_misid").c_str());
  TH1D *bkg_irred_reference_2018 = (TH1D*)file_in_reference_2018->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_irred").c_str());;
  TH1D *bkg_egmisid_reference_2018 = 0;
  if (boson == "WGG") {
    bkg_egmisid_reference_2018 = (TH1D*)file_in_reference_2018->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_egmisid").c_str());
  }

  TFile *file_in_2016 = new TFile((path+"/h_" + boson + "_"+channel+"_pho0_pho1_pt_"+flag+"_2016.root").c_str(),"OPEN");
  TH1D *dibosonSM_2016 = (TH1D*)file_in_2016->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_sig").c_str());
  TH1D *bkg_jetpho_misid_2016 = (TH1D*)file_in_2016->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_misid").c_str());
  TH1D *bkg_irred_2016 = (TH1D*)file_in_2016->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_irred").c_str());;
  TH1D *bkg_egmisid_2016 = 0;
  if (boson == "WGG") {
    bkg_egmisid_2016 = (TH1D*)file_in_2016->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_egmisid").c_str());
  }

  TFile *file_in_2017 = new TFile((path+"/h_" + boson + "_"+channel+"_pho0_pho1_pt_"+flag+"_2017.root").c_str(),"OPEN");
  TH1D *dibosonSM_2017 = (TH1D*)file_in_2017->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_sig").c_str());
  TH1D *bkg_jetpho_misid_2017 = (TH1D*)file_in_2017->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_misid").c_str());
  TH1D *bkg_irred_2017 = (TH1D*)file_in_2017->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_irred").c_str());;
  TH1D *bkg_egmisid_2017 = 0;
  if (boson == "WGG") {
    bkg_egmisid_2017 = (TH1D*)file_in_2017->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_egmisid").c_str());
  }

  TFile *file_in_2018 = new TFile((path+"/h_" + boson + "_"+channel+"_pho0_pho1_pt_"+flag+"_2018.root").c_str(),"OPEN");
  TH1D *dibosonSM_2018 = (TH1D*)file_in_2018->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_sig").c_str());
  TH1D *bkg_jetpho_misid_2018 = (TH1D*)file_in_2018->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_misid").c_str());
  TH1D *bkg_irred_2018 = (TH1D*)file_in_2018->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_irred").c_str());;
  TH1D *bkg_egmisid_2018 = 0;
  if (boson == "WGG") {
    bkg_egmisid_2018 = (TH1D*)file_in_2018->Get(("h_" + boson + "_"+channel+"_pho0_pho1_pt_egmisid").c_str());
  }

  // combine years
  TH1D *dibosonSM = (TH1D*)dibosonSM_2016->Clone("dibosonSM");
  dibosonSM->Reset();
  TH1D *bkg_jetpho_misid = (TH1D*)bkg_jetpho_misid_2016->Clone("bkg_jetpho_misid");
  bkg_jetpho_misid->Reset();
  TH1D *bkg_irred = (TH1D*)bkg_irred_2016->Clone("bkg_irred");
  bkg_irred->Reset();
  TH1D *bkg_egmisid = 0;
  if (boson == "WGG") {
    bkg_egmisid = (TH1D*)bkg_egmisid_2016->Clone("bkg_egmisid");
    bkg_egmisid->Reset();
  }

  for (int bin = 0; bin < dibosonSM->GetNbinsX() + 2; bin++) {
    if (flag.find("_up") != string::npos) {
      dibosonSM->SetBinContent(bin, dibosonSM_reference->GetBinContent(bin) + TMath::Sqrt(TMath::Power(dibosonSM_2016->GetBinContent(bin) - dibosonSM_reference->GetBinContent(bin),2) + TMath::Power(dibosonSM_2017->GetBinContent(bin) - dibosonSM_reference->GetBinContent(bin),2) + TMath::Power(dibosonSM_2018->GetBinContent(bin) - dibosonSM_reference->GetBinContent(bin),2)));
    }
    if (flag.find("_down") != string::npos) {
      dibosonSM->SetBinContent(bin, dibosonSM_reference->GetBinContent(bin) - TMath::Sqrt(TMath::Power(dibosonSM_2016->GetBinContent(bin) - dibosonSM_reference->GetBinContent(bin),2) + TMath::Power(dibosonSM_2017->GetBinContent(bin) - dibosonSM_reference->GetBinContent(bin),2) + TMath::Power(dibosonSM_2018->GetBinContent(bin) - dibosonSM_reference->GetBinContent(bin),2)));
    }
    dibosonSM->SetBinError(bin, TMath::Sqrt( TMath::Power(dibosonSM_reference->GetBinContent(bin),2) + (TMath::Power(dibosonSM_2016->GetBinContent(bin) - dibosonSM_reference->GetBinContent(bin),2)/(TMath::Power(dibosonSM_2016->GetBinContent(bin) - dibosonSM_reference->GetBinContent(bin),2) + TMath::Power(dibosonSM_2017->GetBinContent(bin) - dibosonSM_reference->GetBinContent(bin),2) + TMath::Power(dibosonSM_2018->GetBinContent(bin) - dibosonSM_reference->GetBinContent(bin),2))) * (TMath::Power(dibosonSM_2016->GetBinError(bin),2) + TMath::Power(dibosonSM_reference->GetBinError(bin),2)) + (TMath::Power(dibosonSM_2017->GetBinContent(bin) - dibosonSM_reference->GetBinContent(bin),2)/(TMath::Power(dibosonSM_2016->GetBinContent(bin) - dibosonSM_reference->GetBinContent(bin),2) + TMath::Power(dibosonSM_2017->GetBinContent(bin) - dibosonSM_reference->GetBinContent(bin),2) + TMath::Power(dibosonSM_2018->GetBinContent(bin) - dibosonSM_reference->GetBinContent(bin),2))) * (TMath::Power(dibosonSM_2017->GetBinError(bin),2) + TMath::Power(dibosonSM_reference->GetBinError(bin),2)) + (TMath::Power(dibosonSM_2018->GetBinContent(bin) - dibosonSM_reference->GetBinContent(bin),2)/(TMath::Power(dibosonSM_2016->GetBinContent(bin) - dibosonSM_reference->GetBinContent(bin),2) + TMath::Power(dibosonSM_2017->GetBinContent(bin) - dibosonSM_reference->GetBinContent(bin),2) + TMath::Power(dibosonSM_2018->GetBinContent(bin) - dibosonSM_reference->GetBinContent(bin),2))) * (TMath::Power(dibosonSM_2018->GetBinError(bin),2) + TMath::Power(dibosonSM_reference->GetBinError(bin),2))));

    if (flag.find("_up") != string::npos) {
      bkg_jetpho_misid->SetBinContent(bin, bkg_jetpho_misid_reference->GetBinContent(bin) + TMath::Sqrt(TMath::Power(bkg_jetpho_misid_2016->GetBinContent(bin) - bkg_jetpho_misid_reference->GetBinContent(bin),2) + TMath::Power(bkg_jetpho_misid_2017->GetBinContent(bin) - bkg_jetpho_misid_reference->GetBinContent(bin),2) + TMath::Power(bkg_jetpho_misid_2018->GetBinContent(bin) - bkg_jetpho_misid_reference->GetBinContent(bin),2)));
    }
    if (flag.find("_down") != string::npos) {
      bkg_jetpho_misid->SetBinContent(bin, bkg_jetpho_misid_reference->GetBinContent(bin) - TMath::Sqrt(TMath::Power(bkg_jetpho_misid_2016->GetBinContent(bin) - bkg_jetpho_misid_reference->GetBinContent(bin),2) + TMath::Power(bkg_jetpho_misid_2017->GetBinContent(bin) - bkg_jetpho_misid_reference->GetBinContent(bin),2) + TMath::Power(bkg_jetpho_misid_2018->GetBinContent(bin) - bkg_jetpho_misid_reference->GetBinContent(bin),2)));
    }
    bkg_jetpho_misid->SetBinError(bin, TMath::Sqrt( TMath::Power(bkg_jetpho_misid_reference->GetBinContent(bin),2) + (TMath::Power(bkg_jetpho_misid_2016->GetBinContent(bin) - bkg_jetpho_misid_reference->GetBinContent(bin),2)/(TMath::Power(bkg_jetpho_misid_2016->GetBinContent(bin) - bkg_jetpho_misid_reference->GetBinContent(bin),2) + TMath::Power(bkg_jetpho_misid_2017->GetBinContent(bin) - bkg_jetpho_misid_reference->GetBinContent(bin),2) + TMath::Power(bkg_jetpho_misid_2018->GetBinContent(bin) - bkg_jetpho_misid_reference->GetBinContent(bin),2))) * (TMath::Power(bkg_jetpho_misid_2016->GetBinError(bin),2) + TMath::Power(bkg_jetpho_misid_reference->GetBinError(bin),2)) + (TMath::Power(bkg_jetpho_misid_2017->GetBinContent(bin) - bkg_jetpho_misid_reference->GetBinContent(bin),2)/(TMath::Power(bkg_jetpho_misid_2016->GetBinContent(bin) - bkg_jetpho_misid_reference->GetBinContent(bin),2) + TMath::Power(bkg_jetpho_misid_2017->GetBinContent(bin) - bkg_jetpho_misid_reference->GetBinContent(bin),2) + TMath::Power(bkg_jetpho_misid_2018->GetBinContent(bin) - bkg_jetpho_misid_reference->GetBinContent(bin),2))) * (TMath::Power(bkg_jetpho_misid_2017->GetBinError(bin),2) + TMath::Power(bkg_jetpho_misid_reference->GetBinError(bin),2)) + (TMath::Power(bkg_jetpho_misid_2018->GetBinContent(bin) - bkg_jetpho_misid_reference->GetBinContent(bin),2)/(TMath::Power(bkg_jetpho_misid_2016->GetBinContent(bin) - bkg_jetpho_misid_reference->GetBinContent(bin),2) + TMath::Power(bkg_jetpho_misid_2017->GetBinContent(bin) - bkg_jetpho_misid_reference->GetBinContent(bin),2) + TMath::Power(bkg_jetpho_misid_2018->GetBinContent(bin) - bkg_jetpho_misid_reference->GetBinContent(bin),2))) * (TMath::Power(bkg_jetpho_misid_2018->GetBinError(bin),2) + TMath::Power(bkg_jetpho_misid_reference->GetBinError(bin),2))));

    if (flag.find("_up") != string::npos) {
      bkg_irred->SetBinContent(bin, bkg_irred_reference->GetBinContent(bin) + TMath::Sqrt(TMath::Power(bkg_irred_2016->GetBinContent(bin) - bkg_irred_reference->GetBinContent(bin),2) + TMath::Power(bkg_irred_2017->GetBinContent(bin) - bkg_irred_reference->GetBinContent(bin),2) + TMath::Power(bkg_irred_2018->GetBinContent(bin) - bkg_irred_reference->GetBinContent(bin),2)));
    }
    if (flag.find("_down") != string::npos) {
      bkg_irred->SetBinContent(bin, bkg_irred_reference->GetBinContent(bin) - TMath::Sqrt(TMath::Power(bkg_irred_2016->GetBinContent(bin) - bkg_irred_reference->GetBinContent(bin),2) + TMath::Power(bkg_irred_2017->GetBinContent(bin) - bkg_irred_reference->GetBinContent(bin),2) + TMath::Power(bkg_irred_2018->GetBinContent(bin) - bkg_irred_reference->GetBinContent(bin),2)));
    }
    bkg_irred->SetBinError(bin, TMath::Sqrt( TMath::Power(bkg_irred_reference->GetBinContent(bin),2) + (TMath::Power(bkg_irred_2016->GetBinContent(bin) - bkg_irred_reference->GetBinContent(bin),2)/(TMath::Power(bkg_irred_2016->GetBinContent(bin) - bkg_irred_reference->GetBinContent(bin),2) + TMath::Power(bkg_irred_2017->GetBinContent(bin) - bkg_irred_reference->GetBinContent(bin),2) + TMath::Power(bkg_irred_2018->GetBinContent(bin) - bkg_irred_reference->GetBinContent(bin),2))) * (TMath::Power(bkg_irred_2016->GetBinError(bin),2) + TMath::Power(bkg_irred_reference->GetBinError(bin),2)) + (TMath::Power(bkg_irred_2017->GetBinContent(bin) - bkg_irred_reference->GetBinContent(bin),2)/(TMath::Power(bkg_irred_2016->GetBinContent(bin) - bkg_irred_reference->GetBinContent(bin),2) + TMath::Power(bkg_irred_2017->GetBinContent(bin) - bkg_irred_reference->GetBinContent(bin),2) + TMath::Power(bkg_irred_2018->GetBinContent(bin) - bkg_irred_reference->GetBinContent(bin),2))) * (TMath::Power(bkg_irred_2017->GetBinError(bin),2) + TMath::Power(bkg_irred_reference->GetBinError(bin),2)) + (TMath::Power(bkg_irred_2018->GetBinContent(bin) - bkg_irred_reference->GetBinContent(bin),2)/(TMath::Power(bkg_irred_2016->GetBinContent(bin) - bkg_irred_reference->GetBinContent(bin),2) + TMath::Power(bkg_irred_2017->GetBinContent(bin) - bkg_irred_reference->GetBinContent(bin),2) + TMath::Power(bkg_irred_2018->GetBinContent(bin) - bkg_irred_reference->GetBinContent(bin),2))) * (TMath::Power(bkg_irred_2018->GetBinError(bin),2) + TMath::Power(bkg_irred_reference->GetBinError(bin),2))));

    if (boson == "WGG") {
      if (flag.find("_up") != string::npos) {
        bkg_egmisid->SetBinContent(bin, bkg_egmisid_reference->GetBinContent(bin) + TMath::Sqrt(TMath::Power(bkg_egmisid_2016->GetBinContent(bin) - bkg_egmisid_reference->GetBinContent(bin),2) + TMath::Power(bkg_egmisid_2017->GetBinContent(bin) - bkg_egmisid_reference->GetBinContent(bin),2) + TMath::Power(bkg_egmisid_2018->GetBinContent(bin) - bkg_egmisid_reference->GetBinContent(bin),2)));
      }
      if (flag.find("_down") != string::npos) {
        bkg_egmisid->SetBinContent(bin, bkg_egmisid_reference->GetBinContent(bin) - TMath::Sqrt(TMath::Power(bkg_egmisid_2016->GetBinContent(bin) - bkg_egmisid_reference->GetBinContent(bin),2) + TMath::Power(bkg_egmisid_2017->GetBinContent(bin) - bkg_egmisid_reference->GetBinContent(bin),2) + TMath::Power(bkg_egmisid_2018->GetBinContent(bin) - bkg_egmisid_reference->GetBinContent(bin),2)));
      } 
    bkg_egmisid->SetBinError(bin, TMath::Sqrt( TMath::Power(bkg_egmisid_reference->GetBinContent(bin),2) + (TMath::Power(bkg_egmisid_2016->GetBinContent(bin) - bkg_egmisid_reference->GetBinContent(bin),2)/(TMath::Power(bkg_egmisid_2016->GetBinContent(bin) - bkg_egmisid_reference->GetBinContent(bin),2) + TMath::Power(bkg_egmisid_2017->GetBinContent(bin) - bkg_egmisid_reference->GetBinContent(bin),2) + TMath::Power(bkg_egmisid_2018->GetBinContent(bin) - bkg_egmisid_reference->GetBinContent(bin),2))) * (TMath::Power(bkg_egmisid_2016->GetBinError(bin),2) + TMath::Power(bkg_egmisid_reference->GetBinError(bin),2)) + (TMath::Power(bkg_egmisid_2017->GetBinContent(bin) - bkg_egmisid_reference->GetBinContent(bin),2)/(TMath::Power(bkg_egmisid_2016->GetBinContent(bin) - bkg_egmisid_reference->GetBinContent(bin),2) + TMath::Power(bkg_egmisid_2017->GetBinContent(bin) - bkg_egmisid_reference->GetBinContent(bin),2) + TMath::Power(bkg_egmisid_2018->GetBinContent(bin) - bkg_egmisid_reference->GetBinContent(bin),2))) * (TMath::Power(bkg_egmisid_2017->GetBinError(bin),2) + TMath::Power(bkg_egmisid_reference->GetBinError(bin),2)) + (TMath::Power(bkg_egmisid_2018->GetBinContent(bin) - bkg_egmisid_reference->GetBinContent(bin),2)/(TMath::Power(bkg_egmisid_2016->GetBinContent(bin) - bkg_egmisid_reference->GetBinContent(bin),2) + TMath::Power(bkg_egmisid_2017->GetBinContent(bin) - bkg_egmisid_reference->GetBinContent(bin),2) + TMath::Power(bkg_egmisid_2018->GetBinContent(bin) - bkg_egmisid_reference->GetBinContent(bin),2))) * (TMath::Power(bkg_egmisid_2018->GetBinError(bin),2) + TMath::Power(bkg_egmisid_reference->GetBinError(bin),2))));
    }
  }

  if (nLastBins != -1) {
    dibosonSM = lastbinner(dibosonSM, nLastBins);
    bkg_jetpho_misid = lastbinner(bkg_jetpho_misid, nLastBins);
    bkg_irred = lastbinner(bkg_irred, nLastBins);
    if (boson == "WGG") {
      bkg_egmisid = lastbinner(bkg_egmisid, nLastBins);
    }
  }

  // dump histos into output file
  TFile *file_out = new TFile((path+"/ch_"+channel+"_unequalBinning.root").c_str(),"UPDATE");
  if (flag.find("_up") != string::npos) flag.replace(flag.find("_up"), 3, "Up");
  if (flag.find("_down") != string::npos) flag.replace(flag.find("_down"), 5, "Down");
  dibosonSM->Write(("diboson_"+flag).c_str());
  bkg_jetpho_misid->Write(("bkg_jetpho_misid_"+flag).c_str());
  bkg_irred->Write(("bkg_irred_"+flag).c_str());
  if (boson == "WGG") {
    bkg_egmisid->Write(("bkg_egmisid_"+flag).c_str());
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
