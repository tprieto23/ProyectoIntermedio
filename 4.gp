set terminal pdf enhanced font 'Verdana,12'
set output "4.pdf"

f(x) = 400*exp(-(x - A)/B)
A=5000
B=500000

set xlabel 'Time'
set ylabel 'Molecles in container'

set fit logfile '4.log'

fit f(x) "4.txt" via A, B

plot "4.txt" pt 7 lc 'red' lw 2, f(x) lw 3 lc 'black'