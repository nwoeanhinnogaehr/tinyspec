const int fft_size=1<<12;
double sum[2][fft_size];
void init() {}
void fill(cplx *buf[2], int n, double t) {
    for (int c = 0; c < 2; c++) {
        for (int i = 1; i < n; i++) {
            int factor = 600;
            int r = (int)(t*8)*n/2+i;
            sum[c][i] += fmod(r,1+(double)r/(1+(((r/factor)&(r/101/factor)|r/247/factor)&(i+c))))/(n-i);
            buf[c][i] = (fmod(sum[c][i],1))/pow(i+1, 1.0)/2;
            sum[c][i] *= 0.1+sin(i/(double)n*M_PI*2.0+t)*0.1;
        }
    }
}
