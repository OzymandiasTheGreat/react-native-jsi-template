#include <jni.h>
#include <jsi/jsi.h>
#include "JSITemplateHostObject.h"

using namespace facebook;

void install(jsi::Runtime& runtime) {
    auto hostObject = std::make_shared<ozymandias::JSITemplateHostObject>();
    auto object = jsi::Object::createFromHostObject(runtime, hostObject);
    runtime.global().setProperty(runtime, "__JSITemplateProxy", std::move(object));
}

extern "C"
JNIEXPORT void JNICALL
Java_org_example_jsitemplate_JSITemplateModule_nativeInstall(JNIEnv *env, jobject clazz, jlong jsiPtr) {
    auto runtime = reinterpret_cast<jsi::Runtime*>(jsiPtr);
    if (runtime) {
        install(*runtime);
    }
    // if runtime was nullptr, JSITemplate will not be installed. This should only happen while Remote Debugging (Chrome), but will be weird either way.
}
