// Size of FFT: you will have fft_size/2 frequency bins to work with.
// Must be a power of two.
const int fft_size = 1<<14;

// Called once at program startup.
void init() {}

// Called periodically to fill up a new buffer. You should fill `buf` with `n` complex numbers.
// `t` is the time in seconds since the beginning of playback.
// buf[0] is the DC offset. Usually you'll want this to be zero.
// buf[1] is the lowest frequency, and buf[n-1] is the highest frequency.
// buf is zero initialized before this function is called.
void fill(cplx *buf, int n, double t) {
    // Starting at 1 skips the DC offset.
    for (int i = 1; i < n; i++) {
        buf[i] = sin(t+pow(i,1+sin(t)*0.6)) // Fun little formula
            /i; // Scale magnitude by bin number to prevent loud high frequency noises.
    }
}
