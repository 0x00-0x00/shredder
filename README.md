# Shredder - Secure shredding tool ![version-badge](https://img.shields.io/badge/version-1.23-blue.svg) ![license-badge](https://img.shields.io/badge/license-MIT-green.svg)
'Shredder' is a new utility to erase files safely with Linux boxes.
-----

## Instructions
To use this program, you need to compile it and install it. There are no other requirements other than Linux kernel, make and C compiler.

### Compiling and installing

To compile the program source code, type at terminal:
```bash
make
```

Then, with administrative, install it typing:
```bash
sudo make install
```
or as root:
```bash
make install
```

### Usage
To shred a file named 'secret_file.key' at your current directory, type at terminal:
```bash
shredder secret_file.key
```

To shred and delete 'secret_phrase.txt' at your current directory, type at terminal:
```bash
shedder secret_phrase.txt -u
```

