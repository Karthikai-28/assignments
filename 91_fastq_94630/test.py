import Bio
import sys
import os
import random
import unittest
from Bio import Entrez
from Bio import ExPASy
from Bio import SeqIO
from Bio import SwissProt
from Bio.Seq import Seq
from Bio.SeqRecord import SeqRecord
from Bio.Alphabet import generic_rna, generic_dna, generic_protein
from Bio.Alphabet import IUPAC
from Bio.Blast import NCBIWWW
from Bio.Blast import NCBIXML
from Bio import SeqIO

from collections import Counter
import matplotlib as mp1
import re
from numpy import *
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import math

#creating DNA class and defining DNA characteristics of the DNA 
class DNA:
    def __init__(self, filename, start=3):
        self.type = "DNA"
        self.header = ""
        self.genomeseq = ""
        self.genome_seq_len=0
        self.start = 3
        self.direction(start)
        self.read_FASTA(filename)

    def read_FASTA(self,filename):
        with open(filename) as f:
            fast = f.read()
            for genome in fast.split(">")[1:]:
                self.header, self.genomeseq = genome.splitlines()[0], "".join(genome.splitlines()[1:])
                self.genome_seq_len = len(self.genomeseq)
        #print(self.genomeseq)

    def direction(self, start):
        if start == 3:
            self.start, self.finish = 3, 5
        elif start == 5:
            self.start, self.finish = 5, 3


    def c_gc_skewness(self, piece_seq_len=50):
        # counts = Counter(genomeseq)
        list = [0]
        for i in range(0, self.genome_seq_len, piece_seq_len):
            genome = self.genomeseq[i:i + piece_seq_len]
            counts_Genome = Counter(genome)
            G, C = counts_Genome["G"], counts_Genome["C"]
            try:
                sGC = (G - C) / (G + C)
            except ZeroDivisionError:
                sGC = 0
                # print("sGC:",sGC,"last value",list[-1])
                # print(genome," number of G= ",G," number of C = ",C,"gc shift: ",sGC)
            liste.append((list[-1] + sGC))
            # print(genome,"number of G= ",G," number of C= ",C,"gc shift: ",sGC)
        plt.plot(range(0, len(list)), list)
        plt.show()

    def c_at_skewness(self, piece_seq_len=50):
        # counts = Counter(genomeseq)
        list = [0]
        for i in range(0, self.genome_seq_len, piece_seq_len):
            genome = self.genomeseq[i:i + piece_seq_len]
            countsGenome = Counter(genome)
            A, T = countsGenome["A"], countsGenome["T"]
            try:
                sAT = (A - T) / (A + T)
            except ZeroDivisionError:
                sAT = 0
                # print("sGC:",sGC,"son eleman",list[-1])
                # print(genome," number of G= ",G," number of C= ",C,"gc shift: ",sGC)
            liste.append((liste[-1] + sAT))
            # print(genome," number of G= ",G," number of C = ",C,"gc shift: ",sGC)

        plt.plot(range(0, len(list)), list)
        plt.show()


#it will be demonstrated as a 3D graph
    def Zcurved(self):
        listx, listy, listz = [], [], []
        A, T, G, C = 0, 0, 0, 0
        # count=0
        for i in self.genomeseq:
            if i == "A":
                A = A + 1
            elif i == "T":
                T = T + 1
            elif i == "G":
                G = G + 1
            elif i == "C":
                C = C + 1
            """count=count+1
            if count==10:
                break"""
            listx.append((A + G) - (C + T))
            listy.append((A + C) - (G + T))
            listz.append((A + T) - (G + C))
        mpl.rcParams['legend.fontsize'] = 10
        fig = plt.figure()
        ax = fig.gca(projection='3d')
        ax.plot(listx, listy, listz)


        ax.set_xlabel('X Label')
        ax.set_ylabel('Y Label')
        ax.set_zlabel('Z Label')
        ax.legend()
        plt.show()
        # print("number of A : {}\nT : {}\nG : {}\nC : {}".format(A,T,G,C))
        # print(listx)

    def Point(self):
        pass



def gene_entropi(sequence):
    counts=Counter(sequence)
    A,T,G,C=counts["A"],counts["T"],counts["G"],counts["C"]
    print(A,T,G,C)
    try:
        A       =   (A/len(sequence))*(math.log(2,(A/len(sequence)/(1/4))))
        T       =   (T/len(sequence))*(math.log(2,(T/len(sequence)/(1/4))))
        G       =   (G/len(sequence))*(math.log(2,(G/len(sequence)/(1/4))))
        C       =   (C/len(sequence))*(math.log(2,(C/len(sequence)/(1/4))))
    except ZeroDivisionError:
        A       =   0
        G       =   0
        T       =   0
        C       =   0
    gene      =   A +  T
    print(gene)


def sequencealignment(align1,aling2):
    matris=zeros((len(aling1)+1,len(align2)+1))
    count              =   0

    for i in range(0,len(align2)+1):
        matris[0][i]        =   count
        count               =   count - 2
        count               =   0

    for i in range(0,len(align1)+1):
        matris[i][0] =   count
        count =   count - 2

    for i in matris:
        print(i)

    verticalAxis          =   ["X"]
    horizontalAxis           =   ["X"]
    for i in align1:
        verticalAxis.append(i)
    for i in align2:
        horizontalAxis.append(i)

    print(horizontalAxis)
    gap=-2
    match=5
    Mismatch=-5
    #print(len(verticalAxis))
    for i in range(1,len(horizontalAxis)):
        for j in range(1,len(verticalAxis)):
            if verticalAxis[j]    ==  horizontalAxis[i]:
                #print("this are: ",verticalAxis[j]," ",horizontalAxis[i])
                matris[j][i]    =   matris[j-1][i-1]    +   5
            else:
                leftTop          =   matris[j-1][i-1]    +   Mismatch
                top             =   matris[j-1][i]      +   gap
                left             =   matris[j][i-1]      +   gap
                if leftTop>top and leftTop>left:
                    matris[j][i]    =   leftTop
                elif top>leftTop and top>left:
                    matris[j][i]    =   top
                else:
                    matris[j][i]    =   left
    for i in matris:
        print(i)
		
print(Bio.__version__)		