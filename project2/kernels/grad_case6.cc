void grad_case6(float(&C) [8][16][3][3], float(&dA) [2][8][5][5], float(&dB) [2][16][7][7]) {
  float tmp1[2][16][7][7];
  for (int n=0;n<2;n++){
    for (int c=0;c<16;c++){
      for (int z=0;z<7;z++){
        for (int y=0;y<7;y++){
          tmp1[n][c][z][y]=0;
          for (int p=0;p<5;p++){
            for (int r=0;r<3;r++){
              for (int q=0;q<5;q++){
                for (int s=0;s<3;s++){
                  for (int k=0;k<8;k++){
                    if (y == q + s) {
                      if (z == p + r) {
                        tmp1[n][c][z][y]=tmp1[n][c][z][y] + (C[k][c][r][s] * dA[n][k][p][q]);
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  for (int n=0;n<2;n++){
    for (int c=0;c<16;c++){
      for (int z=0;z<7;z++){
        for (int y=0;y<7;y++){
          dB[n][c][z][y]=tmp1[n][c][z][y];
        }
      }
    }
  }
}
