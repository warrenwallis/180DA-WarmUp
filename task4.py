import numpy as np
import cv2 as cv
from matplotlib import pyplot as plt
import time

# possible color choices: cv.COLOR_BGR2GRAY, cv.COLOR_BGR2HSV, cv.COLOR_BGR2RGB

def task4_1(color_chosen = cv.COLOR_BGR2RGB):
    cap = cv.VideoCapture(0)
    counter = 0

    while(True):
        # Capture frame-by-frame
        ret, frame = cap.read()

        # Our operations on the frame come here
        color = cv.cvtColor(frame, color_chosen)

        # thresholding
        ret,thresh1 = cv.threshold(color,counter,255,cv.THRESH_BINARY_INV)

        # Display the resulting frame
        #cv.imshow('frame', color)
        plt.title(counter)
        plt.imshow(thresh1, 'gray', vmin=0, vmax=255)
        plt.show()
        counter += 15
        if (cv.waitKey(1) & 0xFF == ord('q')) or counter >= 255:
            break

    # When everything done, release the capture
    cap.release()
    cv.destroyAllWindows()

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