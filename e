#!/bin/bash

EXECUTABLE=/tmp/to_exec

g++ $1 -o $EXECUTABLE
$EXECUTABLE
rm $EXECUTABLE
