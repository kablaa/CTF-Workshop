[![hackucf logo](https://github.com/kablaa/CTF-Workshop/blob/master/HackUCF.png)](http://www.hackucf.org)

# Sunshine CTF: Get Gud Kid Writeup

## Requirements
For this challenge, all that is required is a hex editor and the ability to unzip files. For this writeup, we will be using 010 Editor and it's templating capabilities.

## Walkthrough

### Recon
Initially, we are given a binary called `get_gud_kid.dat`. Taking a look at the file, we can see that it has the header `FIF`, which may exist, it may not. However, doing some googling, the format does not match any known format. Therefore we can begin looking to see if there is anything that can provide us clues to start working. Running the find strings tool in 010 editor, we can see that we have a large amount of strings found. However, there are some notable ones at the very beginning of the file:

![strings output screenshot](https://github.com/kablaa/CTF-Workshop/blob/restructure_repository/Forensics/Writeups/UndocumentedFormats/GetGudKid/strings_output.PNG)

We can see that we have `cat1.jpg.zip` to `cat7.jpg.zip` listed at the top. Therefore we can assume that we have 7 files that have entries within this dat file.

Looking further past the header, we can see that there are several zip files contained in the dat file (denoted by the PK header). All of these seem to have appropriate filenames inside of them when comparing to the dat header entries (`cat1.jpg.zip` in the dat file header => `cat1.jpg` in the zip file). However, once we have this, there is no more overly useful information, as the rest seems to be zip file data.

### Header
To continue working on analyzing the file, we have to begin working on the header format. We can use 010 for this, and use some resizing to recognize the patterns (looking for pattern alignments). Resizing the width of the hex view will allow us do see some initial patterns in the header, and start looking at the values within it:

![header alignment](https://github.com/kablaa/CTF-Workshop/blob/restructure_repository/Forensics/Writeups/UndocumentedFormats/GetGudKid/header_entry_alignment_no_color.PNG)

Looking at this, we can see clear a clear pattern between what appear to be the entries for what the dat file contains. However, we don't know what the values are. This is ok, we can add bookmarks for each header entry and add a color so we can begin analyzing the values of each header entry:

![header alignment with highlighting](https://github.com/kablaa/CTF-Workshop/blob/restructure_repository/Forensics/Writeups/UndocumentedFormats/GetGudKid/header_entry_alignment.PNG)

(You can see in red that there is extra stuff past the file signature, so we note that and move on)

#### Header entry
To begin working on each header entry, we can look at the differences between each of the header entries we have, as well as their similarities. To begin, we need to find out how the filenames are being read. Keeping in mind that a computer would actually need to be able to read this in, it must have some way of determining what to read in and when. Therefore, for a filename, we either need to have a null byte at the end of the end of the filename (which we dont have) or we need to have a length to specify the filename. Therefore, looking at the length of the first entry's filename, we can start to look for a value. Counting the characters of the first entry's filename, we can see that it has a length of 12. Therefore, we are looking for a value within this entry that equals 12. Looking for this, we come across `0C 00 00 00` directly before the filename. Using this, we can begin to piece together the start of an 010template for this file, so we might as well make one so we can check our work:

```c
typedef struct {
  char sig[3];
  char unk1[8];
} Header <optimize=false>;

typedef struct {
  // we dont know what these attributes are yet
  DWORD unk1;
  DWORD unk2;
  // but we know these
  DWORD fileNameLength;
  char fileName[fileNameLength];
} HeaderEntry <optimize=false>;

// go ahead and instantiate so we can test on our file.
Header hdr;
// we know there are 7 entries, so manually hardcode this for now.
HeaderEntry hdrEntries[7];
```

Using this we can see that the entries fit, and all of the filenames are captured within the template properly, so we have the beginning of the header entry format. Now we need to make sense of the unknown attributes in both of the structures we just defined.

Looking at the unknown attributes in the `Header` struct first, we can see that there are two 4 byte sequences: `07 00 00 00` and `B3 00 00 00`. Because we know that there are 7 files contained within this dat file, we can assume that the `07 00 00 00` is a `DWORD` indicating that there are 7 header entries. Finally, to figure out what the last value is, we can search for it in the file first, and see if it is a repeating value elsewhere. However, this yields nothing, so we can go ahead and check if it is an offset. As it turns out, this is an offset for the beginning of the data section. It is also the end of the header entries -- so this makes sense. Therefore, our new `Header` structure would be defined as:

```c
typedef struct {
  char sig[3];
  DWORD numberOfFiles;
  DWORD dataStartOffset;
} Header <optimize=false>;
```

Next we need to make sense of the `HeaderEntry` unknown values. Now that we have filenames based on the filename lenghts, all that we are seemingly missing is information regarding the actual data entries. Since based on the `Header` structure we assume we know where the data starts, we can begin to infer information about the last two attributes in question for the `HeaderEntry` structure. The first `HeaderEntry` has `unk1=0` and `unk2=368575`. So if we assume that the data starts at `B3 00 00 00`, we can look at what each unknown value means. Since this is the first entry, we can assume that `0` is an offset, and `368575` is a length. To test this, we can select between offset `179 + 0` and `179 + 368575` (`368754`). From this we can see that it selects an entire zip file. To test this and verify what we are seeing is correct and not a coincidence, we can do this to the second `HeaderEntry`. After doing this, we can confirm what we are seeing, and our new `HeaderEntry` structure looks like:
```c
typedef struct {
  DWORD offset;
  DWORD length;
  DWORD fileNameLength;
  char fileName[fileNameLength];
} HeaderEntry <optimize=false>;
```

Finally, we have our complete structure for the header and its entries, so we can compile these two together. The following is a more beutified version of this template used when solving this challenge:

```c
typedef struct {
    char magic[3];
    int numberOfFiles;
    int dataChunkOffset;
} Header <optimize=false, bgcolor=cBlue>;

typedef struct {
    int offset;
    int length;
    int fileNameLength;
    char fileName[fileNameLength];

    local int curOffset = FTell();
    FSeek(hdr.dataChunkOffset + offset);
    SetBackColor(cGreen);
    char data[length];
    FSeek(curOffset);
} HeaderEntry <optimize=false, bgcolor=cRed, read=HeaderEntryRead>;

string HeaderEntryRead(HeaderEntry &f){
    string s;
    SPrintf(s, "File: %s; Start: %d; End: %d;", f.fileName, f.offset, f.offset + f.length);
    return s;
}

Header hdr;
HeaderEntry finfo[hdr.numberOfFiles];
```

### File Analysis
Now that we have the structure for the file, we can now begin to analyze what is actually inside of this file. We can see that we have the obvious cat images within zip files, and after taking a look at these, everything looks just fine with them. Looking past these zip files, we can see that there is data appended to the format we just found. Because of this, looking at the offset + lenghts was in order. After doing some checking on the data chucks our template caught, we can see that there are small sections at the end of each header entry that are skipped. Starting at the end of the first header entry, we can see that there is a `PK` zip file header in this section. Looking at each of the other skipped sections, it appears that it is the rest of this zip file. Therefore, we have to extract these sections and put them in their own file.

After doing this, we can see that there is a file in this zip file called `flagged.txt`. Upon extracting it and looking at the text file, we see that it is a base64 string. Upon decoding, we get
```python
Python 2.7.10 (default, May 23 2015, 09:44:00) [MSC v.1500 64 bit (AMD64)] on win32
Type "help", "copyright", "credits" or "license" for more information.
>>> "c3Vue2d1M3NzX3VfZzB0X2d1ZH0=".decode("base64")
'sun{gu3ss_u_g0t_gud}'
```
