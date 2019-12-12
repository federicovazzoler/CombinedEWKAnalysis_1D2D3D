TH1D* lastbinner(TH1D* h_in, int nbins)
{ 
  float bins[nbins+1];
  for (int i = 0; i < nbins+1; i++) {
    bins[i] = h_in->GetBinLowEdge(h_in->GetNbinsX()-(nbins-1)+i);
  }
  
  TH1D * h_out = new TH1D("h_out",h_in->GetTitle(), nbins, bins);
  for (int i = h_in->GetNbinsX()-(nbins-1); i < h_in->GetNbinsX()+1; i++) {
    h_out->SetBinContent(i-(h_in->GetNbinsX()-nbins), h_in->GetBinContent(i));
    h_out->SetBinError(i-(h_in->GetNbinsX()-nbins), h_in->GetBinError(i));
  }
  
  string name = h_in->GetName();
  h_in->Delete();
  h_out->SetName(name.c_str());
  
  return h_out;
}
