void grad_case2(float(&A) [4][16], float(&dB) [4][16], float(&dA) [4][16]) {
  float tmp1[4][16];
  for (int i=0;i<4;i++){
    for (int j=0;j<16;j++){
      tmp1[i][j]=0;
      tmp1[i][j]=tmp1[i][j] + (A[i][j] * dB[i][j]);
    }
  }
  for (int i=0;i<4;i++){
    for (int j=0;j<16;j++){
      dA[i][j]=tmp1[i][j];
    }
  }
  float tmp2[4][16];
  for (int i=0;i<4;i++){
    for (int j=0;j<16;j++){
      tmp2[i][j]=dA[i][j];
      tmp2[i][j]=tmp2[i][j] + (A[i][j] * dB[i][j]);
    }
  }
  for (int i=0;i<4;i++){
    for (int j=0;j<16;j++){
      dA[i][j]=tmp2[i][j];
    }
  }
}
