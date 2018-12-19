#include<cmath>
#include<unistd.h>
#include<cstring>
#include<complex>
#include<cassert>
using namespace std;
typedef complex<double> cplx;
const int rate = 44100;

#define XSTR(x) #x
#define STR(x) XSTR(x)
#include STR(HACK)

// FFT author: Zachary Friggstad
void ifft(cplx *in, cplx *v, int n) {
    assert(n > 0 && (n&(n-1)) == 0);
    for (int i = 0; i < n; ++i) {
        int r = 0, k = i;
        for (int j = 1; j < n; j <<= 1, r = (r<<1)|(k&1), k >>= 1);
        v[i] = in[r];
    }
    for (int m = 2; m <= n; m <<= 1) {
        int mm = m>>1;
        cplx zeta = polar<double>(1, 2*M_PI/m);
        for (int k = 0; k < n; k += m) {
            cplx om = 1;
            for (int j = 0; j < mm; ++j, om *= zeta) {
                cplx tl = v[k+j], th = om*v[k+j+mm];
                v[k+j] = tl+th;
                v[k+j+mm] = tl-th;
            }
        }
    }
}

cplx fft_out[2*fft_size], fft_in[2*fft_size];
float abuf[fft_size], atmp[fft_size];
int main() {
    init();
    for (double t = 0;; t += fft_size/(double)rate/4) {
        memset(fft_in, 0, sizeof fft_in);
        cplx* fft_buf[2] = {fft_in, fft_in+fft_size};
        fill(fft_buf, fft_size/2, t);
        for (int c = 0; c < 2; c++) {
            ifft(fft_in+c*fft_size, fft_out+c*fft_size, fft_size);
            for (int i = 0; i < fft_size/4; i++) {
                abuf[i*2+c] = (fft_out[i+c*fft_size].real()*(i/(fft_size/4.0))+atmp[i*2+c+fft_size/4]);
                atmp[i*2+c+fft_size/4] = fft_out[i+c*fft_size+fft_size/4].real()*(1.0-(i)/(fft_size/4.0));
            }
        }
        write(1, abuf, (sizeof abuf)/2);
    }
}
