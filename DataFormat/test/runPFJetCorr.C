#include <vector>

void runPFJetCorr()
{
  gSystem->Load("../../../../lib/slc5_amd64_gcc462/libHcalClosureTestDataFormat.so");
  gROOT->ProcessLine(".L loader.C+");
  

  TChain* tree = new TChain("pf_dijettree");
  //TString input = "/uscms_data/d3/dgsheffi/HCal/test.root";
  //TString input = "/uscms_data/d3/dgsheffi/HCal/Trees/Pion_Pt-50_noHF.root";
  TString input = "/uscms_data/d3/dgsheffi/HCal/Trees/QCD_Pt-15to3000_0030487D5E5F.root";
  tree->Add(input);

  //TString output = "/uscms_data/d3/dgsheffi/HCal/pfJetCorr.root";
  //TString output = "/uscms_data/d3/dgsheffi/HCal/pfJetCorr_noHF_freeHF.root";
  TString output = "/uscms_data/d3/dgsheffi/HCal/pfJetCorr_test.root";

  DijetRespCorrData data;

  const int MAXIETA = 41;
  const int NUMTOWERS = 83;

  float tjet_eta_, tjet_phi_;
  float tjet_unkown_E_, tjet_electron_E_, tjet_muon_E_, tjet_photon_E_;
  int tjet_had_n_;
  vector<float>* tjet_had_EcalE_;
  vector<float>* tjet_had_id_;
  int tjet_ntwrs_;
  vector<int>* tjet_twr_ieta_;
  vector<int>* tjet_twr_candtrackind_;
  vector<float>* tjet_twr_hade_;
  vector<float>* tjet_twr_frac_;
  int tjet_ncandtracks_;
  vector<float>* tjet_candtrack_px_;
  vector<float>* tjet_candtrack_py_;
  vector<float>* tjet_candtrack_pz_;
  vector<float>* tjet_candtrack_EcalE_;
  float pjet_eta_, pjet_phi_;
  float pjet_unkown_E_, pjet_electron_E_, pjet_muon_E_, pjet_photon_E_;
  int pjet_had_n_;
  vector<float>* pjet_had_EcalE_;
  vector<float>* pjet_had_id_;
  int pjet_ntwrs_;
  vector<int>* pjet_twr_ieta_;
  vector<int>* pjet_twr_candtrackind_;
  vector<float>* pjet_twr_hade_;
  vector<float>* pjet_twr_frac_;
  int pjet_ncandtracks_;
  vector<float>* pjet_candtrack_px_;
  vector<float>* pjet_candtrack_py_;
  vector<float>* pjet_candtrack_pz_;
  vector<float>* pjet_candtrack_EcalE_;
  float thirdjet_px_, thirdjet_py_;

  tree->SetBranchAddress("tpfjet_eta",&tjet_eta_);
  tree->SetBranchAddress("tpfjet_phi",&tjet_phi_);
  tree->SetBranchAddress("tpfjet_unkown_E",&tjet_unkown_E_);
  tree->SetBranchAddress("tpfjet_electron_E",&tjet_electron_E_);
  tree->SetBranchAddress("tpfjet_muon_E",&tjet_muon_E_);
  tree->SetBranchAddress("tpfjet_photon_E",&tjet_photon_E_);
  tree->SetBranchAddress("tpfjet_had_n",&tjet_had_n_);
  tree->SetBranchAddress("tpfjet_had_EcalE",&tjet_had_EcalE_);
  tree->SetBranchAddress("tpfjet_had_id",&tjet_had_id_);
  tree->SetBranchAddress("tpfjet_ntwrs",&tjet_ntwrs_);
  tree->SetBranchAddress("tpfjet_twr_ieta",&tjet_twr_ieta_);
  tree->SetBranchAddress("tpfjet_twr_hade",&tjet_twr_hade_);
  tree->SetBranchAddress("tpfjet_twr_frac",&tjet_twr_frac_);
  tree->SetBranchAddress("tpfjet_twr_candtrackind",&tjet_twr_candtrackind_);
  tree->SetBranchAddress("tpfjet_ncandtracks",&tjet_ncandtracks_);
  tree->SetBranchAddress("tpfjet_candtrack_px",&tjet_candtrack_px_);
  tree->SetBranchAddress("tpfjet_candtrack_py",&tjet_candtrack_py_);
  tree->SetBranchAddress("tpfjet_candtrack_pz",&tjet_candtrack_pz_);
  tree->SetBranchAddress("tpfjet_candtrack_EcalE",&tjet_candtrack_EcalE_);
  tree->SetBranchAddress("ppfjet_eta",&pjet_eta_);
  tree->SetBranchAddress("ppfjet_phi",&pjet_phi_);
  tree->SetBranchAddress("ppfjet_unkown_E",&pjet_unkown_E_);
  tree->SetBranchAddress("ppfjet_electron_E",&pjet_electron_E_);
  tree->SetBranchAddress("ppfjet_muon_E",&pjet_muon_E_);
  tree->SetBranchAddress("ppfjet_photon_E",&pjet_photon_E_);
  tree->SetBranchAddress("ppfjet_had_n",&pjet_had_n_);
  tree->SetBranchAddress("ppfjet_had_EcalE",&pjet_had_EcalE_);
  tree->SetBranchAddress("ppfjet_had_id",&pjet_had_id_);
  tree->SetBranchAddress("ppfjet_ntwrs",&pjet_ntwrs_);
  tree->SetBranchAddress("ppfjet_twr_ieta",&pjet_twr_ieta_);
  tree->SetBranchAddress("ppfjet_twr_hade",&pjet_twr_hade_);
  tree->SetBranchAddress("ppfjet_twr_frac",&pjet_twr_frac_);
  tree->SetBranchAddress("ppfjet_twr_candtrackind",&pjet_twr_candtrackind_);
  tree->SetBranchAddress("ppfjet_ncandtracks",&pjet_ncandtracks_);
  tree->SetBranchAddress("ppfjet_candtrack_px",&pjet_candtrack_px_);
  tree->SetBranchAddress("ppfjet_candtrack_py",&pjet_candtrack_py_);
  tree->SetBranchAddress("ppfjet_candtrack_pz",&pjet_candtrack_pz_);
  tree->SetBranchAddress("ppfjet_candtrack_EcalE",&pjet_candtrack_EcalE_);
  tree->SetBranchAddress("pf_thirdjet_px",&thirdjet_px_);
  tree->SetBranchAddress("pf_thirdjet_py",&thirdjet_py_);

  int fails = 0;

  int nEvents = tree->GetEntries();
  nEvents = 5;
  cout << "Running over " << nEvents << " events" << endl;
  for(int iEvent=0; iEvent<nEvents; iEvent++){
    if(iEvent % 1000 == 0){
      cout << "Processing event " << iEvent << endl;
    }
    tree->GetEntry(iEvent);

    if(tjet_ntwrs_ == 0 || pjet_ntwrs_ == 0){
      fails++;
      //cout << "Fails: " << iEvent << " " << tjet_ntwrs_ << " " << pjet_ntwrs_ << endl;
      continue;
    }

    DijetRespCorrDatum datum;
    
    // Fill datum

    float sumt = 0;
    datum.SetTagEta(tjet_eta_);
    datum.SetTagPhi(tjet_phi_);
    for(int i=0; i<tjet_ntwrs_; i++){
      if(tjet_twr_hade_->at(i) > 0.0){
	datum.AddTagHcalE(tjet_twr_hade_->at(i)*tjet_twr_frac_->at(i),tjet_twr_ieta_->at(i));
	sumt += tjet_twr_hade_->at(i)*tjet_twr_frac_->at(i);
      }
    }
    datum.SetCandTrackN(tjet_ncandtracks_);
    for(int i=0; i<tjet_ncandtracks_; i++){
      datum.AddCandTrackP(sqrt(tjet_candtrack_px_->at(i)*tjet_candtrack_px_->at(i) + tjet_candtrack_py_->at(i)*tjet_candtrack_py_->at(i) + tjet_candtrack_pz_->at(i)*tjet_candtrack_pz_->at(i)));
      datum.AddCandTrackEcalE(tjet_candtrack_EcalE_->at(i));
      map<Int_t, Double_t> clusterEnergies;
      for(int j=0; j<tjet_ntwrs_; j++){
	if(tjet_twr_candtrackind_->at(j) == i){
	  if(tjet_twr_hade_->at(j) > 0.0){
	    assert(tjet_twr_ieta_->at(j)<=41 && tjet_twr_ieta_->at(j)>=-41 && tjet_twr_ieta_->at(j)!=0);
	    //clusterEnergies[tjet_twr_ieta_[j]] = tjet_twr_hade_[j];
	    clusterEnergies[tjet_twr_ieta_->at(j)] = tjet_twr_hade_->at(j)*tjet_twr_frac_->at(j);
	  }
	}
      }
      datum.AddCandTrackHcalE(clusterEnergies);
    }
    float tjet_had_EcalE_total = 0;
    for(int iHad=0; iHad<tjet_had_n_; iHad++){
      if(tjet_had_id_->at(iHad) < 2) tjet_had_EcalE_total += tjet_had_EcalE_->at(iHad);
    }
    datum.SetTagEcalE(tjet_unkown_E_ + tjet_electron_E_ + tjet_muon_E_ + tjet_photon_E_ + tjet_had_EcalE_total);

    float sump = 0;
    datum.SetProbeEta(pjet_eta_);
    datum.SetProbePhi(pjet_phi_);
    for(int i=0; i<pjet_ntwrs_; i++){
      if(pjet_twr_hade_->at(i) > 0.0){
	datum.AddProbeHcalE(pjet_twr_hade_->at(i)*pjet_twr_frac_->at(i),pjet_twr_ieta_->at(i));
	sump += pjet_twr_hade_->at(i)*pjet_twr_frac_->at(i);
      }
    }
    datum.SetCandTrackN(pjet_ncandtracks_);
    for(int i=0; i<pjet_ncandtracks_; i++){
      datum.AddCandTrackP(sqrt(pjet_candtrack_px_->at(i)*pjet_candtrack_px_->at(i) + pjet_candtrack_py_->at(i)*pjet_candtrack_py_->at(i) + pjet_candtrack_pz_->at(i)*pjet_candtrack_pz_->at(i)));
      datum.AddCandTrackEcalE(pjet_candtrack_EcalE_->at(i));
      map<Int_t, Double_t> clusterEnergies;
      for(int j=0; j<pjet_ntwrs_; j++){
	if(pjet_twr_candtrackind_->at(j) == i){
	  if(pjet_twr_hade_->at(j) > 0.0){
	    assert(pjet_twr_ieta_->at(j)<=41 && pjet_twr_ieta_->at(j)>=-41 && pjet_twr_ieta_->at(j)!=0);
	    //clusterEnergies[tjet_twr_ieta_->at(j)] = tjet_twr_hade_->at(j);
	    clusterEnergies[pjet_twr_ieta_->at(j)] = pjet_twr_hade_->at(j)*pjet_twr_frac_->at(j);
	  }
	}
      }
      datum.AddCandTrackHcalE(clusterEnergies);
    }
    float pjet_had_EcalE_total = 0;
    for(int iHad=0; iHad<pjet_had_n_; iHad++){
      if(pjet_had_id_->at(iHad) < 2) pjet_had_EcalE_total += pjet_had_EcalE_->at(iHad);
    }
    datum.SetProbeEcalE(pjet_unkown_E_ + pjet_electron_E_ + pjet_muon_E_ + pjet_photon_E_ + pjet_had_EcalE_total);

    datum.SetThirdJetPx(thirdjet_px_);
    datum.SetThirdJetPy(thirdjet_py_);

    if(sumt == 0 || sump == 0){
      fails++;
      continue;
    }
    

    data.push_back(datum);
  }

  cout << data.GetSize() << " data" << endl;
  
  cout << "Passes: " << nEvents - fails << " Fails: " << fails << endl;
  cout << "Do CandTrack? " << data.GetDoCandTrackEnergyDiff() << endl;
  data.SetDoCandTrackEnergyDiff(true);
  cout << "Do CandTrack? " << data.GetDoCandTrackEnergyDiff() << endl;
  
  TH1D* hist = data.doFit("hcorr","Response Corrections");
  hist->GetXaxis()->SetTitle("ieta");
  hist->GetYaxis()->SetTitle("response corrections");

  TFile* fout = new TFile(output,"RECREATE");
  fout->cd();
  hist->Write();
  fout->Close();

  cout << "Passes: " << nEvents - fails << " Fails: " << fails << endl;

  return;
}
