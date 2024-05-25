/**
 * @class HashTable
 * @author J. Shockey
 * @date 30/03/20
 * @file main.cpp
 * @brief Main program to exercise advanced data structures.  This program takes
 * information input from stdin or a file.  The information is processed into
 * operations necessary to construct a data structure.  The input is one or more
 * comma separated operation and data pairs in the form <operation> : <data>.
 * 			where operations are:
 * 				'A' - add element to structure
 * 				'D' - Delete element from structure
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "HashTable.h"

using namespace std;

struct ds_operation {
  char op;
  // int		data;
  string data;
};

/**
 * @brief Decode a single operation into a list of operations
 * @param str - a string of a single element in the form of <operation> : <data>
 * @return struct ds_operation -  the decoded string
 */
ds_operation decode(string str) {
  char sep;
  ds_operation dsop;
  stringstream s_str(str);
  s_str >> skipws >> dsop.op >> skipws >> sep >> dsop.data;
  dsop.op = dsop.op & 0x5F; // make uppercase
  if (sep != ':') {
    dsop.op = 'E'; // incorrectly formed operation
    dsop.data = -1;
  }
  return dsop;
}

/**
 * @brief segment a line of information, separated by commas, into single
 * elements that can be decoded.
 * @param str - a string containing one or more elements separated by commas
 * @return a vector containg an ordered series of decoded operations
 */

vector<ds_operation> segment(string str) {
  vector<ds_operation> result;
  stringstream s_stream(str); // create string stream from the string
  while (s_stream.good()) {
    string substr;
    getline(s_stream, substr, ','); // get first string delimited by comma

    if (substr != "") {
      ds_operation dsop = decode(substr);
      result.push_back(dsop);
    } else
      cout << "End of data" << endl;
  }

  return result;
}

/**
 * @brief print a vector of ds_operations.
 * @param vector
 */

// void vprint(auto const &vector)

void vprint(vector<ds_operation> vec) {
  cout << "size: " << vec.size() << endl;
  for (auto i : vec) {
    std::cout << i.op << " - " << i.data << endl;
  }

  std::cout << '\n';
}

int main(int argc, char **argv) {
  std::cout << "Hello Hash with Chaining" << std::endl;

  HashTable *ht = nullptr;
  int tableSize = 0;
#define defaultTableSize 16

  vector<ds_operation> dsop_vec;

  vector<ds_operation> segments;
  int choice;
  string line;

  cout << "Enter 1 for stdin" << endl;
  cout << "Enter 2 for file" << endl;

  cin >> choice;
  cin.ignore();

  cout << "choice: " << choice << endl;

  if (choice == 1) {
    getline(cin, line);
    while ((line != "") && (line != "END") && (line != "end")) {
      vector<ds_operation> x = segment(line);
      segments.insert(segments.end(), x.begin(), x.end());
      getline(cin, line);
      cout << "* * * *" << line << endl;
    }

  } else if (choice == 2) {
    string fileName = "data.txt";
    fstream fin;
    cout << "Enter File Name [" << fileName << "] > ";
    getline(cin, fileName);
    if (fileName == "")
      fileName = "data.txt";

    fin.open(
        fileName,
        ios::in); // open a file to perform read operation using file object

    if (fin.is_open()) { // checking whether the file is open
      string line;
      while (getline(
          fin, line)) { // read data from file object and put it into string.
        // cout << line << "\n";			//print the data of the
        // string
        vector<ds_operation> x = segment(line);
        segments.insert(segments.end(), x.begin(), x.end());
      }
      fin.close(); // close the file object.
    }
  } else {
    cout << "Nothing to process" << endl;
    return (0);
  }

  // vprint(segments);

  int sum = 0;
  Element *it = nullptr;
  for (unsigned int i = 0; i < segments.size(); i++) {

    switch (segments[i].op) {
    case 'A':
      if (ht == nullptr)
        ht = new HashTable(defaultTableSize);
      // cout << "Add [" << segments[i].op << "]: " << segments[i].data << endl;
      // ???? rb.insert(segments[i].data);
      it = new Element{segments[i].data, NULL};
      ht->insert(it);

      break;
    case 'D':
      if (ht != nullptr) {
        // cout << "Delete [" << segments[i].op << "]: " << segments[i].data <<
        // endl;

        ht->erase(segments[i].data);
      }
      break;
    case 'T':
      tableSize = stoi(segments[i].data);
      // cout << "Table size [" << segments[i].op << "]: " << tableSize << endl;
      // //segments[i].data << endl;
      if (ht != nullptr)
        delete ht;
      ht = new HashTable(tableSize);
      break;
    case 'E':
      cout << "Error in segment list" << endl;
      break;
    default:
      cout << "Empty data in segments list" << endl;
      break;
    }
  }

  cout << endl << endl;

  printf("\n\nDisplay\n");
  cout << endl;

  cout << endl;

  ht->printTable();

  ht->printHistogram();

  delete ht;

  return 0;
}
