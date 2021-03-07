#include <bitset>
#include <vector>
#include "AtlasUtils.C"
#include "AtlasLabels.C"
#include "AtlasStyle.C"
void privet(const char *fname = "zadacha.root", const char *fOutName = "moyaZadacha.root") {

    SetAtlasStyle();

    TFile *file = new TFile(fname, "READ");

    const char *treeName = "output"; // tree from previous tree
    const int nBins = 100;
    const float binLo = 0.0;
    const float binHi = 50.0;

    TFile *fOut = new TFile(fOutName, "RECREATE");
    TTree *tree = new TTree("tree", "Moi_Dannye");

    TTree *old_tree = (TTree*)file->Get("output"); // connect previous tree


    //initialization TLorentzVector
    TLorentzVector I1(0., 0., 0., 0.);
    TLorentzVector I2(0., 0., 0., 0.);
    TLorentzVector ph(0., 0., 0., 0.);



    Float_t ph_E=0;
    Float_t ph_pt=0;
    Float_t ph_eta=0;
    Float_t ph_phi=0;
    Float_t I1_E=0;
    Float_t I1_pt=0;
    Float_t I1_eta=0;
    Float_t I1_phi=0;
    Float_t I2_E=0;
    Float_t I2_pt=0;
    Float_t I2_eta=0;
    Float_t I2_phi=0;
    Float_t Mass_ph = 0;
    Float_t mass = 0;
    Float_t ll_m =0;
    Float_t ll_g =0;


    //create branches
    tree->Branch("ph_E", &ph_E, "ph_E/F");
    tree->Branch("ph_pt", &ph_pt, "ph_pt/F");
    tree->Branch("ph_eta", &ph_eta, "ph_eta/F");
    tree->Branch("ph_phi", &ph_phi, "ph_phi/F");
    tree->Branch("I1_E", &I1_E, "I1_E/F");
    tree->Branch("I1_pt", &I1_pt, "I1_pt/F");
    tree->Branch("I1_eta", &I1_eta, "I1_eta/F");
    tree->Branch("I1_phi", &I1_phi, "I1_phi/F");
    tree->Branch("I2_E", &I2_E, "I2_E/F");
    tree->Branch("I2_pt", &I2_pt, "I2_pt/F");
    tree->Branch("I2_eta", &I2_eta, "I2_eta/F");
    tree->Branch("I2_phi", &I2_phi, "I2_phi/F");
    tree->Branch("Mass_ph", &Mass_ph, "Mass_ph/F");
    tree->Branch("mass", &mass, "mass/F");
    tree->Branch("ll_m", &ll_m, "ll_m/F");
    tree->Branch("ll_g", &ll_g, "ll_g/F");


    Float_t old_ph_E=0;
    Float_t old_ph_pt=0;
    Float_t old_ph_eta=0;
    Float_t old_ph_phi=0;
    Float_t old_I1_E=0;
    Float_t old_I1_pt=0;
    Float_t old_I1_eta=0;
    Float_t old_I1_phi=0;
    Float_t old_I2_E=0;
    Float_t old_I2_pt=0;
    Float_t old_I2_eta=0;
    Float_t old_I2_phi=0;
    Float_t old_ll_m=0;
    Float_t old_ll_g=0;



    //connect branches from file this my new file
    old_tree->SetBranchAddress("ph.E", &old_ph_E);
    old_tree->SetBranchAddress("ph.pt", &old_ph_pt);
    old_tree->SetBranchAddress("ph.eta", &old_ph_eta);
    old_tree->SetBranchAddress("ph.phi", &old_ph_phi);
    old_tree->SetBranchAddress("l1.E", &old_I1_E);
    old_tree->SetBranchAddress("l1.pt", &old_I1_pt);
    old_tree->SetBranchAddress("l1.eta", &old_I1_eta);
    old_tree->SetBranchAddress("l1.phi", &old_I1_phi);
    old_tree->SetBranchAddress("l2.E", &old_I2_E);
    old_tree->SetBranchAddress("l2.pt", &old_I2_pt);
    old_tree->SetBranchAddress("l2.eta", &old_I2_eta);
    old_tree->SetBranchAddress("l2.phi", &old_I2_phi);
    old_tree->SetBranchAddress("ll.m", &old_ll_m);
    old_tree->SetBranchAddress("llg.m", &old_ll_g);


    unsigned int nEntries = old_tree->GetEntries(); // we will entry in each value in old tree


    //create the loop
    for (unsigned int i = 0; i < nEntries; i++) {
    old_tree->GetEntry(i);
    ph_E = old_ph_E;
    ph_pt = old_ph_pt;
    ph_eta = old_ph_eta;
    ph_phi = old_ph_phi;
    I1_E = old_I1_E;
    I1_pt = old_I1_pt;
    I1_eta = old_I1_eta;
    I1_phi = old_I1_phi;
    I2_E = old_I2_E;
    I2_pt = old_I2_pt;
    I2_eta = old_I2_eta;
    I2_phi = old_I2_phi;
    ll_m = old_ll_m;
    ll_g = old_ll_g;


    //m = sqrtf(2*(((I1_pt)*(I2_pt))*(cosh(I1_eta - I2_eta)- cos(I1_phi - I2_phi))));

    //fill components TLorentzVector
    I1[0] = I1_E;
    I1[1] = (I1_pt)*sin(I1_phi);
    I1[2] = (I1_pt)*cos(I1_phi);
    I1[3] = ((I1_pt)*cos(I1_phi)/(sin(I1_phi)));

    I2[0] = I2_E;
    I2[1] = (I2_pt)*sin(I2_phi);
    I2[2] = (I2_pt)*cos(I2_phi);
    I2[3] = ((I2_pt)*cos(I2_phi)/(sin(I2_phi)));

    ph[0] = I2_E;
    ph[1] = (I2_pt)*sin(I2_phi);
    ph[2] = (I2_pt)*cos(I2_phi);
    ph[3] = ((I2_pt)*cos(I2_phi)/(sin(I2_phi)));



    I1.SetPtEtaPhiM(I1_pt, I1_eta, I1_phi, 105.658367);
    I2.SetPtEtaPhiM(I2_pt, I2_eta, I2_phi, 105.658367);
    ph.SetPtEtaPhiM(ph_pt, ph_eta, ph_phi, 0);

    //count the invariant mass
    Mass_ph = (I1 + I2 + ph).M();
    mass = (I1 + I2).M();

    tree->Fill();
    }



    TH1F *h1 = new TH1F("Muons","Z(ll)",100,30000,120000);
    TH1F *h2 = new TH1F("Muons_ph", "Z(ll)_{#gamma}", 100, 40000, 140000);
    TH1F *h3 = new TH1F("InvMuons", "Z(ll)",100,30000,120000);
    TH1F *h4 = new TH1F("InvMuonsPh", "Z(ll)_{#gamma}", 100, 40000, 140000);


    for (unsigned int m = 0; m < nEntries; m++) {
    tree->GetEntry(m);
    h1->Fill(mass);
    h2->Fill(Mass_ph);
    h3->Fill(ll_m);
    h4->Fill(ll_g);
    }


    TCanvas *c1 = new TCanvas ("c1", "canvas_new", 0.,0.,600,600);
    TCanvas *c2 = new TCanvas ("c2", "canvas_new", 0.,0.,600,600);

    h2->GetXaxis()->SetTitle("M_{ll#gamma} [GeV]");
    h2->GetYaxis()->SetTitle("Events");

    h2->SetLineColor(2);
    h1->SetLineColor(31);
    h1->SetMarkerStyle(43);
    h1->SetFillColor(31);
    h2->SetFillColor(kRed-4);
    h2->SetLineStyle(kMagenta+2);
    h4->SetMarkerSize(2);
    h4->SetMarkerColor(1);
    h4->SetMarkerStyle(43);
    h3->SetMarkerStyle(43);
    h3->SetMarkerSize(2);

    h1->GetXaxis()->SetTitle("M_{ll} [GeV]");
    h1->GetYaxis()->SetTitle("Events");

    c1->cd();
    h2->Draw();
    h4->Draw("P same");


    TLegend *lsc= new TLegend(0.1,0.7,0.48,0.9);
    lsc->SetHeader("Z boson invariant mass","C");
    lsc->AddEntry(h2,"Z^{0}->#mu^{+}#mu^{-}#gamma (calcul.)","f");
    lsc->AddEntry(h4,"Z^{0}->#mu^{+}#mu^{-}#gamma (theor.)", "p");
    lsc->Draw();


    c2->cd();
    h1->Draw();
    h3->Draw("P same");

    TLegend *lsc2= new TLegend(0.1,0.7,0.48,0.9);
    lsc2->SetHeader("Z boson invariant mass","C"); // option "C" allows to center the header
    lsc2->AddEntry(h1,"Z^{0}->#mu^{+}#mu^{-} (calcul.)","f");
    lsc2->AddEntry(h3,"Z^{0}->#mu^{+}#mu^{-} (theor.)", "p");
    lsc2->Draw();

    fOut->cd();
    tree->Write();
    h1->Write();
    h2->Write();
    //fOut->Close();
    //file->Close();


}
