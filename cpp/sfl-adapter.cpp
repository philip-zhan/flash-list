#include <jni.h>

#include <fbjni/fbjni.h>
#include <react/fabric/JFabricUIManager.h>
#include <jsi/jsi.h>
#include <ReactCommon/CallInvokerHolder.h>
#include <jsi/JSIDynamic.h>

#include <react/fabric/Binding.h>
#include <react/renderer/scheduler/Scheduler.h>

using namespace facebook; // NOLINT

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_shopify_reactnative_flash_1list_FlashListModule_nativeInstall(JNIEnv *env, jobject thiz,
                                                                       jlong jsi_runtime_ref,
                                                                       jobject js_call_invoker_holder) {
    auto jsiRuntime{ reinterpret_cast<jsi::Runtime*>(jsi_runtime_ref) };
    auto jsCallInvoker{ jni::alias_ref<react::CallInvokerHolder::javaobject>{ reinterpret_cast<react::CallInvokerHolder::javaobject>(js_call_invoker_holder) }->cthis()->getCallInvoker() };

    auto onLayoutCallback = jsi::Function::createFromHostFunction(
            *jsiRuntime,
            jsi::PropNameID::forUtf8(*jsiRuntime, "onLayoutCallback"),
            1,
            [=](jsi::Runtime &runtime,
                const jsi::Value &thisArg,
                const jsi::Value *args,
                size_t count) -> jsi::Value {
                auto cb = args[0].asObject(*jsiRuntime).asFunction(*jsiRuntime);
                auto viewId = args[1].asString(*jsiRuntime);

                jsi::Object callbackRegistry = jsi::Object(*jsiRuntime);
                callbackRegistry.setProperty(*jsiRuntime, viewId, std::move(cb));

                jsiRuntime->global().setProperty(*jsiRuntime, "FLCallbackRegistry", std::move(cb));
                return jsi::Value();
            });


    jsi::Object flashListModule = jsi::Object(*jsiRuntime);
    flashListModule.setProperty(*jsiRuntime, "onLayoutCallback", std::move(onLayoutCallback));
    jsiRuntime->global().setProperty(*jsiRuntime, "FlashListModule", flashListModule);

    return true;
}
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_shopify_reactnative_flash_1list_FlashListModule_nativeCallJSFunction(JNIEnv *env,
                                                                              jobject thiz,
                                                                              jlong jsi_runtime_ref,
                                                                              jobject js_call_invoker_holder,
                                                                              jstring view_id) {
    auto jsiRuntime{ reinterpret_cast<jsi::Runtime*>(jsi_runtime_ref) };
    auto jsCallInvoker{ jni::alias_ref<react::CallInvokerHolder::javaobject>{ reinterpret_cast<react::CallInvokerHolder::javaobject>(js_call_invoker_holder) }->cthis()->getCallInvoker() };

    jsiRuntime->global().getPropertyAsFunction(*jsiRuntime, "FLCallbackRegistry").call(*jsiRuntime);
    return false;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_shopify_reactnative_flash_1list_FlashListModule_initFabric(JNIEnv *env, jobject thiz,
                                                                    jobject fabric_uimanager) {
    auto fabricUIManager { jni::alias_ref<react::JFabricUIManager::javaobject>{ reinterpret_cast<react::JFabricUIManager::javaobject>(fabric_uimanager) }};
    auto uiManager =
            fabricUIManager->getBinding()->getScheduler()->getUIManager();
}