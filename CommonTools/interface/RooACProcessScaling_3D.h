// -*- mode: c++ -*-


#ifndef ROOACPROCESSSCALING_3D
#define ROOACPROCESSSCALING_3D

#include "RooRealProxy.h"
#include "RooAbsPdf.h"
#include "TProfile2D.h"
#include "TProfile3D.h"
#include "TH3D.h"
#include "TF3.h"
#include "TString.h"
#include <iostream>
#include <fstream>
#include <vector>

  
class RooACProcessScaling_3D : public RooAbsReal {
public:
  
  enum LimitType{ par1par2par3_TH3, 
		  par1par2par3_TF3, 
		  EFTtoATGC, 
		  notype };

  RooACProcessScaling_3D ();
  RooACProcessScaling_3D (const char * name, const char * title,
			  RooAbsReal& _x, 
			  RooAbsReal& _par1,
			  RooAbsReal& _par2, 
			  RooAbsReal& _par3,
			  RooAbsReal& _SM_shape,
				   const char * parFilename,LimitType _type);
  RooACProcessScaling_3D (const RooACProcessScaling_3D& other, const char * name);
  virtual TObject * clone(const char * newname) const { 
    return new RooACProcessScaling_3D(*this, newname);
    }
  
  //  void setLimitType(const unsigned& lt) { type_ = (LimitType)lt; }

  virtual ~RooACProcessScaling_3D ();  
  
  void readProfiles(std::vector<double> bins,TDirectory& dir,LimitType _type) const ;

  TString getProfileFilename() const { return profileFilename; }
  
protected:
  
  RooRealProxy par1;
  RooRealProxy par2;
  RooRealProxy par3;
  
  LimitType type_;

  double SM_integral;
  std::vector<double> integral_basis;
  std::vector<double> bins;

  TString profileFilename;
  
  TH3D ** P_par1par2par3_histo; //!
  TF3 ** P_par1par2par3_TF; //!
  
  void initializeProfiles();
  void initializeNormalization(const RooAbsReal& dep,
			       const RooAbsReal& shape);
  void readProfiles(RooACProcessScaling_3D const& other);
  
  virtual double evaluate() const ;
  
private:
  
  ClassDef(RooACProcessScaling_3D, 3) // aTGC function 
};

#endif
