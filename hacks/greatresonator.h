const int fft_size=1<<12;
double phase_sum[2][fft_size];
void init() {}
void fill(cplx *buf[2], int n, double t) {
    for (int c = 0; c < 2; c++) {
        for (int i = 1; i < n; i++) {
            int r = int(t*1024)+(1<<20);
            for (int nn = 1; nn <= 16; nn++) {
                int f = int(pow(i/16+r/255&r/63^r/1023,1+2/double(nn+c)))%256+1;
                int h = i/f;
                int k = i%f;
                phase_sum[c][i] += 2*M_PI*i;
                buf[c][i]+=polar(
                    (double)((k==nn%f)*(h&1?1:-1))/pow(max(1,i-f+1), 0.6)/16,
                    phase_sum[c][i]+c*M_PI/2);
            }
        }
    }
}
