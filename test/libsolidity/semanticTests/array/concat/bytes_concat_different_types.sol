contract C {
    bytes s = "bcdef";

    function f(bytes memory a) public returns (bytes memory) {
        return bytes.concat(a, "bcdef");
    }
    function g(bytes calldata a) public returns (bytes memory) {
        return bytes.concat(a, "bcdef");
    }
    function h(bytes calldata a) public returns (bytes memory) {
        return bytes.concat(a, s);
    }
}
// ====
// compileViaYul: true
// ----
// f(bytes): 0x20, 32, "abcdabcdabcdabcdabcdabcdabcdabcd" -> 0x20, 37, "abcdabcdabcdabcdabcdabcdabcdabcd", "bcdef"
// g(bytes): 0x20, 32, "abcdabcdabcdabcdabcdabcdabcdabcd" -> 0x20, 37, "abcdabcdabcdabcdabcdabcdabcdabcd", "bcdef"
// h(bytes): 0x20, 32, "abcdabcdabcdabcdabcdabcdabcdabcd" -> 0x20, 37, "abcdabcdabcdabcdabcdabcdabcdabcd", "bcdef"
