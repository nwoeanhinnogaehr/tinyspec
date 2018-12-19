#include<cmath>
#include<unistd.h>
#include<cstring>
#include<complex>
#include<cassert>
using namespace std;
typedef complex<double> cplx;
const int rate = 44100;

#include".hack.h" // user code

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

cplx fft_out[fft_size], fft_in[fft_size];
float abuf[fft_size/2], atmp[fft_size/2];
int main() {
    init();
    for(double t = 0;; t += fft_size/(double)rate/4) {
        memset(fft_in, 0, sizeof fft_in);
        fill(fft_in, fft_size/2, t);
        ifft(fft_in, fft_out, fft_size);
        for (int i = 0; i < fft_size/4; i++) {
            abuf[i] = (fft_out[i].real()*(i/(fft_size/4.0)) + atmp[i+fft_size/4]);
            atmp[i+fft_size/4] = fft_out[i+fft_size/4].real()*(1.0-(i)/(fft_size/4.0));
        }
        write(1, abuf, (sizeof abuf)/2);
    }
}
