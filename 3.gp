# set fit logfile '3.log'
# f(x) = a*sqrt(x + b) + c
# fit f(x) "3.txt" via a, b, c

set key right bottom
set terminal pdf enhanced font 'Verdana,12'
set output '3.pdf'

set xlabel 'time'
set ylabel 'size of the drop'
set title 'Size of the drop as a function of time'

stats '3.txt' nooutput
N = STATS_records
# print(N)
stats "3.txt" every ::N-1::N-1 u 2 nooutput
t_fill = int(STATS_max)
# print(t_fill)

set arrow from t_fill,0 to t_fill,250 nohead lc 2 lw 2
plot '3.txt' every ::::N-2 w l t 'Data'
# plot '3.txt' using 1:2 w lp t 'Data', f(x) t 'Square root fit'