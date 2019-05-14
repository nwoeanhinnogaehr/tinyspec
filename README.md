A tiny frequency domain synthesizer for linux.

Check out [tinyspec-cling](https://github.com/nwoeanhinnogaehr/tinyspec-cling) for a slightly more heavyweight version with livecoding support!

Try:
```
$ ./play hacks/brokenconvo.h
```

For full list of examples, see the `hacks` directory. `example.h` has been well commented as a starting point for further exploration.

If your `aplay` is not working, you might want edit the play script to send the output somewhere else instead. The samples are stereo 44100Hz 32-bit floats.
