contract C {
    bytes s;
    function f(bytes calldata c) public {
        bytes memory a;
        bytes16 b;
        uint8[] memory num;
        bytes memory d = bytes.concat(a, b, c, num, s, "abc");
    }
}
// ----
// TypeError 8015: (186-189): Invalid type for argument in the bytes.concat function call. bytes or fixed bytes type is required, but uint8[] provided.
