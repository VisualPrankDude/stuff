#!/bin/bash

cd /var/cache/Vogelcaches/samples/var/ || exit

n="*.mp3 *.MP3 *.ogg *.wav"
#n="*.tschiep *.krill *.krah"

if test -z "$n"
then
  exit 32
fi

n=($n)
# count teh fuckkink arguments
num=${#n[*]}
vogel=${n[$((RANDOM%num))]}
echo $vogel
(sleep 18s; echo q) | /usr/bin/nvlc ${vogel} > /dev/null 2>&1
