BEGIN {
  printf "\n%15s%7s\n", "Word", "Count"
  print "-----------------------"
}
{
  for (i = 1; i <= NF; i++) {
    if ($1 ~ /#/)
      continue
    else {
      split($i, temp, "[.,;:() ]")
      wordList[tolower(temp[1])]++
      wordCount++
    }
  }
}
END {
  for (word in wordList) {
    if (length(word) >= 5 && wordList[word] >= 3) {
      printf "%15s%3d\n", word, wordList[word]
    }
  }

  print "-----------------------"
  print "Number of words: ", wordCount
}
