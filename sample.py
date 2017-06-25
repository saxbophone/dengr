# this is a sample for drawing an archimedean spiral with equal segment lengths
import math
import turtle


def draw_spiral(_a, _b, _step=0.5, loops=5):
    """
    Draw the Archimdean spiral defined by:
    r = a + b*theta
    Args:
        a (real): First parameter
        b (real): Second parameter
        step (real): How much theta should increment by. (default: 0.5)
        loops (int): How many times theta should loop around. (default: 5)
    """
    a = float(_a)
    b = float(_b)
    step = float(_step)
    theta = 0.0
    r = a
    prev_x = int(r*math.cos(theta))
    prev_y = int(r*math.sin(theta))
    turtle.color("blue")
    turtle.down()
    turtle.goto(prev_x, prev_y)
    i = 0
    while theta < 2 * loops * math.pi:
        theta += (step / r)
        r = a + b*theta
        # Draw pixels, but remember to convert to Cartesian:
        x = int(r*math.cos(theta))
        y = int(r*math.sin(theta))
        turtle.goto(x, y)
        prev_x = x
        prev_y = y
    turtle.up()
    turtle.done()

# e.g.
# draw_spiral(25, 0.0015, 15, 10000)
