#ifndef COW_H_
#define COW_H_

class Cow {
  public:
  enum {NAME_MAX=20};

  private:
  char name[NAME_MAX];
  char * hobby;
  double weight;

  public:
  Cow();
  Cow(const char* nm, const char* ho, double wt);
  Cow(const Cow& c);
  ~Cow();
  Cow & operator=(const Cow& c);
  void ShowCow() const;
};
#endif
