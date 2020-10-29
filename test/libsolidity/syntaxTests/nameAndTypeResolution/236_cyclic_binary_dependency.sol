contract A { function f() public { new B(); } }
contract B { function f() public { new C(); } }
contract C { function f() public { new A(); } }
// ----
// TypeError 7813: (131-136): Circular reference found.
// TypeError 7813: (35-40): Circular reference found.
// TypeError 7813: (83-88): Circular reference found.
