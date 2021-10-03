FROM ubuntu:16.04
LABEL maintainer="andrew@berezovskyi.me"

RUN apt-get update && apt-get install -y ocaml ocaml-native-compilers opam m4 sudo
RUN apt-get install -y ocaml-findlib liblablgtk2-gl-ocaml libocamlgraph-ocaml-dev mercurial

# Create a valid user (we don't want to run as root)
RUN adduser --disabled-password --gecos '' ktcuser
RUN adduser ktcuser sudo
RUN echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers
USER ktcuser
WORKDIR /home/ktcuser

COPY files/ocamlinit .ocamlinit
COPY files/profile .profile
RUN mkdir -p /home/ktcuser/app
RUN mkdir -p /home/ktcuser/bin

# Setup OPAM for user
RUN opam init -y
RUN opam config setup -a
RUN opam config env
RUN opam depext conf-m4.1
RUN opam install -y csv
RUN opam install -y yojson
RUN opam install -y cil

RUN ln -s /home/ktcuser/app/bin/ktc /home/ktcuser/bin/ktc

CMD [ "/bin/bash" ]
