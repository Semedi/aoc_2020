#!/bin/bash

EXECUTABLE="/tmp/$(echo $1 | cut -d. -f1)"
args=()

while [[ $# -gt 0 ]]
do
key="$1"

case $key in
    -d|--debug)
    DEBUG=true
    shift
    ;;
    *)
    args+=("$1")
    shift
    ;;
esac
done


if [ "$DEBUG" = true ] ; then
  g++ -fno-inline-functions -Wall -g $args -o $EXECUTABLE
  gdb $EXECUTABLE
else
  g++ $args -o $EXECUTABLE
  $EXECUTABLE
fi
