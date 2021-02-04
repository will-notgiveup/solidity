.. index:: ! error

.. _errors:

******
Errors
******

Errors in Solidity provide a convenient and gas-efficient way to explain to the
user why an operation failed. They can be defined inside and outside of contracts.

::

    // SPDX-License-Identifier: GPL-3.0
    pragma solidity >=0.7.0 <0.9.0;

    /// Insufficient balance for transfer. Needed `required` but only
    /// `available` available.
    error InsufficientBalance(uint256 available, uint256 required);

    contract TestToken {
        mapping(address => uint) balance;
        function transfer(address to, uint256 amount) public {
            require(
                amount <= balance[msg.sender],
                InsufficientBalance({
                    available: balance[msg.sender],
                    required: amount
                })
            );
            // ...
        }

Errors cannot be overloaded or overridden but are inherited.
Instances of errors can only be created inside :ref:` ``revert`` and ``require`` calls <assert-and-require>`.
The error creates data that is then passed to the caller with the revert operation
to either return to the off-chain component or catch it in a try/catch statement.
If you do not provide any parameters, the error only needs four bytes of
data and you can use :ref:`NatSpec <natspec>` as above
to further explain the reasons behind the error, which is not stored on chain.

More specifically, an error instance is ABI-encoded in the same way as
a function call to a function of the same name and types would be
and then used as the return data in the ``revert`` opcode.
This means that the data consists of a 4-byte selector and subsequent :ref:`ABI-encoded<abi>` data.
The selector is the first four bytes of the keccak256-hash of the signature of the error type.

Note that since ``require`` is syntactically just a function call,
all its arguments are evaluated before the function itself is called.
This means that if the arguments to the error cause side-effects,
these side-effects take effect even if the require condition is true.

Before Solidity 0.8.2, only a string could be provided in ``revert`` and ``require``
calls which is usually much more expensive to use.

Using a string in place of an error in ``revert`` and ``require`` calls
will produce an error of the built-in type ``Error(string)``. Similarly, a failing
``assert`` or similar conditions will create an error of the built-in type ``Panic(uint256)``.
