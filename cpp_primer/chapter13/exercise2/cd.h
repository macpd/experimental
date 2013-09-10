// base class
//
#ifndef CD_H
#define CD_H

class Cd {
  private:
    char * performers;
    char * label;
    int selections;
    double playtime; // playtime in minutes
  public:
    Cd(char *s1, char *s2, int n, double x);
    Cd(const Cd & d);
    Cd();
    virtual ~Cd();
    virtual void report() const;
    Cd & operator=(const Cd &d);
};
#endif
