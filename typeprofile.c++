#include "Profile.h"

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
  if(argc != 2) {
    cerr << "Please provide record file" << endl;
    return 1;
  }

  ofstream data(argv[1], ios::app);

  Profile profile;
  optainProfile(profile);

  cout << profile << endl;
  data << profile << endl;
  return 0;
}
