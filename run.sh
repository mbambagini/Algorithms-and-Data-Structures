#! /bin/bash

files=( "list" "double_list" )

for file in "${files[@]}"
do
  echo -ne "FILE $file: "
  g++ $file.cc -o $file.o
  { ./$file.o; } 2> output.tmp
  if [[ -s output.tmp ]] ; then
    echo "ERRORS"
  else
    echo "SUCCESS!"
  fi
done
