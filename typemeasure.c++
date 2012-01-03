#include "Profile.h"
#include "ProfileArray.h"

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
  vector<ProfileArray> profiles;

  for(int i = 1; i < argc; ++i) {
    ifstream in(argv[i]);
    ProfileArray pa(argv[i]);
    in >> pa;
    profiles.push_back(pa);
  }

  Profile measurement;
  optainProfile(measurement);

  string detectedTypist = "none";
  double bestProb = -1;
  double secondBest = -1;

  for(int i = 0; i < argc - 1; ++i) {
    double prob = profiles[i].getProbability(measurement);
    const string &typist = profiles[i].getTypist();

    cout << typist << " maches by " << prob << endl;

    if(prob > bestProb) {
      secondBest = bestProb;
      bestProb = prob;
      detectedTypist = typist;
    } else if(prob > secondBest) {
      secondBest = prob;
    }
  }

  double confidence = bestProb / secondBest;

  cout << "Typist: " << detectedTypist << endl;
  cout << "Confidence: " << confidence << endl;
}
