# froststrappa

A small bootstrap utility for Crypt Linux, written in C.

froststrappa aims to install a minimal Crypt system onto a mounted filesystem, using Synnical for package management.

## Building

```sh
make
```

## Usage

```sh
./froststrappa /mnt base linux linux-firmware
```

Currently, froststrappa supports basic argument parsing and mountpoint validation. Package installation isn't implemented yet.

## Status

Early development. Not ready for actual system installations.

## License

froststrappa is licensed under the MIT License. See the LICENSE file for details.

