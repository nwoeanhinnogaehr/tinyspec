#include<math.h>
typedef struct{long double r; long double i;} complex;
void ifft(complex *v, int n, complex *tmp) {
    if(n>1) {
        int k;
        complex t, z, w = {1., 0.}, *vo=tmp, *ve=tmp+n/2;
        for(k=0; k<n/2; k++) {
            ve[k] = v[2*k];
            vo[k] = v[2*k+1];
        }
        ifft(ve, n/2, v);
        ifft(vo, n/2, v);
        sincosl(2*M_PI/(long double)n,&t.i,&t.r);
        for(k=0; k<n/2; k++) {
            z.r = w.r*vo[k].r - w.i*vo[k].i;
            z.i = w.r*vo[k].i + w.i*vo[k].r;
            v[k].r = ve[k].r + z.r;
            v[k].i = ve[k].i + z.i;
            v[k+n/2].r = ve[k].r - z.r;
            v[k+n/2].i = ve[k].i - z.i;
            complex nw = {w.r*t.r - w.i*t.i, w.r*t.i + w.i*t.r}; w=nw;
        }
    }
}
int s=1<<16;
int main() {
    complex sbuf[s],stmp[s];
    float abuf[s],atmp[s];
    long double t=0;
    for(int i;;t+=1/(float)s) {
        memset(sbuf, 0, sizeof sbuf);
        for (i = 1; i < s/2; i++) {
            int r = (int)(t*s)*s/2+i;
            long double mag=sinl(2.0*M_PI*t*64*(((int)pow(i,0.9))^r|r>>9&r>>7^r>>16))/pow(i+1, 0.8)*8.0;
            long double ang=2.0*M_PI*i*t/s;
            sbuf[i].r=mag*sin(ang);
            sbuf[i].i=mag*cos(ang);
        }
        ifft(sbuf,s,stmp);
        for (i = 0; i < s/4; i++){
            abuf[i]=(sbuf[i].r*(i/(s/4.0)) + atmp[i+s/4])/log2(s);
            atmp[i+s/4]=sbuf[i+s/4].r*(1.0-(i)/(s/4.0));
        }
        write(1,abuf,(sizeof abuf)/4);
    }
}
