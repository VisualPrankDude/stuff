#!/bin/bash

# get a random X display

OFFSET=22
PATH=/bin:/usr/bin:/sbin:/usr/sbin

if test -x /usr/bin/expr
 then 
        x=$(( $OFFSET + `expr "$RANDOM" : "\(..\)"` ))
else
  x=$(( $OFFSET + ${RANDOM%*???} ))
fi

if test `ps ax|grep 'X :'|head -1|awk '{print $9}'|tr -d ':'`
   then
      echo in use, please retry
  exit 
fi


( /usr/bin/startx -- :$x  vt7 )
