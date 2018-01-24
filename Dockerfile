FROM ubuntu:16.04
LABEL maintainer="andrew@berezovskyi.me"

RUN apt-get update && apt-get install -y ocaml ocaml-native-compilers opam m4

RUN opam init
RUN opam config env
RUN opam depext conf-m4.1
RUN opam install cil
RUN echo $(opam config env)

COPY . /opt/ktc
WORKDIR /opt/ktc
RUN ocaml -version
RUN opam --version
RUN ls -la
RUN eval $(opam config env) && make
WORKDIR /opt/ktc/test
RUN eval $(opam config env) && bash run-test.sh

# `opam config env`
ENV CAML_LD_LIBRARY_PATH="/root/.opam/system/lib/stublibs:/usr/lib/ocaml/stublibs"
ENV MANPATH="/root/.opam/system/man:"
ENV PERL5LIB="/root/.opam/system/lib/perl5"
ENV OCAML_TOPLEVEL_PATH="/root/.opam/system/lib/toplevel"
ENV PATH="/root/.opam/system/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

WORKDIR /src

ENTRYPOINT [ "/opt/ktc/bin/ktc" ]
CMD [ "--help" ]