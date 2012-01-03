#include "ProfileArray.h"

#include <iostream>
#include <math.h>

ostream &operator << (ostream &s, const ProfileArray &array) {
  for(vector<Profile>::const_iterator i = array.data.begin();
      i != array.data.end(); ++i) {
    s << array.typist << "'s ";
    s << *i << endl;
  }
  return s;
}

istream &operator >> (istream &s, ProfileArray &array) {
  string line = "";
  while(s.good()) {
    getline(s, line);
    if(line != "") {
      array.data.push_back(Profile(line));
    }
  }
  return s;
}

double ProfileArray::getProbability(const Profile &profile) {
  double overall = 0.0001;

  for(size_t i = 1; i < profile.getDelays().size(); ++i) {
    double p = getProbability(profile, i);
//    cout << "matching on char " << i << " is " << p << endl;
    if(p < 1E-10) {
//      cout << "mistype? skipping char" << endl;
      overall *= 0.1;
      continue;
    }
    overall *= p;
//    cout << "overall is now " << overall << endl;
  }
  return overall;
}

static double gauss(const double &x, const double &mean,
    const double &variance) {
  double difference = x - mean;
  return exp(-difference*difference/(2 * variance * variance))
    / (variance * sqrt(2 * M_PI));
}

double ProfileArray::getProbability(const Profile &profile,
    const size_t &index) {
  double mean = 0;
  for(vector<Profile>::const_iterator i = data.begin(); i != data.end(); ++i) {
    mean += i->getDelays()[index];
  }
  mean /= data.size();

  double variance = 0;
  for(vector<Profile>::const_iterator i = data.begin(); i != data.end(); ++i) {
    double delay = i->getDelays()[index];
    variance = (delay - mean) * (delay - mean);
  }
  variance /= data.size();
  variance = sqrt(variance);

  double measured = profile.getDelays()[index];
  if(measured < 10) {
    return 0.01; // measurement fucked up, bad luck...
  }

//  cout << "variance: " << variance;
//  cout << " mean: " << mean << endl;
//  cout << " measured: " << measured << endl;

  variance = mean / 3;
  return gauss(measured, mean, variance) / gauss(measured, 300000, 300000);
}
