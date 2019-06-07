from sense_hat import SenseHat
import time
import sys

s = SenseHat()
#s.low_light = True

G = (0, 255, 0) #green
Y = (255, 255, 0) #yellow
B = (0, 0, 255) #blue
R = (255, 0, 0) #red
W = (255,255,255) #white
O = (0,0,0) #nothing
P = (255,105, 180) #pink
C = (0, 255, 255) #cyan
Q = (255, 215, 0) #gold
S = (192, 192, 192) #silver

question_mark = [
    O, O, O, R, R, O, O, O,
    O, O, R, O, O, R, O, O,
    O, O, O, O, O, R, O, O,
    O, O, O, O, R, O, O, O,
    O, O, O, R, O, O, O, O,
    O, O, O, R, O, O, O, O,
    O, O, O, O, O, O, O, O,
    O, O, O, R, O, O, O, O
    ]

smiley = [
    O, Y, Y, Y, Y, Y, Y, O,
    Y, O, O, O, O, O, O, Y,
    Y, O, O, Y, O, Y, O, Y,
    Y, O, O, O, O, O, O, Y,
    Y, O, Y, O, O, O, Y, Y,
    Y, O, O, Y, Y, Y, O, Y,
    Y, O, O, O, O, O, O, Y,
    O, Y, Y, Y, Y, Y, Y, O,
    ]

stop_sign = [
    R, O, O, O, O, O, R, R,
    R, R, O, O, O, R, R, O,
    O, R, R, O, R, R, O, O,
    O, O, R, R, R, O, O, O,
    O, O, O, R, R, R, O, O,
    O, O, R, R, O, R, R, O,
    O, R, R, O, O, O, R, R,
    R, R, O, O, O, O, O, R,
    ]

crescendo = [
    O, O, O, O, C, O, O, O,
    O, O, O, C, O, O, O, O,
    O, O, C, O, O, O, O, O,
    O, C, O, O, O, O, O, O,
    O, O, C, O, O, O, O, O,
    O, O, O, C, O, O, O, O,
    O, O, O, O, C, O, O, O,
    O, O, O, O, O, O, O, O,
    ]

decrescendo = [
    O, O, O, P, O, O, O, O,
    O, O, O, O, P, O, O, O,
    O, O, O, O, O, P, O, O,
    O, O, O, O, O, O, P, O,
    O, O, O, O, O, P, O, O,
    O, O, O, O, P, O, O, O,
    O, O, O, P, O, O, O, O,
    O, O, O, O, O, O, O, O,
    ]

sword = [
    S, O, O, O, O, O, O, S,
    O, S, O, O, O, O, S, O,
    O, O, S, O, O, S, O, O,
    O, O, O, S, S, O, O, O,
    O, O, O, S, S, O, O, O,
    O, Y, R, O, O, P, Y, O,
    O, Y, Y, O, O, Y, Y, O,
    Y, O, O, O, O, O, O, Y,
    ]

arrow_up = [
    O, O, O, Q, O, O, O, O,
    O, O, Q, Q, Q, O, O, O,
    O, Q, O, Q, O, Q, O, O,
    Q, O, O, Q, O, O, Q, O,
    O, O, O, Q, O, O, O, O,
    O, O, O, Q, O, O, O, O,
    O, O, O, Q, O, O, O, O,
    O, O, O, Q, O, O, O, O,
    ]

arrow_down = [
    O, O, O, Q, O, O, O, O,
    O, O, O, Q, O, O, O, O,
    O, O, O, Q, O, O, O, O,
    O, O, O, Q, O, O, O, O,
    Q, O, O, Q, O, O, Q, O,
    O, Q, O, Q, O, Q, O, O,
    O, O, Q, Q, Q, O, O, O,
    O, O, O, Q, O, O, O, O,
    ]

arrow_left = [
    O, O, O, Q, O, O, O, O,
    O, O, Q, O, O, O, O, O,
    O, Q, O, O, O, O, O, O,
    Q, Q, Q, Q, Q, Q, Q, Q,
    O, Q, O, O, O, O, O, O,
    O, O, Q, O, O, O, O, O,
    O, O, O, Q, O, O, O, O,
    O, O, O, O, O, O, O, O,
    ]

arrow_right = [
    O, O, O, O, Q, O, O, O,
    O, O, O, O, O, Q, O, O,
    O, O, O, O, O, O, Q, O,
    Q, Q, Q, Q, Q, Q, Q, Q,
    O, O, O, O, O, O, Q, O,
    O, O, O, O, O, Q, O, O,
    O, O, O, O, Q, O, O, O,
    O, O, O, O, O, O, O, O,
    ]

heart = [
    O, O, O, O, O, O, O, O,
    O, P, P, O, P, P, O, O,
    P, P, P, P, P, P, P, O,
    P, P, P, P, P, P, P, O,
    O, P, P, P, P, P, O, O,
    O, O, P, P, P, O, O, O,
    O, O, O, P, O, O, O, O,
    O, O, O, O, O, O, O, O,
    ]

if "__main__" == __name__:
	if "drive" in sys.argv:
		s.show_message("Drive", text_colour=B, scroll_speed=0.1)

	if "reset" in sys.argv:
	        s.show_message("Reset", text_colour=R, scroll_speed=0.1)

	if "help" in sys.argv:
		s.show_message("Help", text_colour=R, scroll_speed=0.1)
		s.set_pixels(question_mark)

	if "clean" in sys.argv:
	        s.show_message("Clean", text_colour=G, scroll_speed=0.1)
	        s.set_pixels(smiley)

	if "dock" in sys.argv:
	        s.show_message("Dock", text_colour=Y, scroll_speed=0.1)
	        s.set_pixels(heart)

	if "battle" in sys.argv:
	        s.show_message("Battle", text_colour=S, scroll_speed=0.1)
	        s.set_pixels(sword)

	if "stop" in sys.argv:
	        s.show_message("Stop", text_colour=R, scroll_speed=0.1)
	        s.set_pixels(stop_sign)

	if "incrpm" in sys.argv:
	        s.show_message("Increase-RPM", text_colour=C, scroll_speed=0.1)
	        s.set_pixels(crescendo)

	if "decrpm" in sys.argv:
	        s.show_message("Decrease-RPM", text_colour=P, scroll_speed=0.1)
	        s.set_pixels(decrescendo)

	if "straight" in sys.argv:
	        s.show_message("Straight", text_colour=Q, scroll_speed=0.1)
	        s.set_pixels(arrow_up)

	if "left" in sys.argv:
	        s.show_message("Left", text_colour=Q, scroll_speed=0.1)
	        s.set_pixels(arrow_left)

	if "right" in sys.argv:
	        s.show_message("Right", text_colour=Q, scroll_speed=0.1)
	        s.set_pixels(arrow_right)

	if "reverse" in sys.argv:
	        s.show_message("Reverse", text_colour=Q, scroll_speed=0.1)
	        s.set_pixels(arrow_down)
