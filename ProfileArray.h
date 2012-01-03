#ifndef __PROFILEARRAY_H__
#define __PROFILEARRAY_H__

#include "Profile.h"

#include <string>

class ProfileArray {
  private:
    vector<Profile> data;
    string typist;

    double getProbability(const Profile &profile, const size_t &index);

  public:
    ProfileArray(const string &typist): typist(typist) { }

    double getProbability(const Profile &profile);
    const string &getTypist() const { return typist; }

    friend ostream &operator << (ostream &, const ProfileArray &);
    friend istream &operator >> (istream &, ProfileArray &);
};

ostream &operator << (ostream &, const ProfileArray &);
istream &operator >> (istream &, ProfileArray &);

#endif
