// ============================================================================
// fs.c - user FileSytem API
// ============================================================================

#include "bfs.h"
#include "fs.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// ============================================================================
// Close the file currently open on file descriptor 'fd'.
// ============================================================================
i32 fsClose(i32 fd) { 
  i32 inum = bfsFdToInum(fd);
  bfsDerefOFT(inum);
  return 0; 
}



// ============================================================================
// Create the file called 'fname'.  Overwrite, if it already exsists.
// On success, return its file descriptor.  On failure, EFNF
// ============================================================================
i32 fsCreate(str fname) {
  i32 inum = bfsCreateFile(fname);
  if (inum == EFNF) return EFNF;
  return bfsInumToFd(inum);
}



// ============================================================================
// Format the BFS disk by initializing the SuperBlock, Inodes, Directory and 
// Freelist.  On succes, return 0.  On failure, abort
// ============================================================================
i32 fsFormat() {
  FILE* fp = fopen(BFSDISK, "w+b");
  if (fp == NULL) FATAL(EDISKCREATE);

  i32 ret = bfsInitSuper(fp);               // initialize Super block
  if (ret != 0) { fclose(fp); FATAL(ret); }

  ret = bfsInitInodes(fp);                  // initialize Inodes block
  if (ret != 0) { fclose(fp); FATAL(ret); }

  ret = bfsInitDir(fp);                     // initialize Dir block
  if (ret != 0) { fclose(fp); FATAL(ret); }

  ret = bfsInitFreeList();                  // initialize Freelist
  if (ret != 0) { fclose(fp); FATAL(ret); }

  fclose(fp);
  return 0;
}


// ============================================================================
// Mount the BFS disk.  It must already exist
// ============================================================================
i32 fsMount() {
  FILE* fp = fopen(BFSDISK, "rb");
  if (fp == NULL) FATAL(ENODISK);           // BFSDISK not found
  fclose(fp);
  return 0;
}



// ============================================================================
// Open the existing file called 'fname'.  On success, return its file 
// descriptor.  On failure, return EFNF
// ============================================================================
i32 fsOpen(str fname) {
  i32 inum = bfsLookupFile(fname);        // lookup 'fname' in Directory
  if (inum == EFNF) return EFNF;
  return bfsInumToFd(inum);
}



// ============================================================================
// Read 'numb' bytes of data from the cursor in the file currently fsOpen'd on
// File Descriptor 'fd' into 'buf'.  On success, return actual number of bytes
// read (may be less than 'numb' if we hit EOF).  On failure, abort
// ============================================================================
i32 fsRead(i32 fd, i32 numb, void* buf) {

  // ++++++++++++++++++++++++
  // Insert your code here
  // ++++++++++++++++++++++++
    if(numb <= 0) {
        FATAL(ENEGNUMB);
    }
    i32 size = fsSize(fd);
    //printf("size: %d\n", size);
    if(numb > size) {
        FATAL(EBIGNUMB);
    }
    i32 readBytes = 0;
    i32 cursor = fsTell(fd);
    //printf("cursor: %d\n", cursor);
    i32 inum = bfsFdToInum(fd);
    i32 offset = 0;
    i32 success = 0;
    //i32 blockCount = ;
    i32 dbn = 0;
    i32 fbn = 0;
    bool found = false;
    while(found != true) {      //get the current DBN block
        if(cursor == offset) {
          found = true;
          fbn = cursor / 512;
          //printf("fbn: %d\n", fbn);
        }
        offset++;
    }
    dbn = bfsFbnToDbn(inum, fbn);
    if(dbn == ENODBN) {
      FATAL(EBADDBN);
    }
    i8 bioBuf[BYTESPERBLOCK] = {0};
    success = bfsRead(inum, fbn, bioBuf);
    if(success != 0) {
      FATAL(EBADREAD);
    }
    //i32 start = cursor - (((fbn + 1) * 512) - 512);
    i32 start = cursor % 512;
    //printf("start: %d\n", start);
    for(int i = start; i < 512; i++) {      //read the curren DBN block
        *((i8 *)buf + readBytes) = bioBuf[i];
        //printf("read %d: %d\n", readBytes, bioBuf[i]);
        if(readBytes == numb - 1) {         //if the bytes needed to be read = numb, then return
          //printf("bytes: %d\n", readBytes);
          fsSeek(fd, readBytes + 1, SEEK_CUR);
          return readBytes + 1;
        }
        readBytes++;
    }
    cursor = cursor + readBytes;
    //printf("cursor: %d\n", cursor);
    while(readBytes < numb) {  //read the next DBN block
        fbn++;
        //printf("fbn: %d\n", fbn);
        dbn = bfsFbnToDbn(inum, fbn);
        if(dbn == ENODBN) {
          FATAL(EBADDBN);
        }
        //printf("dbn: %d\n", dbn);
        success = bfsRead(inum, fbn, bioBuf);
        if(success != 0) {
          FATAL(EBADREAD);
        }
        //i32 count = 0;
        //start = cursor - (((fbn + 1) * 512) - 512);
        start = cursor % 512;
        //printf("start: %d\n", start);
        for(int i = start; i < 512; i++) {
            *((i8 *)buf + readBytes) = bioBuf[i];
            //printf("read %d: %d\n", i, bioBuf[i]);
            if(cursor == size - 1) {
              //printf("bytes: %d\n", readBytes);
              fsSeek(fd, cursor + 1, SEEK_SET);
              //printf("cursor: %d\n", cursor + 1);
              //printf("size: %d\n", size);
              return readBytes + 1;
            }
            if(readBytes == numb - 1) {
                //printf("bytes: %d\n", readBytes);
                fsSeek(fd, cursor + 1, SEEK_SET);
                //printf("cursor: %d\n", cursor + 1);
                //printf("size: %d\n", size);
                return readBytes + 1;
            }
            readBytes++;
            cursor++;
        }
        //blockCount++;
    }
  //FATAL(ENYI);                                  // Not Yet Implemented!
  return 0;
}


