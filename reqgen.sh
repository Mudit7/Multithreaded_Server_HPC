#!/bin/bash
for((i=0;i<50;i++)) do
	#./a.out < input
	#gnome-terminal --tab --title="test" --command="bash -c './a.out < input; $SHELL'"
	#xterm -hold -e "./a.out < input"
	gnome-terminal --tab --title="test" --command="./a.out GET#test ; $SHELL"	
done
