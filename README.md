# sysstatd
====

HTTP API for system resources. I found SNMP really complicated and for most uses I should calculate values on my own so I decided to implement HTTP API for this.

# Requirements

* C++ compiler
* Boost

# Docker

Build:

	docker build -t sysstatd .

Run

	docker run -p 5000:5000/tcp mpapierski/sysstatd

# Usage


## API details

	curl http://localhost:5000/

## CPU

	curl http://localhost:5000/cpu/

Array of CPU details as objects with following keys:

* user,
* sys
* nice
* idle
* wait
* irq
* soft_irq
* stolen
* total

# Support

* OS X
* Linux

# License

MIT. See LICENSE.

Authors

* Michał Papierski <michal@papierski.net>
