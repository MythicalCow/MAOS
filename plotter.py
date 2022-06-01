from turtle import *

FILENAME = "maos.csv"

def read_file(file):
    with open(file) as f:
        line_list = [line.strip().split(",") for line in f]
    return line_list

data = read_file(FILENAME)
penup()
setpos(0,-120)
setheading(90)
pendown()
scale = 480 / len(data)
for x_angle, y_angle, z_angle, x_accleration in data:
    right((heading()-90)-(float(x_angle)*-1))
    forward(scale)
done()