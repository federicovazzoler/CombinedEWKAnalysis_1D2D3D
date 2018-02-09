// -*- mode: c++ -*-

#ifndef ROOACSEMIANALYTICPDF_3D
#define ROOACSEMIANALYTICPDF_3D

#include "RooRealProxy.h"
#include "RooAbsPdf.h"
//#include "RooAbsData.h"
#include "TProfile2D.h"
#include "TProfile3D.h"
#include "TH3D.h"
#include "TF3.h"
#include "TString.h"
  
class RooACSemiAnalyticPdf_3D : public RooAbsPdf {
public:
  
  enum LimitType{ par1par2par3_TH3,
		  par1par2par3_TF3,
		  EFTtoATGC,
		  notype };

  RooACSemiAnalyticPdf_3D ();
  RooACSemiAnalyticPdf_3D (const char * name, const char * title,
			   RooAbsReal& _x, 
			   RooAbsReal& _par1, 
			   RooAbsReal& _par2,
			   RooAbsReal& _par3,
			   RooAbsReal& _SM_shape,
			   const char * parFilename,
			   const unsigned& lt);
  RooACSemiAnalyticPdf_3D (const RooACSemiAnalyticPdf_3D& other, const char * name);
  virtual TObject * clone(const char * newname) const { 
    return new RooACSemiAnalyticPdf_3D(*this, newname);
    }
  
  virtual ~RooACSemiAnalyticPdf_3D ();
  
  //  void setLimitType(const unsigned& lt) { type_ = (LimitType)lt; }

  Int_t getAnalyticalIntegral(RooArgSet& allVars, 
			    RooArgSet& analVars, 
			    const char* rangeName = 0) const;

  Double_t analyticalIntegral(Int_t code, const char* rangeName = 0) const;

  void readProfiles(std::vector<double> bins,TDirectory& dir) const ;
  TString getProfileFilename() const { return profileFilename; }
  
protected:
  
  RooRealProxy x;
  RooRealProxy par1;
  RooRealProxy par2;
  RooRealProxy par3;
  RooRealProxy SM_shape;
  
  LimitType type_;

  mutable std::map<std::string,std::vector<double> > integral_basis;

  mutable std::vector<double> bins; 

  TString profileFilename;
  
  TH3D ** P_par1par2par3_histo; //!
  TF3 ** P_par1par2par3_TF; //!
  
  void initializeProfiles();
  void initializeBins(const RooAbsReal& shape) const;
  void initializeNormalization(const std::string& rName,
			       const RooAbsReal& dep,
			       const RooAbsReal& shape) const;
  void readProfiles(RooACSemiAnalyticPdf_3D const& other);
  
  virtual double evaluate() const ;
  
private:
  
  ClassDef(RooACSemiAnalyticPdf_3D, 2) // aTGC function 
};

#endif
