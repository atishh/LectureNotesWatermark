#!/bin/bash

rm output.txt
touch output.txt
rm post.txt
while IFS= read -r line; do
      echo "$line"
      echo "/home/atish/projects/build/createPost/CreatePost $line" |& tee /tmp/atish.sh
      source /tmp/atish.sh |& tee -a output.txt
done < info.list

