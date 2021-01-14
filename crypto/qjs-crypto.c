#include "qjs-crypto.h"
#include <openssl/rand.h>

#ifdef JS_SHARED_LIBRARY
#define JS_INIT_MODULE js_init_module
#else
#define JS_INIT_MODULE js_init_module_qjscrypto
#endif

 __attribute__ ((visibility ("default")))
JSModuleDef *JS_INIT_MODULE(JSContext *ctx, const char *module_name) {
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, js_qjscrypto_init);
    if (!m)
        return NULL;
    JS_AddModuleExportList(ctx, m, qjscrypto_funcs, countof(qjscrypto_funcs));

    return m;
}

static JSValue qjscrypto_get_random_values(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    size_t size;
    uint8_t *buf;

	buf = JS_GetArrayBuffer(ctx, &size, argv[0]);
	if (!buf)
        return JS_EXCEPTION;
	
	// cryptographically strong pseudo-random bytes
	RAND_bytes(buf, size);
    
    return JS_DupValue(ctx, argv[0]);
}
