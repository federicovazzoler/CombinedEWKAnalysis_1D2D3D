from CombinedEWKAnalysis.CommonTools.AnomalousCouplingModel import *
import ROOT as r
import os

basepath = '%s/src/CombinedEWKAnalysis/CommonTools/data/anomalousCoupling'%os.environ['CMSSW_BASE']

#this model is in the equal couplings scenario of HISZ or something similar
#it does the old style limits of setting the other parameter to zero
class ACModel1D(AnomalousCouplingModel):
    def __init__(self,mode):
        AnomalousCouplingModel.__init__(self)
        self.processes = ['anoCoupl']
        self.channels  = ['process']
        self.lepchannels  = ['ch1','ch2','ch3','ch4','ch5','ch6']
        self.pois      =  ['par1']
        self.mode      = mode
        self.anomCoupSearchWindows = {'par1':['-1.','1.'] }
        
        self.verbose = False

    def buildScaling(self,process,channel,lepchannel):        
        scalerName = '%s_%s_%s'%(process,channel,lepchannel)

        print 'reading %s/signal_proc_%s.root for %s'%(basepath,lepchannel,lepchannel)
        filename = '%s/signal_proc_%s.root'%(basepath,lepchannel)
        f = r.TFile('%s/%s.root'%(basepath,lepchannel),'READ')
        SM_diboson_shape = f.Get('diboson').Clone('SM_aC_%s_shape_for_scale'%lepchannel)
        SM_diboson_shape.SetDirectory(0)
        f.Close()
        self.modelBuilder.out._import(SM_diboson_shape)
        SM_diboson_shape_dhist = r.RooDataHist('DHIST_SM_aC_%s_shape_for_scale'%lepchannel,
                    'DHIST_SM_aC_%s_shape_for_scale'%lepchannel,
                    r.RooArgList(self.modelBuilder.out.var('observable_%s'%lepchannel)),
                    self.modelBuilder.out.obj('SM_aC_%s_shape_for_scale'%lepchannel))
        self.modelBuilder.out._import(SM_diboson_shape_dhist)        
        self.modelBuilder.factory_('RooHistFunc::Scaling_base_pdf_%s({observable_%s},DHIST_SM_aC_%s_shape_for_scale)'%(scalerName,lepchannel,lepchannel))              

        if ( self.mode == 'par1_TH1' or self.mode == 'par1_TF1'):
            self.modelBuilder.factory_('RooACProcessScaling_1D::Scaling_%s(observable_%s,%s,Scaling_base_pdf_%s,"%s",%s)'%(scalerName,lepchannel,self.pois[0],scalerName,filename,self.mode))
        else:
            raise RuntimeError('InvalidCouplingChoice','We can only use 1D (par1_TH1, par1_TF1)  2D (par1par2_TF2par, par1par2_TH2, par1par2_TF2) or 3D (par1par2par3_TH3, par1par2par3_TF3, EFTtoATGC) models right now!')        

        return scalerName

class ACModel2D(AnomalousCouplingModel):
    def __init__(self,mode):
        AnomalousCouplingModel.__init__(self)
        self.processes = ['anoCoupl']
        self.channels  = ['process']
        self.lepchannels  = ['ch1','ch2','ch3','ch4','ch5','ch6']
        self.pois      =  ['par1','par2']
        self.mode      = mode
        self.anomCoupSearchWindows = {'par1':['-1.','1.'],
                                      'par2':['-1.','1.']  }
        
        self.verbose = False

    def buildScaling(self,process,channel,lepchannel):        
        scalerName = '%s_%s_%s'%(process,channel,lepchannel)

        print 'reading %s/signal_proc_%s.root for %s'%(basepath,lepchannel,lepchannel)
        filename = '%s/signal_proc_%s.root'%(basepath,lepchannel)
        f = r.TFile('%s/%s.root'%(basepath,lepchannel),'READ')
        SM_diboson_shape = f.Get('diboson').Clone('SM_aC_%s_shape_for_scale'%lepchannel)
        SM_diboson_shape.SetDirectory(0)
        f.Close()
        self.modelBuilder.out._import(SM_diboson_shape)
        SM_diboson_shape_dhist = r.RooDataHist('DHIST_SM_aC_%s_shape_for_scale'%lepchannel,
                    'DHIST_SM_aC_%s_shape_for_scale'%lepchannel,
                    r.RooArgList(self.modelBuilder.out.var('observable_%s'%lepchannel)),
                    self.modelBuilder.out.obj('SM_aC_%s_shape_for_scale'%lepchannel))
        self.modelBuilder.out._import(SM_diboson_shape_dhist)        
        self.modelBuilder.factory_('RooHistFunc::Scaling_base_pdf_%s({observable_%s},DHIST_SM_aC_%s_shape_for_scale)'%(scalerName,lepchannel,lepchannel))              

        if ( self.mode == 'par1par2_TF2par' or self.mode == 'par1par2_TH2' or self.mode == 'par1par2_TF2'):
            self.modelBuilder.factory_('RooACProcessScaling_2D::Scaling_%s(observable_%s,%s,%s,Scaling_base_pdf_%s,"%s",%s)'%(scalerName,lepchannel,self.pois[0], self.pois[1],scalerName,filename,self.mode))
        else:
            raise RuntimeError('InvalidCouplingChoice','We can only use 1D (par1_TH1, par1_TF1)  2D (par1par2_TF2par, par1par2_TH2, par1par2_TF2) or 3D (par1par2par3_TH3, par1par2par3_TF3, EFTtoATGC) models right now!')        

        return scalerName


