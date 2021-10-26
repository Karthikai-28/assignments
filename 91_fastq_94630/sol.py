# Fasta file which is downloaded is printed on the screen with using below code.  

seq=raw_input('Enter FASTA seq. file name:')
fh = open(seq,'r')
#line=fh.read()
#print line
line = fh.readline()
meta = ''
sequence=''
while line:
    line=line.rstrip('/n')
    if '>' in line:
        meta=line
    else:
        sequence=sequence+line
    line=fh.readline()
print meta
print sequence


# Everything that Bio.SeqIO can be read.

from Bio import SeqIO
human, mouse, rat, the other organisms = tuple(SeqIO.parse("example.fasta", "fasta"))

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

## uniprot and CACNA1E_human
# The code which is below provides all records about CACNA1E_human gene with parses certain Unıprot entries via Biopython module.

from Bio import SeqIO
import urllib
handle = urllib.urlopen("http://www.uniprot.org/uniprot/Q15878.xml")
record = SeqIO.read(handle, "uniprot-xml")
print(record)
print(record.name)

# output results to file
for seq_record in SeqIO.parse("Q15878.fasta", "fasta"):
    print(seq_record.id)
    print(repr(seq_record.seq))
    print(len(seq_record))	
	
	
# Also, rather than downloading files and then parsing them into Python, 
# you can programmatically access sequence files via Entrez using GI numbers:

from Bio import Entrez
from Bio import SeqIO
Entrez.email = "s.ozaydin@newcastle.ac.uk"
handle = Entrez.efetch(db="nucleotide", rettype="gb", retmode="text", id="Q15878")
seq_record = SeqIO.read(handle, "gb")
handle.close()
seq_record

## alignment
from Bio.Align.Applications import ClustalwCommandline
# create bash command
cline = ClustalwCommandline("clustalw", infile="Q15878.fasta")
print(cline)
# execute clustalw
stdout, stderr = cline()


## merge two fasta files
files = ['Q15878.fasta', 'Q1234.fasta']
with open('Q1234.fasta', 'w') as outfile:
    for name in files:
        with open(name) as infile:
            outfile.write(infile.read())
            outfile.write('\n')

from Bio.Align.Applications import ClustalwCommandline
from Bio.Align.Applications import MuscleCommandline
from io import StringIO
from Bio import AlignIO
cline = ClustalwCommandline("clustalw", infile="Q1234.fasta")
cline()

from Bio import AlignIO
alignment = AlignIO.read("Q15878.sth", "stockholm")
print("Alignment length %i" % alignment.get_alignment_length())
# Alignment length 50
for record in alignment:
    print("%s - %s" % (record.seq, record.id))

print(Bio.__version__)
	
	
	
	
	
	