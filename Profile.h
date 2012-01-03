#ifndef __PROFILE_H__
#define __PROFILE_H__

#include <iosfwd>
#include <vector>

#include <sys/time.h>
#include <time.h>

using namespace std;

class Profile {
  private:
    typedef vector<int> DelayList;
    DelayList delays;

  public:
    Profile() { };
    explicit Profile(const string &);

    void addDelay(const timeval &start, const timeval &end) {
      delays.push_back(end.tv_sec * 1000000 + end.tv_usec -
          start.tv_sec * 1000000 - start.tv_usec);
    }

    const DelayList &getDelays() const { return delays; }

    friend ostream &operator << (ostream &, const Profile &);
    friend istream &operator >> (istream &, Profile &);
};

ostream &operator << (ostream &, const Profile &);
istream &operator >> (istream &, Profile &);

void optainProfile(Profile &profile);

#endif
