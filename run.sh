#!/bin/bash
set -e
BPATH="$(dirname `realpath $0`)"

test -d ${BPATH}/opam || mkdir -p ${BPATH}/opam

GID_=$(id -g ${USER})
UID_=$(id -u ${USER})
docker build --tag=ktcbuild .
docker  run -it -v ${BPATH}:/home/ktcuser/app \
	ktcbuild ${params} \
	/bin/bash --login
