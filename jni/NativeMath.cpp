#include <jni.h>
#include <stdio.h>
#include "com_example_androidjniproject_MainActivity.h"


extern "C" jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv* env = NULL;
    jint result = -1;

    if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        return result;
    }

    return JNI_VERSION_1_4;
}


JNIEXPORT jstring JNICALL Java_com_example_androidjniproject_MainActivity_helloString
  (JNIEnv *env, jobject obj, jstring str)
{
	const char* toWhat = env->GetStringUTFChars(str, JNI_FALSE);
	char szData[80];

	sprintf(szData, "Hello %s!", toWhat);

	env->ReleaseStringUTFChars(str, toWhat);

	return env->NewStringUTF(szData);
}

JNIEXPORT void JNICALL Java_com_example_androidjniproject_MainActivity_showHelloString
  (JNIEnv *env, jobject obj, jobject textView, jstring str)
{
	const char* toWhat = env->GetStringUTFChars(str, JNI_FALSE);

	char szData[80];

	sprintf(szData, "Hello %s!", toWhat);

	jstring helloString = env->NewStringUTF(szData);

	jclass textViewClass = env->FindClass("android/widget/TextView");
	jmethodID setText = env->GetMethodID(textViewClass, "setText", "(Ljava/lang/CharSequence;)V");

	env->CallVoidMethod(textView, setText, helloString);

	env->ReleaseStringUTFChars(str, toWhat);
	env->DeleteLocalRef(helloString);
}

JNIEXPORT void JNICALL Java_com_example_androidjniproject_MainActivity_callDialog
  (JNIEnv *env, jobject obj)
{
	jclass myClass = env->FindClass("com/example/androidjniproject/MainActivity");
	jmethodID methodId = env->GetStaticMethodID(myClass, "showMyDialog", "(Ljava/lang/String;)V");

	jstring jstrTitle = env->NewStringUTF("I'am C++!");

	env->CallStaticVoidMethod(myClass, methodId, jstrTitle);

	env->DeleteLocalRef(jstrTitle);
}
