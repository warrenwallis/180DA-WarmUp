'''
This code below utilizes code from the following sources:
    - opencv
    - https://code.likeagirl.io/finding-dominant-colour-on-an-image-b4e075f98097
        - changed number of clusters
'''



import numpy as np
import cv2 as cv
from matplotlib import pyplot as plt
from sklearn.cluster import KMeans

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

def task4_4():
    def find_histogram(clt):
        """
        create a histogram with k clusters
        :param: clt
        :return:hist
        """
        numLabels = np.arange(0, len(np.unique(clt.labels_)) + 1)
        (hist, _) = np.histogram(clt.labels_, bins=numLabels)

        hist = hist.astype("float")
        hist /= hist.sum()

        return hist

    def plot_colors2(hist, centroids):
        bar = np.zeros((50, 300, 3), dtype="uint8")
        startX = 0

        for (percent, color) in zip(hist, centroids):
            # plot the relative percentage of each cluster
            endX = startX + (percent * 300)
            cv.rectangle(bar, (int(startX), 0), (int(endX), 50),
                        color.astype("uint8").tolist(), -1)
            startX = endX

        # return the bar chart
        return bar

    cap = cv.VideoCapture(0)
    x_start, x_end, y_start, y_end = 850, 1050, 450, 650
    start_point, end_point, thickness = (x_start, y_start), (x_end, y_end), 4
    red, green, blue = 0, 0, 0
    while(1):
        # Take each frame
        _, frame = cap.read()

        # Convert BGR to wanted color
        converted_frame = cv.cvtColor(frame, cv.COLOR_BGR2RGB)
        cv.rectangle(frame, start_point, end_point, (red, green, blue), 2)
        crop_frame = converted_frame[y_start:y_end, x_start:x_end]
        # reshape image
        #reshaped_frame = converted_frame.reshape((frame.shape[0]*frame.shape[1],3))
        reshaped_frame = crop_frame.reshape((crop_frame.shape[0]*crop_frame.shape[1],3))

        # create ML algorithm
        clt = KMeans(n_clusters=1)
        clt.fit(reshaped_frame)

        cv.imshow('frame', frame)
        cv.imshow('crop', crop_frame)
        hist = find_histogram(clt)
        bar = plot_colors2(hist, clt.cluster_centers_)

        # clt.cluster_centers_[0] should be our color
        
        plt.axis("off")
        plt.imshow(bar)
        plt.show()

        k = cv.waitKey(5) & 0xFF
        if k == 27:
            break
    cv.destroyAllWindows()

def main():
    task4_4()


if __name__ == '__main__':
    main() 