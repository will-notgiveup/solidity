# Solidity LSP server implementation

This library implements a subset LSP proposal version 3.16, that can be found at:

https://microsoft.github.io/language-server-protocol/specifications/specification-3-16/

### The life of a message

1. The transport layer parses HTTP-alike JSON-RPC messages from stdin (or via an HTTP API).
2. Those JSON-RPC messages are then translated into high-level LSP message objects.
3. The `Server` is then invoking the appropriate message handler that must have been overridden
   in the actual language server implementation.
4. The message handler may handle this error with not responding at all (such as for
   notifications), or with an actual reply being constructed via a high-level LSP response message.
5. This high-level LSP response message is then transformed by the `OutputGenerator` into
   a JSON message, which in turn ...
6. will then be transmitted by the transport layer to the client (such as via stdout or HTTP itself).

