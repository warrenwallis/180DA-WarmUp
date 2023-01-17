import numpy as np
import cv2 as cv
from matplotlib import pyplot as plt
import time

# possible color choices: cv.COLOR_BGR2GRAY, cv.COLOR_BGR2HSV, cv.COLOR_BGR2RGB

def task4_1():
    cap = cv.VideoCapture(0)
    while(1):
        # Take each frame
        _, frame = cap.read()

        # Convert BGR to wanted color
        converted_frame = cv.cvtColor(frame, cv.COLOR_BGR2HSV)

        # define range of green color in HSV
        # green = 60, blue = 120
        green, blue = 60,120
        sensitivity = 10
        selected = blue
        lower_blue = np.array([selected-sensitivity, 100, 0])
        upper_blue = np.array([selected+sensitivity, 255, 255])

        # Threshold the HSV image to get only selected colors
        # mask is already in threshold form
        mask = cv.inRange(converted_frame, lower_blue, upper_blue)

        # find contours
        contours, hierarchy = cv.findContours(mask, cv.RETR_EXTERNAL, cv.CHAIN_APPROX_SIMPLE)
        
        # create bounding box
        if (len(contours) > 0):
            cnt = contours[0]
            x, y, w, h = cv.boundingRect(cnt)
            cv.rectangle(frame, (x, y), (x+w, y+h), (0,255,0), 2)

        # Bitwise-AND mask and original image
        #res = cv.bitwise_and(frame,frame, mask=mask)
        cv.imshow('frame', frame)
        cv.imshow('mask', mask)
        #cv.imshow('res',res)
        k = cv.waitKey(5) & 0xFF
        if k == 27:
            break
    cv.destroyAllWindows()

def main():
    task4_1()


if __name__ == '__main__':
    main() 