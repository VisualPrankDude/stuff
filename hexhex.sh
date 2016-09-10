#!/bin/sh

# this is not about bc
# greetings to finnland :)


if ! test ${BASH}
then
  # variable=$(echo "ibase=16; 0xff" | bc)
  printf "no bash, try bc\n"
  exit 1
fi


if test -z $1 -o  -z "$(echo $1|grep 0x)"
then
  printf "usage: $0 0xff\n"
exit
fi

# using tr since 1994 
n=`echo "$[$1]" | tr -s 'a-z' 'A-Z'`

printf "%s\n" $n
printf "0x%x\n" $n

unset BASH n 
