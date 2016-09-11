#!/bin/sh

# this is not about bc
# greetings to finnland :)


if ! test ${BASH}
then
  # variable=$(echo "ibase=16; 0xff" | bc)
  printf "no bash\n"
  exit 1
fi


if test -z $1
then
  printf "usage: $0 [0xff|255]\n"
exit
fi

n=`echo "$[$1]"`

printf "0x%s\n" $n
printf "0x%x\n" $n
printf "0x%o\n" $n
