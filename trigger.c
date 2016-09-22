#include <string.h>

int main(int argc, char **argv) {

if (strstr(argv[1],"buf")) {
__chk_fail();
} else if (strstr(argv[1],"fmt")) {
__stack_chk_fail();
}
return 0;
}
