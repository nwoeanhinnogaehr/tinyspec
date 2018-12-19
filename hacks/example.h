// Size of FFT: you will have fft_size/2 frequency bins to work with.
// Must be a power of two.
const int fft_size = 1<<14;

// Called once at program startup.
void init() {}

// Called periodically to fill up a new buffer.
// buf[0] is the left channel, and buf[1] is the right channel.
// You should fill both elements of buf with n complex numbers.
// t is the time in seconds since the beginning of playback.
// The 0th bin is the DC offset. Usually this should be left at a value of 0.
// The 1st bin is the lowest frequency, and the n-1th is the highest frequency.
// buf is zeroed out before this function is called.
void fill(cplx *buf[2], int n, double t) {
    // Loop over frequency bins. Starting at 1 skips the DC offset.
    for (int i = 1; i < n; i++) {
        buf[0][i] = buf[1][i] = // Set both left and right channels
            sin(t+pow(i,1+sin(t)*0.6))/2 // Fun little formula
            /i; // Scale magnitude by bin number to prevent loud high frequency noises.
    }
}
