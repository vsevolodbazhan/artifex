# Artifex

The C++ program the renders animation from JSON files.

## Requirements

Requires [SFML](https://www.sfml-dev.org) and [json](https://github.com/nlohmann/json) to be installed.

## Building

Run `make build` to create a binary.

## Running

```bash
./<created_binary> <path_to_json_file> <time_between_frames_in_ms>
```

For example, the following command will render an animation with
100 ms pause between frames:

```bash
./artifex file1_500_500.json 100
```
