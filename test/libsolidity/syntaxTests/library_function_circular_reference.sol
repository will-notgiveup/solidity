library L {
	function f() internal {
		new C();
	}
}

contract D {
	function f() public {
		L.f();
	}
}
contract C {
	constructor() { new D(); }
}

// ----
// TypeError 7813: (92-95): Circular reference found.
// TypeError 7813: (134-139): Circular reference found.
// TypeError 7813: (39-44): Circular reference found.
