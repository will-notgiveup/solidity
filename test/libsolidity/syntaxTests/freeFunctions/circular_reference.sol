contract D {
	function f() public {
		l();
	}
}
contract C {
	constructor() { new D(); }
}
function l() {
	s();
}
function s() {
	new C();
}
// ----
// TypeError 7813: (78-83): Circular reference found.
// TypeError 7813: (130-135): Circular reference found.
