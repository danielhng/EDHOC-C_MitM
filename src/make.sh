CC=/usr/bin/gcc

echo "#Compile main functions"
$CC -fcommon -I./libcbor/  -I./libcbor/libcbor/src/ -I/opt/openssl/include -c -o crypto_functions.o crypto_functions.c
echo "$CC -fcommon -I./libcbor/  -I./libcbor/libcbor/src/ -I/opt/openssl/include -c -o crypto_functions.o crypto_functions.c"
$CC -fcommon -I./libcbor/  -I./libcbor/libcbor/src/ -I/opt/openssl/include -c io_functions.c -o io_functions.o
echo "$CC -fcommon -I./libcbor/  -I./libcbor/libcbor/src/ -I/opt/openssl/include -c io_functions.c -o io_functions.o"
$CC -fcommon -I./libcbor/  -I./libcbor/libcbor/src/ -I/opt/openssl/include -c other_functions.c -o other_functions.o
echo "$CC -fcommon -I./libcbor/  -I./libcbor/libcbor/src/ -I/opt/openssl/include -c other_functions.c -o other_functions.o"
$CC -fcommon -I./libcbor/  -I./libcbor/libcbor/src/ -I/opt/openssl/include -c edhoc_messages.c -o edhoc_messages.o
echo "$CC -fcommon -I./libcbor/  -I./libcbor/libcbor/src/ -I/opt/openssl/include -c edhoc_messages.c -o edhoc_messages.o"
echo "#Compile the client"
$CC -fcommon -I./libcbor/  -I./libcbor/libcbor/src/ -I/opt/openssl/include -c -o edhoc_client.o edhoc_client.c
echo "$CC -fcommon -I./libcbor/  -I./libcbor/libcbor/src/ -I/opt/openssl/include -c -o edhoc_client.o edhoc_client.c"
echo "#Compile the server"
$CC -fcommon -I./libcbor/  -I./libcbor/libcbor/src/ -I/opt/openssl/include -c -o edhoc_server.o edhoc_server.c
echo "#Compile the MitM"
echo "$CC -fcommon -I./libcbor/  -I./libcbor/libcbor/src/ -I/opt/openssl/include -c -o edhoc_server.o edhoc_server.c"
$CC -fcommon -I./libcbor/  -I./libcbor/libcbor/src/ -I/opt/openssl/include -c -o edhoc_MitM.o edhoc_MitM.c
echo "$CC -fcommon -I./libcbor/  -I./libcbor/libcbor/src/ -I/opt/openssl/include -c -o edhoc_MitM.o edhoc_MitM.c"
echo "#Link client"
$CC crypto_functions.o edhoc_client.o edhoc_messages.o io_functions.o other_functions.o -lcrypto -lb64 -L/opt/openssl/lib -L./libcbor/src/ ./libcbor/src/libcbor.a -o edhoc-client
echo "$CC crypto_functions.o edhoc_client.o edhoc_messages.o io_functions.o other_functions.o -lcrypto -lb64 -L/opt/openssl/lib -L./libcbor/src/ ./libcbor/src/libcbor.a -o edhoc-client"
echo "#Link server"
$CC crypto_functions.o edhoc_server.o edhoc_messages.o io_functions.o other_functions.o -lcrypto -lb64 -L/opt/openssl/lib -L./libcbor/src/ ./libcbor/src/libcbor.a -o edhoc-server
echo "$CC crypto_functions.o edhoc_server.o edhoc_messages.o io_functions.o other_functions.o -lcrypto -lb64 -L/opt/openssl/lib -L./libcbor/src/ ./libcbor/src/libcbor.a -o edhoc-server"
echo "#Link MitM"
$CC crypto_functions.o edhoc_MitM.o edhoc_messages.o io_functions.o other_functions.o -lcrypto -lb64 -L/opt/openssl/lib -L./libcbor/src/ ./libcbor/src/libcbor.a -o edhoc-MitM
echo "$CC crypto_functions.o edhoc_MitM.o edhoc_messages.o io_functions.o other_functions.o -lcrypto -lb64 -L/opt/openssl/lib -L./libcbor/src/ ./libcbor/src/libcbor.a -o edhoc-MitM"
