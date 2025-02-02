# MachoCat - The Ultimate OTP Messaging System

## Overview

MachoCat is a highly secure one-time pad (OTP) encryption system designed for private communication. MachoCat ensures that even with quantum computing advancements, messages remain completely unbreakable—so long as the keys remain secret.

With MachoCat, two parties can securely sync large amounts of cryptographic keys via physical means (e.g., USB sticks, serial connection) and then communicate online using a rolling OTP system, ensuring forward secrecy and resistance against statistical analysis attacks.

## How It Works

- **Key Preloading:** Users generate and store large pools of random OTP keys using the built-in keygen.
- **Message Encryption:** Each message is encrypted with a unique OTP key.
- **Salt Chaining:** Each encrypted message contains a SHA-256-derived salt that is required for decrypting subsequent messages. This ensures that even if an attacker steals the key store, they cannot retroactively decrypt future messages unless they also intercept the first message.
- **Self-Destructing Keys and messages:** Used keys are messages are securely wiped to prevent reuse or forensic recovery.
- **Diffie-Hellman Integration (Planned):** In future versions, MachoCat will support Diffie-Hellman key exchange over serial UART for automated secure key negotiation.

## Installation

```sh
git clone https://github.com/TheJostler/machocat.git
cd machocat
make
```

## Usage

### Generate Keys

```sh
./machocat keygen mykeyfile 4096  # Generates a 4096-byte keyfile
```

### Encrypt a Message

```sh
./machocat fxor message.txt mykeyfile encrypted.bin
```

### Decrypt a Message

```sh
./machocat fxor encrypted.bin mykeyfile message.txt
```

## Security Model

MachoCat follows a strict OTP encryption scheme:

- **Quantum-Safe:** True OTP encryption cannot be broken, even by quantum computers.
- **Statistical Randomness:** Salt chaining ensures keys appear statistically random.
- **Ephemeral Keys:** Once used, keys are erased, eliminating the risk of key reuse.
- **Limited Exposure:** Keys must be pre-shared physically, preventing MITM attacks during exchange.

## Future Plans

- Implement Diffie-Hellman key exchange over UART for ad-hoc secure key sharing.
- Enhance automated key management for seamless operation.
- Introduce error correction for noisy channels in UART communications.
- Network Chat Implementation (Planned): MachoCat will include a network chat feature that allows users to communicate securely over the internet using pre-shared OTP keys.

## Contributions

We welcome contributions! Feel free to fork the repo, submit pull requests, or suggest improvements.

## License

MachoCat is released under the MIT License.

---

*Because real security doesn’t mess around.* 🦾🐱

