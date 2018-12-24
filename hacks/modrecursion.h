const int fft_size=1<<10;
int sum[2][fft_size];
void init() {}
void fill(cplx *buf[2], int n, double t) {
    for (int c = 0; c < 2; c++) {
        for (int i = 1; i < n; i++) {
            int r = (int)(t*16)*n/2+i+sum[c][i];
            sum[c][i] += r/64|(r/128&r/512);
            sum[c][i] %= (r/64^(r/128&r/512))+16+c;
            buf[c][i] = (exp(cplx(0.0,2.0*M_PI*sin(M_PI/16.0*sum[c][i]/double(n-i)))))/pow(i+1, 1.0)/2.0;
        }
    }
}
