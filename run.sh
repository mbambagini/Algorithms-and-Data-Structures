#! /bin/bash

files=( "list" "double_list" "stack" "queue" "deque" "heap" "tree" "hash" "sorting" "graph_matrix" "graph_list" "search")

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
