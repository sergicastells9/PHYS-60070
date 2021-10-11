# GNUPLOT Script example

# First line set the type of output and what file you want to write to

set terminal png
set output "plot.png"

# Using various "set" commands you can vary different aspects of your plot
# Most have names that make sense like "xlabel", "xrange", etc.

set xlabel "Energy"
set ylabel "Counts"

# Plot command tells gnuplot what to plot and how to format it
# With columnized data, you specify the data file and which columns to use with "using"
# "with" or "w" specifies the style, "linecolor" or "lc" defines the color, "title" or "tit" is the title of each data set
# You can plot multiple data sets by separating them with a comma
# the '\' is a line break, used just to make the script more readable

# plot "data.file" using xcolumn:ycolumn -options

plot "sorted.dat" using 1:2 w points linecolor rgb "red" tit "Detector 1",\
 "sorted.dat" using 1:3 with points lc rgb "black" tit  "Detector 2",\
 "sorted.dat" using 1:4 with points lc rgb "green" tit  "Detector 3",\
 "sorted.dat" using 1:5 with points lc rgb "blue" tit "Detector 4"