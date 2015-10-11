x=`find . -name "*.c" -or -name "*.h" | xargs cat | grep -v ^$| wc -l`
add=$(expr $x - 91589)
echo "Source:    91589 total"
echo "Now:    $x total"
echo "Addition:    $add total"
