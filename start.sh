#./a.out 3001 &
#./a.out 3002

total_menos_um=$((${TOTAL_APIS} -1))
result=""
total=3000
for counter in $(seq 1 ${total_menos_um});  do 
    total=$((total +1))
    result="${result} ./a.out ${total} & "

 done
total=$((total +1))
result="${result} ./a.out ${total}";
eval $result