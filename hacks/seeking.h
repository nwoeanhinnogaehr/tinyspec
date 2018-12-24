const int fft_size=1<<12;
int feed[2][fft_size];
void init() {}
void fill(cplx *buf[2], int n, double t) {
    for (int c = 0; c < 2; c++) {
        for (int i = 1; i < n; i++) {
            int r = (int)(t*16)*n/2+i+feed[c][i];
            int l = feed[c][i]+c;
            feed[c][i] += (l&r/128^r/512);
            if (int mod = (r/64&r/256^r/1024))
                feed[c][i] %= mod;
            buf[c][i] = (exp(cplx(0.0,M_PI*feed[c][i])))/pow(i+1, 1.0)/2.0;
        }
    }
}
