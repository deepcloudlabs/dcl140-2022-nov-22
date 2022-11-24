#!/bin/bash
trap func exit
trap func2 2 3 6 15 19 20

func() {
 echo "Hello Mars!" 
 xcalc
}
func2() {
 echo "Hello Moon!" 
}
