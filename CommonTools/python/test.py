import ROOT
import os
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('--input', '-i', help='input root file')
args = parser.parse_args()

f_simple = ROOT.TFile(args.input,"READ")
w_simple = f_simple.Get("proc_ch_ele")
w_simple.Print()
