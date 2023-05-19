<div align = center>
<image src="https://raw.githubusercontent.com/MubinMuhammad/Zinc/master/logo.png" width=540 height=290>
<br>
An image processing program written in C.
</div>

## Building
### Using Makefile


Move to the directory you have put the Zinc project, create a bin directory. And then run the following command:

``` bash
make release # for linux and macOS
mingw32-make release # for Windows with mingw GCC. (Don't know what to do with Visual Studio)
```
After that, you will see there are a executable file in the ```bin``` directory.

If you don't want to have the repeat effects question you have to compile it in this way:
``` bash
gcc src/*.c -o bin/zinc -lm -DZINC_DO_NOT_REPEAT_EFFECTS
```


## Download Precompiled Binaries (Soon)
The precomiled binaries will come soon. But you might have to wait for the macOS compiled binraries.
You can still run the program in a mac. But don't forget to build it yourself.
