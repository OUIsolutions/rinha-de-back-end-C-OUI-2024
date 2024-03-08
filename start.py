

import os

query = ''
total_apis = os.environ['TOTAL_APIS']
porta = 3000

for i in range(int(total_apis) -1):
    porta += 1
    query+= f'./a.out {porta} & '

query+=f'./a.out {porta+1}'

os.system(query)