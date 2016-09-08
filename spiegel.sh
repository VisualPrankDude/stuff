#!/bin/sh

# get spiegel.tv rtmpdump streams
# real hardcore programming style


serveur=`youtube-dl -v http://www.spiegel.tv/filme/nachwuchsrennfahrer-formel-4/ 2>/dev/null | egrep '(Hostname|Port)'| awk '{print $5}'| tr -s '\n' ':'`
movies=`lynx  -nonumbers -dump -force-html http://www.spiegel.tv | grep filme`

echo serveur: $serveur

for m in ${movies}
 do
  youtube-dl -v ${m} 2>/dev/null|awk '/Playpath/{print $5}' | tee -a liste.m4v
done
#less liste.m4v

for l in `cat liste.m4v`
do
#rtmpdump -v -r rtmp://sptvfs.fplive.net:1935/sptv/${l} > ${l}.m4v
rtmpdump -v -r rtmp://${serveur}/sptv/${l} > ${l}.m4v
done
