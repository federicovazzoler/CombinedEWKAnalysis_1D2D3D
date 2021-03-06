void fundraw(string path, string name_tf1, string name_tg, double range)
{
//  TFile *file_TF1 = new TFile(("/home/fvazzole/work/aTGC_tool/CMSSW_7_1_5/src/CombinedEWKAnalysis/CommonTools/data/anomalousCoupling_WGG/FITi_" + name + ".root").c_str(),"OPEN");
  TFile *file_TF1 = new TFile((path+"/post_fit/"+name_tf1).c_str(),"OPEN");
  file_TF1->cd();
  file_TF1->ls();
  TList *list_TF1 = file_TF1->GetListOfKeys();

//  TFile *file_TGraph = new TFile(("/home/fvazzole/work/aTGC_tool/CMSSW_7_1_5/src/CombinedEWKAnalysis/CommonTools/data/anomalousCoupling_WGG/all_couplings/" + name + ".root").c_str(),"OPEN");
  TFile *file_TGraph = new TFile((path+"/pre_fit/"+name_tg).c_str(),"OPEN");
  file_TGraph->cd();
  file_TGraph->ls();
  TList *list_TGraph = file_TGraph->GetListOfKeys();

  Double_t min = (-1) * range * TMath::Power(10,-12);
  Double_t max = range * TMath::Power(10,-12);

  const int nPoints = 17;
  Double_t x_value[nPoints];
  Double_t y_value[nPoints];

  for (int i = 0; i < list_TGraph->GetEntries();i++)
  {
    TString name_TF1 = list_TF1->At(i)->GetName();
    TF1 *fitfunc = (TF1*)file_TF1->Get(name_TF1);
    fitfunc->SetRange(min, max);

    TString name_TGraph = list_TGraph->At(i)->GetName();
    TGraph *graph = (TGraph*)file_TGraph->Get(name_TGraph);

    TCanvas* c1 = new TCanvas("c1", "c1", 10, 10, 800, 600);
    c1->cd();

    TPad* pad1 = new TPad("pad1", "pad1", 0.0, 0.3, 1.0, 1.0);
    pad1->SetBottomMargin(0.01);
    pad1->SetGrid();
    pad1->Draw();
    pad1->cd();

    graph->SetTitle(Form("Bin %1.d",i+1));

    graph->GetXaxis()->SetTitle("");
    graph->GetXaxis()->SetTitleOffset(0.7);
    graph->GetXaxis()->SetLabelFont(42);
    graph->GetXaxis()->SetLabelSize(0);

    graph->GetYaxis()->SetTitle("BSM events/SM events");
    graph->GetYaxis()->SetTitleSize(0.05);
    graph->GetYaxis()->SetTitleOffset(0.8);
    graph->GetYaxis()->SetLabelSize(0.045);

    graph->SetMarkerColor(kBlack);
    graph->SetMarkerStyle(20);
    graph->SetMarkerSize(1.0);

    graph->Draw("AP");
    fitfunc->Draw("same");
    pad1->Update();
    c1->Update();

//    auto pt = new TPaveText(0.6,0.2,0.8,0.4,"NDCNB");
    auto pt = new TPaveText(0.35,0.7,0.65,0.9,"NDCNB");
    pt->AddText("a * x^2 + b * x + c");
    pt->AddText(Form("a = %.2f",fitfunc->GetParameter(2)));
    pt->AddText(Form("b = %.2f",fitfunc->GetParameter(1)));
    pt->AddText(Form("c = %.2f",fitfunc->GetParameter(0)));
//    pt->SetX1NDC(0.10); //new x start position
//    pt->SetX2NDC(0.40); //new x end position
//    pt->SetY1NDC(0.1); //dove inizia dal basso su y
//    pt->SetY2NDC(0.6);
    pt->Draw("same");

    c1->cd();

    for (int j = 0; j < nPoints; j++)
    {
      graph->GetPoint(j,x_value[j],y_value[j]);
//      cout << "Point " << j << " x = " << x_value[j] << " y = " << y_value[j] << endl;
      y_value[j] = y_value[j] - fitfunc->Eval(x_value[j]);
    }

    TGraph *pull = new TGraphErrors(17, x_value, y_value);

    TPad* pad2 = new TPad("pad2", "pad2", 0.0, 0.0, 1.0, 0.3);
    pad2->SetTopMargin(0.2);
    pad2->SetBottomMargin(0.3);
    pad2->SetGrid();
    pad2->Draw();
    pad2->cd();

    pull->SetTitle("");

    pull->GetXaxis()->SetTitle("ft0/Lambda^4");
    pull->GetXaxis()->SetTitleFont(42);
    pull->GetXaxis()->SetTitleSize(0.11);
    pull->GetXaxis()->SetTitleOffset(1.1);
    pull->GetXaxis()->SetLabelFont(42);
    pull->GetXaxis()->SetLabelSize(0.10);

    pull->GetYaxis()->SetTitle("Data - Fit");
    pull->GetYaxis()->SetLabelSize(0.045);
    pull->GetYaxis()->SetTitleSize(0.11);
    pull->GetYaxis()->SetTitleOffset(0.36);
    pull->GetYaxis()->SetLabelSize(0.1);
    pull->GetYaxis()->SetLabelOffset(0.01);
    pull->GetYaxis()->SetNdivisions(505);
//    pull->GetYaxis()->SetRangeUser(-0.0001, 0.0001);

    pull->SetMarkerStyle(20);
    pull->Draw("AP");

    TLine* line = new TLine(x_value[0], 0., x_value[16], 0.);
    line->SetLineColor(kRed);
    line->SetLineWidth(2);
    line->Draw("same");

    while (gSystem->AccessPathName(("wgg/" + name_tf1 + "/").c_str())) {
      gSystem->mkdir(("wgg/" + name_tf1 + "/").c_str(), kTRUE);
    }
    c1->SaveAs(("wgg/" + name_tf1 + "/" + "Range_" + std::to_string((int)range) + "_Bin_" + std::to_string(i+1) + ".pdf").c_str());

    delete fitfunc;
    delete graph;
    delete c1;
    delete pt;
  }
}
