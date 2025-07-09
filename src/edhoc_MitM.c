#include "edhoc_messages.h"
#include <unistd.h>

void wait4enter() {
  int c;
  do {
    c = getchar();
  } while ((c!='\n') && (c!=EOF));
  
}

int main(int argc, char *argv[])
{
	print_title();
	srand(time(NULL));

	unsigned char app_1[] = "Hello, my name is EDHOC!";
	unsigned char app_2[] = "If you can read this then message_2 has SUCCEEDED!";
	unsigned char app_3[] = "Last but not least... message_3!";

	size_t app_1_sz = sizeof(app_1);
	size_t app_2_sz = sizeof(app_2);
	size_t app_3_sz = sizeof(app_3);

	EVP_PKEY *session_pkey = gen_x25519();
	//EVP_PKEY *session_pkey = NULL;
	FILE *keyfile_pu = fopen("./input_parameters/MitM_PUBKEY.txt", "w");
	FILE *keyfile_pr = fopen("./input_parameters/MitM_PrivateKey.txt", "w");
	PEM_write_PUBKEY(keyfile_pu, session_pkey);
	PEM_write_PrivateKey(keyfile_pr, session_pkey, NULL, NULL, 0, NULL, NULL);
	//PEM_read_PUBKEY(keyfile_pu, &session_pkey, NULL, NULL);
	//PEM_read_PrivateKey(keyfile_pr, &session_pkey, NULL, NULL);
	fclose(keyfile_pu);
	fclose(keyfile_pr);

	const char *filepath_msg_1_client = "./edhoc_MitM_server_INBOX/edhoc_sym_msg1_RAW.txt";
	const char *filepath_msg_1_server = "./edhoc_server_INBOX/edhoc_sym_msg1_RAW.txt";
	const char *filepath_msg_2_server = "./edhoc_MitM_client_INBOX/edhoc_sym_msg2_RAW.txt";
	const char *filepath_msg_2_client = "./edhoc_client_INBOX/edhoc_sym_msg2_RAW.txt";
	const char *filepath_msg_3_client = "./edhoc_MitM_server_INBOX/edhoc_sym_msg3_RAW.txt";
	const char *filepath_msg_3_server = "./edhoc_server_INBOX/edhoc_sym_msg3_RAW.txt";

	// Receive message 1
	printf("\nWaiting for MESSAGE 1 as MitM...\n");
	fflush(stdout);
	while (access(filepath_msg_1_client, F_OK) == -1) 
	  {   
	    continue;
	  }   
	printf("\nMESSAGE 1 received on MitM....\n");
	wait4enter();
	  
	cbor_item_t *received_msg_1 = print_and_get_cbor_array(filepath_msg_1_client);
	parse_edhoc_sym_msg_1(received_msg_1, "./edhoc_MitM_server_INBOX/client_PUBKEY.txt");

      	// Send Message 1 to server
	
	gen_msg_1_sym(app_1, app_1_sz, session_pkey, filepath_msg_1_server);

	wait4enter();

	// Receive Message 2

	printf("\nWaiting for MESSAGE 2 on MitM...\n");
	fflush(stdout);
	while (access(filepath_msg_2_server, F_OK) == -1)
	{
		continue;
	}
	printf("\nMESSAGE 2 received on MitM...\n");
	wait4enter();

	cbor_item_t *received_msg_2 = print_and_get_cbor_array(filepath_msg_2_server);
	parse_edhoc_sym_msg_2(received_msg_2, "./edhoc_MitM_client_INBOX/server_PUBKEY.txt", "./input_parameters/MitM_PUBKEY.txt", "./input_parameters/MitM_PrivateKey.txt", "MITM_CLIENT");
	
	// Send message 2

	printf("\n Sending Message 2 on MitM...\n");
	wait4enter();
	size_t *msg_1_client_len = malloc(sizeof(size_t));
	unsigned char *msg_1_client = import_msg(filepath_msg_1_client, msg_1_client_len);
	gen_msg_2_sym(app_2, app_2_sz, session_pkey, filepath_msg_2_client, msg_1_client, *msg_1_client_len, "MITM_SERVER");

	// Receive message 3
	printf("\nWaiting for MESSAGE 3 on MitM...\n");
	fflush(stdout);
	while (access(filepath_msg_3_client, F_OK) == -1) 
	  {   
	    continue;
	  }   
	printf("\nMESSAGE 3 received...\n");
	wait4enter();

	cbor_item_t *received_msg_3 = print_and_get_cbor_array(filepath_msg_3_client);
	FILE *keyfile_puR2 = fopen("./input_parameters/MitM_PUBKEY.txt", "r");
	FILE *keyfile_prR2 = fopen("./input_parameters/MitM_PrivateKey.txt", "r");
	parse_edhoc_sym_msg_3(received_msg_3, "./edhoc_MitM_server_INBOX/edhoc_sym_msg1_RAW.txt", keyfile_puR2, keyfile_prR2, "MITM_SERVER");
	fclose(keyfile_puR2);
	fclose(keyfile_prR2);

	// Send Message 3

	printf("\n Sending Message 3 on MitM...");
	wait4enter();
	size_t *msg_1_server_len = malloc(sizeof(size_t));
	size_t *msg_2_server_len = malloc(sizeof(size_t));
	unsigned char *msg_1_server = import_msg(filepath_msg_1_server, msg_1_server_len);
	unsigned char *msg_2_server = import_msg(filepath_msg_2_server, msg_2_server_len);
	gen_msg_3_sym(app_3, app_3_sz, session_pkey, filepath_msg_3_server, msg_1_server, msg_2_server, *msg_1_server_len, *msg_2_server_len, "MITM_CLIENT");

	return 0;
}