class ACModel3D(AnomalousCouplingModel):
    def __init__(self,mode):
        AnomalousCouplingModel.__init__(self)
        self.processes = ['anoCoupl']
        self.channels  = ['process']
        self.lepchannels  = ['ch1','ch2','ch3','ch4','ch5','ch6']
        self.pois      =  ['par1','par2','par3']
        self.mode      = mode
        self.anomCoupSearchWindows = {'par1':['-1.','1.'],
                                      'par2':['-1.','1.'],
                                      'par3' :['-1.','1.'] }
        
        self.verbose = False

    def buildScaling(self,process,channel,lepchannel):        
        scalerName = '%s_%s_%s'%(process,channel,lepchannel)

        print 'reading %s/signal_proc_%s.root for %s'%(basepath,lepchannel,lepchannel)
        filename = '%s/signal_proc_%s.root'%(basepath,lepchannel)
        f = r.TFile('%s/%s.root'%(basepath,lepchannel),'READ')
        SM_diboson_shape = f.Get('diboson').Clone('SM_aC_%s_shape_for_scale'%lepchannel)
        SM_diboson_shape.SetDirectory(0)
        f.Close()
        self.modelBuilder.out._import(SM_diboson_shape)
        SM_diboson_shape_dhist = r.RooDataHist('DHIST_SM_aC_%s_shape_for_scale'%lepchannel,
                    'DHIST_SM_aC_%s_shape_for_scale'%lepchannel,
                    r.RooArgList(self.modelBuilder.out.var('observable_%s'%lepchannel)),
                    self.modelBuilder.out.obj('SM_aC_%s_shape_for_scale'%lepchannel))
        self.modelBuilder.out._import(SM_diboson_shape_dhist)        
        self.modelBuilder.factory_('RooHistFunc::Scaling_base_pdf_%s({observable_%s},DHIST_SM_aC_%s_shape_for_scale)'%(scalerName,lepchannel,lepchannel))              

        if ( self.mode == 'par1par2par3_TH3' or self.mode == 'par1par2par3_TF3' or self.mode == 'EFTtoATGC'):
            self.modelBuilder.factory_('RooACProcessScaling_3D::Scaling_%s(observable_%s,%s,%s,%s,Scaling_base_pdf_%s,"%s",%s)'%(scalerName,lepchannel,self.pois[0], self.pois[1], self.pois[2],scalerName,filename,self.mode))
        else:
            raise RuntimeError('InvalidCouplingChoice','We can only use 1D (par1_TH1, par1_TF1)  2D (par1par2_TF2par, par1par2_TH2, par1par2_TF2) or 3D (par1par2par3_TH3, par1par2par3_TF3, EFTtoATGC) models right now!')        
       
        return scalerName
       

par1_TH1_Model = ACModel1D('par1_TH1')
par1_TF1_Model = ACModel1D('par1_TF1')
par1par2_TF2par_Model = ACModel2D('par1par2_TF2par')
par1par2_TH2_Model = ACModel2D('par1par2_TH2')
par1par2_TF2_Model = ACModel2D('par1par2_TF2')
par1par2par3_TH3_Model = ACModel3D('par1par2par3_TH3')
par1par2par3_TF3_Model = ACModel3D('par1par2par3_TF3')
EFTtoATGC_Model = ACModel3D('EFTtoATGC')
