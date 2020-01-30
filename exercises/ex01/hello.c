#include <stdio.h>
/*1. movl    $5, -4(%rbp) is the line that corresponds to this line. It's 
  assigning the value of 5 to the variable.
  2. The previous line was omitted in the optimized version, because the 
  variable x was never used. 
  3. The previous line appeared in both the optimized and not optimized
  version. This is because the value x was used in the printf statement.
  4. The optimized version only stored the sum of 5 and 1 without storing the 
  variable x. I think this is because the compiler figured out that x was never 
  used in the program, so it can save time and space by omitting this 
  intermediate variable and only storing the end result. 
*/
int main() {
    int x = 5;
    int y = x + 1;
    printf("%i\n",y);
    return 0;
}
