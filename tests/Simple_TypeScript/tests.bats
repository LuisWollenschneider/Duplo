#!/bin/bash

@test "simple_logger.ts" {
    run ./build/duplo -ml 2 tests/Simple_TypeScript/simple_logger.lst out.txt
    [ "$status" -eq 1 ]
    [ "${lines[0]}" = "Loading and hashing files ... 2 done." ]
    [ "${lines[1]}" = "tests/Simple_TypeScript/simple_logger.ts found: 3 block(s)" ]
}

@test "simple_logger.ts out.txt" {
    run ./build/duplo -ml 2 tests/Simple_TypeScript/simple_logger.lst -
    [ "$status" -eq 1 ]
    run diff <(cat tests/Simple_TypeScript/expected.log) <(./build/duplo -ml 2 tests/Simple_TypeScript/simple_logger.lst -)
    [ "$status" -eq 0 ]
    printf 'Lines:\n'
    printf 'lines %s\n' "${lines[@]}" >&2
    printf 'output %s\n' "${output[@]}" >&2
}

@test "simple_logger.ts ignores imports and exports with -ip" {
    run diff <(cat tests/Simple_TypeScript/expected-ip.log) <(./build/duplo -ml 2 -ip tests/Simple_TypeScript/simple_logger.lst -)
    [ "$status" -eq 0 ]
}

@test "typescript extensions use TypeScript filters" {
    run ./build/duplo -ml 100 -ip tests/Simple_TypeScript/preprocessor.lst -
    [ "$status" -eq 0 ]
    [[ "$output" == *"  Number of files: 4"* ]]
    [[ "$output" == *"  Ignore preprocessor directives: 1"* ]]
    [[ "$output" == *"  Lines of code: 12"* ]]
    [[ "$output" == *"  Total 0 duplicate block(s) found."* ]]
}
