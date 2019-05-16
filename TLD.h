#ifndef TLD_H

bool isGamma(int nrKasety){
  bool jest=false;
  switch (nrKasety) {
    case 20577: //zero dose
      break;
    case 20580:
      break;
    case 18237:
      break;
    case 20441:
      jest = true;
      break;
    case 20478:
      jest=true;
      break;
    case 20578://tlo
      break;
    case 20444:
      break;
    case 20551:
      break;
    case 20582:
      break;
    case 20465:
      break;
    case 7809://mieszane
      break;
    case 20461:
      jest = true;
      break;
    case 646:
      jest = true;
      break;
    case 2750:
      jest=true;
      break;
    case 20589:
      jest=true;
      break;
    case 9200:
      break;
  }
  return jest;

}


bool wspKalibracyjny(int nrKasety, int n, int n0, int nT, double &wsp, double &u){
  bool jest = false;
  double hp;
  switch (nrKasety) {
    case 20577: //zero dose
      hp=0;
      break;
    case 20580:
      hp=1;
      jest = true;
      break;
    case 18237:
      hp=1;
      jest = true;
      break;
    case 20441:
      hp=1;
      jest = true;
      break;
    case 20478:
      hp=1;
      jest=true;
      break;
    case 20578:
      hp=0;
      break;
    case 20444:
      hp=1;
      jest = true;
      break;
    case 20551:
      hp=1;
      jest = true;
      break;
    case 20582:
      hp=2;
      break;
    case 20465:
      hp=0.5;
      break;
    case 7809://mieszane
      hp=0;
      break;
    case 20461:
      hp=1;
      jest = true;
      break;
    case 646:
      hp=1;
      jest = true;
      break;
    case 2750:
      hp=2;
      break;
    case 20589:
      hp=0.5;
      break;
    case 9200:
      hp=1;
      jest = true;
      break;
  }
  u=sqrt(3*TMath::Power((hp/(TMath::Power((n-n0-nT),2.0))),2.0));
  wsp=1.0*hp/(n-nT-n0); //za mała liczba aby zwracać ja bez mnożenia przez miliard/10
  //if(jest) cout<<"Kaseta #"<<nrKasety<<" hp="<<hp<<" n="<<n<<" n0="<<n0<<" nT="<<nT<<" Wsp="<<wsp<<" u="<<u<<endl;
  return jest;
}

void wspSredni(int n, int *nrKasety, double *wsp, double *uWsp, double *wspSr, double *uWspSr){
  for(int i=0; i<n/4; i++){
    if( isGamma(nrKasety[i]) ){
      wspSr[4]+=wsp[i*4];
      wspSr[5]+=wsp[i*4+1];
      wspSr[6]+=wsp[i*4+2];
      wspSr[7]+=wsp[i*4+3];
    }else{
      wspSr[0]+=wsp[i*4];
      wspSr[1]+=wsp[i*4+1];
      wspSr[2]+=wsp[i*4+2];
      wspSr[3]+=wsp[i*4+3];
    }
  }
  for(int i=0; i<8; i++){ wspSr[i]/=1.0*n;}
  for(int i=0; i<8; i++){uWspSr[i] = 1.0*3*TMath::Power(uWsp[i], 2.0)/n;}
}

//double hp(int iPastylki, double *wsp, int n, int ){}

void table (int n, int *nrKasety,const char *iName, const char *xName, double *x, double *u){ //n-liczba wartości; xName-nazwa wartości; x- wartości; u- niepewności do x
  Printf(" %13s | %13s |  Niepewnosc   ", iName, xName);
  Printf("----------------------------------------------------------");
  for(int i=0; i<n; i++){
    if( i%4 == 0 ) Printf("%15d|%.10e|%.10e", nrKasety[i/4], x[i], u[i]);
    else if(nrKasety[i/4] == 7809) Printf("%15d|%15e|%15e", nrKasety[i/4], x[i], u[i]);
    else Printf("%15s|%.10e|%.10e", "", x[i], u[i]);
  }
  ofstream ofile;
  ofile.open("output.txt", std::ios_base::app);
  ofile<<endl;
  ofile<<Form(" %13s | %13s |  Niepewnosc   ", iName, xName)<<endl;
  ofile<< "----------------------------------------------------------"<<endl;
  for(int i=0; i<n; i++){
    if( i%4 == 0 ) ofile<<Form("%15d|%.10e|%.10e", nrKasety[i/4], x[i], u[i])<<endl;
    else if(nrKasety[i/4] == 7809) ofile<<Form("%15d|%15e|%15e", nrKasety[i/4], x[i], u[i])<<endl;
    else ofile<<Form("%15s|%.10e|%.10e", "", x[i], u[i])<<endl;
  }
  ofile.close();
}

#endif
