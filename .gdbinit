#.gdbinit:
#
shell date
#define bsave
#    shell rm -f brestore.txt
#    set logging file brestore.txt
#    set logging on
#    info break
#    set logging off
#    # reformat on-the-fly to a valid gdb command file
#    shell perl -n -e 'print "break $1\n" if /^\d+.+?(\S+)$/g' brestore.txt > brestore.gdb
#end 
#document bsave
#  store actual breakpoints
#end
#
#define brestore
#  source brestore.gdb
#end
#document brestore
#  restore b



#if ($64BITS == 1)
##64bits stuff
#	# from rax
#	set $eax = $rax & 0xffffffff
#	set $ax = $rax & 0xffff
#	set $al = $ax & 0xff
#	set $ah = $ax >> 8
#end
