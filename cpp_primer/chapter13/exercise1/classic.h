#ifndef CLASSIC_H
#define CLASSIC_H

#include "cd.h"

class Classic : public Cd {
  private:
    char * primary_work;
  public:
    Classic(char*work, char *s1, char *s2, int n, double x);
    Classic(char* work, Cd & d);
    Classic(Classic & c);
    Classic();
    virtual ~Classic();
    void report() const;
    Classic & operator=(const Classic &c);
};

#endif
