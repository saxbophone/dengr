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


def spiral_points(inner_radius=25, point_distance=1, pitch=0.0015):
    """generate points on an Archimedes' spiral
    with `arc` giving the length of arc between two points
    and `separation` giving the distance between consecutive 
    turnings
    - approximate arc length with circle arc at given distance
    - use a spiral equation r = b * phi
    """
    def p2c(r, phi):
        """polar to cartesian
        """
        return (r * math.cos(phi), r * math.sin(phi))

    turtle.color("blue")
    turtle.down()
    turtle.goto(0, 0)

    # initialize the next point in the required distance
    r = point_distance
    b = pitch / (2 * math.pi)
    # find the first phi to satisfy distance of `arc` to the second point
    phi = float(r) / b
    while True:
        turtle.goto(p2c(r, phi))
        # advance the variables
        # calculate phi that will give desired arc length at current radius
        # (approximating with circle)
        phi += float(point_distance) / r
        r = inner_radius + b * phi

# e.g.
# draw_spiral(25, 0.0015, 15, 10000)
