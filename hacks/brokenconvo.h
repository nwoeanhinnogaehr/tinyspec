const int fft_size=1<<16;
void init() {}
void fill(cplx *buf[2], int n, double t) {
    for (int c = 0; c < 2; c++) {
        for (int i = 1; i < n; i++) {
            int r = (int)(t*M_PI)*n/2+i;
            buf[c][i]=sin(2.0*M_PI*(i/(1+fmod((1+(double)(r/77&r/38&r/24+c)),i+1))))/pow(i+1, 0.75)/2;
        }
    }
}
