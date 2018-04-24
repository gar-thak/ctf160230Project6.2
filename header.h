#ifndef HEADER_H
#define HEADER_H

/*
 * Colton Farlow ctf160230@utdallas.edu
 * 3377.501
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdint.h>
#include <list>
#include <string>
#include <sstream>

using namespace std;


class BinaryFileHeader
{
 public:
  
  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
  string intToHex(uint32_t);
  string getMagicNumTitle();
  string getVersionNumTitle();
  string getNumRecordsTitle();
};


const int maxRecordStringLength = 25;

class BinaryFileRecord
{
 public:
  
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
  string getStrLengthTitle();

};

class BinaryFile
{
 public:
  
  ~BinaryFile();
  BinaryFileHeader header;
  list<BinaryFileRecord> records;

  int readFile(string fileName);

};


string BinaryFileHeader::getMagicNumTitle() {
  string returnstr = "Magic: ";
  returnstr += intToHex(magicNumber);
  return returnstr;
}
string BinaryFileHeader::getVersionNumTitle() {
  stringstream stream;
  stream << "Version: " << versionNumber;
  return stream.str();
}
string BinaryFileHeader::getNumRecordsTitle() {
  stringstream stream;
  stream << "NumRecords: " << numRecords;
  return stream.str();
}
// Function to convert to hex
string BinaryFileHeader::intToHex(uint32_t value) {
  stringstream stream;
  stream << "0x" << setfill('0') << setw(sizeof(uint32_t)*2) << hex << value;
  return stream.str();
}
// Function for string length for first column
string BinaryFileRecord::getStrLengthTitle() {
  stringstream stream;
  stream << "strlen: " << unsigned(strLength);
  return stream.str();
  
}
// Destructor.
BinaryFile::~BinaryFile(){
  records.clear();
}

int BinaryFile::readFile(string fileName) {
  
  ifstream binInfile(fileName.c_str(), ios::in | ios::binary);
  if(binInfile.is_open()){
    
  }else{
   
  }
  binInfile.read((char *) &header, sizeof(BinaryFileHeader));
  // Reading size of to give back the stringlength.
  if(header.magicNumber != 0){
    while(!binInfile.eof()) {
      BinaryFileRecord record;
      binInfile.read((char *) &record, sizeof(BinaryFileRecord));
      if(binInfile.gcount() > 0) {
	records.push_back(record);
      }
      else {
	break;
      }
    }
  }
  
  else{
    header.magicNumber = 0xEEEEEEEE;
  }
  // Closing file.
  binInfile.close();
  
  return 0;
  
}

#endif
