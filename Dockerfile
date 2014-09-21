FROM ubuntu:14.04.1
MAINTAINER Michał Papierski <michal@papierski.net>
ENV DEBIAN_FRONTEND noninteractive

ADD . /code

# Build everything in one step to save space on layers
RUN apt-get update && \
	apt-get install -y cmake build-essential wget libboost-system-dev libboost-thread-dev && \
	cd /code && \
	mkdir _build && \
	cd _build && \
	cmake -DCMAKE_BUILD_TYPE="Release" .. && \
	cmake --build . && \
	cmake --build . --target install && \
	cd / && \
	rm -rf /code && \
	apt-get purge -y cmake build-essential wget && \
	apt-get autoremove -y

WORKDIR /
EXPOSE 5000/tcp
# libsigar.so is installed here.
ENV LD_LIBRARY_PATH /usr/local/lib
ENTRYPOINT /usr/local/bin/sysstatd

