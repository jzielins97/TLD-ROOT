#ifndef TLD_H

double wspKalibracyjny(int nrKasety, int n, int n0, int nT, double *u){
  double hp;
  switch (nrKasety) {
    case 20577:
      hp=0.1;
      break;
    case 20580:
      hp=0.1;
      break;
    case 18237:
      hp=0.1;
      break;
    case 20441:
      hp=0.1;
      break;
    case 20478:
      hp=0.1;
      break;
    case 20578:
      hp=0.1;
      break;
    case 20444:
      hp=0.1;
      break;
    case 20551:
      hp=0.1;
      break;
    case 10582:
      hp=0.1;
      break;
    case 20465:
      hp=0.1;
      break;
    case 7809:
      hp=0.1;
      break;
    case 20461:
      hp=0.1;
      break;
    case 646:
      hp=0.1;
      break;
    case 2750:
      hp=0.1;
      break;
    case 20589:
      hp=0.1;
      break;
    case 9200:
      hp=0.1;
      break;
  }
  u=0;
  //cout<<"Kaseta #"<<nrKasety<<" hp="<<hp<<" n="<<n<<" n0="<<n0<<" nT="<<nT<<" u="<<u<<endl;
  return 1000000000*hp/(n-nT-n0); //za mała liczba aby zwracać ja bez mnożenia przez miliard
}

#endif
