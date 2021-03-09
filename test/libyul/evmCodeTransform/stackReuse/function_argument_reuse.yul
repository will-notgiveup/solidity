{
    function f(a, b, c) -> x { pop(address()) sstore(a, c) pop(callvalue()) x := b }
}
// ====
// stackOptimization: true
// ----
// PUSH1 0x17
// JUMP
// JUMPDEST
// ADDRESS
// POP
// DUP3
// DUP2
// SSTORE
// POP
// CALLVALUE
// POP
// PUSH1 0x0
// SWAP2
// POP
// DUP1
// SWAP2
// POP
// POP
// JUMPDEST
// SWAP1
// JUMP
// JUMPDEST
