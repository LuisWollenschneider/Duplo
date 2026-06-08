#!/bin/bash

@test "simple_logger.swift" {
    run ./build/duplo -ml 2 tests/Simple_Swift/simple_logger.lst out.txt
    [ "$status" -eq 1 ]
    [ "${lines[0]}" = "Loading and hashing files ... 2 done." ]
    [ "${lines[1]}" = "tests/Simple_Swift/simple_logger.swift found: 1 block(s)" ]
}

@test "simple_logger.swift out.txt" {
    run ./build/duplo -ml 2 tests/Simple_Swift/simple_logger.lst -
    [ "$status" -eq 1 ]
    run diff <(cat tests/Simple_Swift/expected.log) <(./build/duplo -ml 2 tests/Simple_Swift/simple_logger.lst -)
    [ "$status" -eq 0 ]
}

@test "simple_logger.swift ignores imports and compiler directives with -ip" {
    run diff <(cat tests/Simple_Swift/expected-ip.log) <(./build/duplo -ml 2 -ip tests/Simple_Swift/simple_logger.lst -)
    [ "$status" -eq 0 ]
}
