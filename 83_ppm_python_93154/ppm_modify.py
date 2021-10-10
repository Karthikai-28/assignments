"""
C200 Homework Assignment 6 : ppm modify
Author: YOUR-NAME-HERE
Date: WHEN YOU COMPLETED IT
The goal of this assignment is to give you practice working with lists
by writing a program that manipulates image files in various ways.
"""
from math import sqrt
from random import randint
import sys
s=[]

def color_translate(inputfile, outputfile):
    try:
        ipfile = open(inputfile,'r')
        invfile = open(outputfile ,'w')
    except IOError:
       print ("Error: can\'t find file or read data "+inputfile)
       print ("Please enter valid file to read data. File doesn't exist!!!")
       sys.exit()
    else:
        for x in range(0, 3):
            invfile.write(ipfile.readline()) 
        for line in ipfile.readlines():
            linesplit=line.split()
            for word in linesplit:
                word = 255 - int(word)
                invfile.write(str(word))
                invfile.write(' ')
            invfile.write('\n')
        ipfile.close()
        invfile.close()
    pass

def process_ppm(in_filename, out_filename, filter):
    try:
        ipfile = open(in_filename,'r')
        flatfile = open(out_filename ,'w')
    except IOError:
       print ("Error: can\'t find file or read data "+in_filename)
       print ("Please enter valid file to read data. File doesn't exist!!!")
       sys.exit()
    else:
        for x in range(0, 3):
            flatfile.write(ipfile.readline()) 
        for line in ipfile.readlines():
            linesplit=line.split()
            for word in range(0,len(linesplit),3):
                for i in range(0, 3):
                    linesplit[word+filter] = 0
                    flatfile.write(str(linesplit[word+i]))
                    flatfile.write(' ')
            flatfile.write('\n')
        ipfile.close()
        flatfile.close()
    pass

def main_part1(inputfile,outputfile):
    flag='f'
    min=0
    try:
        ipfile = open(inputfile,'r')
        opfile = open(outputfile ,'w')
    except IOError:
       print ("Error: can\'t find file or read data "+inputfile)
       print ("Please enter valid file to read data. File doesn't exist!!!")
       exit()
    else:
        for x in range(0, 3):
            ipfile.readline()
        for line in ipfile.readlines():
            linesplit=line.split()        
            for word in range(0,len(linesplit)-1):
                if flag == 'f':
                    min=int(linesplit[word])
                    flag='t'
                if int(linesplit[word+1])<min:
                    min=int(linesplit[word+1])            
        mid=(min+255)/2
        ipfile = open(inputfile,'r')
        for x in range(0, 3):
            opfile.write(ipfile.readline())
        for line in ipfile.readlines():        
            linesplit=line.split() 
            for word in range(0,len(linesplit)):
                if int(linesplit[word])<=int(mid):
                    linesplit[word]=int(0)
                else:
                    linesplit[word]=int(255)            
                opfile.write(str(linesplit[word]))
                opfile.write(' ')
            opfile.write('\n')    
        ipfile.close()
        opfile.close()
    pass

def grey_scale(inputfile,outputfile):
    try:
        ipfile = open(inputfile,'r')
        grayfile = open(outputfile ,'w')
    except IOError:
       print ("Error: can\'t find file or read data "+inputfile)
       print ("Please enter valid file to read data. File doesn't exist!!!")
       sys.exit()
    else:
        for x in range(0, 3):
            grayfile.write(ipfile.readline()) 
        for line in ipfile.readlines():
            linesplit=line.split()
            for word in range(0,len(linesplit),3):
                mean = (int(linesplit[word]) + int(linesplit[word+1]) + int(linesplit[word+2]))/3
                for i in range(0, 3):
                    linesplit[word+i] = int(mean)
                    grayfile.write(str(linesplit[word+i]))
                    grayfile.write(' ')
            grayfile.write('\n')
        ipfile.close()
        grayfile.close()
        
    pass

def rnoise_ppmimage(inputfile,outputfile):  
    try:
        ipfile = open(inputfile,'r')
        noisefile = open(outputfile ,'w')
    except IOError:
       print ("Error: can\'t find file or read data "+inputfile)
       print ("Please enter valid file to read data. File doesn't exist!!!")
       sys.exit()
    else:
        for x in range(0, 3):
            noisefile.write(ipfile.readline()) 
        for line in ipfile.readlines():
            linesplit=line.split()
            for word in range(0,len(linesplit)):
                linesplit[word]=int(linesplit[word])+randint(0,50)
                noisefile.write(str(linesplit[word]))
                noisefile.write(' ')
            noisefile.write('\n')
        ipfile.close()
        noisefile.close()

def main():
    inputfile= input('Enter name of image file you need to add filters:')
    try:
        ipfile = open(inputfile,'r')        
    except IOError:
       print ("Error: can\'t find file or read data "+inputfile)
       print ("Please enter valid file to read data. File doesn't exist!!!")
       sys.exit()
    else:
        c=0    
        while(True):
            c=c+1
            print ('1.Convert to greyscale')
            print ('2.Invert image colors')
            print ('3.Flatten red')
            print ('4.Flatten green')
            print ('5.Flatten blue')
            print ('6.Extreme contrast')
            print ('7.Random Noise')
            print ('press 0 to exit')
            if c>1:            
                inputfile=filterfile
            filterfile="outputfilter"
            filterfile=filterfile+str(c)
            filterfile=filterfile+".ppm"                
            option= input('Enter your option:')        
            if(option=='1'):
                grey_scale(inputfile,filterfile)
                print('Your ppm image now is in grayscale.The output is in '+filterfile)
            elif(option=='2'):
                color_translate(inputfile,filterfile)
                print('Your ppm image now is inverted.The output is in '+filterfile)
            elif(option=='3'):
                process_ppm(inputfile,filterfile,0)
                print('Your ppm image now is flattened red.The output is in '+filterfile)
            elif(option=='4'):
                process_ppm(inputfile,filterfile,1)
                print('Your ppm image now is flattened green.The output is in '+filterfile)
            elif(option=='5'):
                process_ppm(inputfile,filterfile,2)
                print('Your ppm image now is flattened blue.The output is in '+filterfile)
            elif(option=='6'):
                main_part1(inputfile,filterfile)
                print('Your ppm image now has extreme contrast.The output is in '+filterfile)
            elif(option=='7'):
                rnoise_ppmimage(inputfile,filterfile)
                print('Your ppm image now has been exposed some random noise.The output is in '+filterfile)        
            elif(option=='0'):
                sys.exit()
            print(" ")
            input1= input("Press any key to continue!")
    pass

if __name__ == '__main__':
    # main_part1() # comment this out after you check-in for part 1
    main() # uncomment this after you check-in for part 1