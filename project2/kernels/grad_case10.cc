void grad_case10(float(&dA) [8][8], float(&dB) [10][8]) {
  float tmp1[10][8];
  for (int i=0;i<8;i++){
    for (int j=0;j<8;j++){
      tmp1[i][j]=0;
      tmp1[i][j]=tmp1[i][j] + (dA[i][j] / 3.00000);
    }
  }
  for (int i=0;i<8;i++){
    for (int j=0;j<8;j++){
      dB[i][j]=tmp1[i][j];
    }
  }
  float tmp2[10][8];
  for (int z=0;z<10;z++){
    for (int j=0;j<8;j++){
      tmp2[z][j]=dB[z][j];
      for (int i=0;i<8;i++){
        if (z == i + 1) {
          tmp2[z][j]=tmp2[z][j] + (dA[i][j] / 3.00000);
        }
      }
    }
  }
  for (int z=0;z<10;z++){
    for (int j=0;j<8;j++){
      dB[z][j]=tmp2[z][j];
    }
  }
  float tmp3[10][8];
  for (int z=0;z<10;z++){
    for (int j=0;j<8;j++){
      tmp3[z][j]=dB[z][j];
      for (int i=0;i<8;i++){
        if (z == i + 2) {
          tmp3[z][j]=tmp3[z][j] + (dA[i][j] / 3.00000);
        }
      }
    }
  }
  for (int z=0;z<10;z++){
    for (int j=0;j<8;j++){
      dB[z][j]=tmp3[z][j];
    }
  }
}
