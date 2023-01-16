import numpy as np
import cv2 as cv
from matplotlib import pyplot as plt
import time

# possible color choices: cv.COLOR_BGR2GRAY, cv.COLOR_BGR2HSV, cv.COLOR_BGR2RGB

def task4_11():
    cap = cv.VideoCapture(0)
    while(1):
        # Take each frame
        _, frame = cap.read()
        # Convert BGR to HSV
        hsv = cv.cvtColor(frame, cv.COLOR_BGR2HSV)
        # define range of blue color in HSV
        sensitivity = 40
        lower_blue = np.array([60-sensitivity,100,0])
        upper_blue = np.array([60+sensitivity,255,255])
        # Threshold the HSV image to get only blue colors
        mask = cv.inRange(hsv, lower_blue, upper_blue)
        # Bitwise-AND mask and original image
        res = cv.bitwise_and(frame,frame, mask= mask)
        cv.imshow('frame',frame)
        cv.imshow('mask',mask)
        cv.imshow('res',res)
        k = cv.waitKey(5) & 0xFF
        if k == 27:
            break
    cv.destroyAllWindows()

def main():
    task4_11()


if __name__ == '__main__':
    main() 