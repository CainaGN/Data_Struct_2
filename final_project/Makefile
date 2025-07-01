# Nome do executável final
TARGET = ecommerce_manager

# Compilador C
CC = gcc

# Flags do compilador: -g para debug, -Wall para mostrar todos os avisos
CFLAGS = -g -Wall

# Bibliotecas a serem linkadas: -lm (matemática), -lcurl (cURL), -lcjson (cJSON)
LIBS = -lm -lcurl -lcjson

# Arquivos fonte (.c)
SOURCES = main.c lista.c arvore_avl.c tabela_hash.c produto.c

# Converte os arquivos fonte para arquivos objeto (.o)
OBJECTS = $(SOURCES:.c=.o)

# Regra principal: compila o alvo final
all: $(TARGET)

# Regra para linkar os objetos e criar o executável
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

# Regra para compilar cada arquivo .c em um arquivo .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar os arquivos gerados (objetos e executável)
clean:
	rm -f $(OBJECTS) $(TARGET)

# Phony targets não correspondem a nomes de arquivos
.PHONY: all clean
