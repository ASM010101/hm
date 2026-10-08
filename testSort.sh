#!/bin/bash
gcc -o sortprog assgH02.c
read -p "Enter number of random elements: " n
echo "$n $(./sortprog $n)" >> output.txt
echo 'plot "output.txt" using 1:2 w l title "bubble", "output.txt" using 1:4 w l title "merge", "output.txt" using 1:6 w l title "quick1", "output.txt" using 1:8 w l title "quick3", "output.txt" using 1:10 w l title "quickM"' > plot.gnu
gnuplot plot.gnu