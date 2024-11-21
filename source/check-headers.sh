EXIT_TRUE=0
EXIT_FALSE=1

function should_ignore() {
    if [[ $1 == */setjmp.hpp || $1 == */signal.hpp || $1 = *winapi* || $1 == */_* ]]; then
        return $EXIT_TRUE;
    fi
    if [[ $1 == */assertions/has_posix_number_names.hpp ]]; then
        return $EXIT_TRUE
    fi
    return $EXIT_FALSE
}

g='g++ -std=c++20 -pedantic-errors -Wall -Wextra'
for f in `find . -name "*.hpp"`;
do
    if should_ignore $f; then
        : # echo ! $f
    else
        echo Checking \'$f\'...
        $g -c _.cpp -include "$f" || break
    fi
done
