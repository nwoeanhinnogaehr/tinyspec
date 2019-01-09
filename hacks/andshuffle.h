const int fft_size=1<<18;
void init() {}
void fill(cplx *buf[2], int n, double t) {
    for (int c = 0; c < 2; c++) {
        for (int i = 1; i < n; i++) {
            int r = int(t*8)*n/2+n-i;
            int j = r/128+c;
            double mag = sin((1+fmod(i*i, (1+(double)(((j/5&j/7&(j/64^j/127))^j>>16)%128)))))/pow(i+1, 0.75)/8;
            buf[c][i] = cplx(mag,mag);
        }
    }
}
