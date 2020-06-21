void grad_case8(float(&dB) [32], float(&dA) [2][16]) {
  float tmp1[2][16];
  for (int z=0;z<2;z++){
    for (int y=0;y<16;y++){
      tmp1[z][y]=0;
      for (int i=0;i<32;i++){
        if (y == i % 16) {
          if (z == i / 16) {
            tmp1[z][y]=tmp1[z][y] + dB[i];
          }
        }
      }
    }
  }
  for (int z=0;z<2;z++){
    for (int y=0;y<16;y++){
      dA[z][y]=tmp1[z][y];
    }
  }
}
