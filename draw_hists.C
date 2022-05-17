TH1D* make_hist(TString filename = "data1"){

    gROOT->SetStyle("ATLAS");
    const int MCACh = 80;
    const double HistMin = 0.;
    const double HistMax = 800.;

    TH1D* hist = new TH1D(filename,filename,MCACh,HistMin-0.5,HistMax-0.5);

    const TString data_dir = "beta_ray/output/";
    double BufferValue;
    ifstream ifs(data_dir + filename + ".txt");
    if(filename == "20220427_area"){
        while(ifs >> BufferValue){
            hist->Fill(BufferValue*2.);
        }
    }
    else{
        while(ifs >> BufferValue){
            hist->Fill(BufferValue*0.02);
        }
    }


    hist->Rebin(1);
    hist->SetTitle(";Area[pCoulomb];Counts(Normalized)");
    hist->GetYaxis()->SetRange(0, 0.03);
    return hist;

}

int draw_hists(){

    TH1D* hist1 = make_hist("20220505_area");
    TH1D* hist2 = make_hist("20220506_area");
    TH1D* hist3 = make_hist("202204281456_area");
    TH1D* hist4 = make_hist("20220427_area");


    hist1->Add(hist2);
    hist1->Add(hist3);
    hist1->SetLineColor(kRed);
    hist1->DrawNormalized();
    hist4->SetLineColor(kBlue);
    hist4->DrawNormalized("same");
    //hist2->Draw("same");
    //hist3->Draw("same");




    double x = 0.5;
    double y = 0;
    auto legend = new TLegend(0.1+x,0.7+y,0.4+x,0.9+y);
   legend->SetHeader("Beta Ray","C"); // option "C" allows to center the header
   legend->AddEntry(hist1,"45^{#circ}","l"); // (address,"comment","mode f=box or l=line or p=marker ")
   legend->AddEntry(hist4,"0^{#circ}","l");
   legend->Draw();

   

    return 0;
}