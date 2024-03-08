# Use a imagem base do Ubuntu
FROM ubuntu:latest

# Instale o Git
RUN apt-get update && \
    apt-get install -y git &&apt-get install -y gcc  && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Clone o repositório
RUN git clone https://github.com/OUIsolutions/rinha-de-back-end-C-OUI-2024

# Configure o diretório de trabalho
WORKDIR /rinha-de-back-end-C-OUI-2024

# Compile o código C
RUN gcc src/main.c -o a.out


# Comando padrão para executar quando o contêiner for iniciado
CMD ["sh","start.sh" ]


