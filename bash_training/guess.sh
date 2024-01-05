#!/bin/bash
#Random number between 1 and 20
random_number=$((1 + $RANDOM % 20))
echo "My secret number was ${random_number}"
guessed=false


count=1
while [ $count -le 3 ]
do
    echo "Attempt ${count}"
    (( count++ ))
    echo "Guess a number between 1 and 20: "
    read guess_number
    if [ ${guess_number} -eq ${random_number} ];
      then
      echo "You guessed my secret number!"
      guessed=true
      break
    elif [ ${guess_number} -gt ${random_number} ];
      then
      echo "Your number is greater than my secret number"
      continue
    else 
      echo "Your number is less than my secret number"
      continue
    fi
done

if [ $guessed = false ];
  then
  echo "My secret number was ${random_number}"
fi