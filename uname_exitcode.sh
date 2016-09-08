#/bin/bash

M=`/bin/uname -m`

case $M in
x86_64) exit 64; break;
;;
i386) exit 32; break;
;;
*)  printf "48 bits?";
esac 