// ============================================================================
// Move the cursor for the file currently open on File Descriptor 'fd' to the
// byte-offset 'offset'.  'whence' can be any of:
//
//  SEEK_SET : set cursor to 'offset'
//  SEEK_CUR : add 'offset' to the current cursor
//  SEEK_END : add 'offset' to the size of the file
//
// On success, return 0.  On failure, abort
// ============================================================================
i32 fsSeek(i32 fd, i32 offset, i32 whence) {

  if (offset < 0) FATAL(EBADCURS);
 
  i32 inum = bfsFdToInum(fd);
  i32 ofte = bfsFindOFTE(inum);
  
  switch(whence) {
    case SEEK_SET:
      g_oft[ofte].curs = offset;
      break;
    case SEEK_CUR:
      g_oft[ofte].curs += offset;
      break;
    case SEEK_END: {
        i32 end = fsSize(fd);
        g_oft[ofte].curs = end + offset;
        break;
      }
    default:
        FATAL(EBADWHENCE);
  }
  return 0;
}



// ============================================================================
// Return the cursor position for the file open on File Descriptor 'fd'
// ============================================================================
i32 fsTell(i32 fd) {
  return bfsTell(fd);
}



// ============================================================================
// Retrieve the current file size in bytes.  This depends on the highest offset
// written to the file, or the highest offset set with the fsSeek function.  On
// success, return the file size.  On failure, abort
// ============================================================================
i32 fsSize(i32 fd) {
  i32 inum = bfsFdToInum(fd);
  return bfsGetSize(inum);
}


