#!/bin/bash

n="*.tschiep *.krill *.krah"

if test -z "$n"
then
  exit 32
fi

n=($n)
num=${#n[*]}
echo ${n[$((RANDOM%num))]}
(sleep 18s; echo q) | /usr/bin/nvlc ${n[$((RANDOM%num))]} > /dev/null 2>&1
