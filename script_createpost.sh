#!/bin/bash

rm output.txt
touch output.txt
rm post.txt
COUNTER=0
while IFS= read -r line; do
      echo "$line"
      echo "/home/atish/projects/createpost_build/CreatePost $line " |& tee /tmp/atish_p.sh
      source /tmp/atish_p.sh |& tee -a output.txt
      let COUNTER=COUNTER+1
done < info.list

