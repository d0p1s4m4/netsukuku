<div align="center">

![Netsukuku](.github/logo.jpg)

[🌐Website (archive)](https://web.archive.org/web/20170602105941/http://netsukuku.freaknet.org/)
[📖Documentation](https://doc.netsukuku.net/)
[![License](https://img.shields.io/github/license/d0p1s4m4/Netsukuku?logo=gnu&style=flat-square)](./LICENSE)
[![Build](https://img.shields.io/github/actions/workflow/status/d0p1s4m4/netsukuku/ci.yml?style=flat-square)](https://github.com/d0p1s4m4/netsukuku/actions/workflows/ci.yml)
[![Codecov](https://img.shields.io/codecov/c/github/d0p1s4m4/netsukuku?logo=codecov&style=flat-square)](https://app.codecov.io/gh/d0p1s4m4/netsukuku)
[![Reddit](https://img.shields.io/reddit/subreddit-subscribers/netsukuku?color=orange&label=r%2Fnetsukuku&logo=reddit&logoColor=white&style=flat-square)](https://www.reddit.com/r/netsukuku/)

</div>

# What is this?

Netsukuku is an alternative to the internet, It will have all of the features 
of the internet, Such as websites, Instant messaging, File transfers, DNS, Etc. 
It functions as a mesh network or a p2p net system that generates and sustains
itself autonomously. It is designed to handle an unlimited number of nodes
with minimal CPU and memory resources. 

Thanks to this feature it can be easily
used to build a worldwide distributed, anonymous and decentralised network,
separated from the Internet, without the support of any servers, ISPs or
authorities.

This net is composed by computers linked physically each other, Therefore it
isn't build upon any existing network. Netsukuku builds only the routes which
connects all the computers of the net. 
Although it can route through the internet if needed.
In other words, Netsukuku replaces the level 3 of the model iso/osi with
another routing protocol.

The Domain Name System is also replaced by a decentralised and distributed
system, Being the ANDNA system. (A Netsukuku Domain Name Architecture)

The complete features list of Netsukuku is [here](doc/old/misc/Ntk_features_list)

In order to join to Netsukuku, Just install it and run it! Connect as many
nodes together as you want!

# Build and install

## Get the code!

    git clone https://github.com/d0p1s4m4/netsukuku.git

The dependencies of netsukuku can be installed by running this command
for debian-based distros.

    sudo apt install build-essential git gettext \
		libjson-c-dev libreadline-dev libsodium-dev

To compile the code you can do this:
   
    autoreconf -i -f
    ./configure
    make
    sudo make install 

## Once installed

In order to start netsukuku on eth0, It is preferred to run:

    sudo ntkd -D -i eth0 -dd

CURRENTLY NON-FUNCTIONAL:
    
However, There are more options, Such as:

    sudo ntkd -D -i eth0 -r -I -dd
    
This will run netsukuku in restricted mode(Internet compatibility mode) and 
share your internet connection.

(Netsukuku should be able to use any network interface you have, Even VPNs that emulate ethernet such as tinc.)

# How to use it

Before doing anything do:

    $ man ntkd
    $ man andna

when you feel comfortable and you are ready to dare run as root:

    # ntkd

then just wait... ^_-

(For the first times it's cool to use the -D option to see what happens).

**Note:** 
_The daemon at startup takes the list of all the network interfaces which are
currently UP and it uses all of them to send and receive packets. If you want
to force the daemon to use specific interfaces you should use the B<-i>
option._

# Bug report

_{ Don't panic! }_

If you encounter any bug, please report it and explain what the problem is and 
if possible a way to reproduce it.

# License and that kind of stuff...

All the Netsukuku code is released under the GPL-2, please see the COPYING
file for more information.

The authors of Netsukuku and NetsukukuD are listed in the file AUTHORS.

This should be ammended in the future, As more authors come on-board.
