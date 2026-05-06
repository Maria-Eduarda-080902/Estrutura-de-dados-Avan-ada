#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>
#include "redBlackTree.h"
#define INFINITY 999999999;

using namespace std;

int main(int argc, char** argv)
{
  RedBlackTree rbtree;
  string file_name = argv[1];
  ifstream file(file_name);
  ofstream output_file("out.txt");

  if (file.is_open() && output_file.is_open())
  {
    string line;
    while (getline(file, line))
    {
      istringstream iss(line);
      string command;
      iss >> command;
      if (command == "INC")
      {
        int number;
        iss >> number;
        // cout << "INC " << number << endl;
        rbtree.insert(number);
      }
      else if (command == "REM")
      {
        int number;
        iss >> number;
        // cout << "REM "<<number<<endl;
        rbtree.remove(number);
      }
      else if (command == "SUC")
      {
        int number;
        int version;
        iss >> number >> version;
        // cout << "SUC " << number << " " << version << endl;
        output_file << "SUC " << number << " " << version << endl
                    << rbtree.get_successor(number, version) << endl;
      }
      else if (command == "IMP")
      {
        int version;
        iss >> version;
        // cout << "IMP " << version << endl;
        output_file << "IMP " << version << endl;

        rbtree.print_to_file(version, output_file);
        output_file << endl;
      }
    }
    file.close();
    output_file.close();
  }

  return 0;
}