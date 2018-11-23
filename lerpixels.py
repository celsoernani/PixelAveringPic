import serial
import numpy as np
import cv2
import array

def recebe_pixels():
    nPixels = 0
    pixel = ser.read(1)
    pixels = []
    totalPixelsEsperado = 2809
    print("Recebendo pixels")
    while nPixels < totalPixelsEsperado:
        pixel = ser.read(1)
        if(pixel != b'' ):
            nPixels += 1
            pixels.append(ord(pixel))
    print("Transferência concluída!")
    return pixels

def newimage(img, arraynew, size):
    aux = 0
    for i in range(0,size-1):
        for j in range(0,size-1):
            img[i, j] = int(arraynew[aux])
            aux = aux + 1
    return img

def cria_image(pixels):
    img = array.array('B')
    for i in range(2809):
        img.append(pixels[i])
    return img


ser = serial.Serial(port = "/dev/ttyUSB0", baudrate = 9600, timeout = 0)
pixels = recebe_pixels()
img = cria_image(pixels)
imageFile = open("NovaImagem.PGM","w")
imageFile.write("P5\n53 53 255\n")
imageFile = open("NovaImagem.PGM","ab")
img.tofile(imageFile)
print("Imagem .pgm P5 gerada com sucesso!")
imageFile.close()
size = 55
newsize = (size - 2)
sizes = (newsize, newsize)
matriznewimg = np.zeros(sizes)
newimagem = newimage(matriznewimg, pixels , newsize)
cv2.imwrite('imgred.png', newimagem)
cv2.imshow('imgred.png', newimagem)


print("Imagem reduzida em tons de cinza: ")
print(img)
