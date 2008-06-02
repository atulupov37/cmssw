import FWCore.ParameterSet.Config as cms

l1tltc = cms.EDFilter("L1TLTC",
    disableROOToutput = cms.untracked.bool(True),
    verbose = cms.untracked.bool(False),
    DQMStore = cms.untracked.bool(True)
)


