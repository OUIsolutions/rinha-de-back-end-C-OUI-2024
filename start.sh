./a.out 3001 & ./a.out & 3002

#for port in $(seq 3001 $((3001 + $TOTAL_APIS - 1))); do
#  ./a.out $port &
#done
