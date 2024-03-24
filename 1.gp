set terminal pngcairo enhanced font 'Verdana,12'
set output '1.png'

unset key

set xlabel 'time'
set ylabel 'Entropy'
set title 'Entropy versus time'

plot '1.txt' with linespoints
