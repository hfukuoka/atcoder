# $1=cource name(lower case)
# $2=number

make_files(){
    dir=`echo $1 | tr '[a-z]' '[A-Z]'`
    display_num=`printf %03d $2`
    if [ ! -e $dir ]; then mkdir $dir ; fi
    cd $dir
    if [ ! -e $display_num ];then
        mkdir $display_num
        cd $display_num
        touch input.txt
        touch run.sh
        chmod +x run.sh
        echo "g++ \$1.cpp -o \$1 -std=c++17 -I /usr/local/include" >> run.sh
        echo "cat input.txt | ./\$1" >> run.sh
        if [[ $1 = "abc"  ]] ; then
            L=(a b c d e f)
        elif [[ $1 = "agc" ]]; then
            L=(a b c d e f)
        elif [[ $1 = "arc" ]]; then
            L=(a b c d e f)
        fi
        for var in ${L[@]}
        do
            cp ../../template.cpp "$var.cpp"
        done
    fi
}
make_files $1 $2