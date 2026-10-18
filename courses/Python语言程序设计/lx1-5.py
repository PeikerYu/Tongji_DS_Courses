import random
import turtle

screen = turtle.Screen()
screen.title("随机属性射线星形")
screen.bgcolor("black")
pen = turtle.Turtle()
pen.speed(0)
colors = ["red", "yellow", "orange", "white", "pink", "violet", "purple", "blue", "green", "gray"]


def func_draw(center_x, center_y):
    lines = random.randint(10, 40)
    length = random.randint(20, 200)
    thickness = random.randint(1, 5)
    color = random.choice(colors)
    pen.pencolor(color)
    pen.pensize(thickness)
    pen.penup()
    pen.goto(center_x, center_y)
    pen.pendown()
    for i in range(lines):
        pen.forward(length)
        pen.backward(length)
        pen.right(360 / lines)


for i in range(20):
    center_x = random.randint(-300, 300)
    center_y = random.randint(-300, 300)
    func_draw(center_x, center_y)
