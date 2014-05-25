econix
======
[![Build Status](https://travis-ci.org/sillsm/econix.png?branch=master)](https://travis-ci.org/sillsm/econix)

RESTful economy/transaction/contracts simulator for games

See test code for current features/documentation.


== Phase 1 == [status- incomplete]

Create a generic packet verification network.

A sends B a packet (with a unique session identifier).
A has a list of required authorities that must read and sign the packet.
B sends A a confirmation packet signed by A's requested authorities.
