# Man-in-the-Middle Proof-of-Concept on Krontiris’ Ephemeral Diffie-Hellman Over COSE (EDHOC) in C

EDHOC specification: [EDHOC](https://datatracker.ietf.org/doc/draft-selander-ace-cose-ecdhe/)

EDHOC is a key exchange protocol designed to run over CoAP or OSCOAP. The communicating parties run an Elliptic Curve Diffie-Hellman (ECDH) key exchange protocol with ephemeral keys, from which a shared secret is derived. EDHOC messages are encoded with the Consise Binary Object Representation (CBOR) format which is based on the Javascript Object Notation (JSON) data model and the CBOR Object Signing and Encryption (COSE) which specifies how to process encryption, signatures and Message Authentication Code (MAC) operations, and how to encode keys using JSON. 

## Supported authentication
EDHOC supports authentication using pre-shared keys (PSK), raw public keys (RPK) and certificates (Cert).

## Assumptions
The attack scenario assumes compromised long-term authentication credentials of the parties or key escrow techniques (e.g., known pre-shared cryptographic keys held in trust, due to legally mandated situations). The same attack assumption would break any other centralized PKI-based authentication protocol. 

## Attack scope
The attack allows a good insight on what is possible in a context of poor authentication. It is supposed that the attacker has had access to one of the previous authentication methods informations to perform the attack.

### Dependencies
OpenSSL version 1.1.0 (includes X25519 elliptic curve) or newer

libb64 (Base64 Encoding/Decoding Routines)

libcbor (CBOR format implementation for C)

### Usage
Open a new terminal and run the server
```sh
$ cd EDHOC-C/src
$ make clean && make
$ ./edhoc-server
```
Open a new terminal in the same directory and run attacker
```
$ ./edhoc-MitM
```
Open a third terminal in the same directory and run the client
```
$ ./edhoc-client
```

### See the code in action, under the [CoopeRIS](https://github.com/michele-segata/cooperis/) simulator

[![Code in action](https://img.youtube.com/vi/zyN18Rd1N3Y/0.jpg)](https://www.youtube.com/watch?v=zyN18Rd1N3Y)

[![Code in action](https://img.youtube.com/vi/h1KbDFak0xQ/0.jpg)](https://www.youtube.com/watch?v=h1KbDFak0xQ)
