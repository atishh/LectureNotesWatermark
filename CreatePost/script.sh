#!/bin/bash

rm output.txt
touch output.txt
rm post.txt
COUNTER=0
while IFS= read -r line; do
      echo "$line"
      echo "/home/atish/projects/build/createPost/CreatePost $COUNTER $line " |& tee /tmp/atish.sh
      source /tmp/atish.sh |& tee -a output.txt
      let COUNTER=COUNTER+1
done < info.list

