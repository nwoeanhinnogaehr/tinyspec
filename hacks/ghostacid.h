const int fft_size=1<<15;
void init() {}
void fill(cplx *buf[2], int n, double t) {
    for (int c = 0; c < 2; c++) {
        for (int i = 1; i < n; i++) {
            int r = int(t*4)*n+i;
            double mag=sin(M_PI*(fmod(i/24+c, 1+r/(1+(double)(r/97^r&r/2))/7)))/pow(i+1, 1.0)*4.0;
            buf[c][i]=cplx(mag,mag);
        }
    }
}
