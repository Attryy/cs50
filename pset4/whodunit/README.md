# Questions

## What's `stdint.h`?
`stdint.h` is a header file in C standard library which provides a set of typedefs that specify the exact-width integer types.
TODO

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?
It allows the programmer to write more portable code?
TODO

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?
`BYTE`: 1 byte
`DWORD`: 4 bytes
`LONG`: 4 bytes
`WORD`: 2 bytes

TODO

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."
0x424d

TODO

## What's the difference between `bfSize` and `biSize`?
`bfSize` is included in the BITMAPFILEHEADER and `biSize` is included in BITMAPINFOHEADER.

TODO

## What does it mean if `biHeight` is negative?
When `biHeight` is negative, the image is top-down.

TODO

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?
`biBitCount`
TODO

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?
It's possible that there is no file with the specified name in that directory.
TODO

## Why is the third argument to `fread` always `1` in our code?
We use the sizeof() function to identify the size of the element we want to read.
TODO

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

TODO

## What does `fseek` do?

`fseek` is the function to set the file position to the given offset that is specified by the second argument.

TODO

## What is `SEEK_CUR`?
This argument sets the position that the offset will be added to the current file position.

TODO

## Whodunit?

TODO
