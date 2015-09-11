#! /bin/sh

files=( "list" "double_list" )

for file in "${files[@]}"
do
  echo -ne "FILE $file: "
  g++ $file.cc -o $file.o
  ./$file.o 2> output.tmp
  if [[ -s $file ]] ; then
    echo "ERRORS"
  else
    echo "SUCCESS!"
  fi
done
