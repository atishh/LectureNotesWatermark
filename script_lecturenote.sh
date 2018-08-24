#!/bin/bash

rm output.txt
touch output.txt
COUNTER=0
while IFS= read -r line; do
      echo "$line"
      echo "/home/atish/projects/lecturenotes_build/LectureNote $line " |& tee /tmp/atish.sh
      source /tmp/atish.sh |& tee -a output.txt
      let COUNTER=COUNTER+1
      sleep 10
done < info.list

