void kernel_case10(float(&B) [10][10], float(&A) [8][8]) {
  float tmp1[8][8];
  for (int i=0;i<8;i++){
    for (int j=0;j<8;j++){
      tmp1[i][j]=0;
      if (i + 2 <= 10) {
        if (i + 2 >= 0) {
          if (i + 1 <= 10) {
            if (i + 1 >= 0) {
              tmp1[i][j]=tmp1[i][j] + (((B[i][j] + B[i + 1][j]) + B[i + 2][j]) / 3);
            }
          }
        }
      }
    }
  }
  for (int i=0;i<8;i++){
    for (int j=0;j<8;j++){
      A[i][j]=tmp1[i][j];
    }
  }
}
