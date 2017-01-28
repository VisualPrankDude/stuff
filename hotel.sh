#!/bin/bash


if test $# -lt 4
then
  echo "usage: $0 Tage Visa Flug Hotelpreis"
  exit 1
fi


n1=$(($1*$4))
#echo MMM $n1

echo "Hotelpreis ($4) * Tag ($1):" $n1
save=$n1
n2=$2
echo Visa Gebühr: $n2
n3=$3
echo "Flug (Hin+Rück)": $n3

n5=123  # Hotel Intercontinental Pfund
n5=$(($n5*$1))
echo "Mit Hotel Interconti: ($n5)	Total: $(($n1+$n2+$n3+$n5))€"
echo "Mit Standard Hotel  : ($n1)	Total: $(($n1+$n2+$n3))€"
#echo "Mit Standard Hotel  : ($save)	Total: $(($n1+$n2+$n3))€"



#Berlin Warschau ...
#Warschau Smolensk ...
#Smolensk Moskau 40€ Zug
