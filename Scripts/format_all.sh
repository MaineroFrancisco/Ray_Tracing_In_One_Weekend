echo Called format all

find ./ -iname '*.h' -o -iname '*.cpp' | xargs clang-format -i -style=file --Werror