const int fft_size=1<<12;
void init() {}
void fill(cplx *buf[2], int n, double t) {
    for (int c = 0; c < 2; c++) {
        for (int i = 1; i < n; i++) {
            int r = int(t*32)*n+i;
            int k = (r>>14^r>>17)%64+2;
            double mag=sin(pow(i,0.1)*k*16+
                    ((double)((r&r>>13)%k))
                    /(1+(double)((r/3&r/1023)%k)))
                /pow(i+1, 1.0)*1.0;
            buf[c][i]=cplx(mag,mag);
        }
    }
}
