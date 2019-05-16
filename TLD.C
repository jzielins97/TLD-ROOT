#include "TLD.h"

void TLD(int SavePng = 1, int anilacja = 1){ //SavePng = 0 (nie zapisuje), 1 (zapisuje); anilacja = 0 (brak analizy anilacji), 1 (z analizą anilacji)
  gStyle->SetPadLeftMargin(0.15); //ustawienie marginesu w TCanvas = przesuniecie wykresu w prow na Tcanvas

  const char *infile[] = {"dane_root_pomiar0.txt",  //plik z danymi anilacji
                        "dane_root_pomiar1.txt",
                        "dane_root_pomiar2.txt"};

  //Liczba wygrzanych kasetek w pliku
  const int nKaset[] =  {15,
                        5,
                        11};

  //Numer kasetki w kolejnosci występowania w pliku pomiar1 + pomiar2
  const int nrKasety[] = {20577, 20580, 18237, 20441, 20478, 20578, 20444, 20551,  //20578 = 2 pomiar dla 20577
                            10582, 20465, 7809, 20461, 646, 2750, 20589, 9200};

  //Numer kasetki w kolejnosci występowania w pliku pomiar0
  const int nrAnilacji[] = {20478, 646, 20441, 7809, 2750, 20580, 18237, 20577,  //20578 = 2 pomiar dla 20577
                               20589, 20461, 9200, 20582, 20465, 20551, 20444}; //20443 = 1 anilacja 2044 ()

  //ilosc przedzialow czasowych w pliku
  const int n0 = 300; //anilacja
  const int n1 = 200; //pomiar1 i pomiar2

  const int nZero[] = {3360, 3620, 2736, 3616};
  const int nTlo[] = {36820, 36388, 36916, 39856};

  int w =800; //szerokosc TCanvas
  int h =700; //wysokosc TCanvas
  double yTitleOffset = 1.7;  //Wartosc przesuniecia tytułu osi y aby nie nachodziło na numeracje osi


  int pomiar;
  if( anilacja == 1 ){
    pomiar = 0;
  }else{
    pomiar = 1;
  }

  for(pomiar; pomiar<3; pomiar++){
    ifstream ifile;
  	ifile.open(infile[pomiar]);

    if( pomiar == 0 ){
      //cout<<"anilacja"<<endl;
      for(int ii=0; ii<nKaset[pomiar]; ii++){
        TCanvas *c = new TCanvas(Form("Anilacja%d", nrAnilacji[ii]),
                                 Form("Pomiar kasety nr %d", nrAnilacji[ii]),
                                 w,
                                 h);
        TLegend *legend = new TLegend(0.73,0.9,0.9,0.75); //ustawienie legendy w prawym górnym rogu
        for(int ij=0; ij<4; ij++){  //dla każdej kasety trzeby zrobić 4 pastylki
          //TH1D *pastylka = new TH1D(Form("anilacja%d%d", &ii, &ij), "Anilacja", nBins0, 0, 3000);
          TGraph *pastylka = new TGraph(n0);
          int max=0;
          for(int ik=0; ik<n0; ik++){
            int val;
            ifile>>val;
            pastylka->SetPoint(ik, ik*10, val);
          }
          pastylka->SetLineColor(ij+1);
          pastylka->SetTitle(Form("kaseta nr %d", nrAnilacji[ii]));
          pastylka->GetXaxis()->SetTitle("Czas [ms]");
          pastylka->GetYaxis()->SetTitle("Liczba zliczen");
          pastylka->GetYaxis()->SetTitleOffset(yTitleOffset); //przesunięcie tytułu osi y aby nie nachodził na numeracje
          legend->AddEntry(pastylka,Form("Pastylka nr %d", ij+1),"l"); //dodanie kolejnego opisu patylki do legendy
          //cout<<"max="<<max<<"  "<<"GetMaximum = "<<pastylka->GetHistogram()->GetMaximum()<<endl;
          if(max < pastylka->GetHistogram()->GetMaximum()){ //sprawdzanie czy wykresy nie wychodzą poza narysowane osie
            max = pastylka->GetHistogram()->GetMaximum();
            pastylka->GetYaxis()->SetRangeUser(0, 1.1*max); //przedłużenie osi (reskalowanie wykresów)
          }
          if(ij == 0) pastylka->Draw("AL");
          else pastylka->Draw("L same");
        }
        legend->Draw();
        if(SavePng) c->SaveAs(Form("Anilacja%d.png", nrAnilacji[ ii ])); //zapisywanie do pliku
      }
    }else{
      //cout<<endl<<"pomiar"<<endl;
        for(int ii=0; ii<nKaset[pomiar]; ii++){
          TCanvas *c = new TCanvas(Form("Pomiar%d", nrKasety[(pomiar-1)*nKaset[pomiar-1]+ii]),
                                   Form("Pomiar kasety nr %d", nrKasety[(pomiar-1)*nKaset[pomiar-1]+ii]),
                                   w,
                                   h);
          TLegend *legend = new TLegend(0.73,0.9,0.9,0.75); //ustawienie legendy w prawym górnym rogu
          TGraph *pastylka1 = new TGraph(n1);
          for(int ij=0; ij<4; ij++){ //dla każdej kasety trzeby zrobić 4 pastylki
            //TH1D *pastylka = new TH1D(Form("anilacja%d%d", &ii, &ij), "Anilacja", nBins0, 0, 3000);
            TGraph *pastylka = new TGraph(n1);
            int max=0;
            int suma = 0;
            for(int ik=0; ik<n1; ik++){
              int val;
              if(ik>49) suma+=val;
              ifile>>val;
              pastylka->SetPoint(ik, ik*10, val);
            }
            double uKalibracji;
            double wsp=wspKalibracyjny(nrKasety[ (pomiar-1)*nKaset[pomiar-1]+ii ], suma, nZero[ij], nTlo[ij], &uKalibracji);
            Printf("Kaseta %d wspolczynnik kalibracji=%lf+-%lf",nrKasety[ (pomiar-1)*nKaset[pomiar-1]+ii ], wsp, uKalibracji);
            pastylka->SetLineColor(ij+1);
            pastylka->SetTitle(Form("kaseta nr %d", nrKasety[ (pomiar-1)*nKaset[pomiar-1]+ii ]));
            pastylka->GetXaxis()->SetTitle("Czas [ms]");
            pastylka->GetYaxis()->SetTitle("Liczba zliczen");
            pastylka->GetYaxis()->SetTitleOffset(yTitleOffset); //przesunięcie tytułu osi y aby nie nachodził na numeracje
            legend->AddEntry(pastylka,Form("Pastylka nr %d", ij+1),"l"); //dodanie kolejnego opisu patylki do legendy
            //cout<<"max="<<max<<"  "<<"GetMaximum = "<<pastylka->GetHistogram()->GetMaximum()<<endl;
            if(max < pastylka->GetHistogram()->GetMaximum()){ //sprawdzanie czy wykresy nie wychodzą poza narysowane osie
              max = pastylka->GetHistogram()->GetMaximum();
              pastylka1->GetYaxis()->SetRangeUser(0, 1.1*max); //przedłużenie osi (reskalowanie wykresów)
            }
            if(ij == 0){
              pastylka->Draw("AL");
              pastylka1 = pastylka;
            }else pastylka->Draw("L same");
            legend->Draw();
          }
          if(SavePng) c->SaveAs(Form("Pamiar%d.png", nrKasety[ (pomiar-1)*nKaset[pomiar-1]+ii ])); //zapisywanie do pliku
      }
    }
  }
}