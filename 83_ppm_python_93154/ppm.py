##################################################################
'''
A module for loading and displaying PPM-P3 files using Python 2.7.6

To use you must call and which returns to a variable
wn=PPM_set_up()

following this, you may use the class methods which reads an input PPM-P3 file in the constructor.
It never writes to the input file, instead creating two output files with
"-asc" and "-bin" respectively appended to the input filename.
These are intended for the user's use and to display respectively.

to render the image windows call:
PPM_render(wn) # needed to render all of the images you have instantiated where the argument is that which
was returned from PPM_set_up()

# The image data is stored in the following member variables:
self.magic
self.width
self.height
self.colormax
self.pixellist
# Update all of the above which change after manipulating image data.

# Constructor usage:
df=PPM()
df=PPM("bc-flowers.ppm")

# Display image:
df.PPM_display()

# Change image by changing pixellist:
bc.PPM_updatefrompixellist(mylist)

# Written by Dr. Jan Pearce, Berea College

# Attributions:
    # Ben Stephenson: http://pages.cpsc.ucalgary.ca/~jacobs/Courses/cpsc217/W10/code/Topic7/ppm.py
    # working from a class: http://bytes.com/topic/python/answers/520360-trouble-displaying-image-tkinter
# You also need to acknowledge having modifed this code and all other code you modify or use for assitance.
#   To do so, you will indicate something like:
#   Mopidied from code written by Dr. Jan Pearce
#   Original code downloaded from:
#   http://cs.berea.edu/csc226/tasks/yourusername-A15.py and
#   http://cs.berea.edu/csc226/tasks/ppm.py
'''
##################################################################
import sys
import Tkinter as tk   # for display of the PPM image
import copy

# This section represents helper functions which are needed by the PPM class.
global tkintertoggle  # Needed as global to ensure a single Tkinter instance
tkintertoggle=False

def PPM_set_up(): # This must be called at the beginning of any program which uses the PPM class
    '''Sets up the Tkinter root instance which allows for image windows'''
    master = tk.Tk()
    return master # save and send to all PPM methods which need it, including the initializer

def PPM_render(master):
    '''renders all PPM instances'''
    master.mainloop()

class PPM_Exception(Exception):
    '''Create a Python class to enable meaningful error messages on exceptions.'''
    def __init__(self, value):
        self.value = value
    def __str__(self):
        return repr(self.value) # allows a meaningful error message to be displayed

