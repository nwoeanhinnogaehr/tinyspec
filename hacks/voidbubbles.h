const int fft_size=1<<13;
void init() {}
void fill(cplx *buf[2], int n, double t) {
    for (int i = 1; i < n; i++) {
        int r = (int)(t*32)*n+i;
        buf[0][i]=buf[1][i]=sin(2.0*M_PI/64.*(((int)pow(i,1.1))&r/3|r/250|r/136|r>>16))/pow(i+1, 0.7);
    }
}
