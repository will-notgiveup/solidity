contract A {
    function f() public pure {
        type(B).runtimeCode;
    }
}
contract B {
    function f() public pure {
        type(A).runtimeCode;
    }
}
// ----
// TypeError 7813: (133-152): Circular reference found.
// TypeError 7813: (52-71): Circular reference found.
