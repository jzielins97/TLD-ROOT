#ifndef TLD_H

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
  u=0;
  wsp=1.0*hp/(n-nT-n0); //za mała liczba aby zwracać ja bez mnożenia przez miliard/10
  //if(jest) cout<<"Kaseta #"<<nrKasety<<" hp="<<hp<<" n="<<n<<" n0="<<n0<<" nT="<<nT<<" Wsp="<<wsp<<" u="<<u<<endl;
  return jest;
}

void table (int n, int *nrKasety, const char *xName, double *x, double *u){ //n-liczba wartości; xName-nazwa wartości; x- wartości; u- niepewności do x
  Printf("   Nr Kasety   | %13s |  Niepewnosc   ", xName);
  Printf("----------------------------------------------------------");
  for(int i=0; i<n; i++){
    if( i%4 == 0 ) Printf("%15d|%.10e|%.10e", nrKasety[i/4], x[i], u[i]);
    else if(nrKasety[i/4] == 7809) Printf("%15d|%15e|%15e", nrKasety[i/4], x[i], u[i]);
    else Printf("%15s|%.10e|%.10e", "", x[i], u[i]);
  }
  ofstream ofile;
  ofile.open("output.txt");
  ofile<<Form("   Nr Kasety   | %13s |  Niepewnosc   ", xName)<<endl;
  ofile<< "----------------------------------------------------------"<<endl;
  for(int i=0; i<n; i++){
    if( i%4 == 0 ) ofile<<Form("%15d|%.10e|%.10e", nrKasety[i/4], x[i], u[i])<<endl;
    else if(nrKasety[i/4] == 7809) ofile<<Form("%15d|%15e|%15e", nrKasety[i/4], x[i], u[i])<<endl;
    else ofile<<Form("%15s|%.10e|%.10e", "", x[i], u[i])<<endl;
  }
  ofile.close();
}

#endif
