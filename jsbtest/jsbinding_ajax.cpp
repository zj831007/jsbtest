//
//  jsbinding_ajax.cpp
//  jsbtest
//
//  Created by Justin on 13-4-29.
//
//

#include "jsbinding_ajax.h"
#include "cocos2d_specifics.hpp"
#include "XMLHttpRequest.h"

#pragma mark --bind properties
static JSBool jsbinding_ajaxClass_prop_get_status(JSContext *cx, JSHandleObject obj, JSHandleId id, JSMutableHandleValue vp){
    
    XMLHttpRequest *cobj = (XMLHttpRequest *)JS_GetPrivate(obj);
    if (cobj) {
        int status = cobj->getStatus();
        vp.set(INT_TO_JSVAL(status));
        return JS_TRUE;
    }
    JS_ReportError(cx, "Invalid getter call for property status"); 
	return JS_FALSE; 
}
static JSBool jsbinding_ajaxClass_prop_get_readyState(JSContext *cx, JSHandleObject obj, JSHandleId id, JSMutableHandleValue vp){
    
    XMLHttpRequest *cobj = (XMLHttpRequest *)JS_GetPrivate(obj);
    if (cobj) {
        int readyStatus = cobj->getReadyState();
        vp.set(INT_TO_JSVAL(readyStatus));
        return JS_TRUE;
    }
    JS_ReportError(cx, "Invalid getter call for property readyStatus");
	return JS_FALSE;
}

static JSBool jsbinding_ajaxClass_prop_get_responseText(JSContext *cx, JSHandleObject obj, JSHandleId id, JSMutableHandleValue vp){
    
    XMLHttpRequest *cobj = (XMLHttpRequest *)JS_GetPrivate(obj);
    if (cobj) {
        std::string responseText = cobj->getResponseText();
        
        JSString* str = JS_NewStringCopyZ(cx, responseText.c_str());
        if (str) {
            vp.set(STRING_TO_JSVAL(str));
            return JS_TRUE;
        } else {
            vp.set(JSVAL_NULL);
            JS_ReportError(cx, "Error trying to create JSString from data");
            return JS_FALSE;
        }
    }
    vp.set(JSVAL_NULL);
    JS_ReportError(cx, "Invalid getter call for property responseText");
	return JS_FALSE;
}


#pragma mark --bind method

JSBool jsbinding_ajaxClass_method_open(JSContext *cx, uint32_t argc, jsval *vp){
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
//	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
//	XMLHttpRequest* cobj = (XMLHttpRequest *)(proxy ? proxy->ptr : NULL);
    
    XMLHttpRequest *cobj = (XMLHttpRequest *)JS_GetPrivate(obj);
    
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    
    
	if (argc == 3) {
        std::string arg0;
        std::string arg1;
        
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
		cobj->open(arg0, arg1, true);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 3);
    JS_SET_RVAL(cx, vp, JSVAL_FALSE);
	return JS_FALSE;
}
JSBool jsbinding_ajaxClass_method_send(JSContext *cx, uint32_t argc, jsval *vp){
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
//	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
//	XMLHttpRequest* cobj = (XMLHttpRequest *)(proxy ? proxy->ptr : NULL);
    
    XMLHttpRequest *cobj = (XMLHttpRequest *)JS_GetPrivate(obj);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    
    
	if (argc == 1) {
        std::string arg0;
        
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        
		cobj->send(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    JS_SET_RVAL(cx, vp, JSVAL_FALSE);
	return JS_FALSE;
}


#pragma mark -- bind class

JSClass  *jsbinding_ajaxClass_class;
JSObject *jsbinding_ajaxClass_prototype;

JSBool jsbinding_ajaxClass_constructor(JSContext *cx, uint32_t argc, jsval *vp){
//  jsval *argv = JS_ARGV(cx, vp);
//	JSBool ok = JS_TRUE;
    
	JSObject *obj = NULL;
	XMLHttpRequest* cobj = NULL;
    
    cobj = new XMLHttpRequest();
    
    TypeTest<XMLHttpRequest> t;
    js_type_class_t *typeClass;
    uint32_t typeId = t.s_id();
    HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
    assert(typeClass);
    obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    
//    js_proxy_t *proxy;
//    JS_NEW_PROXY(proxy, cobj, obj);
//    JS_AddNamedObjectRoot(cx, &proxy->obj, "XMLHttpRequest");
    
    if (cobj) {
        JS_SetPrivate(obj, cobj);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
void jsbinding_ajaxClass_finalize(JSFreeOp *fop, JSObject *obj){
    
}
void js_register_jsbinding_ajaxClass(JSContext *cx, JSObject *global){
    jsbinding_ajaxClass_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsbinding_ajaxClass_class->name = "XMLHttpRequest";
	jsbinding_ajaxClass_class->addProperty = JS_PropertyStub;
	jsbinding_ajaxClass_class->delProperty = JS_PropertyStub;
	jsbinding_ajaxClass_class->getProperty = JS_PropertyStub;
	jsbinding_ajaxClass_class->setProperty = JS_StrictPropertyStub;
	jsbinding_ajaxClass_class->enumerate = JS_EnumerateStub;
	jsbinding_ajaxClass_class->resolve = JS_ResolveStub;
	jsbinding_ajaxClass_class->convert = JS_ConvertStub;
	jsbinding_ajaxClass_class->finalize = jsbinding_ajaxClass_finalize;
	jsbinding_ajaxClass_class->flags = JSCLASS_HAS_PRIVATE;
    
	static JSPropertySpec properties[] = {
		{"status", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, JSOP_WRAPPER(jsbinding_ajaxClass_prop_get_status), JSOP_NULLWRAPPER},
        {"readyState", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, JSOP_WRAPPER(jsbinding_ajaxClass_prop_get_readyState), JSOP_NULLWRAPPER},
        {"responseText", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, JSOP_WRAPPER(jsbinding_ajaxClass_prop_get_responseText), JSOP_NULLWRAPPER},
        {0, 0, 0, 0, 0}
	};
    
	static JSFunctionSpec funcs[] = {
		JS_FN("open", jsbinding_ajaxClass_method_open, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("send", jsbinding_ajaxClass_method_send, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};
    
    
	jsbinding_ajaxClass_prototype = JS_InitClass(
                                                   cx, global,
                                                   NULL, // parent proto
                                                   jsbinding_ajaxClass_class,
                                                   jsbinding_ajaxClass_constructor, 0, // constructor
                                                   properties,
                                                   funcs,
                                                   NULL, // no static properties
                                                   NULL); //no static method
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "XMLHttpRequest", JSPROP_ENUMERATE | JSPROP_READONLY, &found);
    
	// add the proto and JSClass to the type->js info hash table
	TypeTest<XMLHttpRequest> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsbinding_ajaxClass_class;
		p->proto = jsbinding_ajaxClass_prototype;
		p->parentProto = NULL;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}