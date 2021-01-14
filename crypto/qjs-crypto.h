#include <quickjs/quickjs.h>

#define countof(x) (sizeof(x) / sizeof((x)[0]))

static JSValue qjscrypto_get_random_values(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv);

static const JSCFunctionListEntry qjscrypto_funcs[] = {
	JS_CFUNC_DEF("getRandomValues", 1, qjscrypto_get_random_values),
};

static int js_qjscrypto_init(JSContext *ctx, JSModuleDef *m)
{
	return JS_SetModuleExportList(ctx, m, qjscrypto_funcs, countof(qjscrypto_funcs));
}

