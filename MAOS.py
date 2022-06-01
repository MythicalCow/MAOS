import serial
import csv
import sys
import math
import random
import time
import pygame

# import cv2;

# # capture frames from a video
# cap = cv2.VideoCapture(0)
# ret, frames = cap.read()
# cv2.imshow("backup camera", frames)
# car_cascade = cv2.CascadeClassifier('cars.xml')

header_csv = ["YAW", "PITCH", "ROLL", "X_ACCELERATION"]

screen = pygame.display.set_mode([1000, 750])
pygame.init()
ser = serial.Serial('/dev/cu.usbserial-01BE27D0', 115200, timeout=1)
ser.flush()

with open('maos.csv', 'w', encoding='UTF8', newline='') as f:
    writer = csv.writer(f)
    Velocity = 0
    while True:

        if ser.in_waiting > 0:

            #Storing Drivers Data In CSV For Analyzing Later
            line = ser.readline().decode('utf-8').rstrip()
            line_list = line.split(" ")
            writer.writerow(line_list)

            #Extracting Data For Simulation
            YAW = float(line_list[0])
            # PITCH = float(line_list[1])
            # ROLL = float(line_list[2])
            DISTANCE = float(line_list[3])
            # Velocity += .250*X_ACCELERATION
            screen.fill((220,220,220))
            font = pygame.font.Font('/Users/raghav/Downloads/DM_Sans/DMSans-Bold.ttf',18)
            # text = font.render(f"Speed (m/s): {str(int(Velocity))}", True, "black")
            # textRect = text.get_rect()
            # textRect.center = 500//7, 500//50 
            # screen.blit(text, textRect)
            color = (156, 156, 156)
            if DISTANCE < 10.0 and DISTANCE > 0:
                color = (200, 20, 20)
                # ret, frames = cap.read()
                # cv2.imshow("backup camera", frames)
                # cv2.waitKey(0)
                # cv2.destroyAllWindows()
                time.sleep(0.5)
            pygame.draw.line(screen, color, (500, 400), (500+(150)*math.sin(math.radians(YAW)),400-(150)*math.cos(math.radians(YAW))),100)
            pygame.draw.line(screen, color, (500, 400), (500-(50)*math.sin(math.radians(YAW)),400+(50)*math.cos(math.radians(YAW))),100)
            pygame.display.flip()

            

            






            