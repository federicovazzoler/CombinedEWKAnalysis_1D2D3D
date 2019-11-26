#! /usr/bin/env python

import sys
import os
from array import array
from math import sqrt,exp
from optparse import OptionParser
from ConfigParser import SafeConfigParser
#root and roofit classes
import ROOT
from ROOT import RooWorkspace, TFile, TH1, TChain, RooDataHist, \
    RooHistFunc, RooFit, RooSimultaneous, RooDataSet, TH1F, \
    RooRealVar, RooBinning, RooThresholdCategory, RooCategory, \
    RooArgSet, RooArgList, TH2F, TH2D, TTree, TF2, TH1F, TH1D, TF1, TH3F, TH3D, TF3, RooFormulaVar, TCanvas, TProfile2D, TPaveText, TGraph

ROOT.gROOT.SetBatch(True)

# parser options
parser = OptionParser(description="%prog : A RooStats Implementation of Anomalous Triple Gauge Coupling Analysis.",
                      usage="buildWZworkspace --config=example_config.cfg")
cfgparse = SafeConfigParser()
parser.add_option("--config",dest="config",help="The name of the input configuration file")
parser.add_option("--output",dest="output",help="Path of the output file")
parser.add_option("--rangeDir",dest="rangeDir",help="Path of the range files")
(options,args) = parser.parse_args()

cfgparse.read(options.config)
options.config = cfgparse # put the parsed config file into our options
cfg = options.config
fit_sections = cfg.sections()
fit_sections.remove('Global') # don't need to iterate over the global configuration

pwd = ROOT.gDirectory.GetPath()

# initialize parammeters from global section
nGridPointsForNewF = int(cfg.get('Global','outputgridpoints'))
nGridPar1Bins = int(cfg.get('Global','nGridPar1Bins'))
model=cfg.get('Global','model')
if (model != "par1_TH1" and model != "par1_TF1"):
  print 'Change model'
  sys.exit()
func_string=''
cfg_items=cfg.items('Global')
for cfg_item in cfg_items:
  if 'function' in cfg_item:
    func_string=cfg.get('Global','function')

# other options
DEBUG = False

print 'starting ...'

for section in fit_sections:
  print '*** Section: ', section

  sigFile = cfg.get(section,'signal_model')
  coupling_name = os.path.basename(sigFile)
  pwd = ROOT.gDirectory.GetPath()
  sigFile = TFile.Open(sigFile)
  ROOT.gDirectory.cd(pwd)

  bins = [float(i) for i in cfg.get(section,'obsBins').split(',')]
  nObsBins = len(bins)-1

  if (DEBUG):
    print '- sigFile: ', sigFile
    print '- ngrid points: ',nGridPar1Bins
    print '- fitting func: ', func_string
    print '- model: ', model

  par1Name = cfg.get('Global','par1Name')
  nGridPar1Bins = cfg.getint('Global','nGridPar1Bins')
  par1GridMax = cfg.getfloat('Global','par1GridMax')
  par1GridMin = cfg.getfloat('Global','par1GridMin')

  outfile_newF = TFile.Open(options.output+'/signal_proc_'+section+'.root','RECREATE')

  if (DEBUG): print '---> cycling over bins'
  for i in range(1,len(bins)):
    if (DEBUG): print 'bin: ', i
    # get and book histos
    theBaseData = sigFile.Get('theBaseData_' + section + '_' + str(i))
    newFormatInput = TH1D('bin_content_par1_'+str(i),'bincontent',nGridPointsForNewF,par1GridMin,par1GridMax)

    # add dummy error bars
#    for j in range(1,nGridPar1Bins+2):
#      theBaseData.SetBinError(theBaseData.GetBin(j),0.0000001)
#      theBaseData.SetBinError(theBaseData.GetBin(j),0.)
#      if (i == 7): theBaseData.SetBinError(theBaseData.GetBin(j),10)

    # fit
    func = TF1('bin_content_par1_'+str(i),func_string,par1GridMin,par1GridMax)
    func.SetLineColor(2)

    func.SetParameters(1.0,1.0e10,0.2e22)
    if (coupling_name.split(".")[0] == "FM1"):
      if (i == 5): func.SetParameters(1.0,-1e7,0.0000015e22)
      if (i == 6): func.SetParameters(1.0,-3.1e7,0.000025e22)
      if (i == 7): func.SetParameters(1.0,1.0e7,0.0007e22)
