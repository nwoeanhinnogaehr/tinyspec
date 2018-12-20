const int fft_size=1<<12;
void init() {}
void fill(cplx *buf[2], int n, double t) {
    for (int c = 0; c < 2; c++) {
        for (int i = 1; i < n; i++) {
            int r = int(t*16)*n+i;
            buf[c][i]=sin(2.0*M_PI/128.*(c+((int)pow(r,1.1))^r/13^r>>8|r>>6^r>>14))/pow(i+1, 0.8);
        }
    }
}