class PPM:
    '''Class which can be used to open, close, and display PPM P3 (ASCII) files.'''

    def __init__(self, master, inasciifile="group.ppm"):
        """ Opens or creates a PPM P3 file named inasciifile to construct a PPM object"""
        PPMDEFAULT='''P3
# Created by OOM class, by Dr. Jan Pearce, Berea College
8 10
255
140 140 140 120 120 120 100 100 100 80 80 80 60 60 60 40 40 40 20 20 20 0 0 0
120 120 120 63 72 204 63 72 204 63 72 204 63 72 204 252 252 255 255 255 255 15 15 15
105 105 105 255 255 255 63 72 204 255 255 255 63 72 204 255 255 255 255 255 255 30 30 30
90 90 90 255 255 255 63 72 204 63 72 204 63 72 204 255 255 255 255 255 255 45 45 45
75 75 75 255 255 255 63 72 204 255 255 255 63 72 204 63 72 204 63 72 204 60 60 60
60 60 60 63 72 204 63 72 204 63 72 204 63 72 204 255 255 255 63 72 204 75 75 75
45 45 45 255 255 255 255 255 255 63 72 204 255 255 255 254 254 254 255 255 255 90 90 90
30 30 30 255 255 255 255 255 255 63 72 204 255 255 255 255 255 255 63 72 204 105 105 105
15 15 15 252 252 253 255 255 255 63 72 204 63 72 204 63 72 204 63 72 204 120 120 120
0 0 0 20 20 20 40 40 40 60 60 60 80 80 80 100 100 100 120 120 120 140 140 140
'''
        self.root = master
        self.root.title("PPM Quit")
        global tkintertoggle # This must be global to allow multiple PPM objects but make only a single Quit button on the Tkinter canvas.
        if tkintertoggle == False:
            tk.Button(self.root, text="QUIT", fg="red", command=self.root.quit).pack()
            tkintertoggle = True
        if inasciifile == "": # makes default.ppm as input file if none exists
            inasciifile="default.ppm"
        self.inasciifile=inasciifile # This file is used only for reading
        self.outasciifile=inasciifile[:-4]+"-asc.ppm" # created to store modifications
        self.outbinfile=inasciifile[:-4]+"-bin.ppm"  # binary ppm filename needed for viewing
        self.title=inasciifile # used for the title of the display window
        self.magic="P3" # ppm file type
        self.comment="# Created by ppm-class, by Dr. Jan Pearce\n"
        self.width=0
        self.height=0
        self.colormax=255 #should be set to 255
        self.ascii="" # will store the color intensities in P3 format
        self.pixellist = [] # will store nested list containing pixel colors
        self.image="" # It is necessary that this be a member variable for Tk to display image correctly
        # if there is no filename given, make a file to work with
        self.label="" # used to place image in window
        if self.inasciifile=="default.ppm" :
            self.ascii = PPMDEFAULT
            tmpfile = open(self.inasciifile, "w")
            tmpfile.write(self.ascii)
            tmpfile.close()
        print("PPM object created from "+self.inasciifile)
        self.PPM_makeoutputfiles() # makes ascii and binary output files

    def PPM_makeoutputfiles(self):
        '''given self.inasciifile, sets self.ascii and creates both ascii and binary files for output'''
        outtmpfile = open(self.outasciifile, "w")
        intempfile = open(self.inasciifile, 'r') # self.inasciifile must have data
        self.ascii = intempfile.read()
        outtmpfile.write(self.ascii)
        intempfile.close()
        outtmpfile.close()
        self.PPM_load(self.inasciifile)
        self.PPM_convert2bin()

    def PPM_partition(self,strng,ch):
        '''Given input parameters: strng, the string to partition and ch, the character to use as the delimiter
            Returns a triple with all characters before the delimiter, the delimiter iteself if present
            and all of the characters after the delimiter (if any)'''
        if (ch in strng):
            i = strng.index(ch)
            return (strng[0:i],strng[i],strng[i+1:])
        else:
            return (strng,None,None)

    def PPM_clean(self,strng):
        '''removes all singleline comments present in the input parameter string strng
        Returns a string with all characters after the comment character removed.
        All white space at the end is also removed, including the newline and linefeed characters.'''
        (retval,junk1,junk2) = self.PPM_partition(strng,"#")
        return retval.rstrip(" \t\n\r")

    def PPM_load(self, inasciifile):
        '''input parameter inasciifile is a string containing the name of the file to load
        Assumes an ASCII PPM-P3 (non-binary) file.
        loads the named image file from disk, and stores the image data in member variables'''

      # Open the input file
        infile = open(self.inasciifile,"r")

      # Read the magic number out of the top of the file and verify that we are
      # reading from an ASCII PPM-P3 file
        tmpln=infile.readline()
        self.ascii+=tmpln
        self.magic = self.PPM_clean(tmpln)
        if (self.magic != "P3"):
            raise PPM_Exception, 'The file being loaded does not appear to be a valid ASCII PPM-P3 file'

      # Get the image dimensions
        tmpln=infile.readline()
        while tmpln[0]=='#': #dump full comment lines
            tmpln=infile.readline()
        self.ascii+=tmpln
        imgdimensions = self.PPM_clean(tmpln)

      #unpack dimensions
        (width, sep, height) = self.PPM_partition(imgdimensions," ")
        self.width=int(width)
        self.height=int(height)
        if (self.width <= 0) or (self.height <= 0):
            raise PPM_Exception, "The file being loaded does not appear to have valid dimensions (" + str(width) + " x " + str(height) + ")"

      # Get the maximum color value, which is assumed to be 255
        tmpln=infile.readline()
        self.ascii+=tmpln
        self.colormax = int(self.PPM_clean(tmpln))
        if (self.colormax != 255):
            sys.stderr.write("Warning: PPM file does not have a maximum intensity value of 255.  Image may not be handled correctly.")

      # Create a list of the color intensities
        color_list = [] # hold intensity data temporarily in a list of intensity strings
        for line in infile:
            self.ascii+=line
            line = self.PPM_clean(line)
            color_list += line.split(" ")
        infile.close()  # Close input file since done
        self.PPM_makepixellist(color_list) # Creates self.pixellist, a nested list of rows of [red, green, blue] pixels

    def PPM_makepixellist(self, color_list):
        '''Creates self.pixellist, a nested list of rows of [red, green, blue] pixels
        from a color_list which contains an unnested list of strings'''
        rcount=0
        gcount=1
        bcount=2
        self.pixellist = []
        for row in range(self.height):
            self.pixellist.append([])
            for col in range(self.width):
                self.pixellist[row].append([int(color_list[rcount]), int(color_list[gcount]), int(color_list[bcount])])
                rcount+=3 # move to next red
                gcount+=3  # move to next green
                bcount+=3  # move to next blue

    def PPM_updatefrompixellist(self, pixellist, title="from_pixellist"):
        '''Updates image object data and related files from input pixellist'''
        strout=""
        self.magic="P3"
        self.colormax=255
        self.width=len(pixellist[0])
        self.height=len(pixellist)
        header=self.magic+"\n"
        header+=self.comment
        header+=str(self.width) + " " + str(self.height)+"\n"+str(self.colormax)+"\n" # header is in ASCII
        for rowlist in pixellist:
            for pixel in rowlist:
                for color in pixel:
                    strout+=str(color)+" "
            strout+="\n"
        self.ascii=header+strout
        self.pixellist=pixellist
        tmpfile = open(self.outasciifile, "w")
        tmpfile.write(self.ascii)
        tmpfile.close() #close tmpfile when done
        print("PPM object changed based upon list.")
        if self.title=="default.ppm":
            self.title=title
        self.PPM_convert2bin()

    def PPM_convert2bin(self):
        '''Converts PPM-P3 to PPM-P6 using self.pixellist'''
        header="P6\n"
        header+=self.comment
        header+=str(self.width) + " " + str(self.height)+"\n"+"255\n" # header is in ASCII
        strout=""

        for rowlist in self.pixellist:
            for pixel in rowlist:
                for color in pixel:
                    strout+=chr(color) # Python 2 uses strings to handle binary data, chr() converts the integer to a one-byte string.

        strout=header+strout+'\n'
        tmpfile = open(self.outbinfile, "wb")
        tmpfile.write(strout)
        tmpfile.close() #close tmpfile when done

    def PPM_set_title(self, title):
        '''setter for self.title (title of display window.)'''
        self.title=title

    def PPM_display(self):
        '''displays PPM-P3 binary file using Tkinter'''
        self.mywindow = tk.Toplevel(self.root)
        self.mywindow.geometry(str(self.width)+"x"+str(self.height)) # sets correct window size
        self.mywindow.wm_title(self.title)
        self.image = tk.PhotoImage(file=self.outbinfile) # needed for retaining image after call
        self.label = tk.Label(self.mywindow, image=self.image)
        self.label.place(x=0, y=0, height=self.height, width=self.width)

    def PPM_make_red(self):
        ''''colorizes current image to red by using self.pixellist'''
        newpixellist=self.pixellist
        self.width=len(newpixellist[0])
        self.height=len(newpixellist)
        row=0
        for rowlist in newpixellist:
            col=0
            for pixel in rowlist:
                newpixellist[row][col][1]=0 # update green
                newpixellist[row][col][2]=0 # update blue
                col+=1
            row+=1
        print(self.outasciifile+ " output file turned red.")
        self.PPM_updatefrompixellist(newpixellist) # This call will update all member attributes appropriately.

    def PPM_greyscale(self):
        ''''converts image to greyscale'''
        newpixellist=self.pixellist
        # Hint: What needs to be done here is to convert newpixellist to the equivalent greyscale image.
        # The final call to self.PPM_updatefrompixellist(newpixellist) is essential for updating member attribute appropriately.

        # TODO FIX ME: write the needed changes to newpixellist here

        self.PPM_updatefrompixellist(newpixellist) # This call will update all member apttributes appropriately.

    def PPM_flip_horizontal(self):
        ''''flips image horizontally'''
        newpixellist=self.pixellist
        # Hint 1: What needs to be done here is to convert newpixellist to the equivalent horizontally flipped image.
        # Hint 2: You might want a new file of the correct size or a deep copy.
        # The final call to self.PPM_updatefrompixellist(newpixellist) is essential for updating member attribute appropriately.

        # TODO FIX ME: write the needed changes to newpixellist here

        self.PPM_updatefrompixellist(newpixellist) # This call will update all member apttributes appropriately.

    def PPM_rotateclockwise(self):
        ''''roates image clockwise'''
        newpixellist=self.pixellist
        # Hint 1: What needs to be done here is to convert newpixellist to the equivalent rotated image.
        # Hint 2: It might be helpful to make a new file of the correct size
        # The final call to self.PPM_updatefrompixellist(newpixellist) is essential for updating member attribute appropriately.

        # TODO FIX ME: write the needed changes to newpixellist here

        self.PPM_updatefrompixellist(newpixellist) # This call will update all member attributes appropriately.

    # TODO FIX ME: write at least two additional PPM class methods

    ################# end of class ##############

# See yourusername-L3-ppm.py for code that uses the PPM class.