const int fft_size=1<<10;
int x;
void init() {}
void fill(cplx *buf[2], int n, double t) {
    for (int c = 0; c < 2; c++) {
        for (int i = 1; i < n; i++) {
            int r = (int)(t*8)*n+i;
            int y = int(t/2);
            int a = y/3^y/5;
            int b = y/2^y/7;
            x += (r/(3+a%17)&r/(5+b%11));
            x ^= r;
            buf[c][i] = (exp(cplx(0.0,M_PI/16.0*x)))/pow(i+1, 1.0)/4.0;
        }
    }
}
