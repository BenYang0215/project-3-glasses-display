#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "GlassesDisplay.hpp"

using std::string;
using std::ifstream;
using std::cout;
using std::endl;

// function to return the hash value based on the first digit
unsigned int hashfct1(unsigned int barcode) {
  return (barcode / 1000000) % 10;
}

// function to return the hash value based on the second digit
unsigned int hashfct2(unsigned int barcode) {
  return (barcode / 100000) % 10;
}

// function to return the hash value based on the third digit
unsigned int hashfct3(unsigned int barcode) {
  return (barcode / 10000) % 10;
}

// function to return the hash value based on the fourth digit
unsigned int hashfct4(unsigned int barcode) {
  return (barcode / 1000) % 10;
}

// function to return the hash value based on the fifth digit
unsigned int hashfct5(unsigned int barcode) {
  return (barcode / 100) % 10;
}

// function to return the hash value based on the sixth digit
unsigned int hashfct6(unsigned int barcode) {
  return (barcode / 10) % 10;
}

// function to return the hash value based on the seventh digit
unsigned int hashfct7(unsigned int barcode) {
  return barcode % 10;
}


// Constructor for struct Item
Glasses::Glasses(string glassesColor, string glassesShape, string glassesBrand, unsigned int barcode): glassesColor_(glassesColor), glassesShape_(glassesShape), glassesBrand_(glassesBrand), barcode_(barcode)
{};

// Load information from a text file with the given filename
// THIS FUNCTION IS COMPLETE
void GlassesDisplay::readTextfile(string filename) {
  ifstream myfile(filename);

  if (myfile.is_open()) {
    cout << "Successfully opened file " << filename << endl;
    string glassesColor;
    string glassesShape;
    string glassesBrand;
    unsigned int barcode;
    while (myfile >> glassesColor >> glassesShape >> glassesBrand >> barcode) {
			if (glassesColor.size() > 0)
      	addGlasses(glassesColor, glassesShape, glassesBrand, barcode);
    }
    myfile.close();
  }
  else
    throw std::invalid_argument("Could not open file " + filename);
}

void GlassesDisplay::addGlasses(string glassesColor, string glassesShape, string glassesBrand, unsigned int barcode) {
  // TO BE COMPLETED
  // function that adds the specified pair of glasses to main display (i.e., to all hash tables)
  Glasses newGlasses(glassesColor, glassesShape, glassesBrand, barcode);
  hT1[barcode] = newGlasses;
  hT2[barcode] = newGlasses;
  hT3[barcode] = newGlasses;
  hT4[barcode] = newGlasses;
  hT5[barcode] = newGlasses;
  hT6[barcode] = newGlasses;
  hT7[barcode] = newGlasses;
}

bool GlassesDisplay::removeGlasses(unsigned int barcode) {
  // TO BE COMPLETED
  // function that removes the pair of glasses specified by the barcode from the display
  // if pair is found, then it is removed and the function returns true
  // else returns false
  bool removed = false;
  removed |= hT1.erase(barcode) > 0;
  removed |= hT2.erase(barcode) > 0;
  removed |= hT3.erase(barcode) > 0;
  removed |= hT4.erase(barcode) > 0;
  removed |= hT5.erase(barcode) > 0;
  removed |= hT6.erase(barcode) > 0;
  removed |= hT7.erase(barcode) > 0;
  return removed;
}

unsigned int GlassesDisplay::bestHashing() {
  // function that decides the best has function, i.e. the ones among
  // fct1-fct7 that creates the most balanced hash table for the current
  // GlassDisplay data member allGlasses

  // set the minimum to be the first hash
  unsigned int min_balance = hT1.bucket_count();
  unsigned int best_hash = 1;

  // create an array of all the hashes to iterate through
  CustomHashTable* tables[7] = {&hT1, &hT2, &hT3, &hT4, &hT5, &hT6, &hT7};
  for (unsigned int i = 0; i < 7; ++i) {
    // iterate through all the buckets of the hash and find the min/max bucket sizes
    unsigned int min_bucket_size = tables[i]->bucket_size(0);
    unsigned int max_bucket_size = tables[i]->bucket_size(0);
    for (unsigned int j = 1; j < 10; ++j) {
      unsigned int bucket_size = tables[i]->bucket_size(j);
      min_bucket_size = std::min(min_bucket_size, bucket_size);
      max_bucket_size = std::max(max_bucket_size, bucket_size);
    }

    // calculate the difference and update minimum balance if needed
    unsigned int balance = max_bucket_size - min_bucket_size;
    if (balance < min_balance) {
      min_balance = balance;
      best_hash = i + 1;
    }
  }
  
  // return the best hash function
  return best_hash;
}

// ALREADY COMPLETED
size_t GlassesDisplay::size() {
    if ((hT1.size() != hT2.size()) || (hT1.size() != hT3.size()) || (hT1.size() != hT4.size()) || (hT1.size() != hT5.size())|| (hT1.size() != hT6.size()) || (hT1.size() != hT7.size()))
  	throw std::length_error("Hash table sizes are not the same");
    
	return hT1.size();
}
