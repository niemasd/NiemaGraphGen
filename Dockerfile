# Minimal Docker image for NiemaGraphGen using Alpine base
FROM alpine:3.13.5
MAINTAINER Niema Moshiri <niemamoshiri@gmail.com>

# install NiemaGraphGen
RUN apk update && \
    apk add bash g++ make && \
    wget -qO- "https://github.com/niemasd/NiemaGraphGen/archive/refs/tags/1.0.3.tar.gz" | tar -zx && \
    cd NiemaGraphGen-* && \
    make && \
    mv ngg_* /usr/local/bin/ && \
    cd .. && \
    rm -rf NiemaGraphGen-*
