function l() {
    s();
}
function s() {
	new C();
}
contract D {
	function f() public {
		l();
	}
}
contract C {
	constructor() { new D(); }
}
// ----
// TypeError 7813: (131-136): Circular reference found.
// TypeError 7813: (42-47): Circular reference found.