// ============================================================================
// Write 'numb' bytes of data from 'buf' into the file currently fsOpen'd on
// filedescriptor 'fd'.  The write starts at the current file offset for the
// destination file.  On success, return 0.  On failure, abort
// ============================================================================
i32 fsWrite(i32 fd, i32 numb, void* buf) {

  // ++++++++++++++++++++++++
  // Insert your code here
  // ++++++++++++++++++++++++
    if(numb <= 0) {
        FATAL(ENEGNUMB);
        return ENEGNUMB;
    }
    i32 writeBytes = 0;
    i32 cursor = fsTell(fd);   //the cursor
    //printf("cursor: %d\n", cursor);
    i32 inum = bfsFdToInum(fd); //convert the fd to inum
    i32 size = fsSize(fd);
    //printf("size: %d\n", size);
    i32 fbn = 0;
    i32 dbn = 0;
    i8 bioBuf[BYTESPERBLOCK] = {0};
    i32 offset = 0;
    i32 byteLeft = 0;
    bool found = false;
    
    while(writeBytes < numb) {
      i32 count = 0;  //move the cursor
      if(size == 0) {
        bfsExtend(inum, fbn);
        dbn = bfsFbnToDbn(inum, fbn);
        //printf("dbn: %d\n", dbn);
        for(int i = 0; i < numb; i++) {
          bioBuf[i] = *((i8 *)buf + i);
          //printf("write %d: %d\n", i, bioBuf[i]);
          if(writeBytes == numb - 1) {
            bioWrite(dbn, bioBuf);
            fsSeek(fd, numb, SEEK_SET);
            bfsSetSize(inum, numb);
            return 0;
          }
          writeBytes++;
        }
        bioWrite(dbn, bioBuf);
        fsSeek(fd, numb, SEEK_SET);
        bfsSetSize(inum, numb);
        size = numb;
      } else {
        while(found != true) {
          if(cursor == offset) {  //find the FBN
            fbn = cursor / 512;
            //printf("fbn: %d\n", fbn);
            found = true;
          }
          offset++;
        }
        dbn = bfsFbnToDbn(inum, fbn);
        if(dbn == ENODBN) {
          dbn = bfsAllocBlock(inum, fbn);
        }
        //printf("dbn: %d\n", dbn);
        //if cursor != the start of the current block
        if(cursor != (((fbn + 1) * 512) - 512)) {
          bfsRead(inum, fbn, bioBuf);
          //i32 start = cursor - (((fbn + 1) * 512) - 512);
          i32 start = cursor % 512;
          //printf("start: %d\n", start);
          for(int i = start; i < 512; i++) {
            bioBuf[i] = *((i8 *)buf + writeBytes);
            //printf("write %d: %d\n", writeBytes, bioBuf[i]);
            if(writeBytes == numb - 1) {
              bioWrite(dbn, bioBuf);
              fsSeek(fd, cursor + 1, SEEK_SET);
              cursor++;
              //printf("cursor: %d\n", cursor);
              if(cursor > size) {
                //printf("cursor: %d\n", cursor);
                bfsSetSize(inum, cursor);
                size = fsSize(fd);
                //printf("size: %d\n", size);
              }
              return 0;
            }
            //count++;
            cursor++;
            writeBytes++;
          }
          //fsSeek(fd, cursor + writeBytes, SEEK_SET);
          bioWrite(dbn, bioBuf);
          byteLeft = numb - writeBytes;
          //printf("byte left: %d\n", byteLeft);
          fbn++;
          //printf("fbn: %d\n", fbn);
          //cursor = cursor + count;
          //printf("cursor: %d\n", cursor);
          if(cursor > size) {
            bfsSetSize(inum, cursor);
            size = fsSize(fd);
            //printf("size: %d\n", size);
          }
        } else {
          if(byteLeft < 512) {
            bfsRead(inum, fbn, bioBuf);
          }
          for(int i = 0; i < 512; i++) {
            bioBuf[i] = *((i8 *)buf + writeBytes);
            //printf("write %d: %d\n", writeBytes, bioBuf[i]);
            if(writeBytes == numb - 1) {
              bioWrite(dbn, bioBuf);
              fsSeek(fd, cursor + 1, SEEK_SET);
              cursor++;
              //printf("cursor: %d\n", cursor);
              if(cursor > size) {
                //printf("cursor: %d\n", cursor);
                bfsSetSize(inum, cursor);
                size = fsSize(fd);
                //printf("size: %d\n", size);
              }
              return 0;
            }
            writeBytes++;
            //count++;
            cursor++;
          }
          //fsSeek(fd, cursor)
          bioWrite(dbn, bioBuf);
          byteLeft = numb - writeBytes;
          //printf("byte left: %d\n", byteLeft);
          fbn++;
          //printf("fbn: %d\n", fbn);
          //cursor = cursor + count;
          //printf("cursor: %d\n", cursor);
          if(cursor > size) {
            bfsSetSize(inum, cursor);
            size = fsSize(fd);
            //printf("size: %d\n", size);
          }
        }
      }
    }
    
  //FATAL(ENYI);                                  // Not Yet Implemented!
  return 0;
}
