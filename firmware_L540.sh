#!/bin/sh 

# check L540 firmware iso update

n=$1

if test -z $n
then
  printf "Usage $0 firmware number (eg. 61)\n" 
exit 1
fi


cd /tmp && \
curl -# -4 -A Mozilla --connect-timeout 60 --interface enp0s25 \
-e "https://www.google.com/warez/isos/firmwareL540" -o "j4uj${n}wd.iso" \
"https://download.lenovo.com/ibmdl/pub/pc/pccbbs/mobiles/j4uj${n}wd.iso"
