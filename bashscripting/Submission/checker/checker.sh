#!/bin/bash

#run by: bash ./checker.sh file.cpp
#taking in user code
if [ $# -eq 0 ];then
	echo Please enter the cpp file as an argument
	exit 1
elif [ $# -ne 1 ];then
	echo Please enter only one cpp file
	exit 1
fi
g++ $1 > a.out

#generating test cases and actual result/expected output
t=$(($RANDOM%100+1))
echo $t>input.txt
touch result.txt
for((i=1;i<=$t;i++))do
	value=$(($RANDOM%1000+1))
	echo $value>>input.txt
	if [ $(($value%3)) -eq 0 ];then
		echo Second>>result.txt
	else echo First>>result.txt
	fi
done

#generating user output
./a.out < input.txt > output.txt

#printing
echo Test case
cat input.txt
echo Output  Expected
paste output.txt result.txt > compare.txt
cat compare.txt
echo " "
echo " "

#finding and printing mistakes
i=1
mistake=0
while read -r w1 w2; do
	if [ "$w1" != "$w2" ]; then
		echo "Error at line $i : $w1 --> $w2"
		((mistake++))
	fi
	((i++))
done < compare.txt
if [ $mistake -ne 0 ];then
	echo "Total no. of mistakes is $mistake"
else echo "No mistakes detected"
fi

rm input.txt result.txt output.txt compare.txt