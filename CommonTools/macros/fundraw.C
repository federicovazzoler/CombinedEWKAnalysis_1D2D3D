void fundraw(string file_postfit, string file_prefit, string output_html, string par, double range) {

  TFile *file_TF1 = new TFile((file_postfit).c_str(),"OPEN");
  file_TF1->cd();
  file_TF1->ls();
  TList *list_TF1 = file_TF1->GetListOfKeys();

  TFile *file_TGraph = new TFile((file_prefit).c_str(),"OPEN");
  file_TGraph->cd();
  file_TGraph->ls();
  TList *list_TGraph = file_TGraph->GetListOfKeys();

  Double_t min = (-1) * range;
  Double_t max = range;

  const int nPoints = 17;
  Double_t x_value[nPoints];
  Double_t y_value[nPoints];

  for (int i = 0; i < list_TGraph->GetEntries();i++) {
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

    double dipho_pt_min = -1.;
    double dipho_pt_max = -1.;
    if (i == 0){
      dipho_pt_min = 0;      
      dipho_pt_max = 20;
    } 
    if (i == 1){
      dipho_pt_min = 20;      
      dipho_pt_max = 40;
    } 
    if (i == 2){
      dipho_pt_min = 40;      
      dipho_pt_max = 60;
    } 
    if (i == 3){
      dipho_pt_min = 60;      
      dipho_pt_max = 80;
    } 
    if (i == 4){
      dipho_pt_min = 80;      
      dipho_pt_max = 180;
    } 
    if (i == 5){
      dipho_pt_min = 180;      
      dipho_pt_max = 300;
    } 
    graph->SetTitle(Form("%1.f < Diphoton p_{T} < %1.f", dipho_pt_min, dipho_pt_max));

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

    auto pt = new TPaveText(0.35,0.7,0.65,0.9,"NDCNB");
    pt->AddText("a * x^2 + b * x + c");
    pt->AddText(Form("a = %.2f",fitfunc->GetParameter(2)));
    pt->AddText(Form("b = %.2f",fitfunc->GetParameter(1)));
    pt->AddText(Form("c = %.2f",fitfunc->GetParameter(0)));
//    pt->Draw("same");

    c1->cd();

    for (int j = 0; j < nPoints; j++) {
      graph->GetPoint(j,x_value[j],y_value[j]);
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

    string fancypar = "";
    if (par == "FT0") fancypar="f_{T,0}";
    if (par == "FT1") fancypar="f_{T,1}";
    if (par == "FT2") fancypar="f_{T,2}";
    if (par == "FT5") fancypar="f_{T,5}";
    if (par == "FT6") fancypar="f_{T,6}";
    if (par == "FT7") fancypar="f_{T,7}";
    if (par == "FT8") fancypar="f_{T,8}";
    if (par == "FT9") fancypar="f_{T,9}";
    pull->GetXaxis()->SetTitle((fancypar+"/#Lambda^{4}").c_str());
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

    pull->SetMarkerStyle(20);
    pull->Draw("AP");

    TLine* line = new TLine(x_value[0], 0., x_value[16], 0.);
    line->SetLineColor(kRed);
    line->SetLineWidth(2);
    line->Draw("same");

    string boson = "";
    if (file_postfit.find("WGG") != string::npos) boson = "WGG";
    if (file_postfit.find("ZGG") != string::npos) boson = "ZGG";
 
    while (gSystem->AccessPathName((output_html).c_str())) {
      gSystem->mkdir((output_html).c_str(), kTRUE);
    }
    c1->SaveAs((output_html + "/bin_" + std::to_string(i+1) + ".pdf").c_str());

    delete fitfunc;
    delete graph;
    delete c1;
    delete pt;
  }
}
