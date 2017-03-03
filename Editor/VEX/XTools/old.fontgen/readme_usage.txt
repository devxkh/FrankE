Due to the modification, the executable can not show full usage.

Here is all the switches available:

-a <file> : specify an alphabet file. alphabet needs to be ASCII code ascending order.
-t <size> : Specify the output aquare texture size (ex: 256)
-f <format> : Specify the output data file format
   ("none", "quickgui", "gorilla")
-o <width> : Outline width. Leave to 0 for no outline
-i <intensity> : Intensity modifier
-c <color> : Main glyph color (ex: "0 1 0")
-C <color> : Outline color (ex: "0 1 1")
-s <size> : Font point size
<fontfile> : Specify input font file

*********************************************************************
Example full command lines to generate one font:

fontgen -i 2 -C "1 0 1" -o 3 -c "0 0 1" -f quickgui -s 24 segoepr.ttf
fontgen -c "0 0 1" -f gorilla -s 18 segoepr.ttf

*********************************************************************
Example full command lines to generate multiple font set
in the same texture and .gorilla file:

To initiate multi-font output, start by only specifying
the following 2 arguments:

fontgen -f gorilla -t 512

Then fontgen will ask you for each font arguments. Hit carriage return
without entering any arguments in order to finish adding fonts and
start generrating the texture/data.
Here is some examples:

-o 2 -i 1 -s 18 -c "1 1 0" -C "1 0 0" segoepr.ttf
-o 1 -i 2 -s 24 -c "0 0 1" -C "1 0 1" carolingia.ttf
-o 2 -i 3 -s 36 -c "1 1 1" -C "0 0 0" courbd.ttf


