# Shredder - Secure shredding tool ![version-badge](https://img.shields.io/badge/version-1.23-blue.svg) ![license-badge](https://img.shields.io/badge/license-MIT-green.svg)
'Shredder' is a new utility to erase files safely of your Linux boxes.
-----

## Instructions
To use this program, you need to compile it and install it. There are no other requirements other than Linux kernel, make and C compiler.

### Compiling and installing

To compile the program source code, type at terminal:
```bash
make
```

Then, install it typing:
```bash
make install
```

### Usage
To delete a file named 'secret_file.key' at your current directory, type at terminal:
```bash
shredder secret_file.key
```