#    if (coupling_name.split(".")[0] == "FM0"):
#      func.SetParameters(1.0,1.0e10,0.2e22)
#    elif (coupling_name.split(".")[0] == "FT0"):
#      func.SetParameters(1.0,1.0e10,0.2e22)

    func.FixParameter(0,1.)
    theBaseData.Fit(func,'R0','')

    c1 = TCanvas()
    c1.cd()
    theBaseData.SetMarkerStyle(3)
    theBaseData.Draw('AP')
    func.Draw('same')
    pt = TPaveText(0.6,0.2,0.8,0.4,"NDCNB");
    pt.AddText('p0 = ' + str(func.GetParameter(2)));
    pt.AddText('p1 = ' + str(func.GetParameter(1)));
    pt.AddText('p2 = ' + str(func.GetParameter(0)));
    pt.SetX1NDC(0.70);
    pt.SetX2NDC(0.90);
    pt.SetY1NDC(0.2);
    pt.SetY2NDC(0.6);
    pt.Draw('same');
#    c1.SaveAs('home/fvazzole/work/aTGC_tool/CMSSW_7_1_5/src/CombinedEWKAnalysis/CommonTools/data/anomalousCoupling_WGG/signal_proc_'+section+'bin_content_par1_'+str(i)+'.pdf')
#    c1.SaveAs('../data/anomalousCoupling_WGG/signal_proc_'+section+'_bin_content_par1_'+str(i)+'.pdf')

    # use fitted yield in SM or generated as SM_yield to scale all inputs!
    #SM_yield=func.Eval(0.) # use fitted yield
#    SM_yield=theBaseData.GetBinContent(theBaseData.FindBin(0.)) # use generated yield
#    if (DEBUG): print "SM yield: ", SM_yield

    print "---> checking newframe input:"

    if (model=="par1_TH1"):
      for bin_x in range(1,nGridPointsForNewF+1):
        #lowEdgeBinX = newFormatInput.GetXaxis().GetBinCenter(bin_x) - newFormatInput.GetXaxis().GetBinWidth(bin_x)/2.
        #newFormatInput.SetBinContent(bin_x, 0.)
        #if (bin_x <= 4):
        #  yield_bin = theBaseData.GetBinContent(theBaseData.FindBin(bin_x))
        #else:
        #yield_bin = func.Eval(lowEdgeBinX)
        par1_value=newFormatInput.GetXaxis().GetBinCenter(bin_x)
        yield_bin=func.Eval(par1_value)
        newFormatInput.SetBinContent(bin_x,yield_bin)

      if (DEBUG):
        print "before scaling: read SM yield: ", newFormatInput.GetBinContent(newFormatInput.FindBin(0.))
#        print "scaling with SM yield: ",SM_yield

#      newFormatInput.Scale(1./SM_yield)

      if (DEBUG):
        print "after scaling: read SM yield: ", newFormatInput.GetBinContent(newFormatInput.FindBin(0.))
        print 'model is TH -> write out TH object'

      newFormatInput.Write()
    elif (model=="par1_TF1"):
      if (DEBUG):
        print "before scaling: read SM yield: ", func.Eval(0.)
#        print " scaling with SM yield: ",SM_yield

      for i in range (0,func.GetNumberFreeParameters()):
        if (DEBUG):
          print "par ",i," -> ", func.GetParameter(i)

#        func.FixParameter(i,func.GetParameter(i)/SM_yield)

        if (DEBUG):
          print " ->par ",i," -> ", func.GetParameter(i)

      if (DEBUG):
        print "--->  after scaling: read SM yield: ", func.Eval(0.)
      func.Write()
  
  min_value_x = ROOT.Double(0.) 
  min_value_y = ROOT.Double(0.) 
  theBaseData.GetPoint(0,min_value_x,min_value_y)

  f = open(options.rangeDir+'/range_'+coupling_name.split("_")[0]+'.txt', 'w')
  print >> f, abs(min_value_x)
  f.close()

  outfile_newF.Close()
  sigFile.Close()
