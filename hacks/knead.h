const int fft_size=1<<10;
int feed[2][fft_size];
void init() {}
void fill(cplx *buf[2], int n, double t) {
    for (int c = 0; c < 2; c++) {
        for (int i = 1; i < n; i++) {
            int r = (int)(t*12)*n/2+i+feed[c][i];
            feed[c][i] += r/16^r/63^r/1023^c;
            if (int mod = (r/16^r/65^r/1024))
                feed[c][i] %= mod;
            buf[c][i] = (exp(cplx(0.0,M_PI*sin(M_PI*feed[c][i]/double(n-i)))))/pow(i+1, 1.0)/2.0;
        }
    }
}
