# quickjs-crypto
This package aims to provide simple, minimal and essential crypto functions for QuickJS.  
Currently, it can:
- Creating WebSocket `server`
- Creating WebSocket `client`
- `fetch`

## Usage
Requirements:
- `clang`
- `openssl`

To use `quickjs-crypto` in your QuickJS project, run following commands:
```bash
cd your_project_dir
git clone ...
cd quickjs-crypto
make
```

In your JS script:
```javascript
import * as crypto from "./quickjs-crypto/qjs-crypto.so"
```
