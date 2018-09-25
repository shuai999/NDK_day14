#include <jni.h>
#include <string>
#include <malloc.h>
#include "com_novate_ndk_day14_Parcel.h"
extern "C"
JNIEXPORT jstring

JNICALL
Java_com_novate_ndk_day14_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

// 定义：结构体 和对象Parcel.cpp
class Parcel{

    // 如果不赋值，默认
    int mDataPos = 0 ;
    // 共享内存首地址：char*是一个字节，一个字节一个位置
    char *mData ;

    public:
        Parcel(){
            // 动态开辟 1024字节 大小
            mData = (char*)malloc(1024);
        }

        void writeInt(jint value){
            // 当前数据 + 指针偏移量
            // 第一次写到0位置；第二次写到4位置
            *reinterpret_cast<int*>(mData+mDataPos) = value;
            mDataPos += sizeof(int);
        }

        void setDataPosition(jint position){
             mDataPos = position;
        }

        jint readInt(){
             int result =  *reinterpret_cast<int*>(mData+mDataPos);
             mDataPos += sizeof(int);
             return result ;
        }
}


// 创建parcel对象，并且返回首地址
JNIEXPORT jlong JNICALL Java_com_novate_ndk_day14_Parcel_nativeCreate
  (JNIEnv *, jobject){
        // 创建 parcel对象
        Parcel *parcel = new Parcel();
        // 返回首地址
        return (jlong)parcel;
  }

// 给共享内存写数据
JNIEXPORT void JNICALL Java_com_novate_ndk_day14_Parcel_nativeWriteInt
        (JNIEnv *, jobject,jlong nativePtr,jint value){
       // 这里会把 上边的首地址传递下来，就是这里的 nativePtr
       Parcel* parcel = reinterpret_cast<Parcel*>(nativePtr);
       parcel.writeInt(value);
  }

JNIEXPORT void JNICALL Java_com_novate_ndk_day14_Parcel_nativeSetDataPosition
       (JNIEnv *, jobject,jlong nativePtr,jint value){
           Parcel *parcel = (Parcel *) nativePtr;
           parcel->setDataPosition(value);
   }

JNIEXPORT jint JNICALL Java_com_novate_ndk_day14_Parcel_nativeReadInt
        (JNIEnv *, jobject,jlong nativePtr){
            Parcel *parcel = (Parcel *) nativePtr;
            return parcel->readInt();
}