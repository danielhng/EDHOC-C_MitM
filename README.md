[![arXiv](https://img.shields.io/badge/arXiv-2510.10574-b31b1b.svg)](https://arxiv.org/abs/2510.10574)
[![License](https://img.shields.io/badge/License-BSD_3--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)

# Man-in-the-Middle Proof-of-Concept via Krontiris’ Ephemeral Diffie-Hellman Over COSE (EDHOC) in C

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
$ cd EDHOC-C_MitM/src
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

### Virtual machines to test the code

Virtual machines running the simulator and the attack code are <a href="https://drive.google.com/drive/folders/12vVhr9tcIHX-GdT9XbeFBY6vvSsRyx5c">available online</a>.

## References

If you use the code for research purposes, please cite:

Daniel Hennig and Joaquin Garcia-Alfaro. Man-in-the-Middle Proof-of-Concept via Krontiris' Ephemeral Diffie-Hellman Over COSE (EDHOC) in C, 2025, https://doi.org/10.48550/arXiv.2510.10574.

```
@techreport{Hennig2025MitMTechReport,
  title={{Man-in-the-Middle Proof-of-Concept via Krontiris' Ephemeral Diffie-Hellman Over COSE (EDHOC) in C}}, 
  author={Hennig, Daniel and Garcia-Alfaro, Joaquin},
  year={2025},
  institution = {SAMOVAR, Télécom SudParis, Institut Polytechnique de Paris, 91120 Palaiseau, France},
  eprint={2510.10574},
  archivePrefix={arXiv},
  primaryClass={cs.CR},
  url={https://arxiv.org/abs/2510.10574}, 
}
```
