#include<stdio.h>
 
enum week {Mon, Tue, Wed, Thur, Fri, Sat, Sun};
enum year {Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec};

int main(void) {
  enum week day;
  day = Fri;
  printf("%d\n", day);

  enum year month;
  month = Jan;
  printf("%d\n", month);

  int i;
  for (i=Jan; i<Sep; i++) {
    printf("%d\n", i);
  }
  return 0;
}