# mandelbrot-set

<img src="https://raw.githubusercontent.com/segnoda/mandelbrot-set/master/gallery/M0-1024.png"  width="512" height="512"/>

## Getting Started

Everyone can simply draw almost any part of Mandelbrot set by this code.

### Usage

Just compile `mandelbrot.cpp` and execute `mandelbrot`.

```
$ g++ mandelbrot.cpp -o mandelbrot -std=c++11 -Wall
$ ./mandelbrot
```

## Convert Image

You can convert image from `*.ppm` to `*.png`.

### Linux

```
$ convert mandelbrot.ppm mandelbrot.png
```

### macOS

```
$ sips -s format png mandelbrot.ppm --out mandelbrot.png
```

## Gallery

<img src="https://raw.githubusercontent.com/segnoda/mandelbrot-set/master/gallery/M1-1024.png"  width="512" height="512"/>
<img src="https://raw.githubusercontent.com/segnoda/mandelbrot-set/master/gallery/M2-1024.png"  width="512" height="512"/>
<img src="https://raw.githubusercontent.com/segnoda/mandelbrot-set/master/gallery/M3-1024.png"  width="512" height="512"/>
<img src="https://raw.githubusercontent.com/segnoda/mandelbrot-set/master/gallery/M4-1024.png"  width="512" height="512"/>
