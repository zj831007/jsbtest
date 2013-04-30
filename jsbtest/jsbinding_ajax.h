//
//  jsbinding_ajax.h
//  jsbtest
//
//  Created by Justin on 13-4-29.
//
//

#ifndef __jsbtest__jsbinding_ajax__
#define __jsbtest__jsbinding_ajax__

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsbinding_ajaxClass_class;
extern JSObject *jsbinding_ajaxClass_prototype;


JSBool jsbinding_ajaxClass_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void jsbinding_ajaxClass_finalize(JSContext *cx, JSObject *obj);
void js_register_jsbinding_ajaxClass(JSContext *cx, JSObject *global);

JSBool jsbinding_ajaxClass_method_open(JSContext *cx, uint32_t argc, jsval *vp);
JSBool jsbinding_ajaxClass_method_send(JSContext *cx, uint32_t argc, jsval *vp);

#endif /* defined(__jsbtest__jsbinding_ajax__) */
