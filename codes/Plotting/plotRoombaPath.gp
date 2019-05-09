#!/usr/bin/gnuplot -c

set datafile separator ','

set terminal push
set terminal pngcairo
set output 'RoombaPath.png'

set grid
set title 'Roomba movement'

set style line 1 lc rgb '#0000ad' lt 1 lw 2 pt 7 ps 1.5 # --- blue

set xrange [-1.5:1.5]
set yrange [-1.5:+1.5]

plot ARG1 using 2:3 with linespoints title 'Roomba path', \
     ARG1 using 2:3:1 every 2:2 with labels tc rgb 'red' offset char 3,0 notitle

set terminal pop
set output
replot
