g='g++ -std=c++17 -pedantic-errors -Wall -Wextra'
for f in `find . -name "*.hpp"`;
do
    if [[ $f == */assertions/* ]]; then
        : # echo ! $f
    else
        echo Checking \'$f\'...
        $g -c _.cpp -include "$f" || break
    fi
done
