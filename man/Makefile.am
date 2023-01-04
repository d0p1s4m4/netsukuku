man_MANS = andna.8 netsukuku.conf.5 ntk-resolv.8 ntk-wifi.8 ntkd.8
EXTRA_DIST = $(man_MANS)
MAINTAINERCLEANFILES = $(man_MANS)

andna.8: andna.pod
	pod2man -s 8 $< -c "" -n "ANDNA"  -r "$(VERSION)" $@

netsukuku.conf.5: netsukuku.conf.pod
	pod2man -s 5 $< -c "" -n "netsukuku.conf"  -r "$(VERSION)" $@

ntk-resolv.8: ntk-resolv.pod
	pod2man -s 8 $< -c "" -n "ntk-resolv"  -r "$(VERSION)" $@

ntk-wifi.8: ntk-wifi.pod
	pod2man -s 8 $< -c "" -n "ntk-wifi"  -r "$(VERSION)" $@

ntkd.8: ntkd.pod
	pod2man -s 8 $< -c "" -n "NetsukukuD"  -r "$(VERSION)" $@
