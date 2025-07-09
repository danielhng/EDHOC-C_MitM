CC	= gcc
CFLAGS	= -Wall
LDFLAGS	= -lcrypto -lb64 /usr/local/lib64/libcbor.a

CLIENT_OBJFILES	= crypto_functions.o edhoc_client.o edhoc_messages.o \
			  io_functions.o other_functions.o
SERVER_OBJFILES	= crypto_functions.o edhoc_server.o edhoc_messages.o \
			  io_functions.o other_functions.o
MITM_OBJFILES   = crypto_functions.o edhoc_MitM.o edhoc_messages.o \
			  io_functions.o other_functions.o
ALL_OBJFILES	= crypto_functions.o edhoc_client.o edhoc_server.o edhoc_MitM.o edhoc_messages.o \
			  io_functions.o other_functions.o
EDHOC_MSGS	= ./edhoc_client_INBOX/edhoc_sym_msg2_RAW.txt ./edhoc_server_INBOX/edhoc_sym_msg1_RAW.txt ./edhoc_server_INBOX/edhoc_sym_msg3_RAW.txt ./edhoc_MitM_server_INBOX/edhoc_sym_msg1_RAW.txt ./edhoc_MitM_server_INBOX/edhoc_sym_msg3_RAW.txt ./edhoc_MitM_client_INBOX/edhoc_sym_msg2_RAW.txt
EDHOC_KEYS	= ./edhoc_client_INBOX/server_PUBKEY.txt ./edhoc_server_INBOX/client_PUBKEY.txt ./edhoc_MitM_client_INBOX/server_PUBKEY.txt ./edhoc_MitM_server_INBOX/client_PUBKEY.txt
EDHOC_INP_PARAM	= ./input_parameters/client_PrivateKey.txt ./input_parameters/client_PUBKEY.txt ./input_parameters/server_PrivateKey.txt ./input_parameters/server_PUBKEY.txt ./input_parameters/MitM_PrivateKey.txt ./input_parameters/MitM_PUBKEY.txt

CLIENT_TARGET	=	edhoc-client
SERVER_TARGET	=	edhoc-server
MITM_TARGET	= 	edhoc-MitM

all: $(CLIENT_TARGET) $(SERVER_TARGET) $(MITM_TARGET)

$(CLIENT_TARGET) : $(CLIENT_OBJFILES)
	$(CC) $(CFLAGS) -o $(CLIENT_TARGET) $(CLIENT_OBJFILES) $(LDFLAGS)

$(SERVER_TARGET) : $(SERVER_OBJFILES)
	$(CC) $(CFLAGS) -o $(SERVER_TARGET) $(SERVER_OBJFILES) $(LDFLAGS)

$(MITM_TARGET)	: $(MITM_OBJFILES)
	$(CC) $(CFLAGS) -o $(MITM_TARGET)   $(MITM_OBJFILES)   $(LDFLAGS)
clean:
	rm -f $(ALL_OBJFILES) $(CLIENT_TARGET) $(SERVER_TARGET) $(MITM_TARGET) $(EDHOC_MSGS) $(EDHOC_KEYS) $(EDHOC_INP_PARAM)

clean-keys:
	rm -f $(EDHOC_MSGS) $(EDHOC_KEYS) $(EDHOC_INP_PARAM)
