# Use a imagem base do Ubuntu
FROM ubuntu:latest

# Instale o Git, Python3 e GCC
RUN apt-get update && \
    apt-get install -y git && \
    apt-get install -y gcc && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Crie um diretório para o aplicativo dentro do contêiner
RUN mkdir /app

# Copie o conteúdo do repositório local para o contêiner
COPY . /app

# Configure o diretório de trabalho
WORKDIR /app

# Compile o código C
RUN gcc src/main.c  -DPROCESSO_UNICO -o a.out

# Comando padrão para executar quando o contêiner for iniciado
CMD ["sh", "start.sh"]