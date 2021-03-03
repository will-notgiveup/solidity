pragma experimental SMTChecker;

contract C
{
	function f(string memory s1, string memory s2) public pure {
		assert(bytes(s1).length == bytes(s2).length);
	}
}
// ----
// Warning 6328: (110-154): CHC: Assertion violation happens here.\nCounterexample:\n\ns1 = [9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 14, 9, 9, 9, 9, 9, 9, 9, 9, 9, 26, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9]\ns2 = [18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 15, 18, 18, 18, 18, 18, 20, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18]\n\nTransaction trace:\nC.constructor()\nC.f([9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 14, 9, 9, 9, 9, 9, 9, 9, 9, 9, 26, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9], [18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 15, 18, 18, 18, 18, 18, 20, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18])
