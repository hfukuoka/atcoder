dir=`echo $1`
display_num=`printf %03d $2`
path=~/program/atcoder
if [ ! -e $dir ]; then
    mkdir "${path}/${dir}"
fi
if [ ! -e $display_num ];then
    mkdir "${path}/${dir}/${display_num}"
    touch "${path}/${dir}/${display_num}/input.txt"
    if [[ $1 = "abc"  ]] ; then
        L=(a b c d e f)
    elif [[ $1 = "agc" ]]; then
        L=(a b c d e f)
    elif [[ $1 = "arc" ]]; then
        L=(a b c d e f)
    fi
    for var in ${L[@]}
    do
        cp "${path}/template.cpp" "${path}/${dir}/${display_num}/${var}.cpp"
    done
fi