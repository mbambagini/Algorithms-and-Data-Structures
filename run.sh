#! /bin/bash

files=( "list" "double_list" "stack" "queue" "deque" "heap" "tree" "trie"
        "hash" "graph_matrix" "graph_list"
        "sorting" "search" "dijkstra"
        "examples/ex_17_1" "examples/ex_17_2" "examples/ex_17_3"
        "examples/ex_17_4" "examples/ex_17_5" "examples/ex_17_6"
        "examples/ex_17_7" "examples/ex_17_9" "examples/ex_17_11"
	"examples/ex_17_12" "examples/ex_17_13"
        "examples/ex_18_1" "examples/ex_18_2" "examples/ex_18_4" 
        "examples/ex_18_10" "examples/ex_18_11" "examples/ex_18_12"
        "others/visitor" "others/board")

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

