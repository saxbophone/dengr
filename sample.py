# this is a sample for drawing an archimedean spiral with equal segment lengths
import math
import turtle


def draw_spiral(_a, _b, _step=0.5, count=5):
    """
    Draw the Archimdean spiral defined by:
    r = a + b*theta
    Args:
        a (real): inner radius
        b (real): pitch
        step (real): distance between points
        count (int): number of points to plot
    """
    a = float(_a)
    b = float(_b)
    step = float(_step)
    theta = 0.0
    r = a
    prev_x = int(r * math.cos(theta))
    prev_y = int(r * math.sin(theta))
    turtle.color("blue")
    turtle.down()
    turtle.goto(prev_x, prev_y)
    for i in xrange(count):
        theta += (step / (r * 2 * math.pi))
        r = a + (b * theta)
        # Draw pixels, but remember to convert to Cartesian:
        x = int(r * math.cos(theta * 2 * math.pi))
        y = int(r * math.sin(theta * 2 * math.pi))
        if i % 2 == 0:
            turtle.color("red")
        else:
            turtle.color("blue")
        turtle.goto(x, y)
        prev_x = x
        prev_y = y
    turtle.up()
    turtle.done()

# e.g.
# draw_spiral(25, 0.0015, 15, 10000)
