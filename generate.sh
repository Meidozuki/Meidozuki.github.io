#!/bin/bash
fnames=$(ls */img/*.dot)

for name in $fnames; do
  echo $name
  dot -O -Tjpg $name
done
